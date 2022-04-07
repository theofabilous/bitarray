#include "bitbuffer.h"
#include <stdarg.h>
#include <ctype.h>

#if __BITARRAY_POSIX_MMAP == 1

const uint8_t BITBUFFER_WRITE =    0b00000001;
const uint8_t BITBUFFER_OPENED =   0b00000010;
const uint8_t BITBUFFER_IS_MMAP =  0b00001000;
const uint8_t BITBUFFER_EOF =      0b00100000;
const uint8_t BITBUFFER_ILL_ERR =  0b01000000;
const uint8_t BITBUFFER_MEM_ERR =  0b10000000;
const uint8_t BITBUFFER_MASK_ERR = 0b11100000;

const uint8_t BYTE_ALIGN_FLOOR = 1;
const uint8_t BYTE_ALIGN_CEIL = 2;

bool bitbuffer_align(BitBuffer* self, uint8_t align)
{
    // GCC complains for case labels declared const at top level,
    // clang does not
    //    const uint8_t BYTE_ALIGN_FLOOR = 1;
    //    const uint8_t BYTE_ALIGN_CEIL = 2;
    if(bitbuffer_aligned(self))
        return true;
    switch(align)
    {
        default:
        case 1:
            self->pos &= ~((size_t)0b111);
            return true;
        case 2:
            self->pos = (self->pos & ~((size_t)0b111)) + 8;
            if(self->pos >= bitbuffer_size(self))
            {
                bitbuffer_set_err(self, BITBUFFER_EOF);
                return false;
            }
            return true;
    }
}

// Same as skip, but inline
static inline bool bitbuffer_incr_pos(BitBuffer* self, long long int i)
{
    self->pos += i;
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    return true;
}

uint8_t bitbuffer_get_byte(BitBuffer* self, size_t i)
{
	if(i >= bitbuffer_num_bytes(self))
    {
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
        return -1;
    }
    return self->buffer[i];
}

bool bitbuffer_get_bit(BitBuffer* self, size_t i)
{
	if(i >= bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
        return -1;
    }
    return self->buffer[i >> 3] & (1 << (i & 0b111));
}

bool bitbuffer_seek(BitBuffer* self, long long int i, int whence)
{
    switch(whence)
    {
        case SEEK_CUR:
            self->pos += i;
            break;
        case SEEK_SET:
            self->pos = i;
            break;
        case SEEK_END:
            self->pos = bitbuffer_size(self) + i;
    }
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    return true;
}

bool bitbuffer_seek_byte(BitBuffer* self, long long int i, int whence)
{
    switch(whence)
    {
        case SEEK_CUR:
            self->pos += (i<<3);
            break;
        case SEEK_SET:
            self->pos = (i<<3);
            break;
        case SEEK_END:
            self->pos = bitbuffer_num_bytes(self) + i;
    }
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    return true;
}

bool bitbuffer_skip(BitBuffer* self, long long int i)
{
    self->pos += i;
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    return true;
}

bool bitbuffer_skip_bytes(BitBuffer* self, long long int i)
{
    self->pos += (i<<3);
    if(self->pos >= bitbuffer_size(self))
    {
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    return true;
}

char bitbuffer_read_char(BitBuffer* self)
{
    if(self->flags & BITBUFFER_EOF)
        return -1;
    
    char c = self->buffer[self->pos >> 3];
    self->pos += 8;

    if(self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);

    return c;
}

uint8_t bitbuffer_read_byte(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return -1;
    
    uint8_t c = self->buffer[self->pos >> 3];
    self->pos += 8;

    if(self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);

    return c;
}

bool bitbuffer_read_bit(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return -1;
    
    bool bit = self->buffer[self->pos >> 3] & 
        (1 << (7-(self->pos & 0b111)));

    if(++self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);
    
    return bit;
}

uint16_t bitbuffer_read_uint16(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    if(self->pos + 16 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    uint16_t val;
    memcpy(&val, &(self->buffer[self->pos >> 3]), 2);
    self->pos +=16;
    return val;
}

uint32_t bitbuffer_read_uint32(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    if(self->pos + 32 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    uint32_t val;
    memcpy(&val, &(self->buffer[self->pos >> 3]), 4);
    self->pos +=32;
    return val;
}

uint64_t bitbuffer_read_uint64(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    if(self->pos + 64 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    uint64_t val;
    memcpy(&val, &(self->buffer[self->pos >> 3]), 8);
    self->pos += 64;
    return val;  
}

size_t bitbuffer_read(BitBuffer* self, size_t num, bool little_endian)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    else if(self->pos + num > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }

    #define SZ(x) ((size_t) (x))
    size_t val = 0;
    size_t byte_pos = self->pos >> 3;
    size_t bit_curr;

    if(little_endian)
    {
        size_t bit_max = (SZ(1)) << (num-1);
        size_t bit_pos = 0;
        size_t bit_pos_max = num;
        bit_curr = 1;
        while((self->pos & 0b111) && (bit_curr < bit_max))
        {
            if( self->buffer[byte_pos] & (SZ(1) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr <<= 1;
            bit_pos++;
        }
        while(bit_pos_max - bit_pos >= 8)
        {
            val |= ( SZ(self->buffer[self->pos >> 3]) ) << bit_pos;
            bit_pos += 8;
            bit_curr <<= 8;
            self->pos += 8;
        }
        byte_pos = self->pos >> 3;
        while(bit_pos < bit_pos_max)
        {
            if( self->buffer[byte_pos] & (SZ(1) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr <<= 1;
            bit_pos++;
        }
    }
    else
    {
        bit_curr = (SZ(1)) << (num-1);
        while((self->pos & 0b111) && bit_curr)
        {
            if( self->buffer[byte_pos] & (SZ(1) << (7-(self->pos++ & 0b111))) )
                val |= bit_curr;
            bit_curr >>= 1;
            num--;
        }
        while(bit_curr >= 128)
        {
            num -= 8;
            val |= ( SZ(self->buffer[self->pos >> 3]) ) << num;
            bit_curr >>= 8;
            self->pos += 8;
        }
        byte_pos = self->pos >> 3;
        while(bit_curr)
        {
            if( self->buffer[byte_pos] & ( SZ(1) << (7-(self->pos++ & 0b111))) )
                    val |= bit_curr;
                bit_curr >>= 1; 
        }
    }

    return val;

    #undef SZ

}

bool bitbuffer_read_fourcc(BitBuffer* self, char* dest)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    else if(self->pos + 32 > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        memcpy( dest, &(self->buffer[self->pos >> 3]), q);
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        return false;
    }
    else
    {
        memcpy(dest, &(self->buffer[self->pos >> 3]), 4);
        dest[4] = '\0';
        self->pos += 32;
        return true;
    }
}

bool bitbuffer_peek_fourcc(BitBuffer* self, char* dest)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    else if(self->pos + 32 > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        memcpy( dest, &(self->buffer[self->pos >> 3]), q);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        return false;
    }
    else
    {
        memcpy(dest, &(self->buffer[self->pos >> 3]), 4);
        dest[4] = '\0';
        return true;
    }
}

bool 
bitbuffer_read_bytes(BitBuffer* self, char* dest, size_t len)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    if(!bitbuffer_align(self, 2))
        return false;
    if(self->pos + (len << 3) > bitbuffer_size(self))
    {
        int q = (bitbuffer_num_bytes(self) - (self->pos >> 3));
        memcpy( dest, &(self->buffer[self->pos >> 3]), q);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        dest[q] = '\0';
        self->pos = bitbuffer_size(self);
        return false;
    }
    memcpy(dest, &(self->buffer[self->pos >> 3]), len);
    dest[len] = '\0';
    self->pos += (len << 3);
    return true;
}

bool
bitbuffer_read_fmt(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    while(*format != '\0')
    {
        if(*format != '%')
        {
            va_end(args);
            return false;
        }
        format++;
        switch(*format)
        {
            
        }
    }
    return true;
}

#define ZEROESx32                       \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define ZEROESx64                       \
    ZEROESx32,                          \
    ZEROESx32

#define ZEROESx128                      \
    ZEROESx64,                          \
    ZEROESx64

#define ZEROESx256                      \
    ZEROESx128,                         \
    ZEROESx128


#define QPEEK(fmt) *(fmt)
#define EAT_PEEK(c, fmt) *(fmt)

#define SET_FLAG(x, f) x |= (f)
#define CHECK_FLAG(x, f) ( (x) & (f) )
#define MAP_SET_FLAG(m, i, f) m[(uint8_t) (i)] |= (f)
#define MAP_CHECK_FLAG(m, i, f)  ( (m)[(uint8_t) (i)] & (f) )
#define MAP_SET(m, i, e) m[(uint8_t) (i)] = (e)
#define MAP_GET(m, i) ( (m)[(uint8_t) (i)] )

const uint32_t INTEGRAL_TYPE    = 0b1000000000000000;
const uint32_t LITTLE_END_TYPE  = 0b0100000000000000;
const uint32_t ENV_TYPE         = 0b0010000000000000;
const uint32_t REF_TYPE         = 0b0001000000000000;
const uint32_t ARRAY_TYPE       = 0b0000100000000000;
const uint32_t SKIP_TYPE        = 0b0000010000000000;
const uint32_t SIZE_USES_ENV    = 0b0000001000000000;
const uint32_t SIZE_USES_REF    = 0b0000000100000000;
const uint32_t ARRAY_NO_ALLOC   = 0b0000000010000000;
const uint32_t PTR_TYPE         = 0b0000000001000000;
const uint32_t SKIP_REWIND      = 0b0000000000100000;
const uint32_t USES_BUFFER      = 0b0000000000010000;
const uint32_t BITARRAY_TYPE    = 0b0000000000001000;
const uint32_t STRING_TYPE      = 0b0000000000000100;
const uint32_t PEEK_TYPE        = 0b0000000000000010;
//

const uint32_t BYTE_MULT        = 0b1000000000000000 << 16;
const uint32_t NEGATIVE_MULT    = 0b0100000000000000 << 16;
const uint32_t MODULO           = 0b0010000000000000 << 16;
// const uint32_t ENV_TYPE         = 0b0010000000000000;
// const uint32_t REF_TYPE         = 0b0001000000000000;
// const uint32_t ARRAY_TYPE       = 0b0000100000000000;
// const uint32_t SKIP_TYPE        = 0b0000010000000000;
// const uint32_t SIZE_USES_ENV    = 0b0000001000000000;
// const uint32_t SIZE_USES_REF    = 0b0000000100000000;
// const uint32_t ARRAY_NO_ALLOC   = 0b0000000010000000;
// const uint32_t PTR_TYPE         = 0b0000000001000000;
// const uint32_t SKIP_REWIND      = 0b0000000000100000;
// const uint32_t USES_BUFFER      = 0b0000000000010000;
// const uint32_t BITARRAY_TYPE    = 0b0000000000001000;
// const uint32_t STRING_TYPE      = 0b0000000000000100;
// const uint32_t PEEK_TYPE        = 0b0000000000000010;
//

static uint8_t UNPACK_MAPPINGS[257]     = { ZEROESx256 , false };
static uint8_t UNPACK_BRACES[257]       = { ZEROESx256 , false };
const uint8_t IS_WHITESPACE             = 0b00000001;
const uint8_t IS_BRACE                  = 0b00000010;
const uint8_t NO_ALLOC                  = 0b00000100;
const uint8_t IS_FIELD_BEGIN            = 0b10000000;

#define GET_ARRAY_FLAGS(x) ((x) &       0b1100000000)
#define _ENDIAN(x) ((x) & LITTLE_END_TYPE )

static inline void
_bitbuffer_init_mappings()
{
    UNPACK_MAPPINGS[256] = true;
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '[', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '(', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '<', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '{', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ']', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ')', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '>', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '}', IS_BRACE);
    MAP_SET         (UNPACK_BRACES, '[', ']');
    MAP_SET         (UNPACK_BRACES, '(', ')');
    MAP_SET         (UNPACK_BRACES, '<', '>');
    MAP_SET         (UNPACK_BRACES, '{', '}');
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ' ', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ',', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '\t', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '\n', IS_WHITESPACE);

    MAP_SET_FLAG    (UNPACK_MAPPINGS, '<', NO_ALLOC);

    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'u', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'i', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 's', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'c', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'z', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '!', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '$', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '?', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '&', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '^', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'b', IS_FIELD_BEGIN);
}

typedef struct UnpackCptCtx
{
    uint8_t size;
    uint8_t fmt_skip;
    const char *ptr;
    char c;
    bool set;
} UnpackCptCtx;

typedef struct UnpackCtx
{
    uint32_t flags;
    int64_t amt;
    int64_t mult;
    int64_t modulo;
    size_t pos;
    bool err;
    UnpackCptCtx chkpt;
} UnpackCtx;

// typedef struct AtoiAtom
// {

// } AtoiAtom;

uint32_t ATOI_PLUS_SET = 1;
uint32_t ATOI_IS_REF = 2;
uint32_t ATOI_IS_ENV = 4;
uint32_t ATOI_OUTPUT_SET = 8;

typedef struct AtoiCtx
{
    int64_t output;
    uint32_t flags;
    int64_t incr;
    int64_t amt, mult, mod;
    int64_t plus, plus_amt, plus_mult;
    bool err;
} AtoiCtx;

int UNTIL_EQ = 1;
int UNTIL_MAP_FLAGS = 2;

static inline bool
b_atoi(
    const char* str, 
    int mode, 
    char target, 
    uint64_t flags, 
    uint8_t* flag_src,
    AtoiCtx* actx)
{
    actx->plus = 0;
    actx->plus_mult = 1;
    actx->plus_amt = 0;
    actx->amt = 0;
    actx->mult = 1;
    // actx->mod = 0;
    int64_t acc = 0;
    int64_t m = 0;
    int64_t incr = 0;

    // AtoiCtx actx = {0,0,0,0};
    char c = '\0';
    char prev = '\0';
    eq_mode:
    while( (c = str[incr++]) && c != target)
    {
        if(!isdigit(c))
        {
            switch(c)
            {
                case 'B':
                    if(isdigit(prev))
                    {
                        actx->err = true;
                        return false;
                    }
                    else
                        actx->amt += 3;
                    break;
                case '-':
                    if(actx->flags & ATOI_PLUS_SET)
                    {
                        actx->err = true;
                        return false;  
                    }
                    if(isdigit(prev))
                    {
                        actx->output = acc;
                        acc = 0; m = 0;
                        actx->flags |= ATOI_OUTPUT_SET;
                        actx->flags |= ATOI_PLUS_SET;
                        actx->plus_mult *= -1;
                    }
                


            }
        }
    }

}


static inline int64_t
check_modulo(const char** fmt_ptr, char *c_ptr)
{
    int i;
    char temp_str[100];
    const char* fmt = *fmt_ptr;
    char c = *(fmt++);
    if(!c) return 0;
    for(i=0; i<100 && c && 
        !MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, 
        IS_FIELD_BEGIN | IS_WHITESPACE | IS_BRACE); 
        i++, c = *(fmt++))
    {
        if(!isdigit(c))
            return 0;
        temp_str[i] = c;
    }
    temp_str[i] = '\0';
    *c_ptr = c;
    *fmt_ptr = fmt;
    return atoi(temp_str);
}

static inline bool
parse_atoi_repeat(
    const char** fmt_ptr, 
    char *c_ptr, 
    UnpackCtx* ctx)
{
    char temp_str[100];
    const char* fmt = ++(*fmt_ptr);
    for(ctx->chkpt.fmt_skip=0; ctx->chkpt.fmt_skip<100 
        && !MAP_CHECK_FLAG
            (UNPACK_MAPPINGS, *fmt, 
                IS_FIELD_BEGIN | IS_WHITESPACE | IS_BRACE)
        && *fmt; ctx->chkpt.fmt_skip++, fmt++)
    {
        if(!isdigit(*fmt))
            return false;
        temp_str[ctx->chkpt.fmt_skip] = *fmt;
    }
    temp_str[ctx->chkpt.fmt_skip] = '\0';
    ctx->chkpt.size = atoi(temp_str);
    *fmt_ptr = fmt;
    *c_ptr = **fmt_ptr;
    if(ctx->chkpt.size > 1)
    {
        ctx->chkpt.size--;
        ctx->chkpt.set = true;
    }
    return true;
}

static inline int64_t
parse_atoi_bracket(const char** fmt_ptr, char *c_ptr, char target, UnpackCtx* ctx)
{
    int i;
    
    int64_t mod = 0;
    char temp_str[100];
    const char* fmt = *fmt_ptr;
    char c;
    // uint8_t amt = 0;

    check_prefix_modifiers:
    c = *(fmt++);
    switch(c)
    {
        case 'B':
            SET_FLAG(ctx->flags, BYTE_MULT);
            goto check_prefix_modifiers;
        case '-':
            if(!CHECK_FLAG(ctx->flags, SKIP_TYPE))
            {
                ctx->err = true;
                return 0;
            }
            else
            {
                SET_FLAG(ctx->flags, NEGATIVE_MULT);
                ctx->mult = 1;
            }
            goto check_prefix_modifiers;
        case '&':
            if(CHECK_FLAG(ctx->flags, SIZE_USES_ENV | SIZE_USES_REF))
            {
                ctx->err = true;
                return 0;
            }
            else
                SET_FLAG(ctx->flags, SIZE_USES_REF);
            goto check_prefix_modifiers;
        case '$':
            if(CHECK_FLAG(ctx->flags, SIZE_USES_ENV | SIZE_USES_REF))
            {
                ctx->err = true;
                return 0;
            }
            else
                SET_FLAG(ctx->flags, SIZE_USES_ENV);
            goto check_prefix_modifiers;
        case 0:
            ctx->err = true;
            return 0;
        default:
            break;  
    }
    for(i=0; i<100 && c && c != target; 
        i++, c = *(fmt++))
    {
        if(c == '%')
        {
            c = *(fmt++);
            if(!(mod = check_modulo(&fmt, &c)) ||
               c != target)
                return 0;
            else
            {
                SET_FLAG(ctx->flags, MODULO);
                ctx->modulo = mod;
                break;
            }
        }
        else if(!isdigit(c))
            return 0;
        else
            temp_str[i] = c;
    }
    temp_str[i] = '\0';
    *c_ptr = c;
    *fmt_ptr = fmt;
    return atoi(temp_str);
    // if(mod)
    // {
    //     if(output <= mod)
    //         return mod << amt;
    //     else return (output + (mod - (output % mod))) << amt;
    // }
    // return output << amt;
}

size_t
_bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BitReceiver dst,
    bool peeking,
    size_t *err)
{
    *err = 1;
    if(!UNPACK_MAPPINGS[256])
        _bitbuffer_init_mappings();

    char temp_str[100];
    BField env[100];
    BField* target;
    size_t env_curr = 0;
    // uint16_t flags;
    int64_t ceil;
    int64_t size;
    int64_t array_size;
    int16_t multiple;
    int64_t remainder;
    int64_t array_max;
    char matching_brace;
    UnpackCtx ctx = {
        .flags = 0,
        .chkpt = {.ptr = fmt, .c = *fmt, .size = 0 , .set = false,
                  .fmt_skip = 0 }
    };
    char c;
    int i = 0;
    size_t ii;
    int j;
    while  ((ctx.chkpt.set || (c = *(fmt++))) 
             && bitbuffer_check_status(self)) 
    {
        if(!peeking)
        {
            if(ctx.chkpt.set && ctx.chkpt.size--)
            {
                c = ctx.chkpt.c;
                fmt = ctx.chkpt.ptr;
            }
            else
            {
                if(ctx.chkpt.set)
                    ctx.chkpt.c = (c = *(fmt++));
                else
                    ctx.chkpt.c = c;
                ctx.chkpt.ptr = fmt;
                ctx.chkpt.size = 0;
                ctx.chkpt.set = false;
                ctx.chkpt.fmt_skip = 0;
            }
        }
        if(CHECK_FLAG(ctx.flags, PEEK_TYPE))
            self->pos = ctx.pos;
        ctx.pos = self->pos;

        ctx.flags = 0;
        target = &(dst[i]);
        size = 0;
        array_size = 0;

        #define EAT_CHECK(c, fmt)   \
            if(!(c = *(fmt++))) return i
        #define PEEK_CHECK(fmt, c) ((*(fmt)) == (c))

        check_again:
        while( MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, IS_WHITESPACE) )
            EAT_CHECK(c, fmt); 
        switch(c)
        {
            case 'c':
                SET_FLAG(ctx.flags, INTEGRAL_TYPE);
                SET_FLAG(ctx.flags, USES_BUFFER);
                size = 8;
                goto check_modifiers;
            case 's':
                SET_FLAG(ctx.flags, INTEGRAL_TYPE);
                SET_FLAG(ctx.flags, STRING_TYPE);
                size = 8;
                goto check_modifiers;
            case 'z':
                EAT_CHECK(c, fmt); 
                size = 64;
                SET_FLAG(ctx.flags, INTEGRAL_TYPE);
                goto check_modifiers;
            case 'u':
            case 'i':
                goto get_width;
            case '^':
                if(CHECK_FLAG(ctx.flags, PEEK_TYPE))
                    return i;
                SET_FLAG(ctx.flags, PEEK_TYPE);
                EAT_CHECK(c, fmt);
                goto check_again;
            case '&':
                if(CHECK_FLAG(ctx.flags, PTR_TYPE))
                    return i;
                SET_FLAG(ctx.flags, PTR_TYPE);
                EAT_CHECK(c, fmt);
                goto check_again;
            case '$':
                if(CHECK_FLAG(ctx.flags, ENV_TYPE))
                    return i;
                SET_FLAG(ctx.flags, ENV_TYPE);
                target = &(env[env_curr++]);
                EAT_CHECK(c, fmt);
                goto check_again;
            case '!':
                SET_FLAG(ctx.flags, SKIP_TYPE);
                EAT_CHECK(c, fmt);
                if( !MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, IS_BRACE) )
                    return i;
                matching_brace = MAP_GET(UNPACK_BRACES, c);
                if(MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, NO_ALLOC))
                    SET_FLAG(ctx.flags, ARRAY_NO_ALLOC);
                goto parse_array_type;
            default:
                return i;
        }

        get_width:
        EAT_CHECK(c, fmt);
        if(isdigit(*fmt))
        {
            if((size = atoi((char[]) {c, *fmt, '\0'})) > 64 )
                return i;
            EAT_CHECK(c, fmt);
        }
        else
            size = atoi((char[]) {c ,'\0'});
        if(!(size & 0b111))
            SET_FLAG(ctx.flags, INTEGRAL_TYPE);

        check_modifiers:
        if( MAP_CHECK_FLAG(UNPACK_MAPPINGS, (*fmt), IS_BRACE) )
        {
            matching_brace = MAP_GET(UNPACK_BRACES, (*fmt));
            if(    !CHECK_FLAG(ctx.flags, USES_BUFFER) 
                && MAP_CHECK_FLAG(UNPACK_MAPPINGS, (*fmt), NO_ALLOC) )
                SET_FLAG(ctx.flags, ARRAY_NO_ALLOC);
            EAT_CHECK(c, fmt);
            goto parse_array_type;
        }
        check_wildcard:
        if(PEEK_CHECK(fmt, '*'))
        {
            if(ctx.chkpt.set)
            {
                fmt += ctx.chkpt.fmt_skip;
                EAT_CHECK(c, fmt);
            }
            else if(!parse_atoi_repeat(&fmt, &c, &ctx))
                return i;
        }
        if(CHECK_FLAG(ctx.flags, ARRAY_TYPE))
        {
            i++; continue;
        }
        parse_integral_type:
        if(CHECK_FLAG(ctx.flags, PTR_TYPE))
        {
            if( size > 64 || size < 1 )
                return i;
            else if(size & 0b111)
                ceil = (size & (~((int64_t) 0b111))) + 8;
            else ceil = size;

            switch(ceil)
            {
                case 8:
                    *(target->u8_ptr) = bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
                    break;
                case 16:
                    *(target->u16_ptr) = bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
                    break;
                case 24:
                case 32:
                    *(target->u32_ptr) = bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
                    break;
                default:
                case 64:
                    *(target->u64_ptr) = bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
                    break;
            }
        }
        else
        {
            if(PEEK_CHECK(fmt,'%'))
            {
                EAT_CHECK(c, fmt);
                if(!(ctx.modulo = check_modulo(&fmt, &c)))
                    return i;
                else
                {
                    target->zu = 
                    bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
                    if((remainder = target->zu % ctx.modulo))
                        target->zu = (target->zu - ctx.modulo) - remainder;
                }
            }
            else
                target->zu = bitbuffer_read(self, size, !_ENDIAN(ctx.flags));
        }
  
        if(!CHECK_FLAG(ctx.flags, ENV_TYPE))
            i++;
        continue;

        parse_array_type:
        if(    !CHECK_FLAG(ctx.flags, INTEGRAL_TYPE)
            && !CHECK_FLAG(ctx.flags, SKIP_TYPE)    )
            return i;
        SET_FLAG(ctx.flags, ARRAY_TYPE);
        // if(PEEK_CHECK(fmt,'$'))
        // {
        //     SET_FLAG(ctx.flags, SIZE_USES_ENV);
        //     EAT_CHECK(c, fmt);
        // }
        // else if(PEEK_CHECK(fmt,'&'))
        // {
        //     SET_FLAG(ctx.flags, SIZE_USES_REF);
        //     EAT_CHECK(c, fmt);
        // }
        array_size = parse_atoi_bracket(&fmt, &c, matching_brace, &ctx);
        if(!array_size) return i;

        switch(GET_ARRAY_FLAGS(ctx.flags))
        {
            case 0b1000000000: // env
                --array_size;
                if( !  CHECK_FLAG(ctx.flags, SKIP_TYPE) 
                    && array_size >= env_curr )
                {
                    dst[i].raw = NULL;
                    return i;
                }
                else array_size = env[array_size].zu;
                goto read_into_array;
            case 0b0100000000: // ref
                --array_size;
                if( !  CHECK_FLAG(ctx.flags, SKIP_TYPE)
                    && array_size >= i )
                {
                    dst[i].raw = NULL;
                    return i;
                }
                else array_size = dst[array_size].zu;
                goto read_into_array;
            case 0:
                goto read_into_array;
            default:
                dst[i].raw = NULL;
                return i;
        }

        read_into_array:
        if(    CHECK_FLAG(ctx.flags, MODULO)
            && (remainder = array_size % ctx.modulo)   )
            array_size = (array_size + ctx.modulo ) - remainder;
        if(CHECK_FLAG(ctx.flags, BYTE_MULT))
            array_size <<= 3;
        if(CHECK_FLAG(ctx.flags, SKIP_TYPE))
        {
            if(CHECK_FLAG(ctx.flags, NEGATIVE_MULT))
                bitbuffer_skip(self, -1*array_size);
            else
                bitbuffer_skip(self, array_size);
            continue;
        }
        dst[i].size = array_size;
        multiple = size >> 3;
        array_max = array_size * multiple;

        if(CHECK_FLAG(ctx.flags, USES_BUFFER))
        {
            if(array_max > 8)
                return i;
            for(ii=0; ii < array_max; ii++)
                dst[i].buff[ii] = 
                        bitbuffer_read(self, 8, false);
            if(array_max < 8)
                dst[i].buff[ii] = 0;
            goto check_wildcard;
        }

        if(!CHECK_FLAG(ctx.flags, ARRAY_NO_ALLOC))
        {
            dst[i].raw = 
                calloc(dst[i].size, multiple);
            if(dst[i].raw == NULL)
                return i;
        }

        for(ii=0; ii < array_max; ii++)
            dst[i].u8_ptr[ii] = 
                    bitbuffer_read(self, 8, false);
        if(CHECK_FLAG(ctx.flags, STRING_TYPE))
            dst[i].u8_ptr[ii] = '\0';
        goto check_wildcard;
    }
    *err = 0;
    return i;
}

size_t 
bitbuffer_unpeek(
    BitBuffer* self, 
    const char* fmt, 
    BitReceiver dst)
{
    size_t pos = self->pos, err = 0, output;
    output = _bitbuffer_unpack(self, fmt, dst, true, &err);
    if(err)
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
    else
        self->pos = pos;
    return output;
}

size_t
bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BitReceiver dst)
{
    size_t err = 0, output;
    output = _bitbuffer_unpack(self, fmt, dst, false, &err);
    if(err)
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
    return output;
}

void
bitbuffer_read_into(BitBuffer* self, int size, ReadSequence sequence)
{
    ReadTarget* t;
    for(int i=0; i<size; i++)
    {
        t = &(sequence[i]);
        switch(t->readSize)
        {
            case 1:
                *(t->t8) = bitbuffer_read_byte(self);
                break;
            case 2:
                *(t->t16) = bitbuffer_read_uint16(self);
                break;
            case 4:
                *(t->t32) = bitbuffer_read_uint32(self);
                break;
            case 8:
                *(t->t64) = bitbuffer_read_uint64(self);
                break;
            default:
                break;
        }
    }
}

void 
bitbuffer_read_into_uint32(BitBuffer* self, int size, uint32_t* sequence[])
{
    for(int i=0; i<size; i++)
        *(sequence[i]) = bitbuffer_read_uint32(self);
}

BitBuffer* new_BitBuffer_from_file(const char *path, bool write)
{
	int file_no;
	if(write)
		file_no = open(path, O_RDWR, S_IRUSR | S_IWUSR);
	else
		file_no = open(path, O_RDONLY, S_IRUSR);
	BitBuffer* obj = (BitBuffer*) malloc(sizeof(BitBuffer));
	if(obj == NULL)
	{
		close(file_no);
		return NULL;
	}
    obj->flags = 0;
	if(fstat(file_no, &(obj->file_info)) == -1)
	{
		free(obj);
		close(file_no);
		return NULL;
	}
	obj->file_no = file_no;
	if(write)
	{
		obj->buffer = mmap(NULL, obj->file_info.st_size, 
			PROT_READ | PROT_WRITE, MAP_SHARED, obj->file_no, 0);
		obj->flags = 1;
	}
	else
		obj->buffer = mmap(NULL, obj->file_info.st_size, 
			PROT_READ, MAP_PRIVATE, obj->file_no, 0);
	if(obj->buffer == MAP_FAILED)
	{
		free(obj);
		close(file_no);
		return NULL;
	}
    bitbuffer_set_flag(obj, BITBUFFER_OPENED);
    bitbuffer_set_flag(obj, BITBUFFER_IS_MMAP);
    obj->pos = 0;
	return obj;
}

BitBuffer* new_BitBuffer_from_BitArray(BitArray* source)
{
    BitBuffer* obj = (BitBuffer*) malloc(sizeof(BitBuffer));
	if(obj == NULL)
        return NULL;
    obj->flags = 0;
    obj->source = source;
    obj->pos = 0;
    obj->buffer = (char *) source->data;
    return obj;
}

bool bitbuffer_flush(BitBuffer* self)
{	
	if(!bitbuffer_check_flag(self, BITBUFFER_IS_MMAP) ||
       !(self->flags & 1))
		return false;
	else if(msync(self->buffer, self->file_info.st_size, MS_SYNC) == -1)
		return false;
	else
		return true;
}

void bitbuffer_close(BitBuffer* self)
{
	if(bitbuffer_check_flag(self, BITBUFFER_IS_MMAP) &&
       bitbuffer_check_flag(self, BITBUFFER_OPENED))
	{
		munmap(self->buffer, self->file_info.st_size);
		close(self->file_no);
		bitbuffer_unset_flag(self, BITBUFFER_OPENED);
	}
}

void del_BitBuffer(BitBuffer* self)
{
	bitbuffer_close(self);
    if(self != NULL)
	    free(self);
}

#endif