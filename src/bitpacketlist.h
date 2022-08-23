#include "bitarray.h"

typedef size_t (*allocator_t)(size_t s);

typedef struct BitAllocator
{
	uint8_t allocator_mode;
	union {
		allocator_t alloc_func;
		size_t alloc_size;
	};
} BitAllocator;

typedef struct PackedListSpec
{
	uint8_t* size_sequence;
	BitAllocator* allocator_spec;
} PackedListSpec;

typedef struct PackedList
{
	PackedListSpec* spec;
	size_t size;
	uint8_t* data;
} PackedList;




typedef struct BitPacketList
{
	uint8_t flags;
	union {

	};
} BitPacketList;