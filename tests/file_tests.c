#include "../src/bitarray.h"
IMPORT_BITARRAY_MODULE_AS(Bits);


const char* header_path = "../resources/avi_header.avi";
const char* video_path = "../resources/mp2_test_.avi";

void avi_header_test()
{
	BitArray bits;
	if(!init_BitArray_from_file(&bits, header_path))
		return;
	bitarray_print_bytes(&bits, 0, -1);
	free_BitArray_buffer(&bits);
}

void avi_full_file_test()
{
	BitArray bits;
	if(!init_BitArray_from_file(&bits, video_path))
		return;
	bitarray_print_bytes(&bits, 9992-8, 12);
	free_BitArray_buffer(&bits);
}

struct X
{
	int a;
	int b;
};


int main()
{
	#if __BITARRAY_MMAP__ == 1
	printf("mmap defined!\n");
	#endif
	avi_header_test();
	avi_full_file_test();
	return 0;
}