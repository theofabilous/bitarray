#include "../src/bitarray.h"


void display_bits(BitArray *obj)
{
    char *brepr = obj->to_str(obj);
    printf("%s  (size: %d)\n", brepr, obj->num_bits);
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
    bits->for_each(bits, for_each_test, -1);
    printf("Count: %d\n", counter);
    bits->transform(bits, transform_test, -1);
    display_bits(bits);
    printf("\n ** FINISHED **\n\n");
}

void custom_iter_test_alloc(BitArray *obj)
{
    printf("* --- Running custom iterator tests... --- *\n\n");
    Biterator *it = new_Biterator(1, -1, VOID_INT, do_bit);            
    obj->iterate(obj, it);
    printf("\n");
    del_Biterator(it, true);

    it = new_Biterator(1, -1, INT_INT, transform_test);
    obj->iterate(obj, it);
    obj->for_each(obj, do_bit, -1);
    printf("\n");
    detach_Biterator(it);
    obj->iterate(obj, it);
    del_Biterator(it, true);
    obj->for_each(obj, do_bit, -1);
    printf("\n");

    it = new_Biterator(1, -1, VOID_INT_IDX, do_bit_index);
    obj->iterate(obj, it);
    del_Biterator(it, true);

    it = new_Biterator(3, -1, VOID_INT, do_slice);
    obj->iterate(obj, it);
    del_Biterator(it, true);
    printf("\n ** FINISHED **\n\n");
}

void run_manipulation_tests(BitArray *bits)
{
    printf("* --- Running general tests... --- *\n\n");
    display_bits(bits);
    bits->set(bits, 1, 0);
    bits->set(bits, 1, 3);
    display_bits(bits);
    bits->resize(bits, 15);
    display_bits(bits);
    bits->resize(bits, 3);
    display_bits(bits);
    bits->append(bits, 0b1000);
    bits->append(bits, 0b1011);
    bits->append(bits, 0xFF);
    display_bits(bits);
    printf("[%d:%d] %d, ", 0, 4, bits->slice(bits, 0, 4));
    print_bit_repr(bits->slice(bits, 0, 4));

    printf("\n ** FINISHED **\n\n");
}

int main()
{
    BitArray *bits = new_BitArray(12);
    run_manipulation_tests(bits);
    gen_iter_test(bits);
    // custom_iter_test(bits);
    custom_iter_test_alloc(bits);
    del_BitArray(bits);
    return 0;
}