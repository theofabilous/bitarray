#include <stdio.h>

#include "tokentree.h"
#include "chartable.h"

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
		printf(COLOR_CYAN("%s"), tree->str);
	}
	else if(flags & TREE_MANY)
	{
		// printf("nutz\n");
		if(tree->num_children < 1)
		{
			printf(COLOR_GREEN("%s") "()", tree->str);
			return;
		}
		printf(COLOR_GREEN("%s") "(\n", tree->str);
		_print_tree(tree->children[0], depth+1, end);
		for(int i=1; i< tree->num_children; i++)
		{
			printf(",\n");
			_print_tree(tree->children[i], depth+1, end);
		}
		putchar('\n');
		print_indent_str(depth, "  ");
		if(end)
			printf(")" COLOR_GREEN("%s"), tree->str);
		else
			putchar(')');
	}
	else if(flags & TREE_UNARY)
	{
		// printf("nutz p\n");
		BITASSERT((tree->right == NULL));
		if(flags & TREE_LEFT_ATOMIC)
		{
			printf(COLOR_GREEN("%s") "(" COLOR_CYAN("%s") ")", tree->str, tree->left->str);
			if(end)
				printf(COLOR_GREEN("%s"), tree->str);
		}
		else
		{
			printf(COLOR_GREEN("%s") "(\n", tree->str);
			_print_tree(tree->left, depth+1, end);
			putchar('\n');
			print_indent_str(depth, "  ");
			if(end)
				printf(")" COLOR_GREEN("%s"), tree->str);
			else
				putchar(')');
		}
	}
	else if(flags & TREE_BISIMPLE)
	{
		printf(COLOR_GREEN("%s") "(" COLOR_CYAN("%s") "," COLOR_CYAN("%s") ")", 
				tree->str, tree->left->str, tree->right->str
		);
		if(end)
			printf(COLOR_GREEN("%s"), tree->str);
	}
	else if(flags & TREE_BINARY)
	{
		printf(COLOR_GREEN("%s") "(\n", tree->str);
		_print_tree(tree->left, depth+1, end);
		printf(",\n");
		_print_tree(tree->right, depth+1, end);
		putchar('\n');
		print_indent_str(depth, "  ");
		if(end)
			printf(")" COLOR_GREEN("%s"), tree->str);
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
	// loglevel = 10000;
	Tree* curr = alloc_binary_tree(), *temp = NULL;
	if(curr == NULL)
		return curr;
	char *cptr;
	Token* tok;
	HashToken* res;
	static void* gotos[] = 
	{
		&&TREE_DEFAULT_0,
		&&TREE_ALLOW_COMMAS_1,
		&&TREE_COMMA_2,
		&&TREE_SQUARE_BRACKET_3,
		&&TREE_CURLY_BRACKET_4,
		&&TREE_PARENS_OPEN_5,
		&&TREE_PARENS_CLOSE_6,
		&&TREE_PREOP_7,
		&&TREE_POSTOP_8,
		&&TREE_BINOP_9
	};
	while(*i<100 && *i < list_len(list))
	{
		// cptr = list_get_str(list, *i);
		
		cptr = (tok = &(list->tokens[*i]))->str;
		if(token_is_integral(tok))
		{
			// printf("Integral! %s\n", cptr);
			list_copy_into(list, *i, curr->str);
			curr->flags = 1;
			(*i)++;
			continue;
		}

		res = in_word_set(cptr, strlen(cptr));
		if(res != NULL)
		{
			// printf("Going to %hhu (%s)\n", res->tree_idx, cptr);
			goto *(gotos[res->tree_idx]);
		}

		TREE_DEFAULT_0:
		printf("Unrecognized token: '%s'\n", cptr);
		++(*i);
		continue;

		TREE_ALLOW_COMMAS_1:
		{
			// printf("Allow commas! %s\n", cptr);
			if(!list_incr_br(list))
			{
				// printf("Bracket error! %s\n", cptr);
				return curr;
			}
			(*i)++;
			curr->str[0] = *cptr;
			curr->str[1] = '!';
			curr->str[2] = '\0';
			int jj = list_get_curr_br(list)->close;
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
			++(*i);
			continue;
		}

		TREE_COMMA_2:
		{
			if(*i == j) return curr;
			else return curr; /* to do */
		}

		TREE_SQUARE_BRACKET_3:
		{
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
			continue;
		}

		TREE_CURLY_BRACKET_4:
		{
			++(*i);
			if(!list_incr_br(list))
				return curr;
			curr->str[0] = '{';
			curr->str[1] = '}';
			curr->str[2] = '\0';
			temp = (Tree*) malloc(sizeof(Tree));
			temp->left = NULL;
			temp->right = NULL;
			temp->flags = 1;
			cptr = list_get_str(list, *i);
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
			++(*i);
			continue;
		}

		TREE_PARENS_OPEN_5:
		{
			if(!list_incr_br(list))
				return curr;
			++(*i);
			temp = new_token_tree(i, 
					cptr, 
					list,
					loglevel,
					list_get_curr_br(list)->close,
					parens_node);
			if(parens_node ||
					(  
					((get_token_flags(parent) & TOKEN_READ) != 0) &&
					((get_token_flags(temp->str) & TOKEN_READ) != 0)
					)
				)
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
			continue;
		}

		TREE_PARENS_CLOSE_6:
		{		
			// if (*i == j)
			// {
			// 	++(*i);
			// 	return curr;
			// }
			// printf(COLOR_RED("Somethings wrong! ") "%s\n", cptr);
			// return curr;
			if(*i == j)
			{
				// printf("Returning!\n");
				// printf("Returning and Incrementing!\n");
				// ++(*i); /* NEW */
				return curr;
			}
			else
			{
				// printf("Incrementing\n");
				++(*i);
			}
			continue;
		}

		TREE_PREOP_7:
		{
			list_copy_into(list, *i, curr->str);
			++(*i);
			curr->left = new_token_tree(i, 
				cptr, 
				list, 
				loglevel,
				j,
				parens_node);
			curr->right = NULL;
			continue;
		}

		TREE_POSTOP_8:
		{
			if(has_precedence_str(cptr, parent))
			{
				if(loglevel >= Debug)
					printf("'%s' has precendence over '%s', returning\n", cptr, parent);
				return curr;
			}
			temp = (Tree*) malloc(sizeof(Tree));
			list_copy_into(list, *i, temp->str);
			temp->left = curr;
			curr = temp;
			++(*i);
			continue;
		}

		TREE_BINOP_9:
		{
			if(has_precedence_str(cptr, parent))
			{
				if(loglevel >= Debug)
					printf("'%s' has precendence over '%s', returning\n", cptr, parent);
				return curr;
			}
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
			continue;
		}
	}
	return curr;
}

Tree* create_token_tree(TokenList* list, int loglevel, bool parens_node)
{
	int i=0;
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

