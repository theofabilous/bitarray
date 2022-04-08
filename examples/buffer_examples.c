#include "../src/bitarray.h"
#include "../src/bitbuffer.h"
#include <string.h>
IMPORT_BITARRAY_MODULE_AS(Bin);

typedef char fourcc_t[5];
typedef struct AviList AviList;
typedef struct AviChunk AviChunk;

const uint8_t IS_BYTES = 0b00000001;
const uint8_t IS_LIST  = 0b00000010;
const uint8_t IS_CHUNK = 0b00000100;

typedef struct AviListData
{
    uint8_t flags;
    union
    {
        void* raw;
        uint8_t* bytes;
        AviList* list;
        AviChunk* chunk;
    };
} AviListData;

struct AviList
{
    fourcc_t LIST;
    uint32_t list_size;
    fourcc_t list_type;
    AviListData* data;
};

struct AviChunk
{
    fourcc_t CHUNK;
    uint32_t chunk_size;
    uint8_t* data;
};

typedef struct AviFile
{
    fourcc_t RIFF;
    uint32_t file_size;
    fourcc_t AVI_;
    AviList header_data[10];
    AviList stream_data;
    AviList idx_data;
} AviFile;


void check_movi(CallbackCtx* ctx)
{
    char* list_type = ctx->dst[2].str_buff;
    fourcc_t stream_type;
    if(strcmp(list_type, "movi") == 0)
    {
        unpack_cb_stop(ctx, false);
        *((bool*) ctx->opaque) = true;
        bitbuffer_read_fourcc(ctx->self, stream_type);
        if(strcmp(stream_type, "00dc") == 0)
            printf("Found video frame: %s\n", stream_type);
        else if(strcmp(stream_type, "01wb") == 0)
            printf("Found audio frame: %s\n", stream_type);
        else
            printf("File corrupt! Expected frame fourcc code\n");
    }
}

int
parse_avi_file(const char* path)
{
    BitArray arr;
	if(!init_Bitarray_from_file(&arr, path))
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

    #define fourcc_field(x) { .c_ptr = x }
    #define u32_field(x) { .u32_ptr = x }

    AviFile video;
    BField dst[100] =
    {
        fourcc_field(video.RIFF),
        u32_field(&video.file_size),
        fourcc_field(video.AVI_)
    };

    bitbuffer_unpack(buff, "s<4>, &u32, s<4>", dst, NULL, NULL);
    printf("%s, %zu, %s\n", video.RIFF, video.file_size, video.AVI_);

    bool found_movi = false;

    while(!found_movi)
        bitbuffer_unpack(
            buff, 
            "c<4>, u32%2, c<4>, f(), ![B&2-B4]", 
            dst,
            check_movi,
            &found_movi);

    end:
    free_BitArray_buffer(&arr);
    del_BitBuffer(buff);
    return 0;
}

int main()
{
    return parse_avi_file("../resources/mp2_test_.avi");
}