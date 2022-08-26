#include <stdio.h>

#include "tokentree.h"


FLAG16(TOKEN_BINOP, 0);
FLAG16(TOKEN_PREOP, 1);
FLAG16(TOKEN_POSTOP, 2);
FLAG16(TOKEN_DIGIT, 3);
FLAG16(TOKEN_OPEN, 4);
FLAG16(TOKEN_CLOSE, 5);
FLAG16(TOKEN_SPECIAL, 6);

static uint8_t COMPARISON_PRECEDENCE;
static uint8_t SHIFT_PRECEDENCE;
static uint8_t WALRUS_PRECEDENCE;
static uint8_t ARROW_PRECEDENCE;
static uint8_t LOGICAL_ANDOR_PRECEDENCE;
static uint8_t PRECEDENCE_TABLE[257] = {ZEROESx256, 0};
static uint16_t TOKEN_FLAG_TABLE[257] = {ZEROESx256, 0};

static const char* BIN_OPS = "=+-*%?:<>&|";	//	= --->
static const char* PRE_OPS = "^Bbiu$"; // 		! --->
static const char* POST_OPS = ".";
static const char* _DIGITS = "0123456789";
static const char* OPEN_BRACKETS = "({"; // 	[ --->
static const char* CLOSE_BRACKETS = ")}]";
static const char* SPECIAL_OP = "[!"; // 		<------

static inline void set_precedence(char c, uint8_t precedence)
{
	PRECEDENCE_TABLE[(uint8_t) c] = precedence;
}

static inline uint8_t get_precedence(char c)
{
	return PRECEDENCE_TABLE[(uint8_t) c];
}

#define CHARS2(a, b) (   ( ((uint16_t)(a)) << 8 ) | ( (uint16_t)(b) )   )

static inline uint8_t get_precedence_str(const char* s)
{
	if(s[2] == '\0')
	{
		switch(CHARS2(s[0], s[1]))
		{
			case CHARS2(':', '='):
				return WALRUS_PRECEDENCE;
			case CHARS2('<', '-'):
			case CHARS2('-', '>'):
				return ARROW_PRECEDENCE;
			case CHARS2('&', '&'):
			case CHARS2('|', '|'):
				return LOGICAL_ANDOR_PRECEDENCE;
			case CHARS2('<', '<'):
			case CHARS2('>', '>'):
				return SHIFT_PRECEDENCE;
			default:
				if(s[1] == '=')
					return COMPARISON_PRECEDENCE;
		}
	}
	return get_precedence(*s);
	// if(s[0] == ':' && s[1] == '=')
	// 	return WALRUS_PRECEDENCE;
	// if(s[1] == '=')
	// 	return COMPARISON_PRECEDENCE;
	// bool same_char = s[0] == s[1];
	// bool lefta, righta;
	// if(  same_char && ( (lefta = (s[0] == '<')) || (righta = (s[1] == '>')) )  )
	// 	return SHIFT_PRECEDENCE;
	// else if( (lefta && (s[1] == '-')) || (righta && (s[0] == '-')) )
	// 	return ARROW_PRECEDENCE;
	// else if( same_char && ((s[0] == '&') || (s[0] == '|')))
	// 	return LOGICAL_ANDOR_PRECEDENCE;
	// return get_precedence(*s);
}


static inline bool has_precedence_str(const char* a, const char* b)
{
	if(*a == '\0'
		|| *b == '\0'
		)
		return false;
	uint8_t a_priority = ( (*(a+1)) == '\0' ) ? get_precedence(*a) : get_precedence_str(a);
	uint8_t b_priority = ( (*(b+1)) == '\0' ) ? get_precedence(*b) : get_precedence_str(b);
	return a_priority < b_priority;

}

static inline void dump_precedence(char b, char a)
{
	printf(">> %c: %hhu\n", b, get_precedence(b));
	printf(">> %c: %hhu\n", a, get_precedence(a));
}

void init_precedence_table()
{
	if(PRECEDENCE_TABLE[256] != 0)
		return;
	PRECEDENCE_TABLE[256] = 1;
	// set_precedence('(', 99);
	// set_precedence(')', 99);
	set_precedence('=', 1);
	// set_precedence('[', 1);
	ARROW_PRECEDENCE = 10;
	set_precedence('*', 10);
	set_precedence('?', 20);
	// set_precedence(':', 3);
	set_precedence(':', 55);
	LOGICAL_ANDOR_PRECEDENCE = 57;
	COMPARISON_PRECEDENCE = 70;  // ==, >=, <=, !=
	set_precedence('&', 60);
	set_precedence('|', 60);
	set_precedence('<', 70);
	set_precedence('>', 70);
	WALRUS_PRECEDENCE = 89;
	set_precedence('$', 100);
	set_precedence('u', 100);
	set_precedence('i', 100);
	set_precedence('b', 100);
	set_precedence('B', 105);
	set_precedence('!', 100);
	set_precedence('^', 80);
	set_precedence('.', 90);
	set_precedence('[', 30);
	SHIFT_PRECEDENCE = 60;
	set_precedence('&', 60);
	set_precedence('|', 60);
	set_precedence('%', 50);
	set_precedence('+', 40);
	set_precedence('-', 40);
}

// void init_precedence_table()
// {
// 	if(PRECEDENCE_TABLE[256] != 0)
// 		return;
// 	PRECEDENCE_TABLE[256] = 1;
// 	// set_precedence('(', 99);
// 	// set_precedence(')', 99);
// 	set_precedence('=', 0);
// 	// set_precedence('[', 1);
// 	set_precedence('*', 1);
// 	set_precedence('?', 2);
// 	// set_precedence(':', 3);
// 	set_precedence(':', 6);
// 	COMPARISON_PRECEDENCE = 7;
// 	set_precedence('&', 6);
// 	set_precedence('|', 6);
// 	set_precedence('<', 7);
// 	set_precedence('>', 7);
// 	set_precedence('$', 10);
// 	set_precedence('u', 10);
// 	set_precedence('i', 10);
// 	set_precedence('b', 10);
// 	set_precedence('B', 11);
// 	set_precedence('!', 10);
// 	set_precedence('.', 9);
// 	set_precedence('[', 3);
// 	SHIFT_PRECEDENCE = 6;
// 	set_precedence('&', 6);
// 	set_precedence('|', 6);
// 	set_precedence('%', 5);
// 	set_precedence('+', 4);
// 	set_precedence('-', 4);
// }

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

Tree* new_token_tree(int *i, 
	const char* parent,
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
				printf("parent: %s\n", parent);
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
						if(has_precedence_str(cptr, parent))
						{
							if(loglevel >= Debug)
								printf("'%s' has precendence over '%s', returning\n", cptr, parent);
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
							cptr, 
							list,
							loglevel,
							list_get_curr_br(list)->close,
							parens_node
						);
						curr = temp;
						break;
					// case '<':
					// case '>':
					// 	if(*(cptr+1) == '=')
					// 	{

					// 	}
					// case '=':
					// 	if(*(cptr+1) == '=')
					// 	{
					// 		if(has_precedence_str(cptr, parent))
					// 		{
					// 			if(loglevel >= Debug)
					// 				printf("'%s' has precendence over '%s', returning\n", cptr, parent);
					// 			return curr;
					// 		}
					// 		goto binop_skip_check;
					// 	}
					// 	goto binop;
					case '!':
						if(*(cptr+1) == '=')
						{
							if(has_precedence_str(cptr, parent))
							{
								if(loglevel >= Debug)
									printf("'%s' has precendence over '%s', returning\n", cptr, parent);
								return curr;
							}
							goto binop_skip_check;
						}
						goto preop;
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
						cptr, 
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
				preop:
				list_copy_into(list, *i, curr->str);
				++(*i);
				curr->left = new_token_tree(i, 
					cptr, 
					list, 
					loglevel,
					j,
					parens_node);
				curr->right = NULL;
				break;
			case TOKEN_POSTOP:
				if(has_precedence_str(cptr, parent))
				{
					if(loglevel >= Debug)
						printf("'%s' has precendence over '%s', returning\n", cptr, parent);
					return curr;
				}
				postop_skip_check:
				temp = (Tree*) malloc(sizeof(Tree));
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				curr = temp;
				++(*i);
				break;
			case TOKEN_BINOP:
				binop:
				if(has_precedence_str(cptr, parent))
				{
					if(loglevel >= Debug)
						printf("'%s' has precendence over '%s', returning\n", cptr, parent);
					return curr;
				}
				binop_skip_check:
				temp = (Tree*) malloc(sizeof(Tree));
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				curr = temp;
				++(*i);
				curr->right = new_token_tree(i, 
					cptr, 
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
	return new_token_tree(&i, "", list, loglevel, 0, parens_node);
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

