#include "../src/bitarray.h"
#include "../src/bitbuffer.h"
#include "../resources/mpeg2_vlcs.h"
#include <string.h>
#include <stdalign.h>
IMPORT_BITARRAY_MODULE_AS(Bin);

typedef char fourcc_t[5];

typedef struct AviHeader
{
    fourcc_t RIFF;
    uint32_t file_size;
    fourcc_t AVI_;
} AviHeader;

typedef struct Idx1Frame
{
    fourcc_t ckId;
    uint32_t flags;
    uint32_t offset;
    uint32_t ckSize;
} Idx1Frame;

typedef struct Idx1
{
    fourcc_t id;
    uint32_t size;
    uint32_t num_frames;
    Idx1Frame* frames;
} Idx1;

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

typedef struct MbCtx
{
    uint8_t flags;
} MbCtx;



#define decode_dct_type(structure, pred, mb_flags)      \
    (( ((structure) == 3) && ((pred) == 0) &&           \
        (mb_flags & (MB_INTRA | MB_PTRN)) ) ? 1 : 0)

void check_movi(CallbackCtx* ctx)
{
    char* list_type = ctx->dst[2].str_buff;
    if(!strcmp(list_type, "movi"))
    {
        unpack_cb_stop(ctx, false);
        *((bool*) ctx->opaque) = true;
    }
}

void check_idx1(CallbackCtx* ctx)
{
    char* code = ctx->dst[0].str_buff;
    if(!strcmp(code, "idx1"))
    {
        // Tell the callback context to stop unpacking
        unpack_cb_stop(ctx, true); // false --> don't rewind bitbuffer (stop here)
        // true --> rewind
        *((bool*) ctx->opaque) = true;
    }
    else if(!strcmp(code, "00dc") && false)
    {
        uint32_t frame_size = ctx->dst[1].u32;
        printf("Code: %s, ckSize: %zu, ", code, frame_size);
        uint8_t* start_code = ctx->dst[2].buff;
        if( !memcmp(start_code, 
                    (uint8_t[]) 
                        { 0x00, 0x00, 0x01, 0xB3 }, 
                    4) )
        {
            printf("keyframe\n");
        }
        else if( !memcmp(start_code, 
                    (uint8_t[]) 
                        { 0x00, 0x00, 0x01, 0x00 }, 
                    4) )
        {
            printf("deltaframe\n");
        }
        else
        {
            printf("Unknown frame type: ");
            printf("%hhu %hhu %hhu %hhu\n", start_code[0], start_code[1], start_code[2],
                start_code[3]);
        }
    }
}

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
        if(bitbuffer_read_bit(buff))
            mv_x[0] = -mv_x[0];
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
        if(bitbuffer_read_bit(buff))
            mv_y[0] = -mv_y[0];
    }
    if(mv_y[0] != 0 && ctx->fcode[0][1] != 1)
        mv_y[1] = bitbuffer_read(buff, ctx->fcode[0][1]-1, false);
    
    // printf("Motion x: %d, residual x: %d\n", mv_x[0], mv_x[1]);
    // printf("Motion y: %d, residual y: %d\n", mv_y[0], mv_y[1]);
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
            mb_index += 33;
            // printf("mb escape encountered!\n");
            vlc = bitbuffer_get_vlc(buff, ctx->mb_addr_vlcs);
        }
        mb_index += vlc.entry->value;

        // if(mb_index == 37)
        //     printf("ayo\n");

        // printf("vlc: %s, val: %u\n", vlc.bits, vlc.entry->value);
        // printf("Mb #%d\n", mb_index);

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
                printf("B-frames not supported\n");
            default:
                return false;
        }
        // printf("vlc: %s, val: %u\n", vlc.bits, vlc.entry->value);

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
    } while(mb_index != ctx->hsize/16);
}

#define next_start_code(buff)                               \
    while(bitbuffer_peek(buff, 24, false) != 0x000001)      \
                buff->pos++;                                \
    ((void) 0)
#define fourcc_field(x) {   .c_ptr = (x) }
#define u32_field(x)    { .u32_ptr = (x) }


int
parse_avi_file(const char* path)
{
    BitArray arr;
	if(!init_BitArray_from_file(&arr, path))
	{
		printf("Error creating bitarray!\n");
		return 1;
	}

    BitBuffer* buff = new_BitBuffer_from_BitArray(&arr);
    if(buff == NULL)
    {
        printf("Error allocating buffer!\n");
        free_BitArray_buffer(&arr);
        return 1;
    }

    FrameCtx ctx;
    AviHeader header;

    for(int i=0; i<34; i++)
        MB_ADDR_VLCS[i].skip = i+1;
    ctx.mb_addr_vlcs = build_vlc_table(MB_ADDR_VLCS, 34);
    ctx.i_mb_mode_vlcs = build_vlc_table(I_FRAME_MODE_VLCS, 2);
    ctx.p_mb_mode_vlcs = build_vlc_table(P_FRAME_MODE_VLCS, 7);
    ctx.motion_vlcs = build_vlc_table(MOTION_CODE_VLCS, 16);
    ctx.cbp_vlcs = build_vlc_table(CBP_VLCS, 64);
    ctx.dct_0_vlcs = build_vlc_table(DCT_0_VLCS, 224);
    ctx.dct_1_vlcs = build_vlc_table(DCT_1_VLCS, 224);
    ctx.luma_vlcs = build_vlc_table(DCT_LUMA_VLCS, 12);
    ctx.chroma_vlcs = build_vlc_table(DCT_CHROMA_VLCS, 12);

    BField dst[100] =
    {
        fourcc_field(header.RIFF),
        u32_field(&header.file_size),
        fourcc_field(header.AVI_)
    };
    bitbuffer_unpack(buff, "s<4>, &u32, s<4>", dst);
    printf("%s, %zu, %s\n", header.RIFF, header.file_size, header.AVI_);

    bool found_movi = false;
    while(!found_movi)
        bitbuffer_unpack_cb(
            buff, 
            "c<4>, u32%2, c<4>, f(), ![B$2-B4]", 
            dst,
            check_movi,
            &found_movi);

    int64_t movi_pos = (buff->pos >> 3) - 4;

    bool found_idx1 = false;
    while(!found_idx1)
        bitbuffer_unpack_cb(
            buff,
            "c<4>, u32%2, c<4>, f(), ![B$2-B4]",
            dst,
            check_idx1,
            &found_idx1);

    Idx1Frame frames[6000];
    Idx1 avi_idx = { .frames = frames, .num_frames = 0 };

    dst[0].c_ptr = avi_idx.id;
    dst[1].u32_ptr = &(avi_idx.size);

    bitbuffer_unpack(buff, "s<4>, &u32%2", dst);
    printf("%s, %lu\n", avi_idx.id, avi_idx.size);

    int i;
    for(i=0; buff->pos < bitbuffer_size(buff); i++)
    {
        dst[0].c_ptr = frames[i].ckId;
        dst[1].u32_ptr = &(frames[i].flags);
        dst[2].u32_ptr = &(frames[i].offset);
        dst[3].u32_ptr = &(frames[i].ckSize);
        bitbuffer_unpack(buff, "s<4>, &u32, &u32, &u32%2", dst);
    }
    avi_idx.num_frames = --i;
    Idx1Frame* curr;

    uint8_t start_code=0;
    uint8_t ext_id;

    const char* pic_coding_ext_flags[] = {
        "top field first", "frame pred frame dct",
        "concealment mvs", "q scale type",
        "intra vlc fmt", "alternate scan",
        "repeat first field", "4:2:0 type",
        "progressive frame", "composite display"
    };

    bool keyframe_found = false;
    for(i=0; i<avi_idx.num_frames; i++)
    {
        curr = &(avi_idx.frames[i]);
        if(     !strcmp(curr->ckId, "00dc")
            &&  curr->ckSize )
        {
            bitbuffer_seek_byte(buff, curr->offset + movi_pos + 8, SEEK_SET);
            for(;!keyframe_found || start_code != ctx.vsize/16;)
            {
                bitbuffer_unpack(buff, "![B3] u8", dst);
                // printf("\n\nStart code: 00 00 01 %02X ", dst[0].u8);
                switch( (start_code = dst[0].u8) )
                {
                    case 0xB3:
                    keyframe_found = true;
                    // printf("<Sequence header>\n");
                    dst[0].u16_ptr = &ctx.hsize;
                    dst[1].u16_ptr = &ctx.vsize;
                    bitbuffer_unpack(buff,
                        "&.u12, &.u12, .u4, .u4, .u18"
                        "u1, .u10, u1, u1", dst);
                    // printf("hSize: %hu, vSize: %hu, aspect: %hhu, "
                    //     "frame rate code: %hhu, bit rate: %u\n",
                    //     dst[0].u16, dst[1].u16, dst[2].u8, dst[3].u8,
                    //     dst[4].u32);
                    // ctx.hsize = dst[0].u16;
                    // ctx.vsize = dst[1].u16;
                    // printf("Marker bit: %s, vbv buffer size: %hu\n",
                    //         dst[5].u8 ? "true" : "false", dst[6].u16);
                    break;

                    case 0xB5:
                    switch( (ext_id = bitbuffer_read(buff, 4, false)) )
                    {
                        case 0b0001:
                        // printf("<Sequence extension>\n");
                        bitbuffer_unpack(buff,
                            ".u8, b, .u2*3, .u12, b, u8, b, .u2, .u5",
                            dst);
                        // printf( "Profile/level: %hhu, Progressive?: %s, "
                        //         "Chroma fmt: %hhu, hSize ext: %hhu, vSize ext: %hhu\n",
                        //         dst[0].u8, (dst[1].bl) ? "yes" : "no", dst[2].u8,
                        //         dst[3].u8, dst[4].u8);
                        // printf( "Bitrate ext: %hu, marker: %s, vbv ext: %hhu, "
                        //         "B frames?: %s, frame rate ext n: %hhu, "
                        //         "frame rate ext d: %hhu\n",
                        //         dst[5].u16, dst[6].bl ? "yes" : "no", 
                        //         dst[7].u8, dst[8].bl ? "no" : "yes", 
                        //         dst[9].u8, dst[10].u8);
                        break;

                        case 0b1000:
                        // printf("<Coding extension>\n");
                        bitbuffer_unpack(buff,
                            ".u4*4, .u2, .u2, b*10", dst);
                        // printf( "fcodes: %hhu, %hhu, %hhu, %hhu, "
                                // "dc precision: %hhu, structure: %hhu\n",
                                // dst[0].u8, dst[1].u8, dst[2].u8, dst[3].u8,
                                // dst[4].u8, dst[5].u8);
                        ctx.fcode[0][0] = dst[0].u8;
                        ctx.fcode[0][1] = dst[1].u8;
                        ctx.fcode[1][0] = dst[2].u8;
                        ctx.fcode[1][1] = dst[3].u8;
                        ctx.picture_structure = dst[5].u8;
                        // for(int j=0; j<10; j++)
                        //     printf("%s?: %s\n",
                        //         pic_coding_ext_flags[j], dst[j+6].bl ? "true" : "false");
                        ctx.frame_pred_frame_dct = dst[7].bl;
                        ctx.conceal_mvs = dst[8].bl;
                        ctx.intra_vlc = dst[10].bl;
                        if(dst[15].bl)
                            bitbuffer_skip(buff, 20);
                        break;

                        default:
                        // printf("id: %hhu\n", ext_id);
                        break;
                    }
                    break;

                    case 0xB8:
                    // printf("<GOP header>\n");
                    bitbuffer_unpack(buff,
                        "![1], .u5, .u6, ![1], .u6, .u6, ![2]", dst);
                    // printf( "Time code: "
                            // "%02hhu:%02hhu:%02hhu.%02hhu\n",
                            // dst[0].u8, dst[1].u8, dst[2].u8, dst[3].u8);
                    break;

                    case 0x00:
                    printf("\nStart code: 00 00 01 %02X ", dst[0].u8);
                    printf("<Picture header>\n");
                    bitbuffer_unpack(buff,
                        ".u10, .u3, .u16", dst);
                    printf("Frame: %hu, Coding type: %hhu, Delay: %hu\n",
                        dst[0].u16, dst[1].u8, dst[2].u16);
                    ctx.picture_coding = dst[1].u8;
                    if(dst[1].u8 == 2)
                        bitbuffer_skip(buff, 4);
                    else if(dst[1].u8 == 3)
                        bitbuffer_skip(buff, 8);
                    while(bitbuffer_peek_bit(buff))
                        bitbuffer_skip(buff, 9);
                    bitbuffer_skip(buff, 1);
                    break;

                    case 0x01 ... 0xAF:
                    // printf("<Slice #%hhu>\n", start_code);
                    parse_slice(dst, buff, &ctx);
                    break;
                }
                next_start_code(buff);
            }
            start_code = 0;
        }
    }


    
    end:
    del_MapTreeNav(ctx.cbp_vlcs);
    del_MapTreeNav(ctx.dct_0_vlcs);
    del_MapTreeNav(ctx.dct_1_vlcs);
    del_MapTreeNav(ctx.luma_vlcs);
    del_MapTreeNav(ctx.chroma_vlcs);
    del_MapTreeNav(ctx.motion_vlcs);
    del_MapTreeNav(ctx.mb_addr_vlcs);
    del_MapTreeNav(ctx.i_mb_mode_vlcs);
    del_MapTreeNav(ctx.p_mb_mode_vlcs);
    free_BitArray_buffer(&arr);
    del_BitBuffer(buff);
    return 0;
}


int main()
{
    return parse_avi_file("../resources/mp2_test_.avi");
}