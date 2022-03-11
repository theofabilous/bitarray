#define BITARRAY_MODULE Bits

#include "../src/bitarray.h"

int main()
{
	BitArray *obj = new_BitArray(0);
	Bits.append(obj, 0b11111111000110010);
	char *repr = Bits.to_str(obj);
	printf("%s\n", repr);
	free(repr);
	del_BitArray(obj);

	printf("%zu\n", bitarray_umask);
	printf("%u\n", bitarray_umask_amt);
	printf("%zu\n", bitarray_lmask);

	print_bit_repr(bitarray_umask);
	print_bit_repr(bitarray_lmask);
	return 0;
}