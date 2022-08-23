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
#define IS_LE(x) (!( (x) & BIG_END_TYPE ))

const uint16_t FIELD_FLAGS_MASK =   (1 << 8)-1;

const uint32_t INTEGRAL_TYPE =      1 << 0;
const uint32_t USES_BUFFER =        1 << 1;
const uint32_t BITPACKET_TYPE =     1 << 2;
const uint32_t STRING_TYPE =        1 << 3;
const uint32_t ARRAY_TYPE =         1 << 4;
const uint32_t ARRAY_ALLOC =        1 << 5;
const uint32_t PTR_TYPE =           1 << 6;
const uint32_t SIGNED_TYPE =        1 << 7;
// const uint32_t 

const uint32_t ENV_TYPE =           1 << 8;
const uint32_t REF_TYPE =           1 << 9;
const uint32_t SKIP_TYPE =          1 << 10;
const uint32_t SIZE_USES_ENV =      1 << 11;
const uint32_t SIZE_USES_REF =      1 << 12;
const uint32_t SKIP_REWIND =        1 << 13;
const uint32_t PEEK_TYPE =          1 << 14;
const uint32_t EXPR_TYPE =          1 << 15;
const uint32_t BIG_END_TYPE =    1 << 16;

const uint32_t BYTE_MULT =          1 << 29;
const uint32_t NEGATIVE_MULT =      1 << 30;
const uint32_t MODULO =             1 << 31;

const uint32_t CB_HANDLE_REQUIRED = 1 << 0;
const uint32_t CB_RETURN_SET =      1 << 1;
const uint32_t CB_HAS_INPUT =       1 << 2;
const uint32_t CB_SIGNED =          1 << 3;
const uint32_t CB_W_8 =             1 << 4;
const uint32_t CB_W_16 =            1 << 5;
const uint32_t CB_W_32 =            1 << 6;
const uint32_t CB_W_64 =            1 << 7;
const uint32_t CB_PTR =             1 << 8;
const uint32_t CB_BUFFER =          1 << 9;

const uint32_t CB_REWIND =          1 << 29;
const uint32_t CB_SKIP =            1 << 30;
const uint32_t CB_BREAK =           1 << 31;

// const uint32_t BFIELD_ALLOCATED =   1 << 0;
// const uint32_t BFIELD_USES_BUFFER = 1 << 1;


static uint8_t UNPACK_MAPPINGS[257]     = { ZEROESx256 , false };
static uint8_t UNPACK_BRACES[257]       = { ZEROESx256 , false };
const uint8_t IS_WHITESPACE             = 0b00000001;
const uint8_t IS_BRACE                  = 0b00000010;
const uint8_t BRACE_ALLOC                  = 0b00000100;
const uint8_t IS_FIELD_BEGIN            = 0b10000000;

static inline void
_bitbuffer_init_mappings()
{
    UNPACK_MAPPINGS[256] = true;
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '[', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '<', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '{', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ']', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '>', IS_BRACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '}', IS_BRACE);
    MAP_SET         (UNPACK_BRACES, '[', ']');
    MAP_SET         (UNPACK_BRACES, '<', '>');
    MAP_SET         (UNPACK_BRACES, '{', '}'); // TO-DO
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ' ', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ',', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '\t', IS_WHITESPACE);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '\n', IS_WHITESPACE);

    MAP_SET_FLAG    (UNPACK_MAPPINGS, '[', BRACE_ALLOC);

    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'u', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'i', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 's', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'c', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'z', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '!', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '$', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '&', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '^', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '.', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '(', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'f', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'b', IS_FIELD_BEGIN);


    /*                      TO-DO                        */
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '/', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '|', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '~', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '#', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '@', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, ':', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, 'x', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '=', IS_FIELD_BEGIN);
    MAP_SET_FLAG    (UNPACK_MAPPINGS, '?', IS_FIELD_BEGIN);
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
    size_t pos;
    bool err;
    UnpackCptCtx chkpt;
} UnpackCtx;



uint32_t TERM_IS_REF =      1 << 0;
uint32_t TERM_IS_ENV =      1 << 1;
uint32_t AMT_SET =          1 << 2;
uint32_t MULT_SET =         1 << 3;
uint32_t MOD_SET =          1 << 4;
uint32_t READ_SET =         1 << 5;
uint32_t READ_UNSIGNED =    1 << 6;
uint32_t READ_SIGNED =      1 << 7;
uint32_t PEEK_READ =        1 << 8;


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

void
bitreceiver_clear(BField* r, size_t size)
{
    while(size--)
    {
        if(r->flags & ARRAY_ALLOC)
            free(r->raw);
        *(r++) = (BField) {0, 0, 0, {NULL}};
    }
        
}


void
unpack_cb_stop(CallbackCtx* ctx, bool rewind)
{
    if(rewind)
        ctx->priv.global_flags |= CB_HANDLE_REQUIRED | CB_BREAK | CB_REWIND;
    else
        ctx->priv.global_flags |= CB_HANDLE_REQUIRED | CB_BREAK;
}




int UNTIL_EQ = 1;
int UNTIL_MAP_FLAGS = 2;

static inline int64_t
quick_atoi(char *cp, const char** strp, bool eat_first)
{
    char str_acc[100];
    char* accp = str_acc;
    char c = *cp;
    char *str = *strp;
    if(eat_first)
        c = *(str++);
    while( c && isdigit(c) )
    {
        *(accp++) = c;
        c = *(str++);
    }
    *accp = '\0';
    *cp = c;
    *strp = str;
    if(eat_first)
        *strp = str;
    else
        *strp = --str;
    return (int64_t) atoi(str_acc);
}

static inline bool
build_expr(
    char* c_ptr,
    const char** str_ptr, 
    int mode, 
    char target, 
    uint64_t flags, 
    uint8_t* flag_src,
    ExprCtx* ctx)
{
    const char* str = *str_ptr;
    int size = 0;
    char c;
    int64_t curr_value = 0;
    ctx->terms[0].flags = 0;
    bool got_op = false;

    #define CURR_FLAGS ctx->terms[size].flags

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
        case '^':
            ctx->terms[size].flags |= PEEK_READ;
            goto loop;
        case 'u':
        case 'i':
            ctx->terms[size].flags |= READ_SET;
            ctx->terms[size].flags |= (c == 'u') ? READ_UNSIGNED : READ_SIGNED;
            break;
        case '+':
            if(!size || got_op)
            {
                ctx->err = true;
                return false;
            }
            got_op = true;
            break;
        case '-':
            if(got_op)
            {
                ctx->err = true;
                return false;
            }
            got_op = true;
            ctx->terms[size].mult = -1;
            ctx->terms[size].flags |= MULT_SET;
            goto loop;
        case 'B':
            ctx->terms[size].amt = 3;
            ctx->terms[size].flags |= AMT_SET;
            goto loop;
        case '$':
            ctx->terms[size].flags |= TERM_IS_REF;
            goto loop;
        // case '$':
        //     ctx->terms[size].flags |= TERM_IS_ENV;
        //     goto loop;
        // case '&':
        //     ctx->terms[size].flags |= TERM_IS_REF;
        //     goto loop;
        default:
            break;
    }
    if(     ( (CURR_FLAGS & READ_SET) && (CURR_FLAGS & TERM_IS_REF) )   
        ||  ( (CURR_FLAGS & PEEK_READ) && !(CURR_FLAGS & READ_SET) )
        ||  ( !isdigit(c) )
        ||  ( size && !got_op )         ) 
        
    {
        ctx->err = true;
        return false;
    }
    got_op = false;
    ctx->terms[size].value = quick_atoi(&c, &str, false);
    if(*str == '%')
    {
        if((c = *(str++)) && isdigit(c))
        {
            ctx->terms[size].mod = quick_atoi(&c, &str, false);
            ctx->terms[size].flags |= MOD_SET;
        }
        else
        {
            ctx->err = true;
            return false;
        }
    }
    ctx->terms[++size].flags = 0;
    goto loop;

    end:
    *c_ptr = c;
    *str_ptr = str;
    ctx->expr_size = size;
    return size > 0;
}

static inline int64_t
parse_expr(
    char* c_ptr,
    const char** str_ptr,
    char target,
    BField* env,
    BField* dst,
    size_t env_curr,
    size_t iter_curr,
    ExprCtx* ctx,
    BitBuffer* self
)
{
    int64_t array_size, remainder;
    if(! build_expr(c_ptr, str_ptr, 1, target, 0, NULL, ctx) )
        return 0;
    array_size = 0;
    size_t pos;
    int64_t curr = 0;
    ExprTerm* term;
    for(int i=0; i<ctx->expr_size; i++)
    {
        pos = self->pos;
        term = &(ctx->terms[i]);
        // if(term->flags & TERM_IS_ENV)
        // {
        //     if( (curr = --term->value) < 0 || curr >= env_curr )
        //     {
        //         ctx->err = true;
        //         return 0;
        //     }
        //     curr = (int64_t) env[curr].zu;
        // }
        // else 
        if(term->flags & TERM_IS_REF)
        {
            if( (curr = --term->value) < 0 || curr >= iter_curr )
            {
                ctx->err = true;
                return 0;
            }
            curr = (int64_t) dst[curr].zu;
        }
        else if(term->flags & READ_SET)
        {
            if(term->value > 64)
            {
                ctx->err = true;
                return 0;
            }
            curr = (int64_t) bitbuffer_read(self, term->value, false);
            if( ( term->flags & READ_SIGNED ) &&
                ( curr > 0 ) &&
                ( curr & (((int64_t) 1) << (term->value-1)) )  
                )
            {
                // curr |= ~(( ((int64_t) 1) << term->value ) - 1);
                int64_t m = ( ((int64_t) 1) << (term->value-1) );
                curr = (curr ^ m) - m;
            }
            if(term->flags & PEEK_READ)
                self->pos = pos;
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

size_t
_bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BField* dst,
    bool peeking,
    size_t *err,
    unpack_cb_t cb,
    void *user)
{
    *err = 1;
    if(!UNPACK_MAPPINGS[256])
        _bitbuffer_init_mappings();

    size_t original_pos = self->pos;
    char temp_str[100];
    BField env[20];
    BField* target;
    ExprCtx expr_ctx;
    size_t env_curr = 0;
    int64_t ceil;
    int64_t size;
    int64_t modulo;
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
    CallbackCtx cb_ctx = { .dst = dst, .env = env, .self = self };
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
            case '.':
                SET_FLAG(ctx.flags, BIG_END_TYPE);
                EAT_CHECK(c, fmt);
                goto check_again;
            case 'b':
                SET_FLAG(ctx.flags, BITPACKET_TYPE);
                SET_FLAG(ctx.flags, USES_BUFFER);
                size = 1;
                goto check_modifiers;
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
            case 'i':
                SET_FLAG(ctx.flags, SIGNED_TYPE);
            case 'u':
                goto get_width;
            case '^':
                if(CHECK_FLAG(ctx.flags, PEEK_TYPE))
                    return i;
                SET_FLAG(ctx.flags, PEEK_TYPE);
                EAT_CHECK(c, fmt);
                goto check_again;
            case 'f':
                if( (c = *(fmt++)) != '(' )
                    return i;
                cb_ctx.priv.global_flags = 0;
                if(*fmt != ')')
                {
                    cb_ctx.input.zu = parse_expr(&c, &fmt, ')', env, dst, env_curr, i,
                        &expr_ctx, self);
                    cb_ctx.priv.global_flags |= CB_HAS_INPUT;
                    if(expr_ctx.err)
                        return i;
                }
                else
                {
                    EAT_CHECK(c, fmt);
                    cb_ctx.input.zu = 0;
                }
                cb_ctx.input.size = 0;
                cb_ctx.env_size = env_curr;
                cb_ctx.index = i;
                cb_ctx.output.size = 0;
                cb_ctx.output.zu = 0;
                cb_ctx.priv.size = 0;
                cb_ctx.opaque = user;
                goto do_callback;
                
            case '(':
                SET_FLAG(ctx.flags, EXPR_TYPE);
                target->zu = parse_expr(&c, &fmt, ')', env, dst, env_curr, i,
                    &expr_ctx, self);
                // c = *fmt;
                if(expr_ctx.err)
                    return i;
                goto check_wildcard;
            case '&':
                if(CHECK_FLAG(ctx.flags, PTR_TYPE))
                    return i;
                SET_FLAG(ctx.flags, PTR_TYPE);
                EAT_CHECK(c, fmt);
                goto check_again;
            // case '$':
            //     if(CHECK_FLAG(ctx.flags, ENV_TYPE))
            //         return i;
            //     SET_FLAG(ctx.flags, ENV_TYPE);
            //     target = &(env[env_curr++]);
            //     EAT_CHECK(c, fmt);
            //     goto check_again;
            case '!':
                SET_FLAG(ctx.flags, SKIP_TYPE);
                EAT_CHECK(c, fmt);
                if( !MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, IS_BRACE) )
                    return i;
                matching_brace = MAP_GET(UNPACK_BRACES, c);
                if(MAP_CHECK_FLAG(UNPACK_MAPPINGS, c, BRACE_ALLOC))
                    SET_FLAG(ctx.flags, ARRAY_ALLOC);
                goto parse_array_type;
            case 0:
                *err = 0;
            default:
                return i;
        }

        do_callback:
        cb(&cb_ctx);
        #define CTX_GLOB() cb_ctx.priv.global_flags
        if(!(CTX_GLOB() & CB_HANDLE_REQUIRED))
            continue;
        else if(!(CTX_GLOB() & CB_RETURN_SET))
        {
            if(CTX_GLOB() & CB_REWIND)
                self->pos = original_pos;
            if(CTX_GLOB() & CB_BREAK)
            {
                *err = 0;
                return i;
            }
        }

        get_width:
        EAT_CHECK(c, fmt);
        if(isdigit(*fmt))
        {
            if( (size = atoi((char[]) {c, *fmt, '\0'})) > 64 )
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
                && MAP_CHECK_FLAG(UNPACK_MAPPINGS, (*fmt), BRACE_ALLOC) )
                SET_FLAG(ctx.flags, ARRAY_ALLOC);
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
        if(     CHECK_FLAG(ctx.flags, ARRAY_TYPE)
            ||  CHECK_FLAG(ctx.flags, EXPR_TYPE)  )
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

            size_t val = bitbuffer_read(self, size, IS_LE(ctx.flags));
            if(PEEK_CHECK(fmt,'%'))
            {
                EAT_CHECK(c, fmt);
                if(!(modulo = quick_atoi(&c, &fmt, true)))
                    return i;
                else if((remainder = val % modulo))
                    val = (val + modulo) - remainder;
                c = *(--fmt);
            }

            switch(ceil)
            {
                case 8:
                    *(target->u8_ptr) = val;
                    break;
                case 16:
                    *(target->u16_ptr) = val;
                    break;
                case 24:
                case 32:
                    *(target->u32_ptr) = val;
                    break;
                default:
                case 64:
                    *(target->u64_ptr) = val;
                    break;
            }
        }
        else
        {
            if(PEEK_CHECK(fmt,'%'))
            {
                EAT_CHECK(c, fmt);
                if(!(modulo = quick_atoi(&c, &fmt, true)))
                    return i;
                else
                {
                    target->zu = 
                    bitbuffer_read(self, size, IS_LE(ctx.flags));
                    if((remainder = target->zu % modulo))
                        target->zu = (target->zu + modulo) - remainder;
                }
                c = *(--fmt);
            }
            else
                target->zu = bitbuffer_read(self, size, IS_LE(ctx.flags));
        }
        target->flags = FIELD_FLAGS_MASK & ctx.flags;
  
        if(!CHECK_FLAG(ctx.flags, ENV_TYPE))
            i++;
        continue;

        parse_array_type:
        if(    !CHECK_FLAG(ctx.flags, INTEGRAL_TYPE)
            && !CHECK_FLAG(ctx.flags, SKIP_TYPE)    
            && !CHECK_FLAG(ctx.flags, BITPACKET_TYPE) )
            return i;
        SET_FLAG(ctx.flags, ARRAY_TYPE);

        array_size = parse_expr(&c, &fmt, matching_brace, env, dst, env_curr,
            i, &expr_ctx, self);
        if(     expr_ctx.err
            ||  (CHECK_FLAG(ctx.flags, USES_BUFFER) && array_size*size > 64)    )
            return i;

        if(CHECK_FLAG(ctx.flags, SKIP_TYPE))
        {
            bitbuffer_skip(self, array_size);
            continue;
        }

        dst[i].flags = FIELD_FLAGS_MASK & ctx.flags;        
        
        if( CHECK_FLAG(ctx.flags, BITPACKET_TYPE) )
        {
            dst[i].size = array_size;
            array_max = array_size >> 3;
            for(ii=0; ii<array_max; ii++)
                dst[i].buff[ii] = bitbuffer_read(self, 8, IS_LE(ctx.flags));
            if( (array_size = (array_size & 0b111)) )
                dst[i].buff[array_max] =
                    bitbuffer_read(self, array_size, IS_LE(ctx.flags)) <<
                        (8 - array_size);
            goto check_wildcard;
        }
        dst[i].size = array_size;
        multiple = size >> 3;
        array_max = array_size * multiple;

        if(CHECK_FLAG(ctx.flags, USES_BUFFER))
        {
            for(ii=0; ii < array_max; ii++)
                dst[i].buff[ii] = 
                        bitbuffer_read(self, 8, IS_LE(ctx.flags));
            if(array_max < 8)
                dst[i].buff[ii] = 0;
            goto check_wildcard;
        }
        else if(     CHECK_FLAG(ctx.flags, ARRAY_ALLOC)
                &&   ( (dst[i].raw = calloc(dst[i].size, multiple)) == NULL )    )
            return i;

        for(ii=0; ii < array_max; ii++)
            dst[i].u8_ptr[ii] = 
                    bitbuffer_read(self, 8, IS_LE(ctx.flags));
        if(CHECK_FLAG(ctx.flags, STRING_TYPE))
            dst[i].u8_ptr[ii] = '\0';
        goto check_wildcard;
    }
    *err = 0;
    return i;
}


size_t
bitbuffer_unpack_cb(
    BitBuffer* self, 
    const char* fmt, 
    BField* dst,
    unpack_cb_t cb,
    void* user)
{
    size_t err = 0, output;
    output = _bitbuffer_unpack(self, fmt, dst, false, &err, cb, user);
    if(err)
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
    return output;
}

size_t
bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BField* dst)
{
    size_t err = 0, output;
    output = _bitbuffer_unpack(self, fmt, dst, false, &err, NULL, NULL);
    if(err)
        bitbuffer_set_err(self, BITBUFFER_ILL_ERR);
    return output;
}