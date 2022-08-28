#include "dict.h"

uint32_t
djb2_hash(const uint8_t* str)
{
	uint32_t hash = 5381;
	uint8_t c;

	while ( (c = *(str++)) )
		hash = ((hash << 5) + hash) + c;
	return hash;
}

