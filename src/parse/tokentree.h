#ifndef INCLUDE_TOKENTREE_H
#define INCLUDE_TOKENTREE_H

#include <stdlib.h>
#include <stdbool.h>

#ifndef BITARRAY_NO_DEBUG
	#include <assert.h>
	#define BITASSERT(x) assert(x)
#else
	#define BITASSERT(x) ((void) 0)
#endif

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
	union
	{
		struct Tree* left;
		struct Tree** children;
	};
	union
	{
		struct Tree* right;
		uint64_t num_children;
	};
} Tree;

static inline
Tree* alloc_binary_tree()
{
	Tree *tree = (Tree*) malloc(sizeof(Tree));
	if(tree == NULL)
		return NULL;
	tree->flags = 0;
	tree->left = NULL;
	tree->right = NULL;
	tree->str[0] = '\0';
	return tree;
};


FLAG8(TREE_ATOMIC, 0);
FLAG8(TREE_SIMPLE, 1);
FLAG8(TREE_UNARY, 2);
FLAG8(TREE_BISIMPLE, 3);
FLAG8(TREE_BINARY, 4);
FLAG8(TREE_LEFT_ATOMIC, 5);
FLAG8(TREE_RIGHT_ATOMIC, 6);
FLAG8(TREE_MANY, 7);


static inline uint8_t 
get_tree_details(Tree* tree)
{
	uint8_t flags = 0;
	if(tree->flags & TREE_MANY)
		return TREE_MANY;
	if(tree->left == NULL)
	{
		BITASSERT((tree->right == NULL));
		return TREE_ATOMIC;
	}
	if(!(tree->left->flags & TREE_MANY) && tree->left->left == NULL)
	{
		BITASSERT((tree->left->right == NULL));
		flags |= TREE_LEFT_ATOMIC;
	}
	if(tree->right != NULL)
	{
		flags |= TREE_BINARY;
		if(!(tree->right->flags & TREE_MANY) && tree->right->left == NULL)
		{
			BITASSERT((tree->right->right == NULL));
			flags |= TREE_RIGHT_ATOMIC;
			if(flags & TREE_LEFT_ATOMIC)
				flags |= TREE_BISIMPLE;
		}
	}
	else
	{
		flags |= TREE_UNARY;
		if(flags & TREE_LEFT_ATOMIC)
			flags |= TREE_SIMPLE;
	}
	return flags;
}

Tree* create_token_tree(TokenList* list, int loglevel, bool parens_node);

Tree* make_single_token_tree(const char* fmt, int loglevel, bool parens_node);

void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node);

void debug_tokenize(TokenList* list, int loglevel);

void print_tree(Tree *tree, bool end);

void delete_tree(Tree* tree);

#endif /* tokentree.h */