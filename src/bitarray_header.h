#ifndef _BITARRAY_HEADER_H
#define _BITARRAY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <signal.h>
#include <stdarg.h>

#include "util/bit_util.h"
#include "util/bit_defs.h"
#include "binarymap.h"

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
	void (*set_allocator_size)(BitArray* self, size_t alloc_size);
	void (*for_each)(BitArray *self, void (*f)(bool), int64_t m);
	void (*transform)(BitArray *self, bool (*f)(bool), int64_t m);
	void (*enumerate_each)(BitArray* self, void (*func)(bool bit, size_t index),
						   int64_t max);
	void (*map)(BitArray *self, BinaryMapEntry maps[], size_t n);
} BitArrayModule;

/* ---------------- CONSTANTS ---------------- */

const bit_allocator_t BIT_ALLOC_SIZE_MASK = 0xFFFF0000;
const bit_allocator_t BIT_ALLOC_EXTRA_MASK = 0xFFFF;
const uint8_t STRIP_MSB = 0b0001;
const uint8_t STRIP_LSB = 0b0000;

/* ------------------------------------------- */


/* ------------ PRIVATE FUNCTIONS ------------ */

static inline void 
_bitarray_set_extra_bytes(
	BitArray* self, 
	size_t extra_bytes);

static inline size_t 
_bitarray_get_extra_bytes(
	BitArray* self);

static inline size_t 
_bitarray_get_alloc_size_bytes(
	BitArray* self);

static inline size_t 
_bitarray_get_alloc_size_bits(
	BitArray* self);

static inline void 
_bitarray_set_alloc_size_bytes(
	BitArray* self,
	size_t alloc_size);

static inline void 
_bitarray_set_on(
	BitArray *self,
	size_t i);

static inline void 
_bitarray_set_off(
	BitArray *self,
	size_t i);

static inline bool 
_bitarray_get(
	BitArray *self,
	size_t i);

static inline bitarray_size_t 
_bitarray_size(
	BitArray *self);

static inline bitarray_size_t 
_bitarray_num_bytes(
	BitArray *self);

static inline bitarray_size_t 
_bitarray_real_num_bytes(
	BitArray *self);

static inline bitarray_size_t 
_bitarray_real_num_bits(
	BitArray *self);

static inline bool 
_bitarray_actually_needs_resize_bits(
	BitArray *self,
	size_t num_bits);

static inline bitarray_size_t 
_bitarray_flags(
	BitArray *self);

static inline void 
_bitarray_set_size(
	BitArray *self,
	bitarray_size_t size);

static inline void 
_bitarray_incr_size(
	BitArray *self,
	bitarray_size_t incr);

static inline void 
_bitarray_set_err(
	BitArray* self,
	bitarray_size_t err);

static inline bool 
_bitarray_reserve(
	BitArray* self,
	bitarray_size_t new_size);

static inline void 
_bitarray_resize_quick(
	BitArray* self,
	bitarray_size_t new_size);

static inline bool 
_bitarray_resize_and_reserve(
	BitArray* self,
	bitarray_size_t new_size);

void 
_bitarray_print_info(
	BitArray* self);

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


#endif /* _BITARRAY_HEADER_H */