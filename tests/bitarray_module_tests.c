#include "../src/bitarray.h"
#include "../src/bitbuffer.h"
// #include "binregex.h"
#include "vlc/libvlc.h"
#include "vlc/vlc.h"


IMPORT_BITARRAY_MODULE_AS(Bits);


void vlc_test()
{
	libvlc_instance_t * inst;
	libvlc_media_player_t *mp;
	libvlc_media_t *m;

	/* Load the VLC engine */
	// inst = libvlc_new (0, NULL);
}


void slice_test()
{
	BitArray *obj = new_BitArray(0);
	Bits.append(obj, 0b11111111000110010);
	Bits.print_bits(obj, 0, -1);
	Bits.set_slice(obj, 0, 5, 0b10101);
	Bits.print_bits(obj, 0, -1);
	del_BitArray(obj);
}

void map_test()
{
	BitArray arr;
	init_BitArray(&arr, 0);
	Bits.print_bits(&arr, 0, -1);
	Bits.append(&arr, 0b11110101010);
	Bits.print_bits(&arr, 0, -1);
	
	Bits.resize(&arr, 8);
	Bits.print_bits(&arr, 0, -1);
	Bits.resize(&arr, 10);
	Bits.print_bits(&arr, 0, -1);

	Bits.resize(&arr, 130);
	Bits.print_bits(&arr, 0, -1);

	Bits.resize(&arr, 8);
	Bits.print_bits(&arr, 0, -1);
	Bits.resize(&arr, 10);
	Bits.print_bits(&arr, 0, -1);

	Bits.append_str(&arr, "00000001");
	Bits.print_bits(&arr, 0, -1);

	Bits.set_slice_str(&arr, 10, 18, 0, "10");
	Bits.print_bits(&arr, 0, -1);

	Bits.resize(&arr, 0);
	Bits.append_str(&arr, "1001110100000");
	Bits.print_bits(&arr, 0, -1);
	Bits.map(&arr, 
		(BinaryMapEntry[]) 
		{
			{"1001", "0110", Map_Bits}, 
			{"1101", "1010", Map_Bits},
			{"00000", "11101", Map_Bits}
		}, 3);
	Bits.print_bits(&arr, 0, -1);
	// 0110101011101

	BitArray other;
	init_BitArray(&other, 0);
	Bits.reserve(&other, 20);
	// Bits.append_str(&other, "10010101");
	// Bits.print_bits(&other, 0, -1);
	// BinaryMapEntry mappings[] = {
	// 	{"0110", "1001", Map_Bits}
	// };
	Bits.map_into(&arr, &other,
		(BinaryMapEntry[])
		{
			{"0110", "1001", Map_Bits},
			{"111", 0, Ignore_Bits}
		}, 2
		);
	Bits.print_bits(&other, 0, -1);



	free_BitArray_buffer(&other);
	free_BitArray_buffer(&arr);
}

#define b_field(...) {.size = 0, .raw = (__VA_ARGS__) }
#define b_field_default {.size = 0, .raw = 0 }
#define b_u8_field(...) {.size = 0, .raw = ( (uint8_t[]) __VA_ARGS__) }
#define b_str_field(...) {.size = 0, .raw = ( (char[]) __VA_ARGS__) }

void unpack_test()
{
	const char* header_path = "../resources/avi_header.avi";
	// char riff_fourcc[5];
	// char avi_fourcc[5];
	BitBuffer* buff = new_BitBuffer_from_file(header_path, false);
	BField receiver[19] = {
		b_str_field({0,0,0,0,0}),
		b_field_default,
		b_str_field({0,0,0,0,0}),
		b_str_field({0,0,0,0,0}),
		b_field_default,
		b_str_field({0,0,0,0,0}),
		b_str_field({0,0,0,0,0}),
		b_field_default
	};
	const char* fmt = "c<4>, u32, c<4>*2, u32, c<4>*2, u32, u32*10, ![128]";
	size_t ret = bitbuffer_unpack(buff, fmt, receiver);
	printf("Ret: %zu\n", ret);
	// receiver[3].istr[5] = '\0';
	printf("%s, %zu, %s\n", receiver[0].str, receiver[1].u32, receiver[2].str);
	printf("%s, %zu, %s, %s\n", receiver[3].str, receiver[4].u32, receiver[5].str,
		receiver[6].str);
	for(int i=7; i<18; i++)
		printf("(%d) %zu\n", i, receiver[i].u32);
	printf("POS: %zu\n", buff->pos >> 3);
	del_BitBuffer(buff);
}

void mmap_test()
{
	const char* header_path = "../resources/avi_header.avi";
	char fourcc[5];
	BitBuffer* buff = new_BitBuffer_from_file(header_path, false);
	bitbuffer_read_fourcc(buff, fourcc);
	printf("%s\n", fourcc);
	size_t fsize = bitbuffer_read_uint32(buff);
	printf("%zu\n", fsize);
	bitbuffer_read_fourcc(buff, fourcc);
	printf("%s\n", fourcc);
	bitbuffer_read_fourcc(buff, fourcc);
	printf("%s\n", fourcc);

	bitbuffer_skip(buff, 32);
	bitbuffer_read_fourcc(buff, fourcc);
	printf("%s\n", fourcc);

	bitbuffer_skip(buff, -31);
	bitbuffer_skip(buff, -1);
	bitbuffer_read_fourcc(buff, fourcc);
	printf("%s\n\n", fourcc);
	del_BitBuffer(buff);

	BitArray arr;
	if(!init_Bitarray_from_file(&arr, header_path))
	{
		printf("err\n");
		return;
	}
	Bits.print_bytes(&arr, 0, 4);
	

	BitBuffer* _buff = new_BitBuffer_from_BitArray(&arr);
	if(_buff == NULL)
	{
		printf("err\n");
		return;		
	}
	bitbuffer_read_fourcc(_buff, fourcc);
	printf("%s\n", fourcc);
	fsize = bitbuffer_read_uint32(_buff);
	printf("size: %zu\n", fsize);

	bitbuffer_skip(_buff, -32);
	fsize = bitbuffer_read(_buff, 32, true);
	printf("size: %zu\n", fsize);

	bitbuffer_read_fourcc(_buff, fourcc);
	printf("%s\n", fourcc);
	bitbuffer_read_fourcc(_buff, fourcc);
	printf("%s\n", fourcc);

	del_BitBuffer(_buff);
	free_BitArray_buffer(&arr);

}

// void test_func(char arr[], int size)
// {
// 	for(int i=0; i<size; i++)
// 		printf("%c\n", arr[i]);
// }

int main()
{
	unpack_test();
	// map_test();
	// // test_func( ((char[]){'a', 'b', 'c'}),  3);
	// mmap_test();
	// slice_test();
	// vlc_test();
	return 0;
}