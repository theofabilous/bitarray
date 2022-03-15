#ifndef _BIT_UTIL_H
#define _BIT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// :D
#define bit_cast_voidify(t, x) *((t*)((void *)(&x)))
#define bit_cast(t, x) *((t *)&x)

const uint8_t LEFT_MOST_MASKS[9] = 
{
	0, 0b10000000, 0b11000000, 0b11100000,
	0b11110000, 0b11111000, 0b11111100, 0b11111110,
	0xFF
};

const uint8_t RIGHT_MOST_MASKS[9] = 
{
	0, 1, 0b11, (1 << 4)-1, (1 << 5)-1,
	(1 << 6)-1, (1 << 7)-1, 0b01111111, 0xFF
};



/* ----------------------- */

static size_t inline _byte_part(size_t n)
{
	return n >> 3;
}

static uint8_t inline _bit_part(size_t n)
{
	return n & 0b111;
}

static uint8_t inline get_lr_mask(uint8_t i, uint8_t j)
{
	return LEFT_MOST_MASKS[i] | RIGHT_MOST_MASKS[j];
}

/* ----------------------- */


size_t bit_width(size_t num)
{
	if(num > (size_t) INT_MAX)
	{
		size_t sum = 0;
		size_t curr;
		for(;num>=(size_t) INT_MAX; num>>=16)
			sum+=16;
		return sum + bit_width(num);
	}
	else if(num)
		return 1 + (size_t) floor(log2(num));
	else
		return 0;
}

// should this return 1 if bitsize is zero?
size_t byte_size(size_t bitsize)
{
	size_t num_bytes = bitsize >> 3;
	if(bitsize & 0b111)
		return num_bytes+1;
	else
		return num_bytes;
}

char* bit_repr(size_t num)
{
    size_t w = bit_width(num);
	char* bits = (char *) calloc(w+1, sizeof(char));
	if(bits == NULL)
		return NULL;
    size_t mask = 1 << (w-1);

	for(size_t i = 0; i<w; i++, mask >>= 1)
		bits[i] = (num & mask) ? '1' : '0';
	
	bits[w] = '\0';
	return bits;
}


void print_bit_repr(size_t num)
{
	if(num == 0)
	{
		printf("0\n");
		return;
	}
    size_t w = bit_width(num);
	size_t mask = ((size_t)1) << (w-1);
	char curr;
	for(size_t i = 0; i<w; i++, mask >>= 1)
	{
		curr = (num & mask) ? '1' : '0';
		printf("%c", curr);
	}
	printf("\n");
}

void print_bit_repr_size(size_t num, size_t w)
{
	unsigned int mask = 1 << (w-1);
	char curr;
	for(size_t i = 0; i<w; i++, mask >>= 1)
	{
		curr = (num & mask) ? '1' : '0';
		printf("%c", curr);
	}
	printf("\n");
}


#endif /* _BIT_UTIL_H */
