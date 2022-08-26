#ifndef INCLUDE_TOKENTREE_H
#define INCLUDE_TOKENTREE_H

#include <stdlib.h>
#include <stdbool.h>

#include "tokenize.h"

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

Tree* create_token_tree(TokenList* list, int loglevel, bool parens_node);

void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node);

void print_tree(Tree *tree, bool end);

void delete_tree(Tree* tree);

#endif /* tokentree.h */