#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>

#include "util/bit_util.h"
#include "util/bit_defs.h"
#include "util/bit_macros.h"
#include "biterator.h"
#include "bitbuffer.h"
#include "binarymap.h"

typedef size_t bit_allocator_t;

typedef struct _BitArray
{
	bitarray_size_t size;
	bit_allocator_t allocator;
	uint8_t *data;
} BitArray;




/* ====================================================================== */
/* =======================[] PRIVATE FUNCTIONS []======================== */


/* ------------------------[] ALLOCATOR STUFF []------------------------- */

const bit_allocator_t BIT_ALLOC_SIZE_MASK = 0xFFFF0000;
const bit_allocator_t BIT_ALLOC_EXTRA_MASK = 0xFFFF;

static inline void 
_bitarray_set_extra_bytes(BitArray* self, size_t extra_bytes)
{ 
	self->allocator = ((self->allocator & BIT_ALLOC_SIZE_MASK) 
						| (BIT_ALLOC_EXTRA_MASK & extra_bytes)); 
}

static inline size_t 
_bitarray_get_extra_bytes(BitArray* self)
{ 
	return self->allocator & BIT_ALLOC_EXTRA_MASK;
}

static inline size_t 
_bitarray_get_alloc_size_bytes(BitArray* self)
{ 
	return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 16; 
}

static inline size_t 
_bitarray_get_alloc_size_bits(BitArray* self)
{ 
	return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 13; 
}

static inline void 
_bitarray_set_alloc_size_bytes(BitArray* self, size_t alloc_size)
{ 
	if(!alloc_size) alloc_size = 1;
	self->allocator = (self->allocator & BIT_ALLOC_EXTRA_MASK) 
						| ((0xFFFF & alloc_size) << 16);
}


/* <><><> ----- <><><> ----- <><><> ----- <><><> ----- <><><> ----- <><><> */


static inline void 
_bitarray_set_on(BitArray *self, size_t i)
{
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] |= (1 << (7-bit_index));
}

static inline void 
_bitarray_set_off(BitArray *self, size_t i)
{
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] &= ~(1 << (7-bit_index));
}


static inline bitarray_size_t 
_bitarray_size(BitArray *self)
{
	return bitarray_lmask & self->size;
}


static inline bitarray_size_t 
_bitarray_num_bytes(BitArray *self)
{
	if(self->size & 0b111)
		return ((_bitarray_size(self) >> 3)+1);
	else
		return (_bitarray_size(self) >> 3);
}


static inline bitarray_size_t 
_bitarray_real_num_bytes(BitArray *self)
{
	return _bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self);
}

static inline bitarray_size_t 
_bitarray_real_num_bits(BitArray *self)
{
	return (_bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self)) << 3;
}



static inline bool 
_bitarray_actually_needs_resize_bits(BitArray *self, size_t num_bits)
{
	return _byte_size(num_bits) > _bitarray_real_num_bytes(self);
}


static inline bitarray_size_t 
_bitarray_flags(BitArray *self)
{
	return self->size & bitarray_umask;
}


static inline void 
_bitarray_set_size(BitArray *self, bitarray_size_t size)
{
	self->size = (self->size & bitarray_umask) | size;
}


static inline void 
_bitarray_incr_size(BitArray *self, bitarray_size_t incr)
{
	_bitarray_set_size(self, _bitarray_size(self) + incr);
}


static inline void 
_bitarray_set_err(BitArray* self, bitarray_size_t err)
{
	self->size |= err;
}


static inline bool 
_bitarray_reserve(BitArray* self, bitarray_size_t new_size)
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

static inline void 
_bitarray_resize_quick(BitArray* self, bitarray_size_t new_size)
{
	uint8_t bit_spill = new_size & 0b111;
	size_t prev_real_bytes = _bitarray_real_num_bytes(self);
	bitarray_size_t num_bytes = (new_size) ? _byte_size(new_size) : 1;
	if(bit_spill)
	{
		uint8_t mask = ~((1 << (8-bit_spill)) - 1);
		self->data[num_bytes-1] &= mask;
	}
	_bitarray_set_size(self, new_size);
	size_t extra_bytes = prev_real_bytes - num_bytes;
	_bitarray_set_extra_bytes(self, extra_bytes);
	memset(&(self->data[num_bytes]), 0, extra_bytes*sizeof(uint8_t));
}


static inline bool 
_bitarray_resize_and_reserve(BitArray* self, 
								  bitarray_size_t new_size)
{
	/*
	Might *always* want (even when shrinking) precisely minimum
	number of alloc blocks for new_size
	-> make sure to check if same "real_size" bcuz obv don't want to 
	   realloc if no need for actual resizing
	*/
	bitarray_size_t arr_size = _bitarray_size(self);
	size_t real_num_bits = _bitarray_real_num_bits(self);
	if(_bitarray_actually_needs_resize_bits(self, new_size))
	{
		bit_allocator_t alloc_size = _bitarray_get_alloc_size_bits(self);
		size_t new_real_size_bits = (new_size / alloc_size)*alloc_size;
		if(new_size % alloc_size)
			new_real_size_bits += alloc_size;
		if(!_bitarray_reserve(self, new_real_size_bits))
			return false;
		_bitarray_resize_quick(self, new_size);
	}
	else if(new_size != arr_size)
		_bitarray_resize_quick(self, new_size);
	return true;
}


/* ------------------------------------------------------------ */


void 
bitarray_set_allocator_size(BitArray* self, 
							size_t alloc_size)
{
	self->allocator = 0;
	_bitarray_set_alloc_size_bytes(self, alloc_size);
}


bitarray_size_t 
bitarray_size(BitArray *self)
{
	return bitarray_lmask & self->size;
}


void 
bitarray_unset_err(BitArray* self, 
				   bitarray_size_t err)
{
	self->size &= ~err;
}


void 
bitarray_clear_all_err(BitArray* self)
{
	self->size &= bitarray_lmask;
}


bool 
bitarray_check_err(BitArray* self, 
				   bitarray_size_t err)
{
	return (self->size & err) ? true : false;
}


bool 
bitarray_check_status(BitArray* self)
{
	return (self->size & BITARRAY_ERR_MASK) ? true : false;
}


void 
bitarray_set_byte(BitArray* self, 
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


uint8_t 
bitarray_get_byte(BitArray* self, 
		    	  size_t i)
{
	if(i >= (_bitarray_size(self) >> 3))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return 0;
	}
	return self->data[i];
}


void 
bitarray_set(BitArray *self, 
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


void bitarray_unset(BitArray *self, size_t i)
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

uint8_t bitarray_get(BitArray *self, size_t i)
{
	if(i >= _bitarray_size(self))
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	uint8_t masker = 1 << (7-bit_index);
	masker = (self->data[byte_index] & masker) >> (7-bit_index);
	return masker;
}


size_t bitarray_get_slice(BitArray *self, size_t i, size_t j)
{
	size_t diff = j - i - 1;
	size_t mask = 1 << diff;
	size_t val = 0;
	// Start at j-1, end at i ?? (less shifting idk)
	while(i < j)
	{
		if(bitarray_get(self, i))
		{
			val |= mask;
		}
		mask >>= 1;
		i++;
	}
	return val;
}

void bitarray_memcpy(BitArray* self, size_t i, size_t len, uint8_t* buffer)
{
	if(i >= (_bitarray_size(self) >> 3) || (i+len) >= (_bitarray_size(self) >> 3))
	{
		_bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
		return;
	}
	memcpy(buffer, &(self->data[i]), len);
}

void bitarray_bit_strcpy(BitArray* self, size_t i, int64_t len, char* buffer)
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

void bitarray_print_bits(BitArray* self, size_t i, int64_t len)
{
	size_t max = _bitarray_size(self);
	len = (len < 0) ? (max+1+len) : len;
	for(;i<max && len; i++, len--)
		putchar(bitarray_get(self, i) ? '1' : '0');
	printf("\n");
}

void bitarray_print_bytes(BitArray* self, size_t i, int len)
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


const uint8_t STRIP_MSB = 0b0001;
const uint8_t STRIP_LSB = 0b0000; // do nothing

void bitarray_set_slice_str(BitArray *self, size_t i, size_t j, uint8_t flags, const char* bits)
{
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

	/*  00          
		--11110101
		i         j
		|         |
		0011010001111010110
	*/
	else
	{
		while(j-i > bit_w)
			_bitarray_set_off(self, i++);
	}

	char curr;
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

void bitarray_set_slice(BitArray *self, size_t i, size_t j, size_t val)
{
	size_t byte_i = _byte_part(i), byte_j = _byte_part(j);
	uint8_t bit_i = _bit_part(i), bit_j = _bit_part(j);
	size_t bit_w = _bit_width(val);

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

	size_t byte_w = _byte_size(bit_w);
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
	
	while(byte_j != byte_i)
	{
		self->data[byte_j] = val & 0xFF;
		val >>= 8;
		byte_j--;
		bit_w -= 8;
	}
	self->data[byte_j] = (self->data[byte_j] & LEFT_MOST_MASKS[8-bit_w]) | val;
}

void bitarray_fill_slice(BitArray *self, size_t i, size_t j, bool bit)
{
	size_t byte_i = _byte_part(i), byte_j = _byte_part(j);
	uint8_t bit_i = _bit_part(i), bit_j = _bit_part(j);

	if(bit_j)
	{
		if(byte_i == byte_j)
		{
			if(bit)
				self->data[byte_j] |= ((1 << bit_j - bit_i)-1) << bit_j;
			else
				self->data[byte_j] &= ~(((1 << bit_j - bit_i)-1) << bit_j);
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

char* bitarray_to_str(BitArray *self)
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

bool bitarray_reserve(BitArray* self, bitarray_size_t new_size)
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

bool bitarray_resize(BitArray* self, bitarray_size_t new_size)
{
	return _bitarray_resize_and_reserve(self, new_size);
}


bool bitarray_append(BitArray *self, size_t val)
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

bool bitarray_append_str(BitArray *self, const char* bits)
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

void bitarray_for_each(BitArray *self, void (*func)(bool), int max)
{
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	for(size_t i=0; i<max; i++)
		(*func)(bitarray_get(self, i));
}

void bitarray_transform(BitArray *self, bool(*func)(bool), int max)
{
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	bool result;
	for(size_t i=0; i<max; i++)
	{
		result = (*func)(bitarray_get(self, i));
		bitarray_set(self, result, i);
	}
}

void bitarray_iterate(BitArray *self, Biterator *iter)
{
	iter->parent = self;
	Function *cont = (Function*) iter->function;
	int max = iter->max;
	if(max < 0)
		max = _bitarray_size(self)+1+max;
	max -= iter->increment;
	bool curr;
	switch(iter->sig)
	{
		case VOID_INT:
			while(iter->curr <= max)
			{
				(*(cont->void_int_f))(bitarray_get_slice(self, 
												  iter->curr, 
												  iter->curr+iter->increment));
				iter->curr += iter->increment;
			}
			if(iter->curr <= max+iter->increment)
			{
				unsigned int diff = max+iter->increment - iter->curr;
				(*(cont->void_int_f))(bitarray_get_slice(self, 
												  iter->curr, 
												  iter->curr+diff));
				iter->curr += diff;
			}
			break;
		case INT_INT:
			while(iter->curr <= max)
			{
				curr = (*(cont->int_int_f))(bitarray_get_slice(self, 
														iter->curr, 
														iter->curr+iter->increment));
				bitarray_set(self, curr, iter->curr);
				iter->curr += iter->increment;
			}
			/* ----- NEEDS FIX ------- */
			// Fails when <= is set, but others work...
			if(iter->curr < max+iter->increment)
			{
				unsigned int diff = max+iter->increment - iter->curr;
				curr = (*(cont->int_int_f))(bitarray_get_slice(self, 
												  iter->curr, 
												  iter->curr+diff));
				bitarray_set(self, curr, iter->curr);
				iter->curr += diff;
			}
			break;
		case VOID_INT_IDX:
			while(iter->curr <= max)
			{
				(*(cont->void_int_idx_f))(bitarray_get_slice(self, 
														iter->curr, 
														iter->curr+iter->increment), 
											iter->curr);
				iter->curr += iter->increment;
			}
			if(iter->curr <= max+iter->increment)
			{
				unsigned int diff = max+iter->increment - iter->curr;
				(*(cont->void_int_idx_f))(bitarray_get_slice(self, 
												  iter->curr, 
												  iter->curr+diff),
											iter->curr);
				iter->curr += diff;
			}
			break;
		case VOID_ITER:
			/* To be implemented */
			break;
	}
};

void bitarray_map(BitArray* self, int n, BinaryMapEntry maps[])
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




typedef struct _BitArrayModule
{
	bitarray_size_t (*size)(BitArray *self);
	void (*set)(BitArray *self, bool bit, size_t index);
	void (*unset)(BitArray *self, size_t i);
	bool (*append)(BitArray *self, size_t val);
	bool (*append_str)(BitArray *self, const char* bits);
	uint8_t (*get)(BitArray *self, size_t i);
	size_t (*get_slice)(BitArray *self, size_t i, size_t j);
	void (*set_slice)(BitArray *self, size_t i, size_t j, size_t val);
	void (*fill_slice)(BitArray *self, size_t i, size_t j, bool bit);
	void (*set_slice_str)(BitArray *self, size_t i, size_t j, 
						  uint8_t flags, const char* bits);
	void (*memcpy)(BitArray* self, size_t i, size_t len, uint8_t* buffer);
	void (*bit_strcpy)(BitArray* self, size_t i, int64_t len, char* buffer);
	void (*print_bits)(BitArray* self, size_t i, int64_t len);
	void (*print_bytes)(BitArray* self, size_t i, int len);
	char* (*to_str)(BitArray *self);
	bool (*resize)(BitArray *self, size_t n);
	void (*set_allocator_size)(BitArray* self, size_t alloc_size);
	void (*for_each)(BitArray *self, void (*f)(bool), int m);
	void (*transform)(BitArray *self, bool (*f)(bool), int m);
	void (*iterate)(BitArray *self, Biterator *iter);
	void (*map)(BitArray *self, int n, BinaryMapEntry maps[]);
} BitArrayModule;

#define IMPORT_BITARRAY_MODULE_AS(m) \
BitArrayModule m = { \
	.size = &bitarray_size, \
	.set = &bitarray_set, \
	.unset = &bitarray_unset, \
	.append = &bitarray_append, \
	.append_str = &bitarray_append_str, \
	.get = &bitarray_get, \
	.get_slice = &bitarray_get_slice, \
	.set_slice = &bitarray_set_slice, \
	.fill_slice = &bitarray_fill_slice, \
	.set_slice_str = &bitarray_set_slice_str, \
	.memcpy = &bitarray_memcpy, \
	.bit_strcpy = &bitarray_bit_strcpy, \
	.print_bits = &bitarray_print_bits, \
	.print_bytes = &bitarray_print_bytes, \
	.to_str = &bitarray_to_str, \
	.resize = &bitarray_resize, \
	.set_allocator_size = &bitarray_set_allocator_size, \
	.for_each = &bitarray_for_each, \
	.transform = &bitarray_transform, \
	.iterate = &bitarray_iterate, \
	.map = &bitarray_map \
}; \


void free_BitArray_buffer(BitArray* obj)
{
	free(obj->data);
}


bool init_BitArray(BitArray* obj, bitarray_size_t size)
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


BitArray* new_BitArray(bitarray_size_t size)
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

bool init_Bitarray_from_file(BitArray* obj, const char* path)
{
	FILE *fptr = fopen(path, "rb");
	if(fptr == NULL)
		return false;
	size_t file_size;
	fseek(fptr, 0L, SEEK_END);
	file_size = ftell(fptr);
	rewind(fptr);
	// bitarray_resize(obj, (file_size << 3));
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

BitArray* new_Bitarray_from_file(const char* path)
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

void del_BitArray(BitArray* obj)
{
	free(obj->data);
	free(obj);
}


/* ---------------- DEBUG STUFF -------------------- */

void _bitarray_print_bits_prefix(BitArray* self, const char* prefix, size_t i, int64_t len)
{
	size_t max = _bitarray_size(self);
	len = (len < 0) ? (max+1+len) : len;
	printf("%s", prefix);
	for(;i<max && len; i++, len--)
		putchar(bitarray_get(self, i) ? '1' : '0');
	printf("\n");
}


#define __BPRINT _bitarray_print_bits_prefix(self, "  ", 0, -1)
#define __PDELIM_S printf("\n  [][] ========================= [][] \n")
#define __PDELIM_E printf("  [][] ========================= [][] \n")
#define __BDEBUG(x, f) printf("  " #x ": " f "\n", x)
#define __U_DEBUG(x) __BDEBUG(x, "%zu")
#define __S_DEBUG(x) __BDEBUG(x, "%s")
#define __C_DEBUG(x) __BDEBUG(x, "%c")

void _bitarray_print_info(BitArray* self)
{
	__PDELIM_S;
	__BPRINT;
	size_t len = bitarray_size(self);
	size_t num_bytes = _bitarray_num_bytes(self);
	size_t real_num_bytes = _bitarray_real_num_bytes(self);
	size_t real_num_bits = real_num_bytes << 3;
	__U_DEBUG(len);
	__U_DEBUG(num_bytes);
	__U_DEBUG(real_num_bytes);
	__U_DEBUG(real_num_bits);
	__PDELIM_E;
}

#undef __C_DEBUG
#undef __S_DEBUG
#undef __U_DEBUG
#undef __BDEBUG
#undef __PDELIM_S
#undef __PDELIM_E
#undef __BPRINT

/* ------------------------------------------------- */


#endif /* _BITARRAY_H */

