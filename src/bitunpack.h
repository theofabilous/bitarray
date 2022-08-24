#include "bitbuffer.h"
#include "bitunpackdefs.h"
#include "tokenize.h"
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define ZEROESx32                       \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,    \
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

#define ZEROESx64                       \
    ZEROESx32,                          \
    ZEROESx32

#define ZEROESx128                      \
    ZEROESx64,                          \
    ZEROESx64

#define ZEROESx256                      \
    ZEROESx128,                         \
    ZEROESx128

#define ZEROESx25 \
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
	0,0,0,0,0,0,0,0,0,0

#define ZEROESx100 \
	ZEROESx25, ZEROESx25, ZEROESx25, \
	ZEROESx25

static char acc[100] 			= { ZEROESx100 };
static int acclen 				= 0;



DECL_TOKENIZE(100, 10)
#define tokenize tokenize_100_10
static char tokens[100][10];
static const char* delims = "?:|.%!$=[]<>{}()uiBbcs*+-";




typedef struct Pair
{
	int first, second;
} Pair;

// isprint(char) 					-> check if printable

// isalpha(char) 					-> check if alphabetical
// isdigit(char) 					-> check if digit
// isalnum(char) 					-> check if alphanumeric
// isxdigit(char) 					-> check if hexadecimal digit
// isupper(char) / islower(char) 	-> check upper/lowercase

// tolower(char) / toupper(char)	-> convert case

/*
atof			Convert string to double (function)
atoi			Convert string to integer (function)
atol			Convert string to long integer (function)
atoll			Convert string to long long integer (function)
strtod			Convert string to double (function)
strtof			Convert string to float (function)
strtol			Convert string to long integer (function)
strtold			Convert string to long double (function)
strtoll			Convert string to long long integer (function)
strtoul			Convert string to unsigned long integer (function)
strtoull		Convert string to unsigned long long integer (function)
*/

static const int PARSE_INNER 	= 1;
static const int READ_INST	 	= 1 << 1;
static const int SIGNED_READ 	= 1 << 2;
static const int BIN_READ		= 1 << 3;
static const int HAS_ASSIGN	 	= 1 << 29;


#define CHECK_FLAG(flags, flag) (((flags) & (flag)) != 0)
#define CHECK_NFLAG(flags, flag) (((flags) & (flag)) == 0)
#define SET_FLAG(flags, flag) flags |= (flag)

static uint8_t INNER_FLAGS[257] = {ZEROESx256, 0};

// void init_flags()
// {
// 	if(!READ_FLAGS[256])
// 		return;
// 	READ_FLAGS[(uint8_t) 'u'] = READ_INST;
// 	READ_FLAGS[(uint8_t) 'i'] = READ_INST | SIGNED_READ;
// 	READ_FLAGS[(uint8_t) 'b'] = READ_INST | BIN_READ;
// }

void init_flags()
{
	if(!INNER_FLAGS[256])
		return;
	INNER_FLAGS[(uint8_t) 'u'] = 0;
	INNER_FLAGS[(uint8_t) 'i'] = READ_SIGNED;
	INNER_FLAGS[(uint8_t) 'b'] = READ_BINARY;

	INNER_FLAGS[(uint8_t) '+'] = BINARY_PLUS;
	INNER_FLAGS[(uint8_t) '-'] = BINARY_MINUS;
	INNER_FLAGS[(uint8_t) '%'] = BINARY_ALIGN;
}
	

Instruction compile_single_spec(char str[100])
{
	Instruction item = INSTDEFAULT();
	TargetStack _stack, *stack = &_stack;
	tokenize(str, delims, tokens);
	char* cptr;
	int i=0, val=0, flags=0, tflags=0;
	push_target(stack, &item);
	Instruction *target, *temp, tempr = INSTDEFAULT();
	set_top_addr(stack, &target);
	while(i<100 && tokens[i][0])
	{
		cptr = tokens[i];
		switch(*cptr)
		{	
			case '$':
				if(*(cptr+1))
					return item;
				if(!flags)
				{
					SET_FLAG(flags, HAS_ASSIGN);
					cptr = tokens[++i];
					for(int j=0; cptr[j]; j++)
					{
						if(!isdigit(cptr[j]) || j == 2) // max 2 digits (max 99)
							return item;
					}
					if(!(*cptr))
						return item;
					if(!alloc_assign(target))
						return item;
					target->assign.target->spec |= LITERAL;
					target->assign.target->env_index = atoi(cptr);
					cptr = tokens[++i];
					if(*(cptr) != '=' || *(cptr+1) != '\0')
						return item;
					cptr = tokens[++i];
					push_target(stack, target->assign.value);
				}
				else
				{
					cptr = tokens[++i];
					for(int j=0; cptr[j]; j++)
					{
						if(!isdigit(cptr[j]) || j == 2) // max 2 digits (max 99)
							return item;
					}
					if(!(*cptr))
						return item;
					target->spec |= GET_ENV;
					target->env_index = atoi(cptr);
					cptr = tokens[++i];
				}
				break;
			case '.':
				target->read.read_flags |= READ_BIGENDIAN;
				cptr = tokens[++i];
			case 'u':
			case 'i':
			case 'b':
				if(!alloc_read(target))
					return item;
				target->read.read_flags |= INNER_FLAGS[(uint8_t) *cptr];
				push_target(stack, target->read.read_size);
				cptr = tokens[++i];
				break;
			case 'B':
				// temp = pop_target(stack);
				// if(!alloc_unop(&tempr))
				// 	return item;
				// temp = pop_target(stack);
				// *(target) = tempr;
				// target->unary_expr.unoperand = temp;

				// temp = pop_target(stack);
				// if(!alloc_unop(target))
				// {
				// 	delete_instruction(temp);
				// 	return item;
				// }
				// target->unary_expr.unoperand = temp;
				// target->unary_expr.unop |= UNARY_BYTES;
				if(!alloc_unop(target))
					return item;
				target->unary_expr.unop |= UNARY_BYTES;
				push_target(stack, target->unary_expr.unoperand);
				cptr = tokens[++i];
				break;
			case '+':
			case '-':
			case '%':
				temp = pop_target(stack);
				if(!alloc_binop(target, false))
				{
					delete_instruction(temp);
					return item;
				}
				target->binary_expr.binop |= INNER_FLAGS[(uint8_t) *cptr];
				// free(target->binary_expr.left);
				target->binary_expr.left = temp;
				push_target(stack, target->binary_expr.right);
				cptr = tokens[++i];
				break;
			default:
				return item;

		}
	}
}


UnpackSpec compile_parse_str(const char* fmt)
{
	init_flags();
	UnpackSpec spec = {NULL, 1};
	const char* cptr = fmt;
	while(*cptr)
	{
		if(*cptr == ',')
			spec.len++;
		cptr++;
	}

	if(spec.len > 100)
		return spec;
	spec.items = (UnpackSpec*) calloc(spec.len, sizeof(Instruction));
	if(spec.items == NULL)
		return (UnpackSpec) {NULL, -1};

	char currstr[100];
	int idx = 0;
	cptr = fmt;
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
				// __parse_single_spec(currstr);
				cptr++;
				break;
			default:
				currstr[idx] = *cptr;
				cptr++;
				idx++;
				break;
		}
	}
	return spec;
}



void __parse_single_spec(char str[100])
{
	tokenize(str, delims, tokens);
	// PRINT_TOKENS(40, tokens);
	for(int i=0; i<100 && (tokens[i][0] != '\0'); i++)
		printf("%s ", tokens[i]);
	putchar('\n');
}


void __compile_parse_str(const char* fmt)
{
	// ParseSpec spec = {NULL, 0};
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
				__parse_single_spec(currstr);
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






