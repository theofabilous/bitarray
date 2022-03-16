#include "../src/bitarray.h"
IMPORT_BITARRAY_MODULE_AS(Bits);


void display_bits(BitArray *obj)
{
	char *brepr = Bits.to_str(obj);
	printf("%s  (size: %d)\n", brepr, obj->size);
	free(brepr);
}

int counter;

void for_each_test(bool bit)
{
	if(bit)
		counter += 1;
}

size_t transform_test(bool bit)
{
	if(bit)
		return 0;
	else
		return 1;
}

void do_bit(size_t bit)
{
	if(bit)
		printf("1");
	else
		printf("0");
}

void do_slice(size_t val)
{
	print_bit_repr_size(val, 3);
	// print_bit_repr(val);
}

void do_bit_index(size_t bit, int index)
{
	printf("bit: %d, index: %d\n", bit, index);
}

void gen_iter_test(BitArray *bits)
{
	printf("* ----- Running basic iterator tests... ----- *\n\n");
	counter = 0;
	Bits.for_each(bits, for_each_test, -1);
	printf("Count: %d\n", counter);
	Bits.transform(bits, transform_test, -1);
	display_bits(bits);
	printf("\n ** FINISHED **\n\n");
}

void custom_iter_test_alloc(BitArray *obj)
{
	printf("* --- Running custom iterator tests... --- *\n\n");
	Biterator *it = new_Biterator(1, -1, VOID_INT, do_bit);            
	Bits.iterate(obj, it);
	printf("\n");
	del_Biterator(it, true);

	it = new_Biterator(1, -1, INT_INT, transform_test);
	Bits.iterate(obj, it);
	Bits.for_each(obj, do_bit, -1);
	printf("\n");
	detach_Biterator(it);
	Bits.iterate(obj, it);
	del_Biterator(it, true);
	Bits.for_each(obj, do_bit, -1);
	printf("\n");

	it = new_Biterator(1, -1, VOID_INT_IDX, do_bit_index);
	Bits.iterate(obj, it);
	del_Biterator(it, true);

	it = new_Biterator(3, -1, VOID_INT, do_slice);
	Bits.iterate(obj, it);
	del_Biterator(it, true);
	printf("\n ** FINISHED **\n\n");
}

void run_manipulation_tests(BitArray *bits)
{
	printf("* --- Running general tests... --- *\n\n");
	display_bits(bits);
	Bits.set(bits, 1, 0);
	Bits.set(bits, 1, 3);
	display_bits(bits);
	Bits.resize(bits, 15);
	display_bits(bits);
	Bits.resize(bits, 3);
	display_bits(bits);
	Bits.append(bits, 0b1000);
	Bits.append(bits, 0b1011);
	Bits.append(bits, 0xFF);
	display_bits(bits);
	printf("[%d:%d] %d, ", 0, 4, Bits.slice(bits, 0, 4));
	print_bit_repr(Bits.slice(bits, 0, 4));

	printf("\n ** FINISHED **\n\n");
}

void readme_get_started()
{
	BitArray *bits = new_BitArray(12); // Initiliaze with 12 bits (all zero by default)
	Bits.set(bits, true, 0); // set first bit to 1
	Bits.set(bits, true, 5);

	char *str = Bits.to_str(bits);
	printf("%s\n", str); // prints 0b100001000000
	free(str);

	Bits.resize(bits, 6);

	str = Bits.to_str(bits);
	printf("%s\n", str); // prints 0b100001
	free(str);

	Bits.append(bits, 0b1101);
	str = Bits.to_str(bits);
	printf("%s\n", str); // prints 0b1000011101
	free(str);

	del_BitArray(bits);
}

size_t _counter;

void count_bits(bool bit)
{
	_counter += bit;
}

void print_bits(bool bit)
{
	printf("%d", bit);
}

bool flip_bits(bool bit)
{
	return !bit;
}

void readme_iter_simple()
{
	BitArray *bits = new_BitArray(0);
	Bits.append(bits, 0b100000010101111000011);
	
	_counter = 0;
	Bits.for_each(bits, count_bits, -1); // second arg is the function, third is max
										  // (where -1 means size of bitarray)
	printf("counter: %d\n", _counter); // prints 9
	
	Bits.for_each(bits, print_bits, -1); // prints each bit
	printf("\n"); 

	Bits.transform(bits, flip_bits, -1);
	Bits.for_each(bits, print_bits, -1); // prints each bit
	printf("\n"); 

	del_BitArray(bits);
}

void new_tests(BitArray* bits)
{
	
}

int main()
{
	BitArray *bits = new_BitArray(12);
	run_manipulation_tests(bits);
	gen_iter_test(bits);
	// custom_iter_test(bits);
	custom_iter_test_alloc(bits);
	del_BitArray(bits);

	readme_get_started();
	readme_iter_simple();

	return 0;
}