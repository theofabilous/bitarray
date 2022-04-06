#ifndef _BIT_UTIL_H
#define _BIT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>

#define bit_cast_voidify(t, x) *((t*)((void *)(&x)))
#define bit_cast(t, x) *((t *)&x)

extern const uint8_t LEFT_MOST_MASKS[9];

extern const uint8_t RIGHT_MOST_MASKS[9];

static inline size_t _byte_part(size_t n)
{
	return n >> 3;
}

static inline uint8_t _bit_part(size_t n)
{
	return n & 0b111;
}

static inline uint8_t get_lr_mask(uint8_t i, uint8_t j)
{
	return LEFT_MOST_MASKS[i] | RIGHT_MOST_MASKS[j];
}

static inline size_t 
_bit_width(size_t num)
{
	if(num > (size_t) INT_MAX)
	{
		size_t sum = 0;
		size_t curr;
		for(;num>=(size_t) INT_MAX; num>>=16)
			sum+=16;
		return sum + _bit_width(num);
	}
	else if(num)
		return 1 + (size_t) floor(log2(num));
	else
		return 0;
}

static inline size_t 
_byte_size(size_t bitsize)
{
	size_t num_bytes = bitsize >> 3;
	if(bitsize & 0b111)
		return num_bytes+1;
	else
		return num_bytes;
}

char* bit_repr(size_t num);

void print_bit_repr(size_t num);

void print_bit_repr_size(size_t num, size_t w);

#endif /* _BIT_UTIL_H */
