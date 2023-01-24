#include <stdio.h>
#include <stdbool.h>

// #include "common.h"
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

static inline uint8_t 
find_next_token_greedy (
	const char* str,
	HashToken* initial_token,
	char* buff
)
{
	HashToken* result = NULL;
	uint8_t i=1, 
		search_size = initial_token->max_search_size;

	for(; i < search_size && str[i]; i++)
		buff[i] = str[i];
	
	buff[i] = '\0';

	while(i>1)
	{
		result = in_word_set(buff, i);
		if (result == NULL)
			buff[i--] = '\0';
		else
		{
			*initial_token = *result;
			return i;
		}
	}

	return i;
}

void tokenize(const char* str,
	TokenList* list,
	Stack *stack)
{
	list_init(list);
	stack_init(stack);
	Token tok;
	int incr;
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

		while(i > 1 && (temp == NULL))
		{
			temp = in_word_set(curr, i);
			if(temp == NULL)
				curr[i--] = '\0';
			else
				res = temp;
		}
		// i = find_next_token_greedy(str, res, &(curr[0]));

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
			stack_push(
				stack, 
				list_register_bracket_open_str(
					list, str, curr[i-1], i
				)
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
			tok.flags |= (STR_TOKEN | RAW_TOKEN);
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

