#include "../src/bitunpack.h"


int main()
{
	const char* fmt = "$1=u32%10,i12+(5-2),![B4]";
	// const char* fmt = "$$$$$$$1iii3(((7)";
	__compile_parse_str(fmt);
	return 0;
}

