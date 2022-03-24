
/* -------------- MMAPPED BITS (POSIX ONLY) ------------------- */


#if __BITARRAY_MMAP__ == 1

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

const uint8_t BITBUFFER_WRITE =    0b00000001;
const uint8_t BITBUFFER_OPENED =   0b00000010;
const uint8_t BITBUFFER_EOF =      0b00100000;
const uint8_t BITBUFFER_ILL_ERR =  0b01000000;
const uint8_t BITBUFFER_MEM_ERR =  0b10000000;
const uint8_t BITBUFFER_MASK_ERR = 0b11100000;

const uint8_t BYTE_ALIGN_FLOOR = 1;
const uint8_t BYTE_ALIGN_CEIL = 2;

typedef struct _BitBuffer
{
	uint8_t flags;
    size_t pos;
	int file_no;
	struct stat file_info;
	char* buffer;
} BitBuffer;

static inline void bitbuffer_set_err(BitBuffer* self, uint8_t err)
{
    self->flags |= err;
}

static inline bool bitbuffer_check_err(BitBuffer* self, uint8_t err)
{
    return self->flags & err;
}

static inline bool bitbuffer_check_status(BitBuffer* self)
{
    return !(self->flags & BITBUFFER_MASK_ERR);
}

static inline void bitbuffer_clear_err(BitBuffer* self, uint8_t err)
{
    self->flags &= ~err;
}

static inline size_t bitbuffer_num_bytes(BitBuffer* self)
{
	return self->file_info.st_size;
}

static inline size_t bitbuffer_size(BitBuffer* self)
{
	return (self->file_info.st_size << 3);
}

static inline bool bitbuffer_aligned(BitBuffer* self)
{
    return !(self->pos & 0b111);
}

bool bitbuffer_align(BitBuffer* self, uint8_t align)
{
    if(bitbuffer_aligned(self))
        return true;
    switch(align)
    {
        case BYTE_ALIGN_FLOOR:
            self->pos &= ~0b111;
            return true;
        case BYTE_ALIGN_CEIL:
            self->pos = (self->pos & ~0b111) + 8;
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
    
    bool bit = self->buffer[self->pos >> 3] & (1 << (self->pos & 0b111));

    if(++self->pos >= bitbuffer_size(self))
        bitbuffer_set_err(self, BITBUFFER_EOF);
    
    return bit;
}

uint16_t bitbuffer_read_uint16(BitBuffer* self)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    else if(self->pos + 16 > bitbuffer_size(self))
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
    else if(self->pos + 32 > bitbuffer_size(self))
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
    else if(self->pos + 64 > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    uint64_t val;
    memcpy(&val, &(self->buffer[self->pos >> 3]), 8);
    self->pos += 64;
    return val;  
}

size_t bitbuffer_read(BitBuffer* self, unsigned int num)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    else if(self->pos + num > bitbuffer_size(self))
    {
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    size_t val = 0;

    /* to-do */

    return val;

}

bool bitbuffer_read_fourcc(BitBuffer* self, char* dest)
{
    if(bitbuffer_check_err(self, BITBUFFER_EOF))
        return false;
    else if(self->pos + 32 > bitbuffer_size(self))
    {
        memcpy( dest, &(self->buffer[self->pos >> 3]), 
            1 + (bitbuffer_num_bytes(self) - (self->pos >> 3)) );
        self->pos = bitbuffer_size(self);
        bitbuffer_set_err(self, BITBUFFER_EOF);
        return false;
    }
    else
    {
        memcpy(dest, &(self->buffer[self->pos >> 3]), 5);
        self->pos += 32;
        return true;
    }
}

BitBuffer* new_BitBuffer_from_file(const char *path, bool write)
{
	int file_no;
	if(write)
		file_no = open(path, O_RDWR, S_IRUSR | S_IWUSR);
	else
		file_no = open(path, O_RDONLY, S_IRUSR);
	BitBuffer* obj = (BitBuffer*) malloc(sizeof(BitBuffer));
    obj->flags = 0;
	if(obj == NULL)
	{
		close(file_no);
		return NULL;
	}
	if(fstat(file_no, &(obj->file_info)) == -1)
	{
		free(obj);
		close(file_no);
		return NULL;
	}
	obj->file_no = file_no;
	if(write)
	{
		obj->buffer = mmap(NULL, &(obj->file_info), 
			PROT_READ | PROT_WRITE, MAP_SHARED, obj->file_no, 0);
		obj->flags = 1;
	}
	else
		obj->buffer = mmap(NULL, &(obj->file_info), 
			PROT_READ, MAP_PRIVATE, obj->file_no, 0);
	if(obj->buffer == MAP_FAILED)
	{
		free(obj);
		close(file_no);
		return NULL;
	}
	obj->flags |= BITBUFFER_OPENED;
    obj->pos = 0;
	return obj;
}

bool bitbuffer_flush(BitBuffer* self)
{	
	if(!(self->flags & 1))
		return false;
	if(msync(self->buffer, self->file_info.st_size, MS_SYNC) == -1)
		return false;
	else
		return true;
}

void bitbuffer_close(BitBuffer* self)
{
	if(self->flags & BITBUFFER_OPENED)
	{
		munmap(self->buffer, self->file_info.st_size);
		close(self->file_no);
		self->flags &= ~BITBUFFER_OPENED;
	}
}

void del_BitBuffer(BitBuffer* self)
{
	bitbuffer_close(self);
	free(self);
}

#endif