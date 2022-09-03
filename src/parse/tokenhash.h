#ifndef INCLUDE_TOKENHASH_H
#define INCLUDE_TOKENHASH_H

#include <stdint.h>
#include <string.h>

struct HashToken
{
	const char* name;
	uint8_t precedence;
	uint16_t tokenize_flags;
	uint16_t tree_flags;
	uint16_t compile_flags;
	const char* descr;
	uint8_t max_search_size;
	uint8_t compile_idx;
};

typedef struct HashToken HashToken;

HashToken * in_word_set (register const char* str, register unsigned int len);

#endif /* tokenhash.h */
