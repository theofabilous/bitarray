#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


#define ZEROESx32                       \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define ZEROESx64                       \
    ZEROESx32,                          \
    ZEROESx32

#define ZEROESx128                      \
    ZEROESx64,                          \
    ZEROESx64

#define ZEROESx256                      \
    ZEROESx128,                         \
    ZEROESx128

#define ZEROESx25 \
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
	0,0,0,0,0,0,0,0,0,0

#define ZEROESx100 \
	ZEROESx25, ZEROESx25, ZEROESx25, \
	ZEROESx25


// isprint(char) 					-> check if printable

// isalpha(char) 					-> check if alphabetical
// isdigit(char) 					-> check if digit
// isalnum(char) 					-> check if alphanumeric
// isxdigit(char) 					-> check if hexadecimal digit
// isupper(char) / islower(char) 	-> check upper/lowercase

// tolower(char) / toupper(char)	-> convert case

/*
atof			Convert string to double (function)
atoi			Convert string to integer (function)
atol			Convert string to long integer (function)
atoll			Convert string to long long integer (function)
strtod			Convert string to double (function)
strtof			Convert string to float (function)
strtol			Convert string to long integer (function)
strtold			Convert string to long double (function)
strtoll			Convert string to long long integer (function)
strtoul			Convert string to unsigned long integer (function)
strtoull		Convert string to unsigned long long integer (function)
*/


#define FLAG32(name, shift) \
	static const uint32_t name = 1 << shift

#define FLAG16(name, shift) \
	static const uint16_t name = 1 << shift

#define FLAG8(name, shift) \
	static const uint8_t name = 1 << shift

FLAG32(GET_ENV, 0);
FLAG32(LITERAL, 1);
FLAG32(PATTERN, 2);
FLAG32(UNARY_EXP, 3);
FLAG32(BINARY_EXP, 4);
FLAG32(READ, 5);
FLAG32(SEQUENCE, 6);
FLAG32(ASSIGN, 7);
FLAG32(MATCH, 8);
// FLAG32(SKIP, 9);

FLAG32(ALLOCATED, 31);

FLAG8(READ_SIGNED, 1);
FLAG8(READ_BINARY, 2);
FLAG8(READ_BIGENDIAN, 3);
FLAG8(SKIP_READ, 4);

FLAG8(UNARY_NEG, 1);
FLAG8(UNARY_BYTES, 2);

FLAG8(BINARY_ALIGN, 1);
FLAG8(BINARY_PLUS, 2);
FLAG8(BINARY_MINUS, 3);
FLAG8(BINARY_SHIFTL, 4);
FLAG8(BINARY_SHIFTR, 5);


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




#define INSTDEFAULT() \
	((Instruction) { .spec = 0, .repeat = 0 })

#define INSTALLOC() (Instruction*) malloc(sizeof(Instruction))


// typedef void (*printer_t)(Instruction*, int);
// printer_t get_printer(Instruction* inst);

// void print_get_env(Instruction* inst, int depth)
// {

// }



// printer_t get_printer(Instruction* inst)
// {
// 	// switch(inst->)
// }

const char* boolstr(bool b)
{
	return (b) ? "true" : "false";
}

void print_indent(int depth, char c)
{
	while(depth--)
		putchar(c);
}

void print_indent_str(int depth, const char* s)
{
	while(depth--)
		printf("%s", s);
}

// FLAG32(GET_ENV, 0);
// FLAG32(LITERAL, 1);
// FLAG32(PATTERN, 2);
// FLAG32(UNARY_EXP, 3);
// FLAG32(BINARY_EXP, 4);
// FLAG32(READ, 5);
// FLAG32(SEQUENCE, 6);
// FLAG32(ASSIGN, 7);
// FLAG32(MATCH, 8);

char get_unary_op_symbol(uint8_t op)
{
	switch(op)
	{
		case UNARY_NEG:
			return '-';
		case UNARY_BYTES:
			return 'B';
		default:
			return '`';
	}
}


void print_instruction(Instruction* inst, int depth)
{
	print_indent(depth, ' ');
	switch(inst->spec & (~ALLOCATED))
	{
		case GET_ENV:
			printf("Get_Env($%hhu)\n", inst->env_index);
			break;
		case LITERAL:
			printf("Literal(%lli)\n", inst->num_literal);
			break;
		case PATTERN:
			goto error;
		case UNARY_EXP:
			printf("Unary_Op(\n");
			print_indent(depth+1, ' ');
			printf("Op(%c),\n", get_unary_op_symbol(inst->unary_expr.unop));
			print_indent(depth+1, ' ');
			printf("Operand(\n");
			print_instruction(inst->unary_expr.unoperand, depth+2);
			print_indent(depth+1, ' ');
			printf(")\n");
			print_indent(depth, ' ');
			printf(")\n");

	}

	error:
		// print_indent(depth, ' ');
		printf("-- ERROR --\n");
		return;
}


typedef struct Tree
{
	uint32_t flags;
	// char *cptr;
	char str[50];
	union
	{

		char c;
		uint16_t val;
	};
	struct Tree *left, *right;
} Tree;

FLAG32(READ_PARENT, 0);
FLAG32(ENV_PARENT, 1);
FLAG32(PARENS_OPEN, 2);
FLAG32(UNOP_PARENT, 3);
FLAG32(BINOP_PARENT, 4);

Tree* make_tree_from_tokens(int *i, 
	uint32_t ctx, 
	uint32_t* ctxsig,
	char parent,
	char tokens[][10])
{
	char tstr[100];
	Tree* root = (Tree*) malloc(sizeof(Tree));
	root->left = NULL;
	root->right = NULL;
	Tree* curr = root, *temp = NULL;
	int j=0;
	char *cptr;
	while(*i<100 && tokens[*i][0])
	{
		cptr = tokens[*i];
		printf("--> %s\n", cptr);
		printf("Parens open? %s, Read parent? %s\n",
				boolstr((ctx & PARENS_OPEN)), boolstr((ctx & READ_PARENT)));
		printf("ctx: %u\n", ctx);
		if(parent)
		{
			printf("Parent: %c\n", parent);
		}
		else
			printf("No parent\n");
		if(isdigit(*cptr))
		{
			strcpy(&(curr->str[j]), cptr);
			j=0;
			cptr = tokens[++(*i)];
			continue;
		}
		// "(" --> keep target until ")" ?
		switch(*cptr)
		{
			case '(':
				ctx |= PARENS_OPEN;
				cptr = tokens[++(*i)];
				break;
			case ')':
				// ------------------------

				// return curr;

				// ++(*i);
				// return curr;

				if(ctx & PARENS_OPEN)
					return curr;
				++(*i);

				// ------------------------

				// if(ctx & PARENS_OPEN)
				// {
				// 	*(ctxsig) |= PARENS_OPEN;
				// 	// ++(*i);
				// 	return curr;
				// 	// ctx &= ~(PARENS_OPEN);
				// 	// ++(*i);
				// 	// return curr;
				// }
				// cptr = tokens[++(*i)];
				// ctx &= ~(PARENS_OPEN);
				// cptr = tokens[++(*i)];
				break;
			case 'b':
			case 'u':
			case 'i':
				// temp = (Tree*) malloc(sizeof(Tree));
				curr->str[0] = *cptr;
				curr->str[1] = '\0';
				j = 0;
				++(*i);
				// ctx |= READ_PARENT;
				curr->left = make_tree_from_tokens(i, READ_PARENT, ctxsig, *cptr, tokens);
				curr->right = NULL;
				break;
			case '$':
				j = 0;
				curr->str[0] = *cptr;
				curr->str[1] = '\0';
				j++;
				cptr = tokens[++(*i)];
				break;
			case '=':
			case '%':
			case '-':
			case '+':
				if((ctx & READ_PARENT) &&
					!(ctx & PARENS_OPEN))
				{
					return curr;
				}
				ctx &= ~(READ_PARENT);
				temp = (Tree*) malloc(sizeof(Tree));
				temp->str[0] = *cptr;
				temp->str[1] = '\0';
				j = 0;
				temp->left = curr;
				curr = temp;
				++(*i);
				curr->right = make_tree_from_tokens(i, ctx, ctxsig, *cptr, tokens);
				break;
				// cptr = tokens[*i];
		}
		ctx |= *(ctxsig);
	}
	return curr;
}

Tree* create_token_tree(char tokens[][10])
{
	int i=0;
	uint32_t sig = 0;
	return make_tree_from_tokens(&i, 0, &sig, '\0', tokens);
}

void delete_tree(Tree* tree)
{
	if(tree != NULL)
	{
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
}

void _print_tree(Tree* tree, int depth)
{
	print_indent_str(depth, "  ");
	if(tree->left == NULL && tree->right == NULL)
	{
		printf("%s", tree->str);
	}
	else if ((tree->left != NULL && tree->right == NULL)
			|| (tree->left == NULL && tree->right != NULL))
	{
		Tree *to_print = (tree->left == NULL) ? tree->right : tree->left;
		printf("%s(\n", tree->str);
		_print_tree(to_print, depth+1);
		putchar('\n');
		print_indent_str(depth, "  ");
		printf(")");
	}
	else
	{
		printf("%s(\n", tree->str);
		_print_tree(tree->left, depth+1);
		printf(",\n");
		_print_tree(tree->right, depth+1);
		putchar('\n');
		print_indent_str(depth, "  ");
		putchar(')');
	}
}

void print_tree(Tree *tree)
{
	_print_tree(tree, 0);
	putchar('\n');
}



void delete_instruction(Instruction* inst)
{
	// ...
	return;
}


static inline bool alloc_assign(Instruction* dest)
{
	dest->assign.target = INSTALLOC();
	if(dest->assign.target == NULL)
		return false;
	dest->assign.value = INSTALLOC();
	if(dest->assign.value == NULL)
	{
		free(dest->assign.target);
		return NULL;
	}
	dest->assign.target->spec |= ALLOCATED;
	dest->assign.value->spec |= ALLOCATED;
	dest->spec |= ASSIGN;
	return true;
}


static inline bool alloc_read(Instruction* dest)
{
	dest->read.read_size = INSTALLOC();
	if(dest->read.read_size == NULL)
		return false;
	dest->spec |= READ;
	dest->read.read_size->spec |= ALLOCATED;
	return true;
}


static inline bool alloc_unop(Instruction* dest)
{
	dest->unary_expr.unoperand = INSTALLOC();
	if(dest->unary_expr.unoperand == NULL)
		return false;
	dest->spec |= UNARY_EXP;
	dest->unary_expr.unoperand->spec |= ALLOCATED;
	return true;
}

static inline bool alloc_binop(Instruction* dest, bool alloc_left)
{
	if(alloc_left)
	{
		dest->binary_expr.left = INSTALLOC();
		if(dest->binary_expr.left == NULL)
			return false;
		dest->binary_expr.right = INSTALLOC();
		if(dest->binary_expr.right == NULL)
		{
			free(dest->binary_expr.left);
			return false;
		}
		dest->spec |= BINARY_EXP;
		dest->binary_expr.left->spec |= ALLOCATED;
		dest->binary_expr.right->spec |= ALLOCATED;
		return true;	
	}
	else
	{
		dest->binary_expr.right = INSTALLOC();
		if(dest->binary_expr.right == NULL)
			return false;
		dest->spec |= BINARY_EXP;
		dest->binary_expr.right->spec |= ALLOCATED;
		return true;
	}

}

typedef struct TargetStack
{
	Instruction* targets[100];
	Instruction** top;
	uint8_t len;
} TargetStack;

void set_top_addr(TargetStack* stack, Instruction** ptr)
{
	stack->top = ptr;
}


bool push_target(TargetStack* stack, Instruction* target)
{
	if(stack->len == 100)
		return false;
	stack->targets[stack->len] = target;
	*(stack->top) = target;
	stack->len++;
	return true;
}

Instruction* peek_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	return stack->targets[stack->len - 1];
}

Instruction* pop_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	Instruction* ret = stack->targets[stack->len - 1];
	stack->targets[--stack->len] = NULL;
	*(stack->top) = stack->targets[stack->len - 1];
	return ret;
}

Instruction* rem_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	Instruction* ret = stack->targets[stack->len - 1];
	stack->targets[--stack->len] = NULL;
	return ret;
}


