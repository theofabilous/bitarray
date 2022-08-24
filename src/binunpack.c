#include "binunpack.h"

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


#define FLAG32(name, shift) \
	static const uint32_t name = 1 << shift

#define FLAG16(name, shift) \
	static const uint16_t name = 1 << shift

#define FLAG8(name, shift) \
	static const uint8_t name = 1 << shift


static inline const char* boolstr(bool b)
{
	return (b) ? "true" : "false";
}

static inline void print_indent(int depth, char c)
{
	while(depth--)
		putchar(c);
}

static inline void print_indent_str(int depth, const char* s)
{
	while(depth--)
		printf("%s", s);
}


FLAG32(READ_PARENT, 0);
FLAG32(ENV_PARENT, 1);
FLAG32(PARENS_OPEN, 2);
FLAG32(UNOP_PARENT, 3);
FLAG32(BINOP_PARENT, 4);
FLAG32(SKIP_PARENT, 5);


static char tokens[100][10];
static const char* delims = "?:|.%!$=[]<>{}()uiBbcs*+-";


void tokenize(const char* str,
			   const char* delims,
			   char dest[][10],
			   int max_tokens)
{
	const char* prev = str;
	const char* c = strpbrk(str, delims);
	size_t toksize=0;
	int idx=0;

	while(c != NULL && idx < max_tokens)
	{
		toksize = c-prev;
		if(toksize != 0)
		{
			strncpy(dest[idx], prev, toksize);
			dest[idx][toksize] = '\0';
			idx++;
		}
		dest[idx][0] = *c;
		dest[idx][1] = '\0';
		prev = ++c;
		c = strpbrk(c, delims);
		idx++;
	}
	if(*prev)
	{
		strcpy(dest[idx], prev);
		idx++;
	}
	dest[idx][0] = '\0';
}


void debug_parse_str(const char* fmt)
{
	char currstr[100];
	int idx = 0;
	const char* cptr = fmt;
	bool brk = 0;
	while(idx < 100 && !brk)
	{
		switch(*cptr)
		{
			case ' ':
				cptr++;
				break;
			case '\0':
				brk = true;
				if(!idx)
					break;
			case ',':
				currstr[idx] = '\0';
				idx = 0;
				debug_single_spec(currstr);
				cptr++;
				break;
			default:
				currstr[idx] = *cptr;
				cptr++;
				idx++;
				break;
		}
	}
}

void debug_single_spec(char str[100])
{
	tokenize(str, delims, tokens, 100);
	Tree* tree = create_token_tree(tokens);
	print_tree(tree, true);
	delete_tree(tree);
	for(int i=0; i<100 && (tokens[i][0] != '\0'); i++)
		printf("%s ", tokens[i]);
	putchar('\n');
}

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
			case '!':
				curr->str[0] = *cptr;
				curr->str[1] = '\0';
				++(*i);
				j = 0;
				curr->left = make_tree_from_tokens(i, SKIP_PARENT, ctxsig, *cptr, tokens);
				curr->right = NULL;
				break;
			case '(':
				ctx |= PARENS_OPEN;
				cptr = tokens[++(*i)];
				break;
			case ')':
				// return curr;

				// ++(*i);
				// return curr;

				if(ctx & PARENS_OPEN)
					return curr;
				++(*i);
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
				if(((ctx & READ_PARENT) || (ctx & SKIP_PARENT)) &&
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

void _print_tree(Tree* tree, int depth, bool end)
{
	print_indent_str(depth, "  ");
	if(tree_is_atomic(tree))
	{
		printf("%s", tree->str);
	}
	else if(tree_is_singular(tree))
	{
		Tree *child = (tree->left == NULL) ? tree->right : tree->left;
		if(tree_is_atomic(child))
		{
			printf("%s( %s )", tree->str, child->str);
		}
		else
		{
			printf("%s(\n", tree->str);
			_print_tree(child, depth+1, end);
			putchar('\n');
			print_indent_str(depth, "  ");
			if(end)
				printf(")%s", tree->str);
			else
				putchar(')');
		}
	}
	else
	{
		printf("%s(\n", tree->str);
		_print_tree(tree->left, depth+1, end);
		printf(",\n");
		_print_tree(tree->right, depth+1, end);
		putchar('\n');
		print_indent_str(depth, "  ");
		if(end)
			printf(")%s", tree->str);
		else
			putchar(')');
	}
}

void print_tree(Tree *tree, bool end)
{
	_print_tree(tree, 0, end);
	putchar('\n');
}






/* ----------------------------------------------- */








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

#define INSTDEFAULT() \
	((Instruction) { .spec = 0, .repeat = 0 })

#define INSTALLOC() (Instruction*) malloc(sizeof(Instruction))



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

void delete_instruction(Instruction* inst)
{
	// ...
	return;
}


static const int PARSE_INNER 	= 1;
static const int READ_INST	 	= 1 << 1;
static const int SIGNED_READ 	= 1 << 2;
static const int BIN_READ		= 1 << 3;
static const int HAS_ASSIGN	 	= 1 << 29;

static const int NOT_FIRST		= 1 << 30;


#define CHECK_FLAG(flags, flag) (((flags) & (flag)) != 0)
#define CHECK_NFLAG(flags, flag) (((flags) & (flag)) == 0)
#define SET_FLAG(flags, flag) flags |= (flag)

static uint8_t INNER_FLAGS[257] = {ZEROESx256, 0};


void init_flags()
{
	if(!INNER_FLAGS[256])
		return;
	INNER_FLAGS[(uint8_t) 'u'] = 0;
	INNER_FLAGS[(uint8_t) 'i'] = READ_SIGNED;
	INNER_FLAGS[(uint8_t) 'b'] = READ_BINARY;

	INNER_FLAGS[(uint8_t) '+'] = BINARY_PLUS;
	INNER_FLAGS[(uint8_t) '-'] = BINARY_MINUS;
	INNER_FLAGS[(uint8_t) '%'] = BINARY_ALIGN;
}

#define CASE(name, symbol) 	\
	case_ ## name :			\
	case symbol 


int compile_expr(Instruction* target, int i, int j)
{
	char* cptr;

}

	

Instruction __compile_single_spec(char str[100])
{
	Instruction item = INSTDEFAULT();
	TargetStack _stack, *stack = &_stack;
	tokenize(str, delims, tokens, 100);
	char* cptr;
	int i=0, flags=0;
	push_target(stack, &item);
	Instruction *target, *temp, tempr = INSTDEFAULT();
	set_top_addr(stack, &target);
	while(i<100 && tokens[i][0])
	{
		cptr = tokens[i];
		switch(*cptr)
		{	
			CASE($, '$'):
				if(*(cptr+1))
					return item;
				if(!flags)
				{
					SET_FLAG(flags, HAS_ASSIGN);
					cptr = tokens[++i];
					for(int j=0; cptr[j]; j++)
					{
						if(!isdigit(cptr[j]) || j == 2) // max 2 digits (max 99)
							return item;
					}
					if(!(*cptr))
						return item;
					if(!alloc_assign(target))
						return item;
					target->assign.target->spec |= LITERAL;
					target->assign.target->env_index = atoi(cptr);
					cptr = tokens[++i];
					if(*(cptr) != '=' || *(cptr+1) != '\0')
						return item;
					cptr = tokens[++i];
					push_target(stack, target->assign.value);
				}
				else
				{
					cptr = tokens[++i];
					for(int j=0; cptr[j]; j++)
					{
						if(!isdigit(cptr[j]) || j == 2) // max 2 digits (max 99)
							return item;
					}
					if(!(*cptr))
						return item;
					target->spec |= GET_ENV;
					target->env_index = atoi(cptr);
					cptr = tokens[++i];
				}
				break;
			CASE(excl, '!'):
				target->read.read_flags |= SKIP_READ;
				cptr = tokens[++i];
				break;	
			CASE(dot, '.'):
				target->read.read_flags |= READ_BIGENDIAN;
				cptr = tokens[++i];
				break;
			CASE(u, 'u'):
			CASE(i, 'i'):
			CASE(b, 'b'):
				if(!alloc_read(target))
					return item;
				target->read.read_flags |= INNER_FLAGS[(uint8_t) *cptr];
				push_target(stack, target->read.read_size);
				cptr = tokens[++i];
				break;
			CASE(B, 'B'):
				// temp = pop_target(stack);
				// if(!alloc_unop(&tempr))
				// 	return item;
				// temp = pop_target(stack);
				// *(target) = tempr;
				// target->unary_expr.unoperand = temp;
				if(!alloc_unop(target))
					return item;
				target->unary_expr.unop |= UNARY_BYTES;
				push_target(stack, target->unary_expr.unoperand);
				cptr = tokens[++i];
				break;
			CASE(plus, '+'):
			CASE(minus, '-'):
			CASE(amp, '%'):
				temp = pop_target(stack);
				if(!alloc_binop(target, false))
				{
					delete_instruction(temp);
					return item;
				}
				target->binary_expr.binop |= INNER_FLAGS[(uint8_t) *cptr];
				target->binary_expr.left = temp;
				push_target(stack, target->binary_expr.right);
				cptr = tokens[++i];
				break;
			CASE(sqopen, '['):

			default:
				return item;

		}

		// read_context:
		// switch(*cptr)
		// {
		// 	case 
		// }
		SET_FLAG(flags, NOT_FIRST);
	}
}


UnpackSpec __compile_parse_str(const char* fmt)
{
	init_flags();
	UnpackSpec spec = {NULL, 1};
	const char* cptr = fmt;
	while(*cptr)
	{
		if(*cptr == ',')
			spec.len++;
		cptr++;
	}

	if(spec.len > 100)
		return spec;
	spec.items = (Instruction*) calloc(spec.len, sizeof(Instruction));
	if(spec.items == NULL)
		return (UnpackSpec) {NULL, -1};

	char currstr[100];
	int idx = 0;
	cptr = fmt;
	bool brk = 0;
	while(idx < 100 && !brk)
	{
		switch(*cptr)
		{
			case ' ':
				cptr++;
				break;
			case '\0':
				brk = true;
				if(!idx)
					break;
			case ',':
				currstr[idx] = '\0';
				idx = 0;
				// __parse_single_spec(currstr);
				cptr++;
				break;
			default:
				currstr[idx] = *cptr;
				cptr++;
				idx++;
				break;
		}
	}
	return spec;
}


