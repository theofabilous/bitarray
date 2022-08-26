#include "stringtree.h"


void init_char_flags()
{
	if(CHAR_MAP[256])
		return;

	CHAR_MAP[256] = 1;

	for(uint16_t i=0; i<256; i++)
	{
		if(i<=32)
			CHAR_MAP[i] = CHAR_INVALID;
		else if(i <= 47)
			CHAR_MAP[i] = CHAR_SYMBOL; 						// !"#$%&'()*+,-./
		else if(i <= 57)
			CHAR_MAP[i] = CHAR_DIGIT | CHAR_HEX; 				// 0123456789
		else if(i <= 64)
			CHAR_MAP[i] = CHAR_SYMBOL;						// :;<=>?@
		else if(i <= 70)
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_UPPER | CHAR_HEX;	// ABCDEF
		else if(i <= 90)
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_UPPER;			// GHIJKLMNOPQRSTUVWXYZ	
		else if(i <= 96)
			CHAR_MAP[i] = CHAR_SYMBOL;						// [\]^_`
		else if(i <= 102)
			CHAR_MAP[i] = CHAR_ALPHA | CHAR_HEX;				// abcdef
		else if(i <= 122)
			CHAR_MAP[i] = CHAR_ALPHA;							// ghijklmnopqrstuvwxyz
		else if(i <= 126)
			CHAR_MAP[i] = CHAR_SYMBOL;						// {|}~
		else
			CHAR_MAP[i] = CHAR_INVALID;
	}
}