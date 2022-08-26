#ifndef INCLUDE_STRINGTREE_H
#define INCLUDE_STRINGTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "common.h"

#ifndef SEARCH_NUM_CHARS
	#define SEARCH_NUM_CHARS 94
#endif

static uint32_t CHAR_FLAG_MASK = 0xFFFF0000;

static uint32_t CHAR_MAP[257] = { ZEROESx256, 0 };

FLAG32(CHAR_INVALID, 16);
FLAG32(CHAR_DIGIT, 17);
FLAG32(CHAR_ALPHA, 18);
FLAG32(CHAR_SYMBOL, 19);
FLAG32(CHAR_BRACKET, 20);
FLAG32(CHAR_UPPER, 21);
FLAG32(CHAR_HEX, 22);

static inline uint32_t get_char_flags(char c)
{
	return (CHAR_MAP[(uint8_t) c] & CHAR_FLAG_MASK);
}

static inline bool is_valid_char(char c)
{
	return (get_char_flags(c) & CHAR_INVALID) == 0;
}

static inline bool is_symbol(char c)
{
	return (get_char_flags(c) & CHAR_SYMBOL) != 0;
}

typedef struct SearchNode
{
	uint32_t flags;
	struct SearchNode* children[SEARCH_NUM_CHARS];
} SearchNode;

typedef struct StringTree
{

} StringTree;

// bool is_symbol(char c);

// bool is_valid_char(char c);





#endif /* stringtree.h */