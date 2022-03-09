#ifndef _BIT_UTIL_H
#define _BIT_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int bit_width(int num)
{
	if(num)
		return 1 + (int) floor(log2(num));
	else
		return 0;
}

int byte_size(int bitsize)
{
	int num_bytes = bitsize / 8;
	if(num_bytes * 8 < bitsize)
	{
		num_bytes++;
	}
	return num_bytes;
}

char* bit_repr(size_t num)
{
	int w = bit_width(num);
	char* bits = (char *) calloc(w+1, sizeof(char));
	if(bits == NULL)
	{
		printf("Memory could not be allocated\n");
		exit(1);
	}
	unsigned int mask = 1 << (w-1);
	for(size_t i = 0; i<w; i++, mask >>= 1)
	{
		bits[i] = (num & mask) ? '1' : '0';
	}
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
	int w = bit_width(num);
	unsigned int mask = 1 << (w-1);
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