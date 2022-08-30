#ifndef INCLUDE_STRINGTREE_H
#define INCLUDE_STRINGTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "common.h"

// #ifndef STRINGTREE_NODESIZE
// 	#define 

// static uint32_t CHAR_FLAG_MASK = 0xFFFF0000;

static uint16_t CHAR_MAP[257] = { ZEROESx256, 0 };
static uint16_t CHAR_IDX_MAP[257] = { ZEROESx256, 0 };

FLAG16(CHAR_INVALID, 0);
FLAG16(CHAR_DIGIT, 1);
FLAG16(CHAR_ALPHA, 2);
FLAG16(CHAR_SYMBOL, 3);
FLAG16(CHAR_BRACKET, 4);
FLAG16(CHAR_UPPER, 5);
FLAG16(CHAR_HEX, 6);

// static inline uint32_t get_char_flags(char c)
// {
// 	return (CHAR_MAP[(uint8_t) c] & CHAR_FLAG_MASK);
// }

// static inline bool is_valid_char(char c)
// {
// 	return (get_char_flags(c) & CHAR_INVALID) == 0;
// }

// static inline bool is_symbol(char c)
// {
// 	return (get_char_flags(c) & CHAR_SYMBOL) != 0;
// }


typedef struct SearchLeaf
{
	uint8_t priv_flags;
	uint16_t flags;
	union
	{
		uint64_t value;
		uint64_t u64_val;
		const char* str_val;
		void* opaque;
		int64_t i64_val;
	};
} SearchLeaf;

typedef struct SearchResult
{
	bool valid;
	uint16_t flags;
	union
	{
		uint64_t value;
		uint64_t u64_val;
		const char* str_val;
		void* opaque;
		int64_t i64_val;
	};
} SearchResult;

#define NO_RESULT() ((SearchResult) {.valid=false, .flags=0, .u64_val=0})

typedef struct SearchNode
{
	uint8_t priv_flags;
	uint16_t flags;
	union
	{
		uint64_t value;
		uint64_t u64_val;
		const char* str_val;
		void* opaque;
		int64_t i64_val;
	};
	SearchLeaf leaves[94];
} SearchNode;

typedef struct StringTree
{
	bool init;
	SearchNode nodes[94];
} StringTree;

void init_char_maps();

bool 
init_stringtree(
	StringTree* tree, 
	const char* tokens[],
	int num_tokens
	);

SearchResult 
stringtree_find_str(
	StringTree* tree, 
	const char* s
	);

bool 
stringtree_add_str_u64(
	StringTree* tree, 
	const char* s, 
	uint16_t flags, 
	uint64_t value
	);

bool 
stringtree_add_str_str(
	StringTree* tree, 
	const char* s, 
	uint16_t flags, 
	const char* strv
	);

static inline bool
stringtree_add_str_raw(
	StringTree* tree, 
	const char* s, 
	uint16_t flags, 
	void* opaque
	)
{
	return stringtree_add_str_u64(tree, s, flags, (uint64_t) opaque);
}



#endif /* stringtree.h */