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
	if(*prev)										\
	{												\
		strncpy(dest[idx], prev, toksize);			\
		dest[idx][toksize] = '\0';					\
		idx++;										\
	}												\
	dest[idx][0] = '\0';							\
}


void tokenize(const char* str,
			   const char* delims,
			   char dest[][10],
			   int max_tokens)
{
	const char* prev = str;
	const char* c = strpbrk(str, delims);
	size_t toksize=0;
	int idx=0;
					
	while(c != NULL && idx < max_tokens)
	{
		toksize = c-prev;
		if(toksize != 0)
		{									
			strncpy(dest[idx], prev, toksize);
			dest[idx][toksize] = '\0';
			idx++;	
		}									
		dest[idx][0] = *c;					
		dest[idx][1] = '\0';				
		prev = ++c;							
		c = strpbrk(c, delims);				
		idx++;								
	}
	// printf("prev: %s\n", prev);	
	if(*prev)
	{
		strcpy(dest[idx], prev);
		// printf("prev copied: %s\n", dest[idx]);
		idx++;
	}													
	dest[idx][0] = '\0';					
}







