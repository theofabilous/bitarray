#include "bit_util.h"

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

char* bit_repr(size_t num)
{
    size_t w = _bit_width(num);
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
    size_t w = _bit_width(num);
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
