#include <stdio.h>

#include "tokentree.h"
#include "chartable.h"


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
						temp->left = curr;
						++(*i);
						temp->right = new_token_tree(i, 
							cptr, 
							list,
							loglevel,
							list_get_curr_br(list)->close,
							parens_node
						);
						curr = temp;
						break;
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
					case '{':
						++(*i);
						if(!list_incr_br(list))
							return curr;
						curr->str[0] = '{';
						curr->str[1] = '}';
						curr->str[2] = '\0';
						// cptr = list_get_str(list, *i);
						temp = (Tree*) malloc(sizeof(Tree));
						temp->left = NULL;
						temp->right = NULL;
						cptr = list_get_str(list, *i);
						// printf("cptr: %s\n", cptr);
						list_copy_into(list, *i, temp->str);
						++(*i);
						cptr = list_get_str(list, *i);
						if(cptr[0] != '}')
						{
							printf("Expected matching '}', got '%s'\n", cptr);
							free(temp);
							return curr;
						}
						curr->left = temp;
						curr->right = NULL;
						j = list_get_curr_br(list)->close;
						// printf("J=%d\n", j);
						// ++(*i);
						break;
					default:
						printf("Unrecognized token: %s\n", cptr);
						++(*i);
				}
				break;
			case TOKEN_OPEN:
				if(!list_incr_br(list))
					return curr;
				++(*i);
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
					curr->left = temp;
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

void debug_tokenize(TokenList* list, int loglevel)
{
	int j=0;
	char acc1[256];
	char acc2[256];
	char* currstr;

	putchar('\n');
	for(int i=0; i<100 && i<list_len(list); i++)
	{
		currstr = list_get_str(list, i);
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
	BracketPair* br;
	uint8_t open, close;

	list_reset_curr_br(list);

	while(loglevel >= Inspect && list_incr_br(list))
	{
		br = list_get_curr_br(list);
		open = br->open;
		close = br->close;
		printf("%hhu --> %hhu :: %c --> %c :: '%s' --> '%s'\n",
			open, close, br->copen, br->cclose, list_get_str(list, open), list_get_str(list, close));
	}
}

void debug_single_spec(char str[], int loglevel, bool end, bool parens_node)
{
	TokenList list; 
	Stack stack;
	tokenize(str, &list, &stack);
	
	printf("\n[$] Parsing ' %s '\n", str);
	printf(". . . . . . . . . . . . . . . . . . . . . . . \n");
	debug_tokenize(&list, loglevel);
	printf(". . . . . . . . . . . . . . . . . . . . . . . \n\n");
	
	Tree* tree = create_token_tree(&list, loglevel, parens_node);
	print_tree(tree, end);
	delete_tree(tree);

	debug_tokenize(&list, loglevel);


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

