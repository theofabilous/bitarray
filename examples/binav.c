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

#include "../resources/mpeg2_vlcs.h"

#define USE_ENCODER 0
#define USE_CURSES 1
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

#define decode_dct_type(structure, pred, mb_flags)      \
    (( ((structure) == 3) && ((pred) == 0) &&           \
        (mb_flags & (MB_INTRA | MB_PTRN)) ) ? 1 : 0)

IMPORT_BITARRAY_MODULE_AS(Bits);

typedef struct FrameCtx
{
    size_t save;
    uint16_t hsize, vsize;
    uint8_t fcode[2][2];
    uint8_t picture_coding;
    uint8_t picture_structure;
    uint8_t frame_pred_frame_dct;
    bool intra_vlc;
    bool conceal_mvs;
    uint8_t mb_flags;
    VlcTable* mb_addr_vlcs;
    VlcTable* i_mb_mode_vlcs;
    VlcTable* p_mb_mode_vlcs;
    VlcTable* motion_vlcs;
    VlcTable* cbp_vlcs;
    VlcTable* dct_0_vlcs;
    VlcTable* dct_1_vlcs;
    VlcTable* luma_vlcs;
    VlcTable* chroma_vlcs;
} FrameCtx;

void
parse_mv(BField* dst, BitBuffer* buff, FrameCtx *ctx)
{
    int mv_x[] = {0, 0};
    int mv_y[] = {0, 0};
    VlcOutput vlc;
    if(bitbuffer_peek_bit(buff))
    {
        mv_x[0] = 0;
        buff->pos++;
    }
    else
    {
        vlc = bitbuffer_get_vlc(buff, ctx->motion_vlcs);
        mv_x[0] = (int) vlc.entry->value;
		if(bitbuffer_peek_bit(buff))
		{
			mv_x[0] = -mv_x[0];
			bitbuffer_overwrite_bit(buff, false);
		}
		else
		{
			bitbuffer_overwrite_bit(buff, true);
		}
    }

    if(mv_x[0] != 0 && ctx->fcode[0][0] != 1)
        mv_x[1] = bitbuffer_read(buff, ctx->fcode[0][0]-1, false);
    
    if(bitbuffer_peek_bit(buff))
    {
        mv_y[0] = 0;
        buff->pos++;
    }
    else
    {
        vlc = bitbuffer_get_vlc(buff, ctx->motion_vlcs);
        mv_y[0] = (int) vlc.entry->value;
        if(bitbuffer_peek_bit(buff))
		{
			mv_y[0] = -mv_y[0];
			bitbuffer_overwrite_bit(buff, false);
		}
		else
		{
			bitbuffer_overwrite_bit(buff, true);
		}
    }
    if(mv_y[0] != 0 && ctx->fcode[0][1] != 1)
        mv_y[1] = bitbuffer_read(buff, ctx->fcode[0][1]-1, false);
}


bool
parse_slice(BField* dst, BitBuffer* buff, FrameCtx *ctx)
{
    uint8_t slice_qscale = bitbuffer_read(buff, 5, false);
    int mb_index = 0;
    if(bitbuffer_peek_bit(buff))
    {
        bitbuffer_skip(buff, 9);
        while(bitbuffer_peek_bit(buff))
            bitbuffer_skip(buff, 9);
    }
    bitbuffer_skip(buff, 1);
    VlcOutput vlc;
    // uint8_t flags;
    bool dct_type;
    VlcTable* dct_table;
    uint8_t eob_val, eob_len, luma_chroma_size, cbp, motion_type;
    do {
        vlc = bitbuffer_get_vlc(buff, ctx->mb_addr_vlcs);

        if(vlc.entry == NULL)
            return false;

        while(vlc.entry->value == 34)
        {
			// printf("MB INDEX: %d\n", mb_index);
            mb_index += 33;
            vlc = bitbuffer_get_vlc(buff, ctx->mb_addr_vlcs);
        }
        mb_index += vlc.entry->value;
		// printf("MB INDEX: %d\n", mb_index);
		ctx->picture_coding = 0b010;
        switch(ctx->picture_coding)
        {
            case 0b001:
                vlc = bitbuffer_get_vlc(buff, ctx->i_mb_mode_vlcs);
                ctx->mb_flags = I_FRAME_MODE_MAPS[vlc.entry->value];
                break;
            case 0b010:
                vlc = bitbuffer_get_vlc(buff, ctx->p_mb_mode_vlcs);
                ctx->mb_flags = P_FRAME_MODE_MAPS[vlc.entry->value];
                break;
            case 0b011:
                // printf("B-frames not supported\n");
            default:
                return false;
        }

        if(ctx->mb_flags & (MB_FW | MB_BW))
        {
            if( (   ctx->picture_structure == 3
                &&  !ctx->frame_pred_frame_dct   )
                || ctx->picture_structure != 3      )
                motion_type = bitbuffer_read(buff, 2, false);
        }

        if( decode_dct_type(ctx->picture_structure, ctx->frame_pred_frame_dct,
            ctx->mb_flags) )
            dct_type = bitbuffer_read_bit(buff);

        if(ctx->mb_flags & MB_QUANT)
            bitbuffer_skip(buff, 5);

        if(     ctx->mb_flags & MB_FW 
            || ((ctx->mb_flags & MB_INTRA) && ctx->conceal_mvs) )
            parse_mv(dst, buff, ctx);

        if((ctx->mb_flags & MB_INTRA) && ctx->conceal_mvs)
            bitbuffer_skip(buff, 1);

        if(ctx->mb_flags & MB_PTRN)
        {
            vlc = bitbuffer_get_vlc(buff, ctx->cbp_vlcs);
            cbp = vlc.entry->value;
        }
        else if(ctx->mb_flags & MB_INTRA)
            cbp = 0b111111;
        else
            cbp = 0;

        if(ctx->mb_flags & MB_INTRA && ctx->intra_vlc)
        {
            dct_table = ctx->dct_1_vlcs;
            eob_val = 0b0110;
            eob_len = 4;
        }
        else
        {
            dct_table = ctx->dct_0_vlcs;
            eob_val = 0b10;
            eob_len = 2;            
        }

        for(uint8_t i = 1, j=0;j<6; i<<=1, j++)
        {
            if(!(cbp & i)) continue;
            if(ctx->mb_flags & MB_INTRA)
            {
                vlc = bitbuffer_get_vlc(
                    buff, (j<4) ? ctx->luma_vlcs : ctx->chroma_vlcs
                );
                luma_chroma_size = vlc.entry->value;
                if(luma_chroma_size)
                    bitbuffer_skip(buff, luma_chroma_size);
            }
            else
            {
                if(eob_val == 0b10 && bitbuffer_peek_bit(buff))
                    bitbuffer_skip(buff, 2);
                else
                {
                    vlc = bitbuffer_get_vlc(buff, dct_table);
                    if(vlc.entry->value == 1)
                        bitbuffer_skip(buff, 18);
                }
            }
            while( ( vlc = bitbuffer_get_vlc(buff, dct_table) )
                    .entry->value != 2 )
            {
                if(vlc.entry->value == 1)
                    bitbuffer_skip(buff, 18);
            }
        }
    } while(mb_index != ctx->vsize/16);
	return true;
}


typedef struct MpegFrame MpegFrame;
struct MpegFrame
{
    uint8_t* dataStart;
    size_t frameSize;
	size_t bytePos;
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
		frame->bytePos = buff->pos >> 3;
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

	BField receiver[14];
	bitbuffer_unpack(buff, "u32*14", receiver);
	vid->numFrames = receiver[4].u32;
	vid->w = receiver[8].u32;
	vid->h = receiver[9].u32;
	vid->time_delay = receiver[0].u32;

	#undef HEADER_DATA
	#undef HEADER_DATA_REF
}


MpegVideo
parse_video_from_bits(const char* path)
{
    BitArray arr;
	MpegVideo vid;
	char fourcc[5];

	if(!init_BitArray_from_file(&arr, path))
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

#if USE_ENCODER > 0
	AVCodec *enc_codec;
	AVCodecContext *enc_ctx;
#endif
	
	AVBSFContext* bsf_ctx;
    AVFrame *picture, *other;
	SDL_Event event;
	SDL_Window *screen;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	struct SwsContext *sws_ctx = NULL;

	FrameCtx fctx;
	for(int i=0; i<34; i++)
        MB_ADDR_VLCS[i].skip = i+1;
    fctx.mb_addr_vlcs = build_vlc_table(MB_ADDR_VLCS, 34);
    fctx.i_mb_mode_vlcs = build_vlc_table(I_FRAME_MODE_VLCS, 2);
    fctx.p_mb_mode_vlcs = build_vlc_table(P_FRAME_MODE_VLCS, 7);
    fctx.motion_vlcs = build_vlc_table(MOTION_CODE_VLCS, 16);
    fctx.cbp_vlcs = build_vlc_table(CBP_VLCS, 64);
    fctx.dct_0_vlcs = build_vlc_table(DCT_0_VLCS, 224);
    fctx.dct_1_vlcs = build_vlc_table(DCT_1_VLCS, 224);
    fctx.luma_vlcs = build_vlc_table(DCT_LUMA_VLCS, 12);
    fctx.chroma_vlcs = build_vlc_table(DCT_CHROMA_VLCS, 12);
	BField dst[100];

	FILE *f = fopen(log, "wb");
	if(f==NULL)
		return;

	MpegVideo vid = parse_video_from_bits(path);

	fctx.hsize = vid.h;
	fctx.vsize = vid.w;

	BitArray arr;
	init_BitArray_from_buffer(&arr, vid.fileData, vid.fileSize, vid.fileSize << 3);
    BitBuffer* buff = new_BitBuffer_from_BitArray(&arr);

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
	uint8_t slice_index;
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
			case 's':
				#define next_start_code(buff)                           \
				while(bitbuffer_peek(buff, 24, false) != 0x000001)      \
							buff->pos++;                                \
				((void) 0)

				bitbuffer_seek_byte(buff, vid.frames[i]->bytePos, 0);
				// goto case_e;
				for(;;)
				{
					bitbuffer_skip_bytes(buff, 3);
					switch( bitbuffer_read_byte(buff) )
					{
						default:
						case 0xB3:
						case 0xB8:
							goto case_e;
							break;
						case 0x00:
							bitbuffer_skip(buff, 10+3+16 + 1+3 + 1);
							break;
						case 0xB5:
							switch( bitbuffer_read(buff, 4, false) )
							{ 
								case 0b0001:
									bitbuffer_skip(buff, 8 + 1 + (2*3) + 12 + 1 + 8 + 1 + 2 + 5);
									break;
								default:
								case 0b1000:
									bitbuffer_unpack(buff,
                            			".u4*4, .u2, .u2, b*10", dst);
									fctx.fcode[0][0] = dst[0].u8;
									fctx.fcode[0][1] = dst[1].u8;
									fctx.fcode[1][0] = dst[2].u8;
									fctx.fcode[1][1] = dst[3].u8;
									fctx.picture_structure = dst[5].u8;
									fctx.frame_pred_frame_dct = dst[7].bl;
									fctx.conceal_mvs = dst[8].bl;
									fctx.intra_vlc = dst[10].bl;
									if(dst[15].bl)
										bitbuffer_skip(buff, 20);
									for(;;)
									{
										next_start_code(buff);
										bitbuffer_skip_bytes(buff, 3);
										slice_index = bitbuffer_read_byte(buff);
										// printf("SLICE IDX: %hhu\n", slice_index);
										parse_slice(dst, buff, &fctx);
										if(slice_index == fctx.hsize/16)
											break;	
									}
									// bitbuffer_overwrite(buff, 0b10011001, 8);
									goto case_e;
							}
							break;
					}
					next_start_code(buff);
				}
				goto case_e;
				// break;
			case 'p':
				i = rand() % (vid.numFrames-1);
				c = 'e';
			default:
			case_e:
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
		slice_index = 0;
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
