#ifndef INCLUDE_TREECOMPILE_H
#define INCLUDE_TREECOMPILE_H

#include <stdlib.h>
#include <stdbool.h>

#include "tokentree.h"

typedef struct CodeValue
{
	uint8_t type;
	union
	{
		uint8_t u8_value;
		uint16_t u16_value;
		int32_t i32_value;
		int64_t i64_value;
		bool bool_value;
		void* opaque;
		const char* str_value;
	};
} CodeValue;


typedef struct Instruction
{
	uint16_t spec;
	const char* name;
	CodeValue values[3];
} Instruction;


typedef struct CodeList
{
	uint32_t registers;
	int64_t len;
	Instruction items[200];
} CodeList;

// void init_codelist(CodeList* list);

bool init_stringtables();

int _compile_tokentree(Tree* tree, CodeList* list);

CodeList compile_tokentree(Tree* tree);

void print_codelist(CodeList* list);

void debug_compile(Tree* tree);



#endif /* treecompile.h */