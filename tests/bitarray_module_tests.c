#include "../src/bitarray.h"


IMPORT_BITARRAY_MODULE_AS(Bits);

void slice_test()
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
}

void map_test()
{
	BitArray arr;
	init_BitArray(&arr, 0);
	_bitarray_print_info(&arr);
	Bits.append(&arr, 0b11110101010);
	_bitarray_print_info(&arr);
	Bits.print_bits(&arr, 0, -1);
	
	Bits.resize(&arr, 8);
	_bitarray_print_info(&arr);
	Bits.resize(&arr, 10);
	_bitarray_print_info(&arr);

	Bits.resize(&arr, 130);
	_bitarray_print_info(&arr);

	Bits.resize(&arr, 8);
	_bitarray_print_info(&arr);
	Bits.resize(&arr, 10);
	_bitarray_print_info(&arr);

	Bits.append_str(&arr, "00000001");
	_bitarray_print_info(&arr);

	Bits.set_slice_str(&arr, 10, 18, 0, "10");
	Bits.print_bits(&arr, 0, -1);

	Bits.resize(&arr, 0);
	Bits.append_str(&arr, "1001110100000");
	Bits.map(&arr, 
				bitarray_as_map(
				{"1001", "0110"}, 
				{"1101", "1010"},
				{"00000", "11101"}) );
	Bits.print_bits(&arr, 0, -1);

	free_BitArray_buffer(&arr);
}

void test_func(char arr[], int size)
{
	for(int i=0; i<size; i++)
		printf("%c\n", arr[i]);
}

int main()
{
	map_test();
	test_func( ((char[]){'a', 'b', 'c'}),  3);
	// slice_test();
	return 0;
}