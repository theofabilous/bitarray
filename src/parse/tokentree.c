#include <stdio.h>

#include "tokentree.h"
#include "chartable.h"
#include "stringtree.h"

static StringTree strmap = { .init = false };

typedef struct TokenSpec
{
	uint8_t precedence;
	uint16_t flags;
	const char* descr;
} TokenSpec;



void delete_tree(Tree* tree)
{
	if(tree == NULL)
		return;
	if(tree->flags & TREE_MANY)
	{
		for(int i=0; i<tree->num_children; i++)
			delete_tree(tree->children[i]);
		free(tree);
	}
	else
	{
		delete_tree(tree->left);
		delete_tree(tree->right);
		free(tree);
	}
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

static inline bool
tree_set_many(Tree* tree, int size, Tree** buff)
{
	if(size < 0)
		return false;
	tree->flags |= TREE_MANY;
	tree->num_children = (size_t) size;
	tree->children = (Tree**) calloc(size, sizeof(Tree*));
	if(tree->children == NULL)
		return false;
	for(int i =0; i<size; i++)
		tree->children[i] = buff[i];
	return true;
}

void _print_tree(Tree* tree, int depth, bool end)
{
	print_indent_str(depth, "  ");
	uint8_t flags = get_tree_details(tree);
	if(flags & TREE_ATOMIC)
	{
		// printf("nutzatom\n");
		printf("%s", tree->str);
	}
	else if(flags & TREE_MANY)
	{
		// printf("nutz\n");
		if(tree->num_children < 1)
		{
			printf("%s()", tree->str);
			return;
		}
		printf("%s(\n", tree->str);
		_print_tree(tree->children[0], depth+1, end);
		for(int i=1; i< tree->num_children; i++)
		{
			printf(",\n");
			_print_tree(tree->children[i], depth+1, end);
		}
		putchar('\n');
		print_indent_str(depth, "  ");
		if(end)
			printf(")%s", tree->str);
		else
			putchar(')');
	}
	else if(flags & TREE_UNARY)
	{
		// printf("nutz p\n");
		BITASSERT((tree->right == NULL));
		if(TREE_LEFT_ATOMIC)
		{
			printf("%s( %s )", tree->str, tree->left->str);
			if(end)
				printf("%s", tree->str);
		}
		else
		{
			printf("%s(\n", tree->str);
			_print_tree(tree->left, depth+1, end);
			putchar('\n');
			print_indent_str(depth, "  ");
			if(end)
				printf(")%s", tree->str);
			else
				putchar(')');
		}
	}
	else if(flags & TREE_BISIMPLE)
	{
		printf("%s( %s , %s )", tree->str, tree->left->str, tree->right->str);
		if(end)
			printf("%s", tree->str);
	}
	else if(flags & TREE_BINARY)
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
	Tree* curr = alloc_binary_tree(), *temp = NULL;
	if(curr == NULL)
		return curr;
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
		if(isalnum(*cptr) && (*(cptr+1) == '{'))
		{
			if(!list_incr_br(list))
				return curr;
			(*i)++;
			curr->str[0] = *cptr;
			curr->str[1] = '!';
			curr->str[2] = '\0';
			int jj = list_get_curr_br(list)->close;
			if(*cptr == 'm' || *cptr == 'l')
			{
				Tree* tree_buff[100];
				int ii, num_children = 0;
				for(;*i <= jj && *i < list_len(list) && num_children < 20; num_children++)
				{
					ii = *i;
					while(list_get_str(list, ii)[0] != ',' && ii < jj)
						ii++;
					temp = new_token_tree(
								i, 
								cptr, 
								list, 
								loglevel, 
								ii, 
								parens_node
								);
					tree_buff[num_children] = temp;
					if(ii == jj)
					{
						num_children++;
						break;
					}
					else
						(*i)++;
				}
				if(	*i != jj 
					|| !( tree_set_many(curr, num_children, tree_buff) )
				  )
				{
					for(; num_children > 0; num_children--)
						free(tree_buff[num_children-1]);
					curr->flags = 0;
				}
				// printf("LISTR %s\n", list_get_str(list, *i));
				++(*i);
				// printf("LISTR %s\n", list_get_str(list, *i));
				// if(parent[0])
				// 	return curr;
				// temp->flags = 0;
				// j = 0;
				// printf("HERE!\n");
				// print_tree(curr, false);
				continue;
			}
			if(*i == j)
				curr->left = NULL;
			else
				curr->left = new_token_tree(
					i,
					cptr,
					list,
					loglevel,
					j,
					parens_node);
			curr->right = NULL;
			continue;
		}
		switch(
			#ifndef USE_GPERF
			get_token_flags(*cptr) & HIDE_READ
			#else
			get_token_flags(cptr) & HIDE_READ
			#endif
			)
		{
			case TOKEN_DIGIT:
				// printf("Digit\n");
				list_copy_into(list, *i, curr->str);
				curr->flags = 1;
				(*i)++;
				break;
			case TOKEN_SPECIAL:
				// printf("Special\n");
				switch(*cptr)
				{
					case ',':
						if(*i == j)
							return curr;
						else
						{
							printf("Hmmmmmm\n");
							return curr;
						}
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
						// temp->flags = 0;
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
					#ifndef USE_GPERF
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
					#endif
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
						temp->flags = 1;
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
			// printf("Open\n");
				if(!list_incr_br(list))
					return curr;
				++(*i);
				temp = new_token_tree(i, 
						cptr, 
						list,
						loglevel,
						list_get_curr_br(list)->close,
						parens_node);
				// temp->flags = 0;
				#ifndef USE_GPERF
				if(parens_node ||
						(  
						((get_token_flags(*parent) & TOKEN_READ) != 0) &&
						((get_token_flags(temp->str[0]) & TOKEN_READ) != 0)
						)
					)
				#else
				if(parens_node ||
						(  
						((get_token_flags(parent) & TOKEN_READ) != 0) &&
						((get_token_flags(temp->str) & TOKEN_READ) != 0)
						)
					)
				#endif
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
			// printf("Close\n");
				if(*i == j)
					return curr;
				else
					++(*i);
				break;
			case TOKEN_PREOP:
			// printf("Preop\n");
				preop:

				list_copy_into(list, *i, curr->str);
				// printf("THE STR: %s\n", curr->str);
				++(*i);
				curr->left = new_token_tree(i, 
					cptr, 
					list, 
					loglevel,
					j,
					parens_node);
				// printf("\n\n\nCOKC AND HVAhuw\n\n\n");
				// print_tree(curr->left, false);
				curr->right = NULL;
				break;
			case TOKEN_POSTOP:
			// printf("Post\n");
				if(has_precedence_str(cptr, parent))
				{
					if(loglevel >= Debug)
						printf("'%s' has precendence over '%s', returning\n", cptr, parent);
					return curr;
				}
				postop_skip_check:
				temp = (Tree*) malloc(sizeof(Tree));
				// temp->flags = 0;
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				curr = temp;
				++(*i);
				break;
			case TOKEN_BINOP:
				binop:
				// printf("Bin\n");
				if(has_precedence_str(cptr, parent))
				{
					if(loglevel >= Debug)
						printf("'%s' has precendence over '%s', returning\n", cptr, parent);
					// print_tree(curr, false);
					return curr;
				}
				binop_skip_check:
				temp = (Tree*) malloc(sizeof(Tree));
				list_copy_into(list, *i, temp->str);
				temp->left = curr;
				// temp->flags = 0;
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
	#ifndef USE_GPERF
		init_precedence_table();
		init_token_flag_table();
	#endif
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

Tree* make_single_token_tree(const char* fmt, int loglevel, bool parens_node)
{
	TokenList list; 
	Stack stack;
	tokenize(fmt, &list, &stack);
	debug_tokenize(&list, loglevel);
	return create_token_tree(&list, loglevel, parens_node);
}

void debug_parse_str(const char* fmt, int loglevel, bool end, bool parens_node)
{
	printf("----------------------------------------------\n");
	char currstr[100];
	int idx = 0;
	const char* cptr = fmt;
	bool brk = 0;
	int num_brackets = 0;
	while(idx < 100 && !brk)
	{
		switch(*cptr)
		{
			case '(':
			case '{':
			case '[':
				num_brackets++;
				goto _default_label;
			case ')':
			case '}':
			case ']':
				num_brackets--;
				goto _default_label;
			case ' ':
				cptr++;
				break;
			case '\0':
				brk = true;
				if(!idx)
					break;
			case ',':
				if(num_brackets == 0)
				{
					currstr[idx] = '\0';
					idx = 0;
					debug_single_spec(currstr, loglevel, end, parens_node);
					cptr++;
					break;	
				}
			default:
				_default_label:
				currstr[idx] = *cptr;
				cptr++;
				idx++;
				break;
		}
	}
}

