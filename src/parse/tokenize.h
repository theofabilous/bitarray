#ifndef INCLUDE_TOKENIZE_H
#define INCLUDE_TOKENIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "common.h"
#include "tokenhash.h"

#ifndef TOKEN_BUFFSIZE
	#define TOKEN_BUFFSIZE 25
#endif


typedef struct Token
{
	uint8_t flags;
	char str[TOKEN_BUFFSIZE];
} Token;

typedef struct BracketPair
{
	char copen, cclose;
	uint8_t open, close;
} BracketPair;

typedef struct Stack
{
	int len;
	void* ptrs[100];
} Stack;

typedef struct TokenList
{
	int len;
	Token tokens[100];
	int blen;
	BracketPair brackets[100];
	BracketPair* currbr;
} TokenList;


void tokenize(const char* str, 
	TokenList* list, 
	Stack* stack);

/* -------------------------------------------------------- */
// TOKEN

FLAG8(CHAR_TOKEN, 0);
FLAG8(STR_TOKEN, 1);
FLAG8(INT_TOKEN, 2);
FLAG8(HEX_TOKEN, 3);
FLAG8(BIN_TOKEN, 4);
FLAG8(RAW_TOKEN, 5);

FLAG16(CheckNext, 0);
FLAG16(NotAllowed, 1);
FLAG16(IntegralPrefix, 2);
FLAG16(ParensOpen, 3);
FLAG16(ParensClose, 4);
FLAG16(BracketLiteral, 5);
FLAG16(TokenDigit, 6);
FLAG16(ParensOpenSpecial, 7);

static const uint8_t INTEGRAL_TOKEN = RAW_TOKEN | INT_TOKEN | HEX_TOKEN | BIN_TOKEN;

static inline bool token_is_valid(Token* tok)
{
	return tok->flags != 0;
}

static inline bool token_is_int(Token* tok)
{
	return tok->flags & INT_TOKEN;
}

static inline bool token_is_integral(Token* tok)
{
	return tok->flags & INTEGRAL_TOKEN;
}

static inline bool token_is_char(Token* tok)
{
	return tok->flags & CHAR_TOKEN;
}

static inline void reset_token(Token* tok)
{	
	tok->flags = 0;
	memset(tok->str, '\0', TOKEN_BUFFSIZE*sizeof(char));
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
	for(i=0; i<TOKEN_BUFFSIZE && isdigit(str[i]); i++)
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

static inline int set_token_hex(Token* tok, const char *str)
{
	int i;
	tok->str[0] = '0';
	tok->str[1] = 'x';
	for(i=2; i<TOKEN_BUFFSIZE && isxdigit(str[i]); i++)
		tok->str[i] = str[i];
	tok->str[i] = '\0';
	if(i<=2)
	{
		reset_token(tok);
		return -1;
	}
	tok->flags |= STR_TOKEN;
	tok->flags |= HEX_TOKEN;
	return i;
}

static inline int set_token_bin(Token* tok, const char *str)
{
	int i;
	tok->str[0] = '0';
	tok->str[1] = 'b';
	for(i=2; i<TOKEN_BUFFSIZE && (str[i] == '0' || str[i] == '1'); i++)
		tok->str[i] = str[i];
	tok->str[i] = '\0';
	if(i<=2)
	{
		reset_token(tok);
		return -1;
	}
	tok->flags |= STR_TOKEN;
	tok->flags |= BIN_TOKEN;
	return i;
}



static inline void set_token_str(Token* tok, const char* str)
{
	int i;
	for(i=0; i<TOKEN_BUFFSIZE && str[i]; i++)
		tok->str[i] = str[i];
	tok->str[i] = str[i];
	tok->flags |= STR_TOKEN;
}

static inline bool set_token_strn(Token* tok, const char* str, int len)
{
	if(len > TOKEN_BUFFSIZE)
		return false;
	int i;
	for(i=0; i<len && str[i]; i++)
		tok->str[i] = str[i];
	tok->str[i] = '\0';
	tok->flags |= STR_TOKEN;
	return true;
}


/* -------------------------------------------------------- */
// BRACKETPAIR

static inline bool bracketpair_is_valid(BracketPair* br)
{
	return br->copen != '\0' && br->cclose != '\0';
}

/* -------------------------------------------------------- */
// LIST

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

static inline BracketPair* 
list_register_bracket_open(
	TokenList* list, 
	char c)
{
	list->brackets[list->blen] = (BracketPair) {.copen = c, .open=list->len, .close=0};
	// list->brackets[list->blen+1] = (BracketPair) {.copen='\0', .cclose='\0'};
	// Token tok = {.flags = CHAR_TOKEN, .c= '('};
	Token tok;
	reset_token(&tok);
	set_token_char(&tok, c);
	if(!list_append(list, &tok))
		return NULL;
	return &(list->brackets[list->blen++]);
}

static inline BracketPair* 
list_register_bracket_open_str(
	TokenList* list, 
	const char* s, 
	char c, 
	int size)
{
	list->brackets[list->blen] = (BracketPair) {.copen = c, .open=list->len, .close=0};
	// list->brackets[list->blen+1] = (BracketPair) {.copen='\0', .cclose='\0'};
	// Token tok = {.flags = CHAR_TOKEN, .c= '('};
	Token tok;
	reset_token(&tok);
	set_token_strn(&tok, s, size);
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


#endif /* tokenize.h */