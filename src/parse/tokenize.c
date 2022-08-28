#include <stdio.h>
#include <stdbool.h>

#include "tokenize.h"


/* -------------------------------------------------------- */
// STACK

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
/* -------------------------------------------------------- */

static const int SKIP_MODE = -10;
static const int SET_CHAR_MODE = 1;
// static const SET_STR_
void tokenize(const char* str, 
	TokenList* list, 
	Stack* stack)
{
	list_init(list);
	stack_init(stack);
	Token tok;
	int incr;
	int mode = 0;
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
			list_append(list, &tok);
			continue;
		}
		else
		{
			switch(*str)
			{
				case ' ':
					mode=SKIP_MODE;
					break;
				case '<':
					if(*(str+1) == '-')
					{
						mode=2;
						break;
					}
				case '&':
				case '|':
				case '>':
					if(*(str+1) == *str)
					{
						mode=2;
						break;
					}
				case ':':
				case '!':
				case '=':
					if(*(str+1) == '=')
						mode=2;
					else
						mode=SET_CHAR_MODE;
					break;
				case '{':
					stack_push(stack, list_register_bracket_open(list, *str));
					str++;
					reset_token(&tok);
					for(mode=0; str[mode] && (str[mode] != '}') && (mode<TOKEN_BUFFSIZE); mode++)
						tok.str[mode] = str[mode];
					if(str[mode] != '}')
					{
						printf("Expected matching '}' when tokenizing, not found\n");
						mode = -1;
						break;
					}
					tok.str[mode] = '\0';
					tok.flags |= STR_TOKEN;
					list_append(list, &tok);
					str+=(mode);
					goto bracket_close;
				case '[':
				case '(':
					stack_push(stack, list_register_bracket_open(list, *str));
					mode=SKIP_MODE;
					break;
				case '}':
				case ']':
				case ')':
					bracket_close:
					bpair = stack_pop(stack);
					bpair->cclose = *str;
					bpair->close = list_len(list);
					mode=SET_CHAR_MODE;
					break;
				case '-':
					if(*(str+1) == '>')
					{
						mode=2;
						break;
					}
				case 'u':
				case 'i':
				case '@':
				case '$':
				case 'B':
				case '^':
				case '?':
				case 'b':
				case '*':
				case '.':
				case '+':
				case '%':

					// set_char:
					// set_token_char(&tok, *str);
					// str++;
					mode = SET_CHAR_MODE;
					break;
				default:
					printf("Unrecognized char: %c\n", *str);
					mode=SKIP_MODE;
			}
		}
		if(mode == SKIP_MODE)
		{
			str++;
			mode=0;
			continue;
		}
		else if(mode == SET_CHAR_MODE)
		{
			set_token_char(&tok, *str);
			str++;
		}
		else if(mode > 0)
		{
			set_token_strn(&tok, str, mode);
			str += mode;
		}
		else if(mode != 0)
		{
			printf("Encountered error!\n");
			list_init(list);
			return;
		}
		mode=0;
		list_append(list, &tok);
	}
}