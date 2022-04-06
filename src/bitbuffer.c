#include "bitbuffer.h"
#include <stdarg.h>

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


#define QPEEK(str) *(str+1)
#define EAT_PEEK(c, str) *(str+1)
#define EAT_CHECK(c, str) if( !((c) = *((str))++) ) return i
#define EAT_CHECK_EQ(c, c2, str) if( ((c) = *((str))++) != (c2) ) return i
#define CHECK_0(c) if(!c) return i
#define c_to_u8(x) ((uint8_t) (x))
#define c_to_u16(x) ((uint16_t) (x))
#define c_to_u32(x) ((uint32_t) (x))
#define c_to_u64(x) ((uint64_t) (x))
#define STR_VAL2(c1, c2) (( c_to_u16(c1) << 8 ) | c_to_u8(c2))
#define STR_VAL3(c1, c2, c3) \
    ( ((c_to_u32( STR_VAL2(c1, c2) )) << 8 ) | c_to_u8(c3)  )
#define STR_VAL4(c1, c2, c3, c4) \
    ( (STR_VAL3(c1, c2, c3)  << 8 ) | c_to_u8(c4) )
// #define BINL(x, y, z, w) x ## y ## z ## w

#define _SET_FLAG(x, f) x |= (f)
#define _CHECK_FLAG(x, f) ( (x) & (f) )

#define CONTINUE_INCR(i, incr) i += (incr); continue
#define CONTINUE_INCR_IFN(i, x, flag) \
    i += (_CHECK_FLAG((x), (flag))) ? 0 : 1; continue

const uint16_t INTEGRAL_TYPE    = 0b1000000000000000;
const uint16_t LITTLE_END_TYPE  = 0b0100000000000000;
const uint16_t ENV_TYPE         = 0b0010000000000000;
const uint16_t REF_TYPE         = 0b0001000000000000;
const uint16_t ARRAY_TYPE       = 0b0000100000000000;
const uint16_t SKIP_TYPE        = 0b0000010000000000;
const uint16_t SIZE_USES_ENV    = 0b0000001000000000;
const uint16_t SIZE_USES_REF    = 0b0000000100000000;
const uint16_t BITARRAY_TYPE    = 0b0000000000001000;

#define GET_ARRAY_FLAGS(x) ((x) &       0b1100000000)
#define _ENDIAN(x) ((x) & LITTLE_END_TYPE )

size_t
bitbuffer_unpack(
    BitBuffer* self, 
    const char* fmt, 
    BitReceiver dst, 
    size_t num)
{
    char temp_str[100];
    BField env[100];
    BField* target;
    size_t env_curr = 0;
    uint16_t flags;
    size_t size;
    size_t array_size;
    uint8_t multiple;
    size_t array_max;
    char c;
    int i = 0;
    int j;
    while( (c = *(fmt++)) && i <= num && bitbuffer_check_status(self) )
    {
        dst[i].zu = (size_t) 0;
        target = &(dst[i]);
        flags = 0;
        size = 0;
        array_size = 0;
        if(c != '%') return i;
        env_type:
        EAT_CHECK(c, fmt);
        switch(c)
        {
            case 'z':
                EAT_CHECK_EQ(c, 'u', fmt);
                size = 64;
                _SET_FLAG(flags, INTEGRAL_TYPE);
                goto check_modifiers;
            case 'u':
            case 'i':
                _SET_FLAG(flags, INTEGRAL_TYPE);
                goto integral_type;
            case '$':
                if(_CHECK_FLAG(flags, ENV_TYPE))
                        return i;
                _SET_FLAG(flags, ENV_TYPE);
                target = &(env[env_curr++]);
                goto env_type;
            case '!':
                _SET_FLAG(flags, SKIP_TYPE);
                EAT_CHECK_EQ(c, '[', fmt);
                goto parse_array_type;
            default:
                return i;
        }

        integral_type:
        EAT_CHECK(c, fmt);
        switch(c)
        {
            case '8':
                size = 8;
                goto check_modifiers;
            case '1':
                EAT_CHECK_EQ(c, '6', fmt);
                size = 16;
                goto check_modifiers;
            case '3':
                EAT_CHECK_EQ(c, '2', fmt);
                size = 32;
                goto check_modifiers;
            case '6':
                EAT_CHECK_EQ(c, '4', fmt);
                size = 64;
                goto check_modifiers;
            default:
                return i;
        }

        check_modifiers:
        switch(QPEEK(fmt))
        {
            case '%':
            case '\0':
                goto parse_integral_type;
            case '[':
                EAT_CHECK(c, fmt);
                goto parse_array_type;
            default:
                return i;
        }

        parse_integral_type:
        switch(size)
        {
            case 8:
                target->u8 = bitbuffer_read(self, 8, _ENDIAN(flags));
                break;
            case 16:
                target->u16 = bitbuffer_read(self, 16, _ENDIAN(flags));
                break;
            case 32:
                target->u32 = bitbuffer_read(self, 32, _ENDIAN(flags));
                break;
            case 64:
                target->u64 = bitbuffer_read(self, 64, _ENDIAN(flags));
                break;
            default:
                return i;
        }
        if(_CHECK_FLAG(flags, ENV_TYPE))
        {
            CONTINUE_INCR(i, 0);
        }
        else
        {
            CONTINUE_INCR(i, 1);
        }

        parse_array_type:
        if(!_CHECK_FLAG(flags, INTEGRAL_TYPE))
            return i;
        _SET_FLAG(flags, ARRAY_TYPE);
        if(QPEEK(fmt) == '$') 
        {
            _SET_FLAG(flags, SIZE_USES_ENV);
            fmt++;
        }
        else if(QPEEK(fmt) == '&')
        {
            _SET_FLAG(flags, SIZE_USES_REF);
            fmt++;
        }
        for (j=0; 
             j<100 && c != ']';
             j++, c = *(fmt++))
        {
            if(!c) return i;
            else temp_str[j] = c;
        }
        temp_str[j] = '\0';
        array_size = atoi(temp_str);
        j = 0;

        switch(GET_ARRAY_FLAGS(flags))
        {
            case 0b1000000000: // env
                if( !  _CHECK_FLAG(flags, SKIP_TYPE) 
                    && array_size >= env_curr )
                {
                    dst[i].raw = NULL;
                    return i;
                }
                else array_size = env[array_size].zu;
                goto read_into_array;
            case 0b0100000000: // ref
                if( !  _CHECK_FLAG(flags, SKIP_TYPE)
                    && array_size >= num )
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
        if(_CHECK_FLAG(flags, SKIP_TYPE))
        {
            bitbuffer_skip(self, array_size);
            CONTINUE_INCR(i, 0);
        }
        dst[i].size = array_size;
        multiple = size >> 3;
        array_max = array_size * multiple;
        dst[i].raw = 
            calloc(dst[i].size, multiple);
        if(dst[i].raw == NULL)
            return i;
        for(size_t ii=0; ii < array_max; ii++)
            dst[i].u8_ptr[ii] = 
                    bitbuffer_read(self, 8, false);
        i++;
    }
    return i;
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