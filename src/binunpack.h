#include "bitbuffer.h"
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

enum LogLevel
{
	Quiet = 0,
	Info = 1,
	Inspect = 2,
	Debug = 5,
	Full = 10
};

typedef struct Tree
{
	uint32_t flags;
	char str[50];
	union
	{
		char c;
		uint16_t val;
	};
	struct Tree *left, *right;
} Tree;

void tokenize(const char* str,
			   const char* delims,
			   char dest[][10],
			   int max_tokens);

Tree* create_token_tree(char tokens[][10], int loglevel);

Tree* make_tree_from_tokens(int *i, 
	uint32_t ctx, 
	uint32_t* ctxsig,
	char parent,
	char tokens[][10],
	int loglevel,
	Tree* mainroot);

void delete_tree(Tree* tree);

void _print_tree(Tree* tree, int depth, bool end);

void print_tree(Tree *tree, bool end);


void debug_parse_str(const char* fmt, int loglevel);

void debug_single_spec(char str[100], int loglevel);




/* ----------------------------------------------- */




typedef struct Instruction
{
	uint32_t spec;
	uint8_t repeat;
	union
	{
		uint8_t env_index;
		int64_t num_literal;

		struct
		{
			uint8_t pattern_flags;
			uint8_t pattern[16];
		} pattern;

		struct
		{
			uint8_t unop;
			struct Instruction* unoperand;
		} unary_expr;

		struct
		{
			uint8_t binop;
			struct Instruction *left, *right;
		} binary_expr;

		struct
		{
			uint8_t read_flags;
			struct Instruction* read_size;
			// struct Instruction* sequence_len;
		} read;

		struct
		{
			struct Instruction* item;
			struct Instruction* len; 
		} sequence;

		struct
		{
			struct Instruction *target, *value;
		} assign;

		struct
		{
			uint8_t match_flags;
			struct Instruction* match_pattern;
			struct Instruction *match_success, *match_fail;
		} match;
	};
} Instruction;

typedef struct UnpackSpec
{
	Instruction* items;
	int len;
} UnpackSpec;

typedef struct TargetStack
{
	Instruction* targets[100];
	Instruction** top;
	uint8_t len;
} TargetStack;


void delete_instruction(Instruction* inst);
