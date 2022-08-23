#include <string.h>
#include <stdio.h>

void toktest(char* str, const char* delims)
{
	printf(">> %s\n", str);
	char* tok = strtok(str, delims);
	while(tok != NULL)
	{
		printf("%s ", tok);
		tok = strtok(NULL, delims);
	}
	printf("\n--> %s\n\n", str);
}

void brktest(const char* str, const char* delims)
{
	char *c;
	const char* prev = str;
	printf(">> %s\n", str);
	c = strpbrk(str, delims);
	char temp[100];
	while(c != NULL)
	{
		strncpy(temp, prev, (c - prev));
		temp[(c-prev)] = '\0';
		printf("%s %c ", temp, *c);
		prev = c+1;
		c = strpbrk(c+1, delims);
	}
	printf("\n");
}

int main()
{

	char fmt1[] = "[25]u32";
	char fmt2[] = "$1=[i32+$2]";

	const char* delims = "$=iu+[]";

	toktest(fmt1, delims);
	toktest(fmt2, delims);

	brktest("[25]u32", delims);
	brktest("$1=[i32+$2]", delims);

	// char* token = strtok(fmt1, delims);
	// while (token != NULL)
	// {
	// 	printf("%s\n", token);
	// 	token = strtok(NULL, delims);
	// }
	// printf("%s\n", fmt1);
	// printf("\n---\n");

	// token = strtok(fmt2, delims);
	// while (token != NULL)
	// {
	// 	printf("%s\n", token);
	// 	token = strtok(NULL, delims);
	// }


	return 0;

}