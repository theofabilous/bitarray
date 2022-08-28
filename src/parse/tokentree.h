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
	struct Tree *left, *right;
} Tree;


static inline bool tree_is_atomic(Tree* tree)
{
	return (tree->left == NULL && tree->right == NULL);
}

static inline bool tree_is_unary(Tree* tree)
{
	return ( (tree->left != NULL && tree->right == NULL)
		     || (tree->left == NULL && tree->right != NULL) );
}

static inline bool tree_is_simple(Tree* tree)
{
	if(!tree_is_unary(tree))
		return false;
	Tree *child = (tree->left == NULL) ? tree->right : tree->left;
	return tree_is_atomic(child);
}

static inline bool tree_is_binary(Tree* tree)
{
	return (tree->left != NULL && tree->right != NULL);
}

static inline bool tree_is_bisimple(Tree* tree)
{
	if(!tree_is_binary(tree))
	{
		return false;
	}
	return tree_is_atomic(tree->left) && tree_is_atomic(tree->right);
}

FLAG8(TREE_ATOMIC, 0);
FLAG8(TREE_SIMPLE, 1);
FLAG8(TREE_UNARY, 2);
FLAG8(TREE_BISIMPLE, 3);
FLAG8(TREE_BINARY, 4);
FLAG8(TREE_LEFT_ATOMIC, 5);
FLAG8(TREE_RIGHT_ATOMIC, 6);


static inline uint8_t get_tree_details(Tree* tree)
{
	uint8_t flags = 0;
	if(tree->left == NULL)
	{
		BITASSERT((tree->right == NULL));
		return TREE_ATOMIC;
	}
	if(tree->left->left == NULL)
	{
		BITASSERT((tree->left->right == NULL));
		flags |= TREE_LEFT_ATOMIC;
	}
	if(tree->right != NULL)
	{
		flags |= TREE_BINARY;
		if(tree->right->left == NULL)
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


	// if(tree->left == NULL)
		// flags |= TREE_LEFT_NULL;
	// else if(tree->left->left == NULL && tree->left->right == NULL)
	// 	flags |= TREE_LEFT_ATOMIC;
	// else if(tree->left->right == NULL && tree->left->left != NULL)
	// {
	// 	if(tree->left->left->left == NULL)
	// 		flags |= TREE_LEFT_SIMPLE;
	// }

	// if(tree->right == NULL)
	// 	flags |= TREE_RIGHT_NULL;
	// else if(tree->right->left == NULL && tree->right->right == NULL)
	// 	flags |= TREE_RIGHT_ATOMIC;
	// else if(tree->right->right == NULL && tree->right->left != NULL)
	// {
	// 	if(tree->right->left->left == NULL)
	// 		flags |= TREE_RIGHT_SIMPLE;
	// }
	// return flags;
}

Tree* create_token_tree(TokenList* list, int loglevel, bool parens_node);

Tree* make_single_token_tree(const char* fmt, int loglevel);

void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node);

void print_tree(Tree *tree, bool end);

void delete_tree(Tree* tree);

#endif /* tokentree.h */