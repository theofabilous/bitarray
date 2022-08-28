#include "bitarray.h"

// Temporary empty instruction
// to place in indented blocks, case statements,
// goto labels, etc.
#define __PASS__ ((void) 0)

const bit_allocator_t BIT_ALLOC_SIZE_MASK = 0xFFFF0000;
const bit_allocator_t BIT_ALLOC_EXTRA_MASK = 0xFFFF;
const uint8_t STRIP_MSB = 0b0001;
const uint8_t STRIP_LSB = 0b0000;

// Define type that holds the bitarray size
uint8_t _bitarray_ssize_t = sizeof(bitarray_size_t);
uint8_t _bitarray_ssize_t_bits = sizeof(bitarray_size_t)<<3;

// Used for the following definitions...
const bitarray_size_t BITARRAY_S_ONE = (bitarray_size_t) 1;
const bitarray_size_t BITARRAY_S_ZERO = (bitarray_size_t) 0;
const bitarray_size_t BITARRAY_S_THREE = (bitarray_size_t) 0b11;

// Defined first as macros so they can be composed
// Otherwise IDE/editor/compiler complains about non-constexprs
#define BITARRAY_UMASK_AMT ((sizeof(bitarray_size_t)<<3)-4)
#define BITARRAY_UMASK (((bitarray_size_t)0xF) << (BITARRAY_UMASK_AMT))
#define BITARRAY_LMASK ~(BITARRAY_UMASK)
#define BITARRAY_MAX_BYTES ((BITARRAY_LMASK) >> 3)

bitarray_size_t bitarray_umask = BITARRAY_UMASK;
uint8_t bitarray_umask_amt = BITARRAY_UMASK_AMT;
bitarray_size_t bitarray_lmask = BITARRAY_LMASK;
bitarray_size_t bitarray_max_bytes = BITARRAY_MAX_BYTES;

// The 4 MSBs in bitarray->size are flags
// Init the mask values instead of computing them each time
bitarray_size_t BITARRAY_MEM_ERR_FLAG = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+3));
bitarray_size_t BITARRAY_ILL_ERR_FLAG = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+2));
bitarray_size_t BITARRAY_FLAG1 = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+1));
bitarray_size_t BITARRAY_FLAG2 = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT));
bitarray_size_t BITARRAY_ERR_MASK = (BITARRAY_S_THREE << (BITARRAY_UMASK_AMT+2));

#undef BITARRAY_UMASK_AMT
#undef BITARRAY_UMASK
#undef BITARRAY_LMASK
#undef BITARRAY_MAX_BYTES


#define DECL_BIT_PACKET_INIT(s) 	\
	BitPacket_##s 					\
	init_BitPacket_##s () 			\
	{								\
		BitPacket_##s pkt;			\
		pkt.size = 0;				\
		return pkt;					\
	}

DECL_BIT_PACKET_INIT(8)
DECL_BIT_PACKET_INIT(16)
DECL_BIT_PACKET_INIT(24)
DECL_BIT_PACKET_INIT(32)
DECL_BIT_PACKET_INIT(40)
DECL_BIT_PACKET_INIT(48)
DECL_BIT_PACKET_INIT(56)
DECL_BIT_PACKET_INIT(64)
DECL_BIT_PACKET_INIT(128)

int64_t 
buffer_append_w(
	uint8_t* buff,
	size_t curr_bits,
	size_t buffer_size,
	size_t val,
	size_t w)
{
	if((curr_bits + w) > (buffer_size << 3))
		return -1;
	size_t byte_w = _byte_size(w);
	size_t n_bytes = _byte_size(curr_bits);
	uint8_t fill = curr_bits & 0b111;
	uint8_t remaining = 8-fill;
	int64_t new_size = curr_bits;
	if(fill && w <= remaining)
	{
		buff[n_bytes-1] |= val << (remaining - w);
		new_size += w;
	}
	else
	{
		if(fill)
		{
			uint8_t shifted_val = val >> (w - remaining);
			buff[n_bytes-1] |= shifted_val;
			new_size += remaining;
			w -= remaining;
			val &= ((1 << w) - 1);
		}
		size_t mask = 1 << (w-1);
		new_size += w;
		for(size_t i=new_size-w;i<new_size;i++, mask >>= 1)
			if(val & mask)
				buff[i >> 3] |= (1 << (7-(i & 0b111)));
	}
	return new_size;
}


bool 
buffer_set_bit(
	uint8_t* buffer,
	size_t buffer_size,
	bool bit,
	size_t i)
{
	if(i >= buffer_size)
		return false;
	if(bit)
		buffer[i >> 3] |= (1 << (7-(i & 0b111)));
	else
		buffer[i >> 3] &= ~(1 << (7-(i & 0b111)));
	return true;
}

bool 
buffer_get_bit(
	uint8_t* buffer,
	size_t buffer_size,
	size_t i)
{
	if(i >= buffer_size)
		return false;
	return ( buffer[i >> 3] & (1 << (7-(i & 0b111))) ) ? true : false;
}

size_t 
buffer_get_slice(
	uint8_t* buffer,
	size_t buffer_size, 
	size_t i, 
	size_t j)
{
	if(j > i && j <= (buffer_size << 3) && j-i <= 64)
	{
		size_t val = 0;
		for(size_t mask=1; i<j; i++, mask <<= 1)
			if(buffer[i >> 3] & (1 << (7-(i & 0b111))))
				val |= mask;
		return val;
	}
	else return -1;
}

bool 
buffer_print_bits(
	uint8_t* buffer,
	size_t buffer_size,  
	size_t i, 
	int64_t len)
{
	size_t max = buffer_size << 3;
	len = (len < 0) ? (max+1+len) : len;
	if((i + len ) > max) return false;
	for(;i<max && len; i++, len--)
		putchar(buffer_get_bit(buffer, buffer_size, i) ? '1' : '0');
	putchar('\n');
	return true;
}

bool 
buffer_print_bytes(
	uint8_t* buffer,
	size_t buffer_size,  
	size_t i, 
	int64_t len)
{
	len = (len < 0) ? (buffer_size+1+len) : len;
	for(;i<buffer_size && len; i++, len--)
		putchar(buffer[i]);
	putchar('\n');	
}


/* -------- INSTANTIATING / DELETING --------- */

bool 
init_BitArray(
	BitArray* obj, 
	bitarray_size_t size)
{
	bitarray_size_t num_bytes = _byte_size(size);
	uint8_t* data = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
	if(data == NULL)
	{
		_bitarray_set_err(obj, BITARRAY_MEM_ERR_FLAG);
		return false;
	}

	memset(data, 0, num_bytes);
	_bitarray_set_size(obj, size);
	obj->data = data;

	bitarray_set_allocator_size(obj, 16);

	return true;
}

void
init_BitArray_from_buffer(
	BitArray* obj,
	uint8_t* buffer,
	size_t buffer_size,
	size_t num_bits)
{
	obj->data = buffer;
	_bitarray_set_size(obj, num_bits);
	// _bitarray_set_extra_bytes(obj, buffer_size - (num_bits << 3));
	_bitarray_set_extra_bytes(obj, buffer_size - (num_bits >> 3));
	bitarray_set_allocator_size(obj, 16);
}

BitArray* 
new_BitArray(
	bitarray_size_t size)
{
	bitarray_size_t num_bytes = _byte_size(size);
	
	BitArray* obj= (BitArray *) malloc(sizeof(BitArray));
	if(obj== NULL)
	{
		return NULL;
	}
	uint8_t* data = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
	if(data == NULL)
	{
		free(obj);
		return NULL;
	}

	memset(data, 0, num_bytes);
	_bitarray_set_size(obj, size);
	obj->data = data;

	bitarray_set_allocator_size(obj, 16);

	return obj;
}

bool 
init_BitArray_from_file(
	BitArray* obj, 
	const char* path)
{
	FILE *fptr = fopen(path, "rb");
	if(fptr == NULL)
		return false;
	size_t file_size;
	fseek(fptr, 0L, SEEK_END);
	file_size = ftell(fptr);
	rewind(fptr);
	obj->data = (uint8_t*) calloc(file_size, sizeof(uint8_t));
	if(obj->data == NULL)
	{
		fclose(fptr);
		return false;
	}
	_bitarray_set_size(obj, file_size << 3);
	fread(obj->data, file_size, 1, fptr);
	fclose(fptr);

	bitarray_set_allocator_size(obj, 128);
	return true;
}

BitArray* 
new_BitArray_from_file(
	const char* path)
{
	BitArray* obj = (BitArray *) malloc(sizeof(BitArray));
	if(obj == NULL)
		return NULL;
	FILE *fptr = fopen(path, "rb");
	if(fptr == NULL)
	{
		free(obj);
		return NULL;
	}
	size_t file_size;
	fseek(fptr, 0L, SEEK_END);
	file_size = ftell(fptr);
	rewind(fptr);

	uint8_t* data = (uint8_t *) calloc(file_size, sizeof(uint8_t));
	if(data == NULL)
	{
		free(obj);
		fclose(fptr);
		return NULL;
	}

	fread(data, file_size, 1, fptr);
	_bitarray_set_size(obj, (file_size << 3));
	obj->data = data;

	bitarray_set_allocator_size(obj, 128);
	return obj;
}

void 
del_BitArray(
	BitArray* obj)
{
	free(obj->data);
	free(obj);
}

void 
free_BitArray_buffer(
	BitArray* obj)
{
	free(obj->data);
}

/* ------------------------------------------- */


/* ------------------ SIZE ------------------- */

void 
bitarray_set_allocator_size(
	BitArray* self, 
	size_t alloc_size)
{
	self->allocator = 0;
	_bitarray_set_alloc_size_bytes(self, alloc_size);
}

bitarray_size_t 
bitarray_size(
	BitArray *self)
{
	return bitarray_lmask & self->size;
}

bool 
bitarray_reserve(
	BitArray* self, 
	bitarray_size_t new_size)
{
	if(!_bitarray_actually_needs_resize_bits(self, new_size))
		return true;
	
	bitarray_size_t alloc_size = _byte_size(new_size);
	if(!alloc_size)
		alloc_size = 1;

	uint8_t* new_data;
	if(self->data == NULL)
		new_data = (uint8_t*) calloc(alloc_size, sizeof(uint8_t));
	else
		new_data = (uint8_t*) realloc(self->data, alloc_size*sizeof(uint8_t));
	if(new_data == NULL)
	{
		free(self->data);
		_bitarray_set_err(self, BITARRAY_MEM_ERR_FLAG);
		return false;
	}

	bitarray_size_t n_bytes = _bitarray_num_bytes(self);

	memset(&new_data[n_bytes], 0, (alloc_size-n_bytes)*sizeof(uint8_t));

	_bitarray_set_extra_bytes(self, alloc_size - n_bytes);
	self->data = new_data;
	return true;
}

bool 
bitarray_resize(
	BitArray* self, 
	bitarray_size_t new_size)
{
	return _bitarray_resize_and_reserve(self, new_size);
}

/* ------------------------------------------- */

/* ---------------- SETTING ------------------ */

void 
bitarray_set(
	BitArray *self,
	bool bit, 
	size_t i)
{
	if(i >= _bitarray_size(self))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}

	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);

	uint8_t masker;
	if(bit)
	{
		masker = 1 << (7-bit_index);
		self->data[byte_index] |= masker;
	}
	else
	{
		masker = ~(1 << (7-bit_index));
		self->data[byte_index] &= masker;
	}
}



void 
bitarray_unset(
	BitArray *self, 
	size_t i)
{
	if(i >= _bitarray_size(self))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}

	size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] &= ~(1 << (7-bit_index));
}

void 
bitarray_set_byte(
	BitArray* self,
	uint8_t byte,
	size_t i)
{
	if(i >= (_bitarray_size(self) >> 3))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}
	self->data[i] = byte;
}


void 
bitarray_set_slice(
	BitArray *self, 
	size_t i, 
	size_t j, 
	size_t val)
{
	size_t byte_i = _byte_part(i), byte_j = _byte_part(j);
	uint8_t bit_i = _bit_part(i), bit_j = _bit_part(j);
	size_t bit_w = _bit_width(val);

	if(j <= i || j > _bitarray_size(self))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}

	if(j-i < bit_w)
	{
		val >>= bit_w - (j-i);
		bit_w = (j-i);
	}
	else if(bit_w > j-i)
	{
		val <<= (j-i) - bit_w;
		bit_w = (j-i);
	}
	uint8_t bit_spill = bit_w & 0b111;
	if(bit_j)
	{
		if(byte_i == byte_j)
		{
			val <<= (8-bit_spill-bit_i);
			self->data[byte_i] = (self->data[byte_i] & get_lr_mask(bit_i, 8-bit_w)) | val;
			return;
		}
		else
		{
			uint8_t shifted = (val & 0xFF) << (8-bit_j);
			self->data[byte_j] = (self->data[byte_j] & ~LEFT_MOST_MASKS[bit_j]) | shifted;
			val >>= bit_j;
			bit_w -= bit_j;
			byte_j--;
		}
	}
	else
		byte_j--;
	
	for(;byte_j != byte_i;val >>=8, byte_j--, bit_w -= 8)
		self->data[byte_j] = val & 0xFF;

	self->data[byte_j] = (self->data[byte_j] & LEFT_MOST_MASKS[8-bit_w]) | val;
}

void 
bitarray_set_slice_str(
	BitArray *self, 
	size_t i, 
	size_t j, 
	uint8_t flags, 
	const char* bits)
{
	if(j <= i || j > _bitarray_size(self))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}

	size_t bit_w = strlen(bits);

	/*
	 (11110)101         [1] (STRIP_MSB)
			111(10101)  [2] (STRIP_LSB) (do nothing)
			i  j
			|  |
			0011010001111010110
	*/
	if(j-i < bit_w && (flags & STRIP_MSB))
		bits = &(bits[bit_w - (j-i)]);
	else
	{
		while(j-i > bit_w)
			_bitarray_set_off(self, i++);
	}

	for(;i < j;i++)
	{
		switch(*(bits++))
		{
			case '0':
				_bitarray_set_off(self, i);
				break;
			case '1':
				_bitarray_set_on(self, i);
				break;
			default:
				_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
				return;	
		}
	}
}

void 
bitarray_fill_slice(
	BitArray *self, 
	size_t i, 
	size_t j, 
	bool bit)
{
	size_t byte_i = _byte_part(i), byte_j = _byte_part(j);
	uint8_t bit_i = _bit_part(i), bit_j = _bit_part(j);

	if(j <= i || j > _bitarray_size(self))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}

	if(bit_j)
	{
		if(byte_i == byte_j)
		{
			if(bit)							// ------------- // <-- parens placed here
				self->data[byte_j] |= ((1 << (bit_j - bit_i))-1) << bit_j;
			else
				self->data[byte_j] &= ~(((1 << (bit_j - bit_i))-1) << bit_j);
			return;
		}
		else
		{
			if(bit)
				self->data[byte_j] |= (1 << (7-bit_j))-1;
			else
				self->data[byte_j] &= ~((1 << (7-bit_j))-1);
			byte_j--;
		}
	}
	
	uint8_t fill = (bit) ? 0xFF : 0;
	while(byte_j != byte_i)
	{
		self->data[byte_j] = fill;
		byte_j--;
	}
	if(bit)
		self->data[byte_i] |= (1 << (7-bit_i)) - 1;
	else
		self->data[byte_i] &= ~((1 << (7-bit_i)) - 1);
}

bool 
bitarray_append(
	BitArray *self, 
	size_t val)
{
	size_t w = _bit_width(val);
	size_t byte_w = _byte_size(w);
	bitarray_size_t n_bytes = _bitarray_num_bytes(self);
	uint8_t fill = _bit_part(self->size); // ok because uses mask
	uint8_t remaining = 8-fill;
	if(fill && w <= remaining)
	{
		self->data[n_bytes-1] |= val << (remaining - w);
		_bitarray_incr_size(self, w);
	}
	else
	{
		if(fill)
		{
			uint8_t shifted_val = val >> (w - remaining);
			self->data[n_bytes-1] |= shifted_val;
			_bitarray_incr_size(self, remaining);
			w -= remaining;
			val &= ((1 << w) - 1);
		}

		bitarray_size_t prev_num_bits = _bitarray_size(self);
		if( !_bitarray_resize_and_reserve(self, prev_num_bits+w) )
			return false;
		size_t mask = 1 << (w-1);
		w += prev_num_bits;
		for(size_t i=prev_num_bits;i<w;i+=1)
		{
			if(val & mask)
				_bitarray_set_on(self, i);
			mask >>= 1;
		}
	}
	return true;

}



bool 
bitarray_append_str(
	BitArray *self, 
	const char* bits)
{
	size_t bit_w = strlen(bits);
	size_t arr_size = _bitarray_size(self);
	if(!_bitarray_resize_and_reserve(self, arr_size + bit_w))
		return false;
	while(*bits)
	{
		switch(*(bits++))
		{
			case '0':
				_bitarray_set_off(self, arr_size++);
				break;
			case '1':
				_bitarray_set_on(self, arr_size++);
				break;
			default:
				_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
				return false;
		}
	}
	return true;
}

/* ------------------------------------------- */


/* ---------------- GETTING ------------------ */

uint8_t 
bitarray_get(
	BitArray *self, 
	size_t i)
{
	if(i >= _bitarray_size(self))
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	uint8_t masker = 1 << (7-bit_index);
	masker = (self->data[byte_index] & masker) >> (7-bit_index);
	return masker;
}

uint8_t 
bitarray_get_byte(
	BitArray* self,
	size_t i)
{
	if(i >= (_bitarray_size(self) >> 3))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return 0;
	}
	return self->data[i];
}

size_t 
bitarray_get_slice(
	BitArray *self, 
	size_t i, 
	size_t j)
{
	if(j > i && j <= _bitarray_size(self) && j-i <= 64)
	{
		size_t val = 0;
		for(size_t mask=1; i<j; i++, mask <<= 1)
			if(_bitarray_get(self, i++)) // probably shouldn't be i++ but just i
				val |= mask;
		return val;
	}
	else
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return -1;
	}
}

void 
bitarray_memcpy(
	BitArray* self, 
	size_t i, 
	size_t len, 
	uint8_t* buffer)
{
	if(i >= (_bitarray_size(self) >> 3) || (i+len) >= (_bitarray_size(self) >> 3))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}
	memcpy(buffer, &(self->data[i]), len);
}

void 
bitarray_bit_strcpy(
	BitArray* self, 
	size_t i, 
	int64_t len, 
	char* buffer)
{
	len = (len < 0) ? (_bitarray_size(self)+1+len) : len;
	if(i >= _bitarray_size(self) || (i+len-1) >= _bitarray_size(self) >> 3)
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}
	uint8_t mask = 1 << (i & 0b111);
	size_t j;
	for(j=0;len;j++, i++, len--)
	{
		buffer[j] = (self->data[i >> 3] & mask) ? '1' : '0';
		mask = (mask & 0b10000000) ? 1 : (mask << 1);
	}
	buffer[j+1] = 0;
}

void 
bitarray_print_bits(
	BitArray* self, 
	size_t i, 
	int64_t len)
{
	size_t max = _bitarray_size(self);
	len = (len < 0) ? (max+1+len) : len;
	for(;i<max && len; i++, len--)
		putchar(bitarray_get(self, i) ? '1' : '0');
	printf("\n");
}

void 
bitarray_print_bytes(
	BitArray* self, 
	size_t i, 
	int64_t len)
{
	char c;
	size_t max = _bitarray_num_bytes(self);
	unsigned int num = (len < 0) ? (max+1+len) : len;
	for(;i<max && num; i++, num--)
	{
		c = bitarray_get_byte(self, i);
		putchar( c ? c : ' ');
	}
	printf("\n");
}

char* 
bitarray_to_str(
	BitArray *self)
{
	char* repr = (char *) calloc((_bitarray_size(self))+3, sizeof(char));
	if(repr == NULL)
	{
		_bitarray_set_err(self, BITARRAY_MEM_ERR_FLAG);
		return NULL;
	}
	uint8_t curr;
	repr[0] = '0';
	repr[1] = 'b';
	for(size_t i=0; i<_bitarray_size(self); i++)
	{
		curr = bitarray_get(self, i);
		if(curr)
		{
			repr[i+2] = '1';
		}
		else {
			repr[i+2] = '0';
		}
	}
	repr[_bitarray_size(self)+2] = '\0';
	return repr;
}

/* ------------------------------------------- */


/* --------------- ITERATING ----------------- */

void 
bitarray_for_each(
	BitArray *self, 
	void (*func)(bool), 
	int64_t max)
{
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	if(max > _bitarray_size(self))
		max = _bitarray_size(self);
	for(size_t i=0; i<max; i++)
		(*func)(_bitarray_get(self, i));
}

void 
bitarray_transform(
	BitArray *self, 
	bool(*func)(bool), 
	int64_t max)
{
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	if(max > _bitarray_size(self))
		max = _bitarray_size(self);
	bool result;
	for(size_t i=0; i<max; i++)
	{
		result = (*func)(_bitarray_get(self, i));
		bitarray_set(self, result, i);
	}
}

void
bitarray_enumerate_each(
	BitArray* self,
	void (*func)(bool bit, size_t index),
	int64_t max)
{
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	if(max > _bitarray_size(self))
		max = _bitarray_size(self);
	for(size_t i=0; i<max; i++)
		(*func)(_bitarray_get(self, i), i);
}


void 
bitarray_map(
	BitArray* self, 
	BinaryMapEntry maps[],
	size_t n)
{
	MapTreeNav* nav = build_binary_map(maps, n);

	size_t r=0;
	size_t repl;
	bool is_leaf, is_mapped, has_right, has_left, bit;
	is_leaf = mapnode_is_leaf(nav->curr);
	for(size_t i=0; i<_bitarray_size(self) || is_leaf;)
	{
		if(!is_leaf)
		{
			is_mapped = mapnode_is_mapped(nav->curr);
			has_right = mapnode_has_right(nav->curr);
			has_left = mapnode_has_left(nav->curr);
			bit = bitarray_get(self, i);
		}
		if(is_leaf ||  
			(   is_mapped && ( (bit && !has_right) || (!bit && !has_left) )   )
		  )
		{
			bitarray_set_slice_str(self, r, i, 0, nav->curr->result);
			nav->curr = nav->root;
			is_leaf = false;
			r=i;
		}
		else if(bit && has_right)
		{
			nav->curr = nav->curr->children[1];
			is_leaf = mapnode_is_leaf(nav->curr);
			i++;
		}
		else if(!bit && has_left)
		{
			nav->curr = nav->curr->children[0];
			is_leaf = mapnode_is_leaf(nav->curr);
			i++;
		}
		else
		{
			i = ++r;
			nav->curr = nav->root;
			is_leaf = false;
		}
	}

	del_MapTreeNav(nav);
}


bool
bitarray_map_into(
	BitArray* self,
	BitArray* other,
	BinaryMapEntry maps[],
	size_t n)
{
	MapTreeNav* nav = build_binary_map(maps, n);
	size_t r=0;
	// size_t repl;
	bool is_leaf, is_mapped, has_right, has_left, bit;
	is_leaf = mapnode_is_leaf(nav->curr);

	// const char* bit_1 = "1"

	char bit_acc[500];
	uint16_t acc_indx=0;
	// size_t i;

	BinaryMapContext ctx = {self, other, 0, bit_acc};

	for(;ctx.index < _bitarray_size(self) || is_leaf;)
	{
		if(!is_leaf)
		{
			is_mapped = mapnode_is_mapped(nav->curr);
			has_right = mapnode_has_right(nav->curr);
			has_left = mapnode_has_left(nav->curr);
			bit = bitarray_get(self, ctx.index);
		}
		if(is_leaf ||  
			(   is_mapped && ( (bit && !has_right) || (!bit && !has_left) )   )
		  )
		{
			// bitarray_set_slice_str(self, r, i, 0, nav->curr->result);
			bit_acc[acc_indx] = '\0';
			switch(nav->curr->flags & 0b111000)
			{
				case 0b1000:  // keep
					// bitarray_append_str(other, bit_acc);
					for (uint32_t j = (uint32_t) nav->curr->skip; j>0; j--)
						bit_acc[acc_indx++] = 
							_bitarray_get(self, ctx.index++) ? '1' : '0';
					bit_acc[acc_indx] = '\0';
					bitarray_append_str(other, bit_acc);
					break;
				case 0b100000:
					(*nav->curr->cb)(&ctx);
					break;
				case 0:       // regular
					bitarray_append_str(other, nav->curr->result);
				case 0b1000000: // opaque
				case 0b10000: // ignore
					break;
			}
			acc_indx = 0;
			nav->curr = nav->root;
			is_leaf = false;
			r=ctx.index;
		}
		else if(bit && has_right)
		{
			nav->curr = nav->curr->children[1];
			bit_acc[acc_indx++] = '1';
			is_leaf = mapnode_is_leaf(nav->curr);
			ctx.index++;
		}
		else if(!bit && has_left)
		{
			nav->curr = nav->curr->children[0];
			bit_acc[acc_indx++] = '0';
			is_leaf = mapnode_is_leaf(nav->curr);
			ctx.index++;
		}
		else
		{
			bitarray_append_str(other, 
				bitarray_get(self, r) ? "1" : "0");
			acc_indx = 0;
			ctx.index = ++r;
			nav->curr = nav->root;
			is_leaf = false;
		}
		// bitarray_print_bits(other, 0, -1);
	}
	if(acc_indx)
		bit_acc[acc_indx] = '\0';
		bitarray_append_str(other, bit_acc);

	del_MapTreeNav(nav);
	return true;
}

/* ------------------------------------------- */


/* ------------- ERROR HANDLING -------------- */

void 
bitarray_unset_err(
	BitArray* self,
	bitarray_size_t err)
{
	self->size &= ~err;
}

void 
bitarray_clear_all_err(
	BitArray* self)
{
	self->size &= bitarray_lmask;
}

bool 
bitarray_check_err(
	BitArray* self,
	bitarray_size_t err)
{
	return (self->size & err) ? true : false;
}

bool 
bitarray_check_status(
	BitArray* self)
{
	return (self->size & BITARRAY_ERR_MASK) ? true : false;
}

/* ------------------------------------------- */


/* ---------------- DEBUG STUFF -------------------- */

void _bitarray_print_info(BitArray* self)
{
	printf("\n[][] ========================= [][]\n");
	bitarray_print_bits(self, 0, -1);
	size_t len = bitarray_size(self);
	size_t num_bytes = _bitarray_num_bytes(self);
	size_t real_num_bytes = _bitarray_real_num_bytes(self);
	size_t real_num_bits = real_num_bytes << 3;
	printf("len: %zu\n", len);
	printf("num_bytes: %zu\n", num_bytes);
	printf("real_num_bytes: %zu\n", real_num_bytes);
	printf("real_num_bits: %zu\n", real_num_bits);
	printf("[][] ========================= [][]\n");
}

/* ------------------------------------------------- */

