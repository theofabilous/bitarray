#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define DECL_TOKENIZE(x, y) \
void tokenize_ ## x ## _ ## y (const char* str, 	\
			 			      const char* delims, 	\
			 				  char dest[x][y])		\
{													\
	const char* prev = str;							\
	const char* c = strpbrk(str, delims);			\
	size_t toksize=0;								\
	int idx=0;										\
													\
	while(c != NULL && idx < x)						\
	{												\
		toksize = c-prev;							\
		if(toksize != 0)							\
		{											\
			strncpy(dest[idx], prev, toksize);		\
			dest[idx][toksize] = '\0';				\
			idx++;									\
		}											\
		dest[idx][0] = *c;							\
		dest[idx][1] = '\0';						\
		prev = ++c;									\
		c = strpbrk(c, delims);						\
		idx++;										\
	}												\
	dest[idx][0] = '\0';							\
}													\
													\


DECL_TOKENIZE(10, 10)
DECL_TOKENIZE(20, 10)
DECL_TOKENIZE(30, 10)
DECL_TOKENIZE(40, 10)
DECL_TOKENIZE(50, 10)

