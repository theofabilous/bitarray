#include "../src/bitunpack.h"



int main()
{
	// const char* fmt = "$1=u32%10,i12+(5-2),![B4]";
	// const char* fmt = "$$$$$$$1iii3(((7)";
	// const char* fmt = "$1=u10";
	// const char* fmt = "$1=u32%10";
	const char* fmt0 = "u(3+$2)-4";
	// const char* fmt = "$1=u45+$2,$2=u(0+b1)";
	// const char* fmt2 = "$1=u(45+b6)";
	__compile_parse_str(fmt0);
	return 0;
}

