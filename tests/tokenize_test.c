// #include "../src/binunpack.h"
#include "tokentree.h"


void simple_tests()
{
	const char* fmt[] = {
		"![$1]",
		"$1=u10",
		"$1=u32%10",
		"!$33+u5",
		"$1=u32*2",
		"$1100=!{B4*2}",
		"$99==u32",
		""
	};
  	for(int i=0; fmt[i][0]; i++)
		debug_parse_str(fmt[i], Quiet, false, false);
}

void bracket_tests()
{
	const char* fmt[] = {
		"$25=(u(3+$2)-4)",
		"$9=u($8+(1+2))-4",
		"$1=u32.%10*2,$1=u(B32%10)*2,$1=(u(32%10))*2",
		"$1=u(B32%10)*2",
		"$(50+B4)=u59%(10*2)",
		"$1=u9+10*2,$1=(u{9+10})*2",
		""
  	};
  	for(int i=0; fmt[i][0]; i++)
	  	debug_parse_str(fmt[i], Quiet, false, false);
}

void sequence_tests()
{
	const char* fmt[] = {
		"$1=u32[B5+i7],$1=(u{32})[B5+i7]",
		"$1=u32.[5]",
		""
	};
	for(int i=0; fmt[i][0]; i++)
		debug_parse_str(fmt[i], Quiet, false, false);
}

void condition_tests()
{
	const char* fmt[] = {
		"$1=(u32?u1:u2)",
		// "$1=1==u33?u1+$2:10",
		// "$1=u33>>4+(1<<3)",
		// "$99 = u32==1 || u31==$1 ? $2 := u1:u3",
		"$99 = u32 || u31?1:2",
		// "u($1)->u32==100",
		// "$1=1==u33?u1+$2:10,$1=(1==u33)?(u1+$2:10),$1=(1==u33)?((u1+$2):10)",
		""
	};
 	for(int i=0; fmt[i][0]; i++)
		debug_parse_str(fmt[i], Quiet, false, false);
}

void new_operators_tests()
{
	const char* fmt[] = {
		"$1=^u33>>4+(1<<3)",
		"$99 = ^u32 || Bu31. ? $2 := u1:u3",
		"u($1)->u32==100",
		""
	};
	for(int i=0; fmt[i][0]; i++)
		debug_parse_str(fmt[i], Quiet, false, false);
}


int main()
{
	// simple_tests();
	// bracket_tests();
	// sequence_tests();
	// condition_tests();
	new_operators_tests();
	return 0;
}

// ALSO SEE:
// $1=(u32%10)*2
// which should give: 
/*
=(
  $( 1 )$,
  *(
	u(
	  %( 32 , 10 )%
	)u,
	2
  )*
)=
*/

// SEE fmt[6] (   "$1=u32%10*2,$1=u(32%10)*2,$1=(u(32%10))*2"	 )
// with following precedences:
/*
	set_precedence('*', 11);
	set_precedence('u', 10);
	set_precedence('i', 10);
	set_precedence('b', 10);
	set_precedence('!', 10);
	set_precedence('%', 5);
	set_precedence('+', 4);
	set_precedence('-', 4);
*/

/*

=(
  $1,
  %(
	u( 32 ),
	*(
	  10,
	  2
	)*
  )%
)=
$ 1 = u 32 % 10 * 2 

=(
  $1,
  u(
	*(
	  %(
		32,
		10
	  )%,
	  2
	)*
  )u
)=
$ 1 = u ( 32 % 10 ) * 2 

=(
  $1,
  *(
	u(
	  %(
		32,
		10
	  )%
	)u,
	2
  )*
)=
$ 1 = ( u ( 32 % 10 ) ) * 2 


*/
