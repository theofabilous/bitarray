#include "bitbuffer.h"
#include "bitunpackdefs.h"
#include "tokenize.h"
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

#define ZEROESx25 \
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
	0,0,0,0,0,0,0,0,0,0

#define ZEROESx100 \
	ZEROESx25, ZEROESx25, ZEROESx25, \
	ZEROESx25

static char acc[100] 			= { ZEROESx100 };
static int acclen 				= 0;

static char tokens[40][10];
static const char* delims = "%!$=[]<>{}()uiBbcs*+-";


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


// bool compile_insert_inner(const char* fmt,
// 	void* target, int i, int j, int flags)
// {

// }



// ParseItem compile_single_spec_str(const char* fmt, int i, int j)
// {
// 	char c;
// 	ParseItem item = DEFAULT_PARSE_ITEM();
// 	while(  i < j && (c = fmt[i])  ) // fmt[i++]?
// 	{
// 		if(isdigit(c))
// 		{
// 			acclen = 0;
// 			do
// 			{
// 				acc[acclen++] = c;
// 			} while(isdigit( (c = fmt[++i]) ));

// 			acc[acclen] = '\0';
// 			c = fmt[++i];

// 			if(c == '*')
// 			{
// 				item.repeat = atoi(acc);
// 				item.flags |= HasRepeat;
// 			}
// 			else if(c == '=') 
// 			{
// 				item.target = atoi(acc);
// 				item.flags |= HasAssign;
// 			}
// 			else
// 				return item;
// 			c = fmt[++i];
// 		}
// 		else if(isalpha(c))
// 		{

// 		}
// 	}

// }

void parse_single_spec(char str[100])
{

}


ParseSpec compile_parse_str(const char* fmt)
{
	ParseSpec spec = {NULL, 0};
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
				parse_single_spec(currstr);
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

// ParseSpec compile_parse_str(const char* fmt)
// {
// 	ParseSpec spec = {NULL, 0};
// 	Pair indices[1000] = { {0, -1} };
// 	const char* cptr = fmt;
// 	int str_size = strlen(fmt);
// 	while(*(cptr++) != '\0')
// 	{
// 		if(spec.len >= 999)
// 			return (ParseSpec) {NULL, -1};
// 		if(*cptr == ',')
// 		{
// 			indices[spec.len].second = ((int) (cptr - fmt));
// 			while(*(++cptr) == ' '){}
// 			indices[++spec.len] = 
// 				(Pair) { ((int) (cptr - fmt)), -1 };
// 		}
// 	}
// 	indices[spec.len++].second = str_size;
// 	cptr = fmt;
// 	spec.items = (ParseItem*) calloc(spec.len, sizeof(ParseItem));
// 	if(spec.items == NULL)
// 		return (ParseSpec) {NULL, -1};
// 	// int index = 0;

// 	for(int i=0; i<spec.len; i++)
// 		spec.items[i] = compile_single_spec_str(fmt, 
// 			indices[i].first, indices[i].second);

// 	// ...

// }





