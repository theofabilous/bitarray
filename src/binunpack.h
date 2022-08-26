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


typedef struct Token
{
	uint8_t flags;
	char str[10];
} Token;

typedef struct BracketPair
{
	char copen, cclose;
	uint8_t open, close;
} BracketPair;

typedef struct Stack
{
	int len;
	void* ptrs[100];
} Stack;

typedef struct TokenList
{
	int len;
	Token tokens[100];
	int blen;
	BracketPair brackets[100];
	BracketPair* currbr;
} TokenList;


void delete_tree(Tree* tree);

void _print_tree(Tree* tree, int depth, bool end);

void print_tree(Tree *tree, bool end);


void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node);

void debug_single_spec(char str[], int loglevel, bool end, bool parens_node);

