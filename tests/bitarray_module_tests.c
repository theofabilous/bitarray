#include "../src/bitarray.h"


IMPORT_BITARRAY_MODULE_AS(Bits);

int main()
{
	BitArray *obj = new_BitArray(0);
	Bits.append(obj, 0b11111111000110010);
	char *repr = Bits.to_str(obj);
	printf("%s\n", repr);
	free(repr);
	Bits.set_slice(obj, 0, 5, 0b10101);
	repr = Bits.to_str(obj);
	printf("%s\n", repr);
	free(repr);
	del_BitArray(obj);
	return 0;
}