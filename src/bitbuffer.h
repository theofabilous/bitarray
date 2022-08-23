#ifndef BITBUFFER_H
#define BITBUFFER_H

/* -------------- MMAPPED BITS (POSIX ONLY) ------------------- */

#ifdef __has_include
    #if __has_include (<unistd.h>)
        #define __GNU_CHECK_INCLUDE_UNISTD__ 1
    #else 
        #define __GNU_CHECK_INCLUDE_UNISTD__ 0
    #endif
#else 
        #define __GNU_CHECK_INCLUDE_UNISTD__ 0
#endif

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__)) || \
    defined (__gnu_linux__) || (__GNU_CHECK_INCLUDE_UNISTD__ == 1)




#define __BITARRAY_POSIX_MMAP 1

#include "bitarray.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdbool.h>
#include <stdint.h>

extern const uint8_t BITBUFFER_WRITE;
extern const uint8_t BITBUFFER_OPENED;
extern const uint8_t BITBUFFER_ALLOC;
extern const uint8_t BITBUFFER_IS_MMAP;
extern const uint8_t BITBUFFER_EOF;
extern const uint8_t BITBUFFER_ILL_ERR;
extern const uint8_t BITBUFFER_MEM_ERR;
extern const uint8_t BITBUFFER_MASK_ERR;

extern const uint8_t BYTE_ALIGN_FLOOR;
extern const uint8_t BYTE_ALIGN_CEIL;

typedef struct BitBuffer
{
	uint8_t flags;
    size_t pos;
    union
    {
        struct 
        {
            int file_no;
	        struct stat file_info;
        };
        BitArray* source;
    };
    uint8_t *buffer;
} BitBuffer;

typedef struct BField BField;

struct BField
{
    uint32_t flags;
    uint32_t size;
    union
    {
        void*           raw;
        uint8_t         u8;
        uint16_t        u16;
        uint32_t        u32;
        uint64_t        u64;
        size_t          zu;
        uint8_t*        u8_ptr;
        uint16_t*       u16_ptr;
        uint32_t*       u32_ptr;
        uint64_t*       u64_ptr;
        size_t*         zu_ptr;
        int8_t          i8;
        int16_t         i16;
        int32_t         i32;
        int64_t         i64;
        int8_t*         i8_ptr;
        int16_t*        i16_ptr;
        int32_t*        i32_ptr;
        int64_t*        i64_ptr;
        bool            bl;
        char            c;
        char*           c_ptr;
        char*           str;
        unsigned char   uc;
        unsigned char*  uc_ptr;
        char            str_buff[8];
        unsigned char   ustr_buff[8];
        uint8_t         buff[8];
        BField*         bf_ptr;
        BitArray*       bits;
        // BitPacket*   pkt; (Small bitarray)
    };
};

typedef struct CallbackCtx
{
    struct private_data
    {
        int size;
        uint32_t global_flags;
        struct private_output
        {
            uint32_t flags;
        } out[10];
    } priv;
    uint16_t env_size;
    uint16_t index;
    BField input;
    BField output;
    BField* env;
    BField* dst;
    BitBuffer* self;
    void* opaque;
} CallbackCtx;

typedef void (*unpack_cb_t)(CallbackCtx* ctx);

BField*
unpack_cb_get_input(CallbackCtx* ctx);

void
unpack_cb_stop(CallbackCtx* ctx, bool rewind);

void
unpack_cb_skip(CallbackCtx* ctx, int64_t skip_len);

void
unpack_cb_return_fmt(CallbackCtx* ctx, const char* fmt, ...);

void
unpack_cb_set_env(CallbackCtx* ctx, int i, const char* fmt, ...);


void
bitreceiver_clear(BField* r, size_t size);



static inline void bitbuffer_set_flag(BitBuffer* self, uint8_t flag)
{
    self->flags |= flag;
}

static inline void bitbuffer_set_err(BitBuffer* self, uint8_t err)
{
    self->flags |= err;
}

static inline bool bitbuffer_check_flag(BitBuffer* self, uint8_t flag)
{
    return self->flags & flag;
}

static inline bool bitbuffer_check_err(BitBuffer* self, uint8_t err)
{
    return self->flags & err;
}

static inline bool bitbuffer_check_status(BitBuffer* self)
{
    return !(self->flags & BITBUFFER_MASK_ERR);
}

// static inline bool bitbuffer_check_status(BitBuffer* self)
// {
//     if(self->flags & BITBUFFER_MASK_ERR)
//     {
//         printf("Err!\n");
//     }
//     return !(self->flags & BITBUFFER_MASK_ERR);
// }

static inline void bitbuffer_unset_flag(BitBuffer* self, uint8_t flag)
{
    self->flags &= ~flag;
}

static inline void bitbuffer_clear_err(BitBuffer* self, uint8_t err)
{
    self->flags &= ~err;
}

static inline size_t bitbuffer_num_bytes(BitBuffer* self)
{
    if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP))
	    return self->file_info.st_size;
    else
        return _bitarray_num_bytes(self->source);
}

static inline size_t bitbuffer_size(BitBuffer* self)
{
    if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP))
	    return (self->file_info.st_size << 3);
    else
        return _bitarray_size(self->source);
}

static inline bool bitbuffer_aligned(BitBuffer* self)
{
    return !(self->pos & 0b111);
}

static inline bool bitbuffer_eof(BitBuffer* self)
{
    return bitbuffer_check_err(self, BITBUFFER_EOF) || 
           self->pos >= bitbuffer_size(self);
}

bool bitbuffer_align(BitBuffer* self, uint8_t align);

// Same as skip, but inline
static inline bool bitbuffer_incr_pos(BitBuffer* self, long long int i);

uint8_t bitbuffer_get_byte(BitBuffer* self, size_t i);

bool bitbuffer_get_bit(BitBuffer* self, size_t i);

bool bitbuffer_seek(BitBuffer* self, long long int i, int whence);

bool bitbuffer_seek_byte(BitBuffer* self, long long int i, int whence);

bool bitbuffer_skip(BitBuffer* self, long long int i);

bool bitbuffer_skip_bytes(BitBuffer* self, long long int i);

char bitbuffer_read_char(BitBuffer* self);

uint8_t bitbuffer_read_byte(BitBuffer* self);

bool bitbuffer_read_bit(BitBuffer* self);

bool bitbuffer_peek_bit(BitBuffer* self);

uint16_t bitbuffer_read_uint16(BitBuffer* self);

uint32_t bitbuffer_read_uint32(BitBuffer* self);

uint64_t bitbuffer_read_uint64(BitBuffer* self);

size_t bitbuffer_read(BitBuffer* self, size_t num, bool little_endian);

size_t bitbuffer_peek(BitBuffer* self, size_t num, bool little_endian);

VlcOutput bitbuffer_get_vlc(BitBuffer* self, VlcTable* vlc_table);

bool bitbuffer_read_fourcc(BitBuffer* self, char* dest);

bool bitbuffer_peek_fourcc(BitBuffer* self, char* dest);

bool bitbuffer_read_bytes(BitBuffer* self, char* dest, size_t len);

bool bitbuffer_overwrite(BitBuffer* self, size_t value, size_t len);

bool bitbuffer_overwrite_bit(BitBuffer* self, bool bit);

BitBuffer* new_BitBuffer_from_file(const char *path, bool write);

BitBuffer* new_BitBuffer_from_BitArray(BitArray* source);

BitBuffer* new_BitBuffer_from_buffer(uint8_t* buffer, size_t num_bytes);

size_t 
bitbuffer_unpack_cb(
    BitBuffer* self, 
    const char* fmt, 
    BField* dst, 
    unpack_cb_t cb,
    void* user);

size_t 
bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BField* dst);


bool bitbuffer_flush(BitBuffer* self);

void bitbuffer_close(BitBuffer* self);

void del_BitBuffer(BitBuffer* self);

#else
#define __BITARRAY_POSIX_MMAP 0

#endif

#endif /* bitbuffer.h */