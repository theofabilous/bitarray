#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/motion_vector.h"
#include "libswscale/swscale.h"
#include "libavutil/imgutils.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavcodec/bsf.h"
// #include "libavutil/internal.h"
#include "libavutil/pixdesc.h"
#include "libavutil/opt.h"

// #include "/Users/theofabilous/Documents/Coding Resources/ffmpeg/libavcodec/bsf_internal.h"

#include <SDL.h>
#include <SDL_thread.h>

#ifdef __MINGW32__
#undef main /* Prevents SDL from overriding main() */
#endif

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <curses.h>

#include "bitarray.h"
#include "bitbuffer.h"


#define USE_ENCODER 0
#define USE_CURSES 0
#define EXPORT_MVS 0

#define AV_LOG(pred, msg, lbl) \
do { \
	if(pred) \
	{ \
		av_log(NULL, AV_LOG_ERROR, msg); \
		goto lbl; \
	} \
} while(false)  

#define INIT_CURSES() \
	initscr(); \
	nodelay(stdscr, true); \
	cbreak(); \
	noecho(); \
	clear();

#define FINISH_CURSES() \
	refresh(); \
	nodelay(stdscr, false); \
	nocbreak(); \
	echo(); \
	endwin(); \
	clear()

IMPORT_BITARRAY_MODULE_AS(Bits);


typedef struct MpegFrame MpegFrame;
struct MpegFrame
{
    uint8_t* dataStart;
    size_t frameSize;
};

typedef struct MpegVideo MpegVideo;
struct MpegVideo
{
	uint32_t w, h, time_delay;
    size_t fileSize;
    size_t numFrames;
	size_t moviSize;
    uint8_t* fileData;
	AVPacket* pkt;
    MpegFrame** frames;
};

void
free_MpegVideo_frames(MpegVideo* mv)
{
	MpegFrame* curr;
	while(mv->numFrames)
	{
		curr = mv->frames[--mv->numFrames];
		free(curr);
	}
	free(mv->frames);
}

void
mpeg_parse_packet(MpegVideo* vid, uint32_t frame_index)
{
	if(vid->pkt == NULL)
		return;
	MpegFrame* frame = vid->frames[frame_index];
	vid->pkt->data = frame->dataStart;
	vid->pkt->size = frame->frameSize;
}

MpegFrame*
parse_frame(BitBuffer* buff, bool *audio)
{
	char fourcc[5];
	size_t skip_size;
	bitbuffer_read_fourcc(buff, fourcc);
	if(!strcmp(fourcc, "00dc"))
	{
		MpegFrame* frame = (MpegFrame*) malloc(sizeof(MpegFrame));
		if(frame == NULL) return NULL;
		skip_size = bitbuffer_read_uint32(buff);
		frame->dataStart = &(buff->source->data[buff->pos>>3]);
		frame->frameSize = skip_size;
		if(skip_size & 1)
			frame->frameSize++;
		bitbuffer_skip_bytes(buff, frame->frameSize);
		*audio = false;
		return frame;
	} 
	else
	{
		skip_size = bitbuffer_read_uint32(buff);
		bitbuffer_skip_bytes(buff,
			((skip_size & 1) ? skip_size + 1 : skip_size) );
		*audio = true;
		return (MpegFrame*) (NULL + 1);
	}
}

int64_t
skip_avi_list_unless(BitBuffer* buff, const char* target)
{
	char fourcc[5];
	size_t list_size;
	bitbuffer_read_fourcc(buff, fourcc);
	if(!strcmp(fourcc, "JUNK"))
	{
		list_size = bitbuffer_read_uint32(buff);
		bitbuffer_skip_bytes(buff, list_size);
		return 0;
	}
	else if(!strcmp(fourcc, "LIST"))
	{
		list_size = bitbuffer_read_uint32(buff);
		bitbuffer_peek_fourcc(buff, fourcc);
		if(!strcmp(fourcc, target))
		{
			bitbuffer_skip_bytes(buff, 4);
			return list_size;
		}
		else
		{
			bitbuffer_skip_bytes(buff, list_size);
			return 0;
		}
	}
	return -1;
}

void
parse_avi_header(BitBuffer* buff, MpegVideo* vid)
{
	bitbuffer_skip_bytes(buff, 4);
    vid->fileSize = bitbuffer_read_uint32(buff);

	bitbuffer_seek_byte(buff, 32, 0);

	#define HEADER_DATA time_delay, avi_data_rate, padding_size, \
		param_flags, num_frames, num_prv, num_streams, \
		buffer_size, width, height, time_scale, data_rate, \
		start_time, chunk_size_ts
	#define HEADER_DATA_REF &time_delay, &avi_data_rate, &padding_size, \
		&param_flags, &num_frames, &num_prv, &num_streams, \
		&buffer_size, &width, &height, &time_scale, &data_rate, \
		&start_time, &chunk_size_ts
	uint32_t HEADER_DATA;
	bitbuffer_read_into_uint32(buff, 14, (uint32_t*[]) {HEADER_DATA_REF});
	vid->numFrames = num_frames;
	vid->w = width;
	vid->h = height;
	vid->time_delay = time_delay;

	#undef HEADER_DATA
	#undef HEADER_DATA_REF
}


MpegVideo
parse_video_from_bits(const char* path)
{
    BitArray arr;
	MpegVideo vid;
	char fourcc[5];

	if(!init_Bitarray_from_file(&arr, path))
		return (MpegVideo) {0,0,0,0,0,0,NULL,NULL};

    BitBuffer* buff = new_BitBuffer_from_BitArray(&arr);

    if(buff == NULL)
	{
		free_BitArray_buffer(&arr);
		return (MpegVideo) {0,0,0,0,0,0,NULL,NULL};
	}

	parse_avi_header(buff, &vid);

	bitbuffer_seek_byte(buff, 12, 0);

	while( !( vid.moviSize = 
			  skip_avi_list_unless(buff, "movi") ) )
	{}

	size_t i=0;
	bool audio_found;
	vid.frames = (MpegFrame**) calloc(vid.numFrames, sizeof(MpegFrame*));
	if(vid.frames == NULL)
	{
		del_BitBuffer(buff);
		free_BitArray_buffer(&arr);
		return (MpegVideo) {0,0,0,0,0,0,NULL,NULL};
	}
	MpegFrame* curr;
	while( ((curr = parse_frame(buff, &audio_found)) != NULL) 
			&& i < vid.numFrames )
		if(!audio_found) vid.frames[i++] = curr;

	vid.fileData = arr.data; // dont free
    del_BitBuffer(buff);
	
	return vid;
}



AVPacket*
get_new_destroyed_packet(AVPacket* src, MpegFrame* f, int kill_prob)
{
	AVPacket* pkt = av_packet_alloc();
	pkt->data = (uint8_t*) calloc(f->frameSize + AV_INPUT_BUFFER_PADDING_SIZE, 1);
	for(size_t i=0; i<f->frameSize; i++)
	{
		if((rand() % kill_prob) == 1)
			pkt->data[i] = (uint8_t) (0xFF & rand());
		else
			pkt->data[i] = f->dataStart[i];
	}
	pkt->size = f->frameSize;
	return pkt;
}


int 
init_filters(
	const char *filters_descr, 
	AVFilterGraph *filter_graph,
	AVFilterContext *sink_ctx,
	AVFilterContext *src_ctx
	)
{
    char args[512];
    int ret = 0;
    const AVFilter *buffersrc  = avfilter_get_by_name("buffer");
    const AVFilter *buffersink = avfilter_get_by_name("buffersink");
    AVFilterInOut *outputs = avfilter_inout_alloc();
    AVFilterInOut *inputs  = avfilter_inout_alloc();
    enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_GRAY8, AV_PIX_FMT_NONE };

    filter_graph = avfilter_graph_alloc();
    if (!outputs || !inputs || !filter_graph) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    ret = avfilter_graph_create_filter(&src_ctx, buffersrc, "in",
                                       args, NULL, filter_graph);
    AV_LOG((ret < 0), "Cannot create buffer source\n", end);

    ret = avfilter_graph_create_filter(&sink_ctx, buffersink, "out",
                                       NULL, NULL, filter_graph);
	AV_LOG((ret < 0), "Cannot create buffer sink\n", end);

    ret = av_opt_set_int_list(sink_ctx, "pix_fmts", pix_fmts,
                              AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN);
    AV_LOG((ret < 0), "Cannot set output pixel format\n", end);
	
    outputs->name       = av_strdup("in");
    outputs->filter_ctx = src_ctx;
    outputs->pad_idx    = 0;
    outputs->next       = NULL;

    inputs->name       = av_strdup("out");
    inputs->filter_ctx = sink_ctx;
    inputs->pad_idx    = 0;
    inputs->next       = NULL;

    if ((ret = avfilter_graph_parse_ptr(filter_graph, filters_descr,
                                    &inputs, &outputs, NULL)) < 0)
        goto end;

    if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
        goto end;

end:
    avfilter_inout_free(&inputs);
    avfilter_inout_free(&outputs);

    return ret;
}


#if EXPORT_MVS > 0
void display_mv_info(AVFrame* frame, FILE* f)
{
	AVFrameSideData* sd = av_frame_get_side_data(frame, AV_FRAME_DATA_MOTION_VECTORS);
	if(sd == NULL) return;
	AVMotionVector* mvs = (AVMotionVector *)sd->data;
	size_t num_mvs = sd->size / sizeof(*mvs);
	for(size_t i=0; i<num_mvs; i++, mvs++)
		if(mvs->motion_x || mvs->motion_y)
			fprintf(f, "Source: %d, mx: %d, my: %d\n", 
				mvs->source, mvs->motion_x, mvs->motion_y);
}
#endif


void
draw_decoded_frame(
	AVCodecContext* ctx, AVFrame* frame, AVFrame* other, 
	struct SwsContext *sws_ctx,
	SDL_Texture* texture, SDL_Renderer* renderer)
{
	sws_scale(sws_ctx, (uint8_t const * const *) frame->data,
		frame->linesize, 0, ctx->height, other->data,
		other->linesize);

	SDL_UpdateYUVTexture(
		texture, NULL,
		other->data[0], ctx->width,
		other->data[1], other->linesize[1],
		other->data[2], other->linesize[2]
	);

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}



void
play_parsed_video(const char *path, int num_frames_play, const char* log)
{
	AVDictionary* opts = NULL;
	AVCodec *codec;
    AVCodecContext *ctx;
	AVCodec *enc_codec;
	AVCodecContext *enc_ctx;
	AVBSFContext* bsf_ctx;
    AVFrame *picture, *other;
	SDL_Event event;
	SDL_Window *screen;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	struct SwsContext *sws_ctx = NULL;

	FILE *f = fopen(log, "wb");
	if(f==NULL)
		return;

	MpegVideo vid = parse_video_from_bits(path);
	if(vid.fileSize == 0)
		goto free_vid;

	if( (vid.pkt = av_packet_alloc()) == NULL )
		goto free_vid;

	picture = av_frame_alloc();
	other = av_frame_alloc();
	if(picture == NULL || other == NULL)
		goto free_no_frame;

	if(    !(codec = avcodec_find_decoder(AV_CODEC_ID_MPEG2VIDEO))
#if USE_ENCODER > 0
		|| !(enc_codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO)) 
#endif
		)
		goto free_no_ctx;

	if(    !(ctx = avcodec_alloc_context3(codec)) 
#if USE_ENCODER > 0
		|| !(enc_ctx = avcodec_alloc_context3(enc_codec))
#endif 
		)
		goto free_no_ctx;


#if EXPORT_MVS > 0
	av_dict_set(&opts, "flags2", "+export_mvs", 0);
#endif

	if(    0 > (avcodec_open2(ctx, codec, &opts)) 
#if USE_ENCODER > 0
		|| 0 > (avcodec_open2(enc_ctx, enc_codec, NULL)) 
#endif
		)
		goto free_all;

	picture->width = (int) vid.w;
	picture->height = (int) vid.h;
	other->width = (int) vid.w;
	other->height = (int) vid.h;
	ctx->width = (int) vid.w;
	ctx->height = (int) vid.h;
	ctx->pix_fmt = AV_PIX_FMT_YUV420P;

	int ret = av_image_alloc(picture->data, picture->linesize, ctx->width,
		ctx->height, ctx->pix_fmt, 1);
	ret = av_image_alloc(other->data, other->linesize, ctx->width,
		ctx->height, ctx->pix_fmt, 1);

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) 
	{
		fprintf(stderr, "Could not initialize SDL - %s\n", SDL_GetError());
		goto free_all_img;
	}

	screen = SDL_CreateWindow(
		"Player",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		ctx->width,
		ctx->height,
		0
	);
	if(screen == NULL)
		goto free_all_quit_sdl;

	renderer = SDL_CreateRenderer(screen, -1, 0);
	if (!renderer) 
	{
		SDL_DestroyWindow(screen);
		goto free_all_quit_sdl;
	}

	texture = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_YV12,
		SDL_TEXTUREACCESS_STREAMING,
		ctx->width,
		ctx->height
	);
	if (!texture) 
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(screen);
		goto free_all_quit_sdl;
	}

	sws_ctx = sws_getContext(
		ctx->width, ctx->height,
		ctx->pix_fmt,
		ctx->width, ctx->height,
		AV_PIX_FMT_YUV420P,
		SWS_BILINEAR,
		NULL,
		NULL,
		NULL);

	MpegFrame* curr_frame;

	srand(time(NULL));


	AVBitStreamFilter* bsf;

	if( (bsf = av_bsf_get_by_name("noise")) == NULL )
		goto free_all_quit_sdl;

	if( av_bsf_alloc(bsf, &bsf_ctx) < 0 )
		goto free_all_quit_sdl;

	AVCodecParameters par_in;

	if( avcodec_parameters_from_context(&par_in, ctx) < 0 )
	{
		av_bsf_free(&bsf_ctx);
		goto free_all_quit_sdl;
	}

	if ( avcodec_parameters_copy(bsf_ctx->par_in, &par_in) < 0)
		goto free_all_quit_sdl;

	int __x__ = av_opt_set(bsf_ctx, "amount", "500", 
		AV_OPT_SEARCH_CHILDREN);

	bsf_ctx->time_base_in = ctx->time_base;

	if( av_bsf_init(bsf_ctx) < 0 )
	{
		av_bsf_free(&bsf_ctx);
		goto free_all_quit_sdl;
	}

	AVPacket *noise_pkt = av_packet_alloc();

	int bsf_send, bsf_receive, codec_send, codec_receive;
	#define LOG_RET(f, x) fprintf(f, #x ": %d\n", x)

	bool need_fix = false;
#if USE_CURSES > 0
	INIT_CURSES();
#endif
	char c = ERR, temp;
	int played=0;
	for(uint32_t i=0; played<num_frames_play; 
		i = ((i+1)%vid.numFrames), played++)
	{
#if USE_CURSES > 0
		if(!i) c = 'e';
		else if ( (temp = getch()) != ERR )
		{
			need_fix = c == 'k' && temp == 'r';
			fprintf(f, "Switched from %c to %c\n", c, temp);
			c = temp;
		}
		refresh();
#else
		c =  'e';
#endif
		switch(c)
		{
			case 'q':
				goto finish;
			case 'k':
				mpeg_parse_packet(&vid, i);
				bsf_send = av_bsf_send_packet(bsf_ctx, vid.pkt);
				bsf_receive = av_bsf_receive_packet(bsf_ctx, noise_pkt);
				codec_send = avcodec_send_packet(ctx, noise_pkt);
				codec_receive = avcodec_receive_frame(ctx, picture);
				LOG_RET(f, bsf_send);
				LOG_RET(f, bsf_receive);
				LOG_RET(f, codec_send);
				LOG_RET(f, codec_receive);
				av_packet_unref(noise_pkt);
				break;
			case 'r':
				--i;
				if (need_fix)
				{
					do {
						bsf_receive = av_bsf_receive_packet(bsf_ctx, noise_pkt);
					} while(bsf_receive != AVERROR(EAGAIN) && bsf_receive != AVERROR_EOF);
					avcodec_send_packet(ctx, noise_pkt);
				}
				codec_send = avcodec_send_packet(ctx, vid.pkt);
				codec_receive = avcodec_receive_frame(ctx, picture);
				LOG_RET(f, codec_send);
				LOG_RET(f, codec_receive);
				break;
			case 'p':
				i = rand() % (vid.numFrames-1);
				c = 'e';
			default:
			case 'e':
				mpeg_parse_packet(&vid, i);
				codec_send = avcodec_send_packet(ctx, vid.pkt);
				codec_receive = avcodec_receive_frame(ctx, picture);
				LOG_RET(f, codec_send);
				LOG_RET(f, codec_receive);
		}
#if EXPORT_MVS > 0
		display_mv_info(picture, f);
#endif
		draw_decoded_frame(ctx, picture, other,
					sws_ctx, texture, renderer);
		SDL_PollEvent(&event);
		av_frame_unref(picture);
		if(event.type == SDL_QUIT)
			goto finish;
		SDL_Delay(25);
	}

	finish:
	// finish_bitstream_filter(&bsf_ctx);
	av_packet_free(&noise_pkt);
	av_bsf_free(&bsf_ctx);
#if USE_CURSES > 0
	FINISH_CURSES();
#endif

	free_all_destroy_sdl:
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);

	free_all_quit_sdl:
	SDL_Quit();

	free_all_img:
	av_freep(&(other->data[0]));
	av_freep(&(picture->data[0]));

	free_all:
	av_dict_free(&opts);
	avcodec_free_context(&ctx);
#if USE_ENCODER > 0
	avcodec_free_context(&enc_ctx);
#endif

	free_no_ctx:
	av_frame_free(&other);
	av_frame_free(&picture);

	free_no_frame:
	av_packet_free(&(vid.pkt));

	free_vid:
	fclose(f);
	free_MpegVideo_frames(&vid);
	free(vid.fileData);
}

int main()
{
	char path[200];
	const char* dir = "/Users/theofabilous/Desktop/Coding/Datamoshing/pynamo/resources/";
	const char* avi_slices_3 = "slicewise_3.avi";
	const char* satan_vid = "satan_1080.avi";
	const char* original = "mp2_test_.avi";
	strcpy(path, dir);
	// strcat(path, original);
	strcat(path, satan_vid);

	const char* log_file = "mv_info.txt";
	char log_path[200];
	strcpy(log_path, dir);
	strcat(log_path, log_file);

	play_parsed_video(path, 5000, log_file);
	return 0;
}