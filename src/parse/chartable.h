#ifndef INCLUDE_CHARTABLE_H
#define INCLUDE_CHARTABLE_H

/* 
No associated .c file, these functions and constants
are put in their own file to avoid bloating tokentree.c
and should *only* be included in that file
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "common.h"
#include "tokenhash.h"

#define USE_GPERF



FLAG16(TOKEN_BINOP, 0);
FLAG16(TOKEN_PREOP, 1);
FLAG16(TOKEN_POSTOP, 2);
FLAG16(TOKEN_DIGIT, 3);
FLAG16(TOKEN_OPEN, 4);
FLAG16(TOKEN_CLOSE, 5);
FLAG16(TOKEN_SPECIAL, 6);
FLAG16(TOKEN_READ, 8);
static const uint16_t HIDE_READ = ~TOKEN_READ;


static inline bool has_precedence_str(const char* a, const char* b)
{
	if(*a == '\0' || *b == '\0')
		return false;
	HashToken* tok;
	uint8_t a_priority = ( (tok = in_word_set(a, strlen(a))) != NULL ) ? tok->precedence : 0;
	uint8_t b_priority = ( (tok = in_word_set(b, strlen(b))) != NULL ) ? tok->precedence : 0;
	return a_priority < b_priority;

}

static inline uint16_t get_token_flags(const char* s)
{
	if(*s >= '0' && *s <= '9')
		return TOKEN_DIGIT;
	HashToken* tok = in_word_set(s, strlen(s));
	if(tok == NULL)
		return 0;
	return tok->tree_flags;
}

static inline char get_matching_brace(char c)
{
	static char map[256] = { 
		['('] = ')',
		[')'] = '(',
		['['] = ']',
		[']'] = '[',
		['{'] = '}',
		['}'] = '{',
		['<'] = '>',
		['>'] = '<'
	};
	return map[c];
}



#endif /* chartable.h */