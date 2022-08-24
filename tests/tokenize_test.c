#include "../src/binunpack.h"


int main()
{
	const char* fmt[] = {
		"$1=u32%10,i12+(5-2),![B4]", // 0
		"$1=u10",					// 1
		"$1=u32%10",				// 2
		"$25=u(3+$2)-4",			// 3
		"!$33+u5",					// 4
		"$9=u($8+(1+2))-4",			// 5
		"$1=u32%10*2,$1=u(32%10)*2,$1=(u(32%10))*2"		// 6
	};
	debug_parse_str(fmt[6], false);
	// debug_parse_str(fmt[0], false);
	return 0;
}

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
