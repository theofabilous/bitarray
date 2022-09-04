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
void _tokenize(const char* str, 
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
		if(*str == '0')
		{
			// str += 2;
			if(*(str+1) == 'x')
				incr = set_token_hex(&tok, str);
			else if(*(str+1) == 'b')
				incr = set_token_bin(&tok, str);
			else
				goto leave_num_fmt;
			if(incr < 0)
			{
				list_init(list);
				return;
			}
			str += incr;
			list_append(list, &tok);
			continue;
		}
		leave_num_fmt:
		if(*(str+1) == '{' &&
			isalnum(*str))
		{
			stack_push(stack, 
				list_register_bracket_open_str(
					list, str, '{', 2)
			);
			str+=2;
			mode=0;
			continue;
		}
		else if(isdigit(*str))
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
				case ';':
				case ',':
					mode = SET_CHAR_MODE;
					break;
				case ' ':
					mode=SKIP_MODE;
					break;
				case '<':
					if(*(str+1) == '-')
					{
						mode=2;
						break;
					}
				case '|':
					if(*(str+1) == '>')
					{
						mode=2;
						break;
					}
				case '&':
				case '>':
					if(*(str+1) == *str)
					{
						mode=2;
						break;
					}
				case ':':
				case '!':
				case '=':
					if(*(str+1) == '='
						|| *(str+1) == '>')
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
					tok.flags |= STR_TOKEN | RAW_TOKEN;
					list_append(list, &tok);
					str+=(mode);
					reset_token(&tok);
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
				case '*':
					if(*(str+1) == '*'
						|| *(str+1) == '>')
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



void tokenize(const char* str,
	TokenList* list,
	Stack *stack)
{
	list_init(list);
	stack_init(stack);
	Token tok;
	int incr;
	int mode = 0;
	uint8_t i = 0;
	BracketPair* bpair = NULL;
	HashToken* res = NULL, *temp = NULL;
	char curr[64] = { '\0', '\0', '\0', '\0' };

	while(*str && list_len(list) < 100)
	{
		i = 0;
		temp = NULL;
		reset_token(&tok);
		curr[0] = *str;
		curr[1] = '\0';
		if( (res = in_word_set(curr, 1)) == NULL )
		{
			switch(*str)
			{
				case ' ':
					str++;
					continue;
				default:
					list_init(list);
					printf("Unable to parse: %s\n", str);
					return;
			}
		}
		for(i=1; i<res->max_search_size && str[i]; i++)
			curr[i] = str[i];


		curr[i] = '\0';
		// printf("\nMax search: %hhu, i: %hhu, str: %s\n", 
		// 	res->max_search_size, i, curr);

		while(i > 1 && (temp == NULL))
		{
			temp = in_word_set(curr, i);
			if(temp == NULL)
			{
				// printf("\t(%hhu) NULL: %s\n", i, curr);
				curr[i] = '\0';
				i--;
			}
			else
			{
				// printf("\t(%hhu) NONNULL: %s\n", i, temp->name);
				res = temp;
			}
		}
		// printf("Got: %s, i=%hhu\n\n", res->name, i);

		if(res->tokenize_flags & IntegralPrefix)
		{
			if(curr[2] != '\0' || curr[0] != '0')
			{
				printf("Invalid integral prefix! %s\n", curr);
				list_init(list);
				return;
			}
			switch(curr[1])
			{
				case 'x':
					incr = set_token_hex(&tok, str);
					break;
				case 'b':
					incr = set_token_bin(&tok, str);
					break;
				default:
					incr = -1;
			}
			if(incr < 0)
			{
				printf("Could not parse formatted integral! %s\n", curr);
				list_init(list);
				return;
			}
			str += incr;
			list_append(list, & tok);
		}
		else if(res->tokenize_flags & TokenDigit)
		{
			incr = set_token_int(&tok, str);
			if(incr < 0)
			{
				list_init(list);
				return;
			}
			str += incr;
			list_append(list, &tok);
		}
		else if(res->tokenize_flags & ParensOpen)
		{
			stack_push(stack, list_register_bracket_open(list, *str));
			str++;
		}
		else if(res->tokenize_flags & ParensOpenSpecial)
		{
			stack_push(stack, 
				list_register_bracket_open_str(
					list, str, '{', i)
			);
			str += i;
		}
		else if(res->tokenize_flags & BracketLiteral)
		{
			stack_push(stack, list_register_bracket_open(list, *str));
			str++;
			reset_token(&tok);
			for(i=0; str[i] && (str[i] != '}') && (i<TOKEN_BUFFSIZE); i++)
				tok.str[i] = str[i];
			if(str[i] != '}')
			{
				printf("Expected matching '}' when tokenizing, not found\n");
				list_init(list);
				return;
			}
			tok.str[i] = '\0';
			tok.flags |= STR_TOKEN | RAW_TOKEN;
			list_append(list, &tok);
			str+=(i);
		}
		else if(res->tokenize_flags & ParensClose)
		{
			bpair = stack_pop(stack);
			bpair->cclose = *str;
			bpair->close = list_len(list);
			set_token_char(&tok, *str);
			str++;
			list_append(list, &tok);
		}
		else
		{
			set_token_strn(&tok, str, i);
			str += i;
			list_append(list, &tok);
		}
	}

}




