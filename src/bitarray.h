#ifndef _BITARRAY_H
#define _BITARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>

#include "bit_util.h"
#include "biterator.h"
#include "bit_defs.h"



/* ------------------------ BITARRAY ------------------------- */


typedef struct _BitArray
{
	bitarray_size_t size;
	uint8_t *data;

	#ifdef __BITARRAY_USE_OOP
	void (*set)(struct _BitArray *self, bool bit, size_t index);
	void (*unset)(struct _BitArray *self, size_t i);
	bool (*append)(struct _BitArray *self, size_t val);
	uint8_t (*get)(struct _BitArray *self, size_t i);
	size_t (*slice)(struct _BitArray *self, size_t i, size_t j);
	void (*set_slice)(struct _BitArray *self, size_t i, size_t j, size_t val);
	void (*fill_slice)(struct _BitArray *self, size_t i, size_t j, size_t val);
	char* (*to_str)(struct _BitArray *self);
	bool (*resize)(struct _BitArray *self, size_t n);
	void (*for_each)(struct _BitArray *self, void (*f)(bool), int m);
	void (*transform)(struct _BitArray *self, bool (*f)(bool), int m);
	void (*iterate)(struct _BitArray *self, Biterator *iter);
	#endif

} BitArray;


/* ------------------------------------------------------------ */




static inline bitarray_size_t bitarray_size(BitArray *self)
{
	return bitarray_lmask & self->size;
}


static inline bitarray_size_t bitarray_num_bytes(BitArray *self)
{
	if(self->size & 0b111)
		return ((bitarray_size(self) >> 3)+1);
	else
		return (bitarray_size(self) >> 3);
}

static inline bool bitarray_needs_new_byte(BitArray *self)
{
	return !(self->size & 0b111);
}

static inline bitarray_size_t bitarray_flags(BitArray *self)
{
	return self->size & bitarray_umask;
}


static inline void bitarray_set_size(BitArray *self, bitarray_size_t size)
{
	self->size = (self->size & bitarray_umask) | size;
}

static inline void bitarray_incr_size(BitArray *self, bitarray_size_t incr)
{
	bitarray_set_size(self, bitarray_size(self) + incr);
}



void bitarray_set_err(BitArray* self, bitarray_size_t err)
{
	self->size |= err;
}


void bitarray_unset_err(BitArray* self, bitarray_size_t err)
{
	self->size &= ~err;
}


void bitarray_clear_all_err(BitArray* self)
{
	self->size &= bitarray_lmask;
}


bool bitarray_check_err(BitArray* self, bitarray_size_t err)
{
	return (self->size & err) ? true : false;
}

bool bitarray_check_status(BitArray* self)
{
	return (self->size & BITARRAY_ERR_MASK) ? true : false;
}







void bitarray_set(BitArray *self, bool bit, size_t i)
{
	if(i >= bitarray_size(self))
		bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);

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
	if(i >= bitarray_size(self))
		bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);

	size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] &= ~(1 << (7-bit_index));
}


uint8_t bitarray_get(BitArray *self, size_t i)
{
	if(i >= bitarray_size(self))
		bitarray_set_err(self, BITARRAY_ILL_ERR_FLAG);
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	uint8_t masker = 1 << (7-bit_index);
	masker = (self->data[byte_index] & masker) >> (7-bit_index);
	return masker;
}


size_t bitarray_slice(BitArray *self, size_t i, size_t j)
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

void bitarray_set_slice(BitArray *self, size_t i, size_t j, size_t val)
{
	size_t byte_i = _byte_part(i), byte_j = _byte_part(j);
	uint8_t bit_i = _bit_part(i), bit_j = _bit_part(j);
	size_t bit_w = bit_width(val);

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

	size_t byte_w = byte_size(bit_w);
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
			switch(bit)
			{
				case 0:
					self->data[byte_j] &= ~(((1 << bit_j - bit_i)-1) << bit_j);
				case 1:
					self->data[byte_j] |= ((1 << bit_j - bit_i)-1) << bit_j;
			}
			return;
		}
		else
		{
			switch(bit)
			{
				case 0:
					self->data[byte_j] &= ~((1 << (7-bit_j))-1);
				case 1:
					self->data[byte_j] |= (1 << (7-bit_j))-1;
			}
			byte_j--;
		}
	}
	
	uint8_t fill = (bit) ? 0xFF : 0;
	while(byte_j != byte_i)
	{
		self->data[byte_j] = fill;
		byte_j--;
	}
	switch(bit)
	{
		case 0:
			self->data[byte_i] &= ~((1 << (7-bit_i)) - 1);
		case 1:
			self->data[byte_i] |= (1 << (7-bit_i)) - 1;
	}
}

char* bitarray_to_str(BitArray *self)
{
	char* repr = (char *) calloc((bitarray_size(self))+3, sizeof(char));
	if(repr == NULL)
	{
		bitarray_set_err(self, BITARRAY_MEM_ERR_FLAG);
		return NULL;
	}
	uint8_t curr;
	repr[0] = '0';
	repr[1] = 'b';
	for(size_t i=0; i<bitarray_size(self); i++)
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
	repr[bitarray_size(self)+2] = '\0';
	return repr;
}



bool bitarray_resize(BitArray* self, bitarray_size_t new_size)
{
	bitarray_size_t new_memsize = byte_size(new_size);
	if(!new_memsize)
		new_memsize = 1;

	uint8_t* new = (uint8_t*) realloc(self->data, new_memsize);
	if(new == NULL)
	{
		free(self->data);
		bitarray_set_err(self, BITARRAY_MEM_ERR_FLAG);
		return false;
	}
	uint8_t diff = _bit_part(new_size);
	bitarray_size_t n_bytes = bitarray_num_bytes(self);

	if(new_memsize > n_bytes)
		memset(&new[n_bytes], 0, new_memsize-n_bytes);
	else if(diff)
	{
		uint8_t mask = ~((1 << (8-diff)) - 1);
		new[new_memsize-1] &= mask;
	}

	bitarray_set_size(self, new_size);
	self->data = new;
	return true;
}

bool bitarray_append(BitArray *self, size_t val)
{
	size_t w = bit_width(val);
	size_t byte_w = byte_size(w);
	bitarray_size_t n_bytes = bitarray_num_bytes(self);
	uint8_t fill = _bit_part(self->size);
	uint8_t remaining = 8-fill;
	if(fill && w <= remaining)
	{
		self->data[n_bytes-1] |= val << (remaining - w);
		bitarray_incr_size(self, w);
	}
	else
	{
		if(fill)
		{
			// uint8_t shifted_val = val >> (w + ((byte_w-1)<<3) - remaining);
			uint8_t shifted_val = val >> (w - remaining);
			self->data[n_bytes-1] |= shifted_val;
			bitarray_incr_size(self, remaining);
			w -= remaining;
			val &= ((1 << w) - 1);
		}

		bitarray_size_t prev_num_bits = bitarray_size(self);
		if(!bitarray_resize(self, prev_num_bits+w))
			return false;
		size_t mask = 1 << (w-1);
		w += prev_num_bits;
		for(size_t i=prev_num_bits;i<w;i+=1)
		{
			if(val & mask)
				bitarray_set(self, true, i);
			mask >>= 1;
		}
	}
	return true;

}


void bitarray_for_each(BitArray *self, void (*func)(bool), int max)
{
	if(max < 0)
		max = bitarray_size(self)+1+max;
	for(size_t i=0; i<max; i++)
	{
		(*func)(bitarray_get(self, i));
	}
}

void bitarray_transform(BitArray *self, bool(*func)(bool), int max)
{
	if(max < 0)
		max = bitarray_size(self)+1+max;
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
		max = bitarray_size(self)+1+max;
	max -= iter->increment;
	bool curr;
	switch(iter->sig)
	{
		case VOID_INT:
			while(iter->curr <= max)
			{
				(*(cont->void_int_f))(bitarray_slice(self, 
												  iter->curr, 
												  iter->curr+iter->increment));
				iter->curr += iter->increment;
			}
			if(iter->curr <= max+iter->increment)
			{
				unsigned int diff = max+iter->increment - iter->curr;
				(*(cont->void_int_f))(bitarray_slice(self, 
												  iter->curr, 
												  iter->curr+diff));
				iter->curr += diff;
			}
			break;
		case INT_INT:
			while(iter->curr <= max)
			{
				curr = (*(cont->int_int_f))(bitarray_slice(self, 
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
				curr = (*(cont->int_int_f))(bitarray_slice(self, 
												  iter->curr, 
												  iter->curr+diff));
				bitarray_set(self, curr, iter->curr);
				iter->curr += diff;
			}
			break;
		case VOID_INT_IDX:
			while(iter->curr <= max)
			{
				(*(cont->void_int_idx_f))(bitarray_slice(self, 
														iter->curr, 
														iter->curr+iter->increment), 
											iter->curr);
				iter->curr += iter->increment;
			}
			if(iter->curr <= max+iter->increment)
			{
				unsigned int diff = max+iter->increment - iter->curr;
				(*(cont->void_int_idx_f))(bitarray_slice(self, 
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


typedef struct _BitArrayModule
{
	void (*set)(BitArray *self, bool bit, size_t index);
	void (*unset)(BitArray *self, size_t i);
	bool (*append)(BitArray *self, size_t val);
	uint8_t (*get)(BitArray *self, size_t i);
	size_t (*slice)(BitArray *self, size_t i, size_t j);
	void (*set_slice)(BitArray *self, size_t i, size_t j, size_t val);
	void (*fill_slice)(BitArray *self, size_t i, size_t j, bool bit);
	char* (*to_str)(BitArray *self);
	bool (*resize)(BitArray *self, size_t n);
	void (*for_each)(BitArray *self, void (*f)(bool), int m);
	void (*transform)(BitArray *self, bool (*f)(bool), int m);
	void (*iterate)(BitArray *self, Biterator *iter);
} BitArrayModule;

#define IMPORT_BITARRAY_MODULE_AS(m) \
BitArrayModule m = { \
	.set = &bitarray_set, \
	.unset = &bitarray_unset, \
	.append = &bitarray_append, \
	.get = &bitarray_get, \
	.slice = &bitarray_slice, \
	.set_slice = &bitarray_set_slice, \
	.fill_slice = &bitarray_fill_slice, \
	.to_str = &bitarray_to_str, \
	.resize = &bitarray_resize, \
	.for_each = &bitarray_for_each, \
	.transform = &bitarray_transform, \
	.iterate = &bitarray_iterate \
}; \



bool init_BitArray(BitArray* obj, bitarray_size_t size)
{
	bitarray_size_t num_bytes = byte_size(size);
	uint8_t* data = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
	if(data == NULL)
	{
		bitarray_set_err(obj, BITARRAY_MEM_ERR_FLAG);
		return false;
	}

	memset(data, 0, num_bytes);
	bitarray_set_size(obj, size);
	obj->data = data;

	#ifdef __BITARRAY_USE_OOP

	obj->set = bitarray_set;
	obj->unset = bitarray_unset;
	obj->get = bitarray_get;
	obj->slice = bitarray_slice;
	obj->set_slice = bitarray_set_slice;
	obj->fill_slice = bitarray_fill_slice;
	obj->append = bitarray_append;
	obj->resize = bitarray_resize;
	obj->to_str = bitarray_to_str;
	obj->for_each = bitarray_for_each;
	obj->transform = bitarray_transform;
	obj->iterate = bitarray_iterate;

	#endif

	return true;
}


BitArray* new_BitArray(bitarray_size_t size)
{
	bitarray_size_t num_bytes = byte_size(size);
	
	BitArray* new = (BitArray *) malloc(sizeof(BitArray));
	if(new == NULL)
	{
		return NULL;
	}
	uint8_t* data = (uint8_t *) calloc(num_bytes, sizeof(uint8_t));
	if(data == NULL)
	{
		free(new);
		return NULL;
	}

	memset(data, 0, num_bytes);
	bitarray_set_size(new, size);
	new->data = data;

	#ifdef __BITARRAY_USE_OOP

	new->set = bitarray_set;
	new->unset = bitarray_unset;
	new->get = bitarray_get;
	new->slice = bitarray_slice;
	new->set_slice = bitarray_set_slice;
	new->fill_slice = bitarray_fill_slice;
	new->append = bitarray_append;
	new->resize = bitarray_resize;
	new->to_str = bitarray_to_str;
	new->for_each = bitarray_for_each;
	new->transform = bitarray_transform;
	new->iterate = bitarray_iterate;

	#endif

	return new;
}


void del_BitArray(BitArray* obj)
{
	free(obj->data);
	free(obj);
}


#endif /* _BITARRAY_H */

