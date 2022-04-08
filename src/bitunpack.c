#include "bitbuffer.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

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


#define EAT_CHECK(c, fmt)   \
    if(!(c = *(fmt++))) return i
#define PEEK_CHECK(fmt, c) ((*(fmt)) == (c))

#define SET_FLAG(x, f) x |= (f)
#define CHECK_FLAG(x, f) ( (x) & (f) )
#define MAP_SET_FLAG(m, i, f) m[(uint8_t) (i)] |= (f)
#define MAP_CHECK_FLAG(m, i, f)  ( (m)[(uint8_t) (i)] & (f) )
#define MAP_SET(m, i, e) m[(uint8_t) (i)] = (e)
#define MAP_GET(m, i) ( (m)[(uint8_t) (i)] )

#define GET_ARRAY_FLAGS(x) ((x) & ((uint32_t)0b1100000000))
#define _ENDIAN(x) ((x) & LITTLE_END_TYPE )

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
// const uint32_t ___F1_1___       = 0b0000000000000001;

const uint32_t BYTE_MULT        = 0b1000000000000000 << 16;
const uint32_t NEGATIVE_MULT    = 0b0100000000000000 << 16;
const uint32_t MODULO           = 0b0010000000000000 << 16;
// const uint32_t ENV_TYPE         = 0b0010000000000000 << 16;
// const uint32_t REF_TYPE         = 0b0001000000000000 << 16;
// const uint32_t ARRAY_TYPE       = 0b0000100000000000 << 16;
// const uint32_t SKIP_TYPE        = 0b0000010000000000 << 16;
// const uint32_t SIZE_USES_ENV    = 0b0000001000000000 << 16;
// const uint32_t SIZE_USES_REF    = 0b0000000100000000 << 16;
// const uint32_t ARRAY_NO_ALLOC   = 0b0000000010000000 << 16;
// const uint32_t PTR_TYPE         = 0b0000000001000000 << 16;
// const uint32_t SKIP_REWIND      = 0b0000000000100000 << 16;
// const uint32_t USES_BUFFER      = 0b0000000000010000 << 16;
// const uint32_t BITARRAY_TYPE    = 0b0000000000001000 << 16;
// const uint32_t STRING_TYPE      = 0b0000000000000100 << 16;
// const uint32_t PEEK_TYPE        = 0b0000000000000010 << 16;
// const uint32_t PEEK_TYPE        = 0b0000000000000001 << 16;

static uint8_t UNPACK_MAPPINGS[257]     = { ZEROESx256 , false };
static uint8_t UNPACK_BRACES[257]       = { ZEROESx256 , false };
const uint8_t IS_WHITESPACE             = 0b00000001;
const uint8_t IS_BRACE                  = 0b00000010;
const uint8_t NO_ALLOC                  = 0b00000100;
const uint8_t IS_FIELD_BEGIN            = 0b10000000;

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
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '=', IS_FIELD_BEGIN);
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



uint32_t TERM_IS_REF =      1 << 0;
uint32_t TERM_IS_ENV =      1 << 1;
uint32_t AMT_SET =          1 << 2;
uint32_t MULT_SET =         1 << 3;
uint32_t MOD_SET =          1 << 4;

typedef struct ExprTerm
{
    uint32_t flags;
    int64_t value;
    uint16_t amt;
    int64_t mult;
    int64_t mod;
} ExprTerm;


typedef struct ExprCtx
{
    int expr_size;
    bool err;
    ExprTerm terms[10];
} ExprCtx;

int UNTIL_EQ = 1;
int UNTIL_MAP_FLAGS = 2;

static inline int64_t
quick_atoi(char *cp, const char** strp)
{
    char str_acc[100];
    char* accp = str_acc;
    char c = *cp;
    char *str = *strp;
    while( c && isdigit(c) )
    {
        *(accp++) = c;
        c = *(str++);
    }
    *accp = '\0';
    *cp = c;
    *strp = --str;
    return (int64_t) atoi(str_acc);
}

static inline bool
build_expr(
    const char** str_p, 
    int mode, 
    char target, 
    uint64_t flags, 
    uint8_t* flag_src,
    ExprCtx* ctx)
{
    const char* str = *str_p;
    int size = 0;
    char c;
    int64_t curr_value = 0;
    ctx->terms[0].flags = 0;

    loop:
    if(mode == 1)
    {
        if(! ((c = *(str++)) && c != target) )
            goto end;
    }
    else if(mode == 2)
    {
        if(!( (c = *(str++)) && !(flag_src[(uint8_t) c] & flags) ))
            goto end;        
    }
    switch(c)
    {
        case '+':
            if(!size)
            {
                ctx->err = true;
                return false;
            }
            break;
        case '-':
            ctx->terms[size].mult = -1;
            ctx->terms[size].flags |= MULT_SET;
            goto loop;
        case 'B':
            ctx->terms[size].amt = 3;
            ctx->terms[size].flags |= AMT_SET;
            goto loop;
        case '$':
            ctx->terms[size].flags |= TERM_IS_ENV;
            goto loop;
        case '&':
            ctx->terms[size].flags |= TERM_IS_REF;
            goto loop;
        default:
            break;
    }
    if(isdigit(c))
        ctx->terms[size].value = quick_atoi(&c, &str);
    else
    {
        ctx->err = true;
        return false;
    }
    if(*str == '%')
    {
        if((c = *(str++)) && isdigit(c))
        {
            ctx->terms[size].mod = quick_atoi(&c, &str);
            ctx->terms[size].flags |= MOD_SET;
        }
        else
        {
            ctx->err = true;
            return false;
        }
    }
    // if(*str && (!(*str=='+') && !(*str=='-')))
    // {
    //     ctx->err = true;
    //     return false;
    // }
    ctx->terms[++size].flags = 0;
    goto loop;

    end:
    *str_p = str;
    ctx->expr_size = size;
    return size > 0;
}

static inline int64_t
parse_expr(
    const char** str_p,
    char target,
    BField* env,
    BField* dst,
    size_t env_curr,
    size_t iter_curr,
    ExprCtx* ctx
)
{
    int64_t array_size, remainder;
    if(! build_expr(str_p, 1, target, 0, NULL, ctx) )
        return 0;
    array_size = 0;
    int64_t curr = 0;
    ExprTerm* term;
    for(int i=0; i<ctx->expr_size; i++)
    {
        term = &(ctx->terms[i]);
        if(term->flags & TERM_IS_ENV)
        {
            if( (curr = --term->value) < 0 || curr >= env_curr )
            {
                ctx->err = true;
                return 0;
            }
            curr = (int64_t) env[curr].zu;
        }
        else if(term->flags & TERM_IS_REF)
        {
            if( (curr = --term->value) < 0 || curr >= iter_curr )
            {
                ctx->err = true;
                return 0;
            }
            curr = (int64_t) dst[curr].zu;
        }
        else
            curr = term->value;
        
        if(term->flags & AMT_SET)
            curr <<= term->amt;
        if((term->flags & MOD_SET) &&
            (remainder = curr & term->mod))
            curr = (curr + term->mod) - remainder;
        if(term->flags & MULT_SET)
            curr *= term->mult;
        array_size += curr;
    }
    return array_size;
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
    ExprCtx expr_ctx;
    size_t env_curr = 0;
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

        array_size = parse_expr(&fmt, matching_brace, env, dst, env_curr,
            i, &expr_ctx);
        if(expr_ctx.err)
            return i;
        c = *(fmt);

        if(CHECK_FLAG(ctx.flags, SKIP_TYPE))
        {
            bitbuffer_skip(self, array_size);
            continue;
        }
        
        
        // array_size = parse_atoi_bracket(&fmt, &c, matching_brace, &ctx);
        // if(!array_size) return i;

        // switch(GET_ARRAY_FLAGS(ctx.flags))
        // {
        //     case 0b1000000000: // env
        //         --array_size;
        //         if( !  CHECK_FLAG(ctx.flags, SKIP_TYPE) 
        //             && array_size >= env_curr )
        //         {
        //             dst[i].raw = NULL;
        //             return i;
        //         }
        //         else array_size = env[array_size].zu;
        //         goto read_into_array;
        //     case 0b0100000000: // ref
        //         --array_size;
        //         if( !  CHECK_FLAG(ctx.flags, SKIP_TYPE)
        //             && array_size >= i )
        //         {
        //             dst[i].raw = NULL;
        //             return i;
        //         }
        //         else array_size = dst[array_size].zu;
        //         goto read_into_array;
        //     case 0:
        //         goto read_into_array;
        //     default:
        //         dst[i].raw = NULL;
        //         return i;
        // }

        // read_into_array:
        // if(    CHECK_FLAG(ctx.flags, MODULO)
        //     && (remainder = array_size % ctx.modulo)   )
        //     array_size = (array_size + ctx.modulo ) - remainder;
        // if(CHECK_FLAG(ctx.flags, BYTE_MULT))
        //     array_size <<= 3;
        // if(CHECK_FLAG(ctx.flags, SKIP_TYPE))
        // {
        //     if(CHECK_FLAG(ctx.flags, NEGATIVE_MULT))
        //         bitbuffer_skip(self, -1*array_size);
        //     else
        //         bitbuffer_skip(self, array_size);
        //     continue;
        // }
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