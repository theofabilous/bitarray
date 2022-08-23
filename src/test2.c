#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// void tokenize(const char* str, const char* delims, char** dest)
// {
// 	const char* prev = str;
// 	const char* c = strpbrk(str, delims);
// 	size_t toksize = c-prev;

// 	while(c != NULL)
// 	{
// 		printf("Hi!\n");
// 		(*dest)[0] = *c;
// 		(*dest)[1] = '\0';
// 		printf("Hi!!\n");
// 		// (*dest) = (char[]){*c, '\0'};
// 		strncpy(*(++dest), prev, toksize);
// 		(*dest)[toksize] = '\0';
// 		prev = ++c;
// 		c = strpbrk(c, delims);
// 		toksize = c-prev;
// 		dest++;
// 	}
// 	*dest = NULL;
// }

// void tokenize(const char* str, const char* delims, char dest[10][10])
// {
// 	const char* prev = str;
// 	const char* c = strpbrk(str, delims);
// 	// size_t toksize = c-prev;
// 	size_t toksize;

// 	int idx=0;

// 	while(c != NULL)
// 	{
// 		toksize = c-prev;
// 		dest[idx][0] = *c;
// 		dest[idx][1] = '\0';
// 		// printf("DELIM: %s\n", dest[idx]);
// 		// printf("PREV: %s\n", prev);
// 		// printf("TOKSIZE: %zu\n", toksize);
// 		// (*dest) = (char[]){*c, '\0'};
// 		if(toksize != 0)
// 		{
// 			strncpy(dest[++idx], prev, toksize);
// 			dest[idx][toksize] = '\0';
// 			// printf("NUMS: %s\n", dest[idx]);	
// 		}

// 		prev = ++c;
// 		c = strpbrk(c, delims);
// 		idx++;
// 	}
// 	dest[idx][0] = '\0';
// }

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
}											

DECL_TOKENIZE(10, 10)

// void tokenize(const char* str, const char* delims, char dest[10][10])
// {
// 	const char* prev = str;
// 	const char* c = strpbrk(str, delims);
// 	size_t toksize=0;
// 	int idx=0;

// 	while(c != NULL)
// 	{
// 		toksize = c-prev;
// 		if(toksize != 0)
// 		{
// 			strncpy(dest[idx], prev, toksize);
// 			dest[idx][toksize] = '\0';
// 			idx++;
// 		}
// 		dest[idx][0] = *c;
// 		dest[idx][1] = '\0';
// 		prev = ++c;
// 		c = strpbrk(c, delims);
// 		idx++;
// 	}
// 	dest[idx][0] = '\0';
// }

int main()
{
	// char** destp = (char**) calloc(10, sizeof(char*));
	// for(int i=0; i<10; i++)
	// {

	// }

	char dest[10][10];
	// char** destp = dest;
	const char* str = "$1=[i32+$2]";
	const char* delims = "$=iu+[]";
	tokenize_10_10(str, delims, dest);
	for(int i=0; i<10 && (dest[i][0]); i++)
	{
		printf("%s ", dest[i]);
	}
	// while(*dest != NULL)
	// {
	// 	printf("%s ", *(destp++));
	// }
	printf("\n");
}