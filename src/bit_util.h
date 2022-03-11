#ifndef _BIT_UTIL_H
#define _BIT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

// uint8_t BIT_WIDTH_TABLE[] =
// {

// };

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
	{
		printf("Memory could not be allocated\n");
		exit(1);
	}
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