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
#include "binarymap.h"

#define __PASS__ ((void) 0)

#ifdef _MSC_VER
    #define bitarray_force_inline __forceinline
#elif defined(__GNUC__)
	#define bitarray_force_inline __attribute__((always_inline))
#elif (defined (__APPLE__) && defined (__MACH__))
	#define bitarray_force_inline static inline
#else
	#define bitarray_force_inline
#endif

// https://graphics.stanford.edu/~seander/bithacks.html
// #if defined(__builtin_ctz)
// 	#define CNT_TRZ __builtin_ctz
// #elif defined(_BitScanForward)
// 	#define CNT_TRZ _BitScanForward
// #else
// 	// #error "No builtins found to count trailing zeros"
// #endif

#ifndef BITARRAY_SIZE_T
#define BITARRAY_SIZE_T size_t
#endif

typedef BITARRAY_SIZE_T bitarray_size_t;

typedef size_t bit_allocator_t;

typedef struct BitArray
{
	bitarray_size_t size;
	bit_allocator_t allocator;
	uint8_t *data;
} BitArray;

typedef struct BitArrayModule
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
	void (*print_bytes)(BitArray* self, size_t i, int64_t len);
	char* (*to_str)(BitArray *self);
	bool (*resize)(BitArray *self, size_t n);
	bool (*reserve)(BitArray* self, bitarray_size_t new_size);
	void (*set_allocator_size)(BitArray* self, size_t alloc_size);
	void (*for_each)(BitArray *self, void (*f)(bool), int64_t m);
	void (*transform)(BitArray *self, bool (*f)(bool), int64_t m);
	void (*enumerate_each)(BitArray* self, void (*func)(bool bit, size_t index),
						   int64_t max);
	void (*map)(BitArray *self, BinaryMapEntry maps[], size_t n);
	bool (*map_into)(BitArray* self, BitArray* other, BinaryMapEntry maps[], size_t n);
} BitArrayModule;

/* ---------------- CONSTANTS ---------------- */

extern uint8_t _bitarray_ssize_t;
extern uint8_t _bitarray_ssize_t_bits;
extern const bitarray_size_t BITARRAY_S_ONE;
extern const bitarray_size_t BITARRAY_S_ZERO;
extern const bitarray_size_t BITARRAY_S_THREE;
extern bitarray_size_t bitarray_umask;
extern uint8_t bitarray_umask_amt;
extern bitarray_size_t bitarray_lmask;
extern bitarray_size_t bitarray_max_bytes;
extern bitarray_size_t BITARRAY_MEM_ERR_FLAG;
extern bitarray_size_t BITARRAY_ILL_ERR_FLAG;
extern bitarray_size_t BITARRAY_FLAG1;
extern bitarray_size_t BITARRAY_FLAG2;
extern bitarray_size_t BITARRAY_ERR_MASK;

extern const bit_allocator_t BIT_ALLOC_SIZE_MASK;
extern const bit_allocator_t BIT_ALLOC_EXTRA_MASK;
extern const uint8_t STRIP_MSB;
extern const uint8_t STRIP_LSB;

/* ------------------------------------------- */


/* -------- INSTANTIATING / DELETING --------- */

void 
free_BitArray_buffer(
	BitArray* obj);

bool 
init_BitArray(
	BitArray* obj,
	bitarray_size_t size);

BitArray* 
new_BitArray(
	bitarray_size_t size);

bool 
init_Bitarray_from_file(
	BitArray* obj,
	const char* path);

BitArray* 
new_Bitarray_from_file(
	const char* path);

void 
del_BitArray(
	BitArray* obj);

/* ------------------------------------------- */


/* ------------------ SIZE ------------------- */

void 
bitarray_set_allocator_size(
	BitArray* self,
	size_t alloc_size);

bitarray_size_t 
bitarray_size(
	BitArray *self);

bool 
bitarray_reserve(
	BitArray* self,
	bitarray_size_t new_size);

bool 
bitarray_resize(
	BitArray* self,
	bitarray_size_t new_size);

/* ------------------------------------------- */

/* ---------------- SETTING ------------------ */

void 
bitarray_set(
	BitArray *self,
	bool bit,
	size_t i);

void 
bitarray_unset(
	BitArray *self,
	size_t i);

void 
bitarray_set_byte(
	BitArray* self,
	uint8_t byte,
	size_t i);

void 
bitarray_set_slice(
	BitArray *self, 
	size_t i, 
	size_t j, 
	size_t val);

void 
bitarray_set_slice_str(
	BitArray *self, 
	size_t i, 
	size_t j, 
	uint8_t flags, 
	const char* bits);

void 
bitarray_fill_slice(
	BitArray *self, 
	size_t i, 
	size_t j, 
	bool bit);

bool 
bitarray_append(
	BitArray *self, 
	size_t val);

bool 
bitarray_append_str(
	BitArray *self, 
	const char* bits);

/* ------------------------------------------- */


/* ---------------- GETTING ------------------ */

uint8_t 
bitarray_get(
	BitArray *self,
	size_t i);

uint8_t 
bitarray_get_byte(
	BitArray* self, 
	size_t i);

size_t 
bitarray_get_slice(
	BitArray *self, 
	size_t i, 
	size_t j);

void 
bitarray_memcpy(
	BitArray* self,
	size_t i, 
	size_t len, 
	uint8_t* buffer);

void 
bitarray_bit_strcpy(
	BitArray* self, 
	size_t i, 
	int64_t len, 
	char* buffer);

void 
bitarray_print_bits(
	BitArray* self, 
	size_t i, 
	int64_t len);

void 
bitarray_print_bytes(
	BitArray* self, 
	size_t i, 
	int64_t len);

char* 
bitarray_to_str(
	BitArray *self);

/* ------------------------------------------- */


/* --------------- ITERATING ----------------- */

void 
bitarray_for_each(
	BitArray *self,
	void (*func)(bool),
	int64_t max);

void
bitarray_transform(
	BitArray *self, 
	bool(*func)(bool), 
	int64_t max);

void
bitarray_enumerate_each(
	BitArray* self,
	void (*func)(bool bit, size_t index),
	int64_t max);

void 
bitarray_map(
	BitArray* self,
	BinaryMapEntry maps[],
    size_t n);

bool
bitarray_map_into(
	BitArray* self,
	BitArray* other,
	BinaryMapEntry maps[],
	size_t n);

/* ------------------------------------------- */


/* ------------- ERROR HANDLING -------------- */

void 
bitarray_unset_err(
	BitArray* self,
	bitarray_size_t err);

void 
bitarray_clear_all_err(
	BitArray* self);

bool 
bitarray_check_err(
	BitArray* self,
	bitarray_size_t err);

bool 
bitarray_check_status(
	BitArray* self);

/* ------------------------------------------- */



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
	.reserve = &bitarray_reserve, \
	.set_allocator_size = &bitarray_set_allocator_size, \
	.for_each = &bitarray_for_each, \
	.transform = &bitarray_transform, \
	.enumerate_each = &bitarray_enumerate_each, \
	.map = &bitarray_map, \
	.map_into = &bitarray_map_into \
};


static inline void 
_bitarray_set_extra_bytes(
	BitArray* self, 
	size_t extra_bytes)
{ 
	self->allocator = ((self->allocator & BIT_ALLOC_SIZE_MASK) 
						| (BIT_ALLOC_EXTRA_MASK & extra_bytes)); 
}

static inline size_t 
_bitarray_get_extra_bytes(
	BitArray* self)
{ 
	return self->allocator & BIT_ALLOC_EXTRA_MASK;
}

static inline size_t 
_bitarray_get_alloc_size_bytes(
	BitArray* self)
{ 
	return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 16; 
}

static inline size_t 
_bitarray_get_alloc_size_bits(
	BitArray* self)
{ 
	return (self->allocator & BIT_ALLOC_SIZE_MASK) >> 13; 
}

static inline void 
_bitarray_set_alloc_size_bytes(
	BitArray* self, 
	size_t alloc_size)
{ 
	if(!alloc_size) alloc_size = 1;
	self->allocator = (self->allocator & BIT_ALLOC_EXTRA_MASK) 
						| ((0xFFFF & alloc_size) << 16);
}

static inline void 
_bitarray_set_on(
	BitArray *self, 
	size_t i)
{
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] |= (1 << (7-bit_index));
}

static inline void 
_bitarray_set_off(
	BitArray *self, 
	size_t i)
{
	bitarray_size_t byte_index = _byte_part(i);
	uint8_t bit_index = _bit_part(i);
	self->data[byte_index] &= ~(1 << (7-bit_index));
}

static inline bool 
_bitarray_get(
	BitArray *self,
	size_t i)
{
	uint8_t r_bit_index = 7 - (i & 0b111);
	return (self->data[i >> 3] & (1 << r_bit_index)) >> r_bit_index;
}

static inline bitarray_size_t 
_bitarray_size(
	BitArray *self)
{
	return bitarray_lmask & self->size;
}

static inline bitarray_size_t 
_bitarray_num_bytes(
	BitArray *self)
{
	if(self->size & 0b111)
		return ((_bitarray_size(self) >> 3)+1);
	else
		return (_bitarray_size(self) >> 3);
}

static inline bitarray_size_t 
_bitarray_real_num_bytes(
	BitArray *self)
{
	return _bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self);
}

static inline bitarray_size_t 
_bitarray_real_num_bits(
	BitArray *self)
{
	return (_bitarray_num_bytes(self) + _bitarray_get_extra_bytes(self)) << 3;
}

static inline bool 
_bitarray_actually_needs_resize_bits(
	BitArray *self, 
	size_t num_bits)
{
	return _byte_size(num_bits) > _bitarray_real_num_bytes(self);
}

static inline bitarray_size_t 
_bitarray_flags(
	BitArray *self)
{
	return self->size & bitarray_umask;
}

static inline void 
_bitarray_set_size(
	BitArray *self, 
	bitarray_size_t size)
{
	self->size = (self->size & bitarray_umask) | size;
}

static inline void 
_bitarray_incr_size(
	BitArray *self, 
	bitarray_size_t incr)
{
	_bitarray_set_size(self, _bitarray_size(self) + incr);
}

static inline void 
_bitarray_set_err(
	BitArray* self, 
	bitarray_size_t err)
{
	self->size |= err;
}

static inline bool 
_bitarray_reserve(
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

static inline void 
_bitarray_resize_quick(
	BitArray* self, 
	bitarray_size_t new_size)
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
_bitarray_resize_and_reserve(
	BitArray* self, 
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



#endif /* _BITARRAY_HEADER_H */