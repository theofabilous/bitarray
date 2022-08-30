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

#ifdef USE_GPERF

#include "tokenhash.h"

static inline bool has_precedence_str(const char* a, const char* b)
{
	if(*a == '\0'
		|| *b == '\0'
		)
		return false;
	uint8_t a_priority, b_priority;
	HashToken* tok;
	a_priority = ( (tok = in_word_set(a, strlen(a))) != NULL ) ? tok->precedence : 0;
	b_priority = ( (tok = in_word_set(b, strlen(b))) != NULL ) ? tok->precedence : 0;
	// uint8_t a_priority = ( (*(a+1)) == '\0' ) ? get_precedence(*a) : get_precedence_str(a);
	// uint8_t b_priority = ( (*(b+1)) == '\0' ) ? get_precedence(*b) : get_precedence_str(b);
	return a_priority < b_priority;

}

static inline uint16_t get_token_flags(const char* s)
{
	if(*s >= '0' && *s <= '9')
		return TOKEN_DIGIT;
	HashToken* tok = in_word_set(s, strlen(s));
	if(tok == NULL)
	{
		return 0;
	}
	return tok->tree_flags;
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

#else

static uint8_t 	COMPARISON_PRECEDENCE;
static uint8_t 	REPEAT_PRECEDENCE;
static uint8_t 	SHIFT_PRECEDENCE;
static uint8_t 	WALRUS_PRECEDENCE;
static uint8_t 	ARROW_PRECEDENCE;
static uint8_t 	LOGICAL_ANDOR_PRECEDENCE;
static uint8_t 	PRECEDENCE_TABLE[257] 		= {ZEROESx256, 0};
static uint16_t TOKEN_FLAG_TABLE[257] 		= {ZEROESx256, 0};
static uint8_t 	BRACKET_TABLE[257]			= {ZEROESx256, 0};

static const char* BIN_OPS 			= "=+-*%?:<>&|";
static const char* PRE_OPS 			= "^Bbiu$@";
static const char* POST_OPS 		= ".";
static const char* _DIGITS 			= "0123456789";
static const char* OPEN_BRACKETS 	= "(";
static const char* CLOSE_BRACKETS 	= ")}]";
static const char* SPECIAL_OP 		= "{[!,";
static const char* READ_OPS			= "^bui.";

static inline void set_precedence(char c, uint8_t precedence)
{
	PRECEDENCE_TABLE[(uint8_t) c] = precedence;
}

static inline uint8_t get_precedence(char c)
{
	return PRECEDENCE_TABLE[(uint8_t) c];
}


static inline uint8_t get_precedence_str(const char* s)
{
	#define CHARS2(a, b) \
		(   ( ((uint16_t)(a)) << 8 ) | ( (uint16_t)(b) )   )

	if(s[2] == '\0')
	{
		switch(CHARS2(s[0], s[1]))
		{
			case CHARS2('*', '*'):
				return REPEAT_PRECEDENCE;
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

	#undef CHARS2
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

	set_precedence('=', 			1);
	ARROW_PRECEDENCE 			= 	10;
	REPEAT_PRECEDENCE 			=	10;
	set_precedence('*', 			REPEAT_PRECEDENCE);
	set_precedence('?', 			20);
	set_precedence(':', 			55);
	LOGICAL_ANDOR_PRECEDENCE 	= 	57;
	COMPARISON_PRECEDENCE 		= 	70;
	set_precedence('&', 			60);
	set_precedence('|', 			60);
	set_precedence('<', 			70);
	set_precedence('>', 			70);
	WALRUS_PRECEDENCE = 			89;
	set_precedence('@', 			100);
	set_precedence('$', 			100);
	set_precedence('u', 			100);
	set_precedence('i', 			100);
	set_precedence('b', 			100);
	set_precedence('B', 			105);
	set_precedence('!', 			100);
	set_precedence('^', 			80);
	set_precedence('.', 			90);
	set_precedence('[', 			30);
	SHIFT_PRECEDENCE = 				60;
	set_precedence('&', 			60);
	set_precedence('|', 			60);
	set_precedence('%', 			50);
	set_precedence('+', 			40);
	set_precedence('-', 			40);
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

	cptr = READ_OPS;
	while(*cptr)
	{
		TOKEN_FLAG_TABLE[(uint8_t) *cptr] |= TOKEN_READ;
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

#endif /* #ifdef USE_GPERF */


#endif /* chartable.h */