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
FLAG32(SEQUENCE_OPEN, 6);

static char tokens[100][10];
static const char* delims = "?:|.%!$=[]<>{}()uiBbcs*+-";


FLAG8(CHAR_TOKEN, 0);
FLAG8(STR_TOKEN, 1);
FLAG8(INT_TOKEN, 2);

static inline bool token_is_valid(Token* tok)
{
	return tok->flags != 0;
}

static inline bool token_is_int(Token* tok)
{
	return tok->flags & INT_TOKEN;
}

static inline bool token_is_char(Token* tok)
{
	return tok->flags & CHAR_TOKEN;
}

static inline void reset_token(Token* tok)
{	
	tok->flags = 0;
	memset(tok->str, '\0', 10*sizeof(char));
}

static inline void set_token_char(Token* tok, char c)
{
	tok->str[0] = c;
	tok->str[1] = '\0';
	tok->flags |= CHAR_TOKEN;
}

static inline bool token_is_str(Token* tok)
{
	return tok->flags & STR_TOKEN;
}

static inline int set_token_int(Token* tok, const char *str)
{
	int i;
	for(i=0; i<10 && isdigit(str[i]); i++)
		tok->str[i] = str[i];
	tok->str[i] = '\0';
	if(i<1)
	{
		reset_token(tok);
		return -1;
	}
	tok->flags |= STR_TOKEN;
	tok->flags |= INT_TOKEN;
	return i;
}

static inline void set_token_str(Token* tok, const char* str)
{
	int i;
	for(i=0; i<10 && str[i]; i++)
		tok->str[i] = str[i];
	tok->str[i] = str[i];
	tok->flags |= STR_TOKEN;
}

static inline bool set_token_strn(Token* tok, const char* str, int len)
{
	if(len > 10)
		return false;
	int i;
	for(i=0; i<len && str[i]; i++)
		tok->str[i] = str[i];
	tok->str[i] = '\0';
	// tok->str[i] = str[i];
	tok->flags |= STR_TOKEN;
	return true;
}

static inline bool bracketpair_is_valid(BracketPair* br)
{
	return br->copen != '\0' && br->cclose != '\0';
}

static inline void list_init(TokenList* list)
{
	list->blen = 0;
	list->len = 0;
	// list->brackets[0] = (BracketPair) {.copen='\0', .cclose='\0'};
	// list->currbr = list->brackets;
	list->currbr = NULL;
	memset(list->tokens, '\0', 100*sizeof(Token));
	memset(list->brackets, '\0', 100*sizeof(BracketPair));
}

static inline bool list_incr_br(TokenList* list)
{
	if(list->currbr == NULL)
	{
		// printf("Yo1\n");
		list->currbr=list->brackets;
		// printf("%s\n", ( (list->currbr == NULL) ? "Null" : "Non-null"));
		return bracketpair_is_valid(list->currbr);
	}
	// printf("Yo2\n");
	return bracketpair_is_valid(++(list->currbr));
}

static inline BracketPair* list_get_curr_br(TokenList* list)
{
	return list->currbr;
}

static inline bool list_curr_br_is_valid(TokenList* list)
{
	return (list->currbr != NULL) && bracketpair_is_valid(list->currbr);
}

static inline void list_reset_curr_br(TokenList* list)
{
	// printf("\nRESET\n\n");
	list->currbr = NULL;
}

static inline bool list_append(TokenList* list, Token* tok)
{
	if(list->len >= 100)
		return false;
	list->tokens[list->len++] = *tok;
	return true;
}

static inline BracketPair* list_register_bracket_open(TokenList* list, char c)
{
	list->brackets[list->blen] = (BracketPair) {.copen = c, .open=list->len, .close=0};
	// list->brackets[list->blen+1] = (BracketPair) {.copen='\0', .cclose='\0'};
	// Token tok = {.flags = CHAR_TOKEN, .c= '('};
	Token tok;
	set_token_char(&tok, c);
	if(!list_append(list, &tok))
		return NULL;
	return &(list->brackets[list->blen++]);
}

static inline Token* list_get(TokenList* list, int index)
{
	if(index > 99 || index < 0)
		return NULL;
	Token* tok = &(list->tokens[index]);
	if(!token_is_valid(tok))
		return NULL;
	return tok;
}

static inline char* list_get_str(TokenList* list, int index)
{
	if(index > 99 || index < 0 || index >= list->len)
		return NULL;
	Token* tok = &(list->tokens[index]);
	if(!token_is_valid(tok) || tok->str[0] == '\0')
		return NULL;
	return tok->str;
}

static inline char list_get_char(TokenList* list, int index)
{
	if(index > 99 || index < 0 || index >= list->len)
		return '\0';
	Token* tok = &(list->tokens[index]);
	if(!token_is_valid(tok))
		return '\0';
	return tok->str[0];
}

static inline bool list_copy_into(TokenList* list, int index, char* dest)
{
	char* str = list_get_str(list, index);
	if(str == NULL)
		return false;
	strcpy(dest, str);
	return true;
}


static inline BracketPair* list_get_br(TokenList* list, int index)
{
	if(index > 99 || index < 0 || index >= list->blen)
		return NULL;
	return &(list->brackets[index]);
}

static inline int list_len(TokenList* list)
{
	return list->len;
}

static inline int list_blen(TokenList* list)
{
	return list->blen;
}

static inline BracketPair* list_within_brackets(TokenList* list, int index)
{
	BracketPair *pair = NULL;
	for(int i=0; i<list_blen(list); i++)
	{
		pair = list_get_br(list, i); 
		if(index > pair->open && index < pair->close)
			return pair;
	}
	return NULL;
}


static inline void stack_init(Stack* stack)
{
	stack->len = 0;
	stack->ptrs[0] = NULL;
}

static inline bool stack_push(Stack* stack, BracketPair* pair)
{
	if(stack->len >= 100)
		return false;
	stack->ptrs[stack->len++] = pair;
	return true; 
}

static inline BracketPair* stack_pop(Stack* stack)
{
	if(stack->len < 1)
		return NULL;
	return (BracketPair*) stack->ptrs[--stack->len];
}


static uint8_t PRECEDENCE_TABLE[257] = {ZEROESx256, 0};

static inline void set_precedence(char c, uint8_t precedence)
{
	PRECEDENCE_TABLE[(uint8_t) c] = precedence;
}

static inline uint8_t get_precedence(char c)
{
	return PRECEDENCE_TABLE[(uint8_t) c];
}

static inline bool has_precedence_over(char a, char b)
{
	if(a == '\0')
		return false;
	uint8_t a_priority = get_precedence(a);
	// if( b == 0)
	// 	return false;
	return a_priority < get_precedence(b);
}

static inline void dump_precedence(char b, char a)
{
	printf(">> %c: %hhu\n", b, get_precedence(b));
	printf(">> %c: %hhu\n", a, get_precedence(a));
}

static const char* BIN_OPS = "=+-*%";
static const char* PRE_OPS = "!Bbiu$";
static const char* POST_OPS = ".";
static const char* _DIGITS = "0123456789";
static const char* OPEN_BRACKETS = "({"; // [
static const char* CLOSE_BRACKETS = ")}]";
static const char* SPECIAL_OP = "[";

FLAG16(TOKEN_BINOP, 0);
FLAG16(TOKEN_PREOP, 1);
FLAG16(TOKEN_POSTOP, 2);
FLAG16(TOKEN_DIGIT, 3);
FLAG16(TOKEN_OPEN, 4);
FLAG16(TOKEN_CLOSE, 5);
FLAG16(TOKEN_SPECIAL, 6);

static uint16_t TOKEN_FLAG_TABLE[257] = {ZEROESx256, 0};


void init_precedence_table()
{
	if(PRECEDENCE_TABLE[256] != 0)
		return;
	PRECEDENCE_TABLE[256] = 1;
	// set_precedence('(', 99);
	// set_precedence(')', 99);
	set_precedence('=', 0);
	// set_precedence('[', 1);
	set_precedence('*', 1);
	set_precedence('$', 10);
	set_precedence('u', 10);
	set_precedence('i', 10);
	set_precedence('b', 10);
	set_precedence('B', 11);
	set_precedence('!', 10);
	set_precedence('.', 9);
	set_precedence('[', 3);
	set_precedence('%', 5);
	set_precedence('+', 4);
	set_precedence('-', 4);
}

void init_token_flag_table()
{
	if(TOKEN_FLAG_TABLE[256] != 0)
		return;
	TOKEN_FLAG_TABLE[256] = 1;
	const char *cptr = BIN_OPS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_BINOP;
		cptr++;
	}

	cptr = PRE_OPS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_PREOP;
		cptr++;
	}

	cptr = POST_OPS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_POSTOP;
		cptr++;
	}

	cptr = _DIGITS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_DIGIT;
		cptr++;
	}

	cptr = OPEN_BRACKETS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_OPEN;
		cptr++;
	}

	cptr = CLOSE_BRACKETS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_CLOSE;
		cptr++;
	}

	cptr = SPECIAL_OP;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_SPECIAL;
		cptr++;
	}
}

static inline uint8_t get_token_flags(char c)
{
	return TOKEN_FLAG_TABLE[(uint8_t) c];
}

static inline char get_matching_brace(char c)
{
	switch(c)
	{
		case '(':
			return ')';
		case ')':
			return '(';
		case '[':
			return ']';
		case ']':
			return '[';
		case '{':
			return '}';
		case '}':
			return '{';
		case '<':
			return '>';
		case '>':
			return '<';
		default:
			return '\0';
	}
}



Tree* new_token_tree(int *i, 
	char parent,
	TokenList* list,
	int loglevel,
	int j,
	bool parens_node)
{

	// char tstr[100];
	Tree* curr = (Tree*) malloc(sizeof(Tree)), *temp = NULL;
	if(curr == NULL)
		return curr;
	curr->str[0] = '\0';
	curr->left = NULL;
	curr->right = NULL;
	char *cptr;
	while(*i<100 && *i < list_len(list))
	{
		cptr = list_get_str(list, *i);
		if(loglevel > Inspect)
		{
			printf("--> %s\n", cptr);
			printf("i: %d, j: %d\n", *i, j);
			if(parent)
			{
				printf("parent: %c\n", parent);
			}		
		}
		if(loglevel >= Full)
		{
			printf("\n. . . . CURR TREE . . . . .\n");
			print_tree(curr, true);
			  printf(". . . . . . . . . . . . . .\n\n");
		}
		switch(get_token_flags(*cptr))
		{
			case TOKEN_DIGIT:
				list_copy_into(list, *i, curr->str);
				(*i)++;
				break;
			case TOKEN_SPECIAL:
				switch(*cptr)
				{
					case '[':
						if(has_precedence_over(*cptr, parent))
						{
							if(loglevel >= Debug)
								printf("'%c' has precendence over '%c', returning\n", *cptr, parent);
							return curr;
						}
						if(!list_incr_br(list))
							return curr;
						temp = (Tree*) malloc(sizeof(Tree));
						temp->str[0] = '[';
						temp->str[1] = ']';
						temp->str[2] = '\0';
						// list_copy_into(list, *i, temp->str);
						temp->left = curr;
						// print_tree(temp->left, true);
						++(*i);
						// curr = temp;
						temp->right = new_token_tree(i, 
							*cptr, 
							list,
							loglevel,
							list_get_curr_br(list)->close,
							parens_node
						);
						curr = temp;
						break;
					// case '!':
					// 	if(*(cptr+1))
					default:
						printf("Unrecognized token: %s\n", cptr);
						++(*i);
				}
				break;
			case TOKEN_OPEN:
				// printf("Opening! %s, %d\n", cptr, *i);
				if(!list_incr_br(list))
					return curr;
				++(*i);
				// printf("%hhu --> %hhu\n",
				// 	list_get_curr_br(list)->open,
				// 	list_get_curr_br(list)->close);
				temp = new_token_tree(i, 
						*cptr, 
						list,
						loglevel,
						list_get_curr_br(list)->close,
						parens_node);
				if(parens_node)
				{
					curr->str[0] = *cptr;
					curr->str[1] = get_matching_brace(*cptr);
					curr->str[2] = '\0';
					// ++(*i);
					curr->left = temp;
					// curr->left = new_token_tree(i, 
					// 	*cptr, 
					// 	list,
					// 	loglevel,
					// 	list_get_curr_br(list)->close,
					// 	parens_node);
					curr->right = NULL;
				}
				else
				{
					free(curr);
					curr = temp;
				}
				break;
			case TOKEN_CLOSE:
				if(*i == j)
					return curr;
				else
					++(*i);
				break;
			case TOKEN_PREOP:
				list_copy_into(list, *i, curr->str);
				++(*i);
				curr->left = new_token_tree(i, 
					*cptr, 
					list, 
					loglevel,
					j,
					parens_node);
				curr->right = NULL;
				break;
			case TOKEN_POSTOP:
				if(has_precedence_over(*cptr, parent))
				{
					if(loglevel >= Debug)
						printf("'%c' has precendence over '%c', returning\n", *cptr, parent);
					return curr;
				}
				temp = (Tree*) malloc(sizeof(Tree));
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				curr = temp;
				++(*i);
				break;
			case TOKEN_BINOP:
				if(has_precedence_over(*cptr, parent) 
					// && parent != '['
					)
				{
					if(loglevel >= Debug)
						printf("'%c' has precendence over '%c', returning\n", *cptr, parent);
					return curr;
				}
				temp = (Tree*) malloc(sizeof(Tree));
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				curr = temp;
				++(*i);
				curr->right = new_token_tree(i, 
					*cptr, 
					list, 
					loglevel,
					j,
					parens_node);
				break;
			default:
				printf("Unrecognized token: '%s'\n", cptr);
				++(*i);
		}
	}
	return curr;
}

Tree* create_token_tree(TokenList* list, int loglevel, bool parens_node)
{
	int i=0;
	init_precedence_table();
	init_token_flag_table();
	list_reset_curr_br(list);
	return new_token_tree(&i, '\0', list, loglevel, 0, parens_node);
}

void tokenize(const char* str, 
	TokenList* list, 
	Stack* stack)
{
	list_init(list);
	stack_init(stack);
	Token tok;
	int incr;
	BracketPair* bpair = NULL;
	while(*str && list_len(list) < 100)
	{
		reset_token(&tok);
		if(isdigit(*str))
		{
			incr = set_token_int(&tok, str);
			if(incr < 0)
			{
				list_init(list);
				return;
			}
			str += incr;
		}
		else
		{
			switch(*str)
			{
				case ' ':
					str++;
					continue;
				case '=':
					if(*(str+1) == '=')
					{
						set_token_strn(&tok, str, 2);
						str += 2;
					}
					else
						goto set_char;
					break;
				case '{':
				case '[':
				case '(':
					stack_push(stack, list_register_bracket_open(list, *str));
					str++;
					continue;
				case '}':
				case ']':
				case ')':
					bpair = stack_pop(stack);
					bpair->cclose = *str;
					bpair->close = list_len(list);
					// stack_pop(stack)->close = list_len(list);
					goto set_char;

				case 'u':
				case 'i':
				case '$':
				case 'B':
				case '?':
				case 'b':
				case '*':
				case '.':
				case '+':
				case '-':
				case '%':
				case '!':
					set_char:
					set_token_char(&tok, *str);
					str++;
					break;
				default:
					printf("Unrecognized char: %c\n", *str);
					str++;
					continue;
			}
		}
		list_append(list, &tok);
	}
}


void debug_single_spec(char str[], int loglevel, bool end, bool parens_node)
{
	TokenList list; 
	Stack stack;
	
	printf("\n[$] Parsing ' %s '\n", str);
	printf(". . . . . . . . . . . . . . . . . . . . . . . \n\n");
	tokenize(str, &list, &stack);
	Tree* tree = create_token_tree(&list, loglevel, parens_node);
	print_tree(tree, end);
	delete_tree(tree);
	int j=0;
	char acc1[256];
	char acc2[256];
	char* currstr;

	putchar('\n');
	for(int i=0; i<100 && i<list_len(&list); i++)
	{
		currstr = list_get_str(&list, i);
		bool sw = true;
		while(*currstr)
		{
			acc1[j]= *currstr;
			if(sw)
			{
				acc2[j]= (i % 10) + '0';
				sw = false;
			}
			else
				acc2[j]=' ';
			j++; currstr++;
		}
		acc1[j] = ' ';
		acc2[j] = ' ';
		j++;
	}
	acc1[j] = '\0';
	acc2[j] = '\0';
	printf("%s\n", acc1);
	if(loglevel >= Inspect)
		printf("%s\n\n", acc2);
	else
		putchar('\n');
	// printf("%s\n%s\n\n", acc1, acc2);
	BracketPair* br;
	uint8_t open, close;

	list_reset_curr_br(&list);

	while(loglevel >= Inspect && list_incr_br(&list))
	{
		br = list_get_curr_br(&list);
		open = br->open;
		close = br->close;
		printf("%hhu --> %hhu :: %c --> %c :: '%s' --> '%s'\n",
			open, close, br->copen, br->cclose, list_get_str(&list, open), list_get_str(&list, close));
	}
	printf("----------------------------------------------\n");
}

void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node)
{
	printf("----------------------------------------------\n");
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
				debug_single_spec(currstr, loglevel, end, parens_node);
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


void delete_tree(Tree* tree)
{
	if(tree != NULL)
	{
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
}

static inline bool tree_is_atomic(Tree* tree)
{
	return (tree->left == NULL && tree->right == NULL);
}

static inline bool tree_is_singular(Tree* tree)
{
	return ( (tree->left != NULL && tree->right == NULL)
		     || (tree->left == NULL && tree->right != NULL) );
}

static inline bool tree_is_simple(Tree* tree)
{
	if(!tree_is_singular(tree))
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
			if(end)
				printf("%s", tree->str);
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
	else if(tree_is_bisimple(tree))
	{
		printf("%s( %s , %s )", tree->str, tree->left->str, tree->right->str);
		if(end)
			printf("%s", tree->str);
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

