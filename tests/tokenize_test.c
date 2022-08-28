// #include "../src/binunpack.h"
#include "tokentree.h"
#include "stringtree.h"
#include "treecompile.h"
#include <stdio.h>

#define FMT_END ,""

#define FMTS(name, ...) 	\
	const char* name[] = {	\
		__VA_ARGS__			\
		, ""				\
	}

// char arr[1000*3<<2];

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
		// "$1=^u33>>4+(1<<3)",
		// "$99 = ^u32 || uB31. ? $2 := u1:u3",
		// "u($1)->u32==100||@($1+@5)<=u33",
		"$1=($1==(i(99+u32)-{5acd_aaaaa_i0}))?(u32:i32)",
		"u32%2->(^u32=={00dc})",
		""
	};
	for(int i=0; fmt[i][0]; i++)
		debug_parse_str(fmt[i], Quiet, false, false);
}


void string_tree_test()
{
	bool ok;
	StringTree tree;
	SearchResult res;
	init_stringtree(&tree, NULL, 0);
	const char* strs[10] =
	{
		">", "<", "<<", ">>", "<>", "><", "-", "--",
		"<-", "->"
	};
	for(int i=0; i<10; i++)
	{
		ok = stringtree_add_str_u64(&tree, strs[i], 0, 0);
		if(!ok)
			printf("Error adding str!\n");
	}
	// ok = stringtree_add_str(&tree, "->", 1, 10);
	// if(!ok) printf("Error\n");
	// ok = stringtree_add_str(&tree, "--", 2, 11);
	// if(!ok) printf("Error\n");
	// ok = stringtree_add_str(&tree, "<>", 3, 13);
	// if(!ok) printf("Error\n");
	printf("Starting!\n");
	int i;
	size_t errs=0, succeeds=0;
	for(i=0; i<1000000; i++)
	{
		for(int j=0; j<10; j++)
		{
			res = stringtree_find_str(&tree, strs[j]);
			if(res.valid)
				succeeds++;
			else
				errs++;
		}
		res = stringtree_find_str(&tree, ">-");
		if(res.valid)
			succeeds++;
		else
			errs++;
		res = stringtree_find_str(&tree, ">-");
		if(res.valid)
			succeeds++;
		else
			errs++;
	}
	printf("Done! i=%d, errs=%zu, succeeds=%zu\n", i, errs, succeeds);

	// if(!res.valid) printf("Invalid\n");
}

void compile_test()
{
	FMTS(fmts,
		"u(31+1)->$1=={00dc}",
		"$(50+B4)=u59%(10*2)",
		"$1=(u32?u1:u2)"
		);
	const char* fmt;
	for(int i=0; ((fmt = fmts[i])[0]); i++)
	{
		printf("\n\n[INPUT]: %s\n\n", fmt);
		Tree* tree = make_single_token_tree(fmt, Quiet);
		printf("\n--- Tree representation ---\n");
		print_tree(tree, true);
		debug_compile(tree);
		delete_tree(tree);
	}
	// for(int i=0; fmt[i][0]; i++)
	// 	debug_parse_str(fmt[i], Quiet, false, false);

	// const char* fmt = "u(31+1)->$1=={00dc}";
	// const char* fmt = "$(50+B4)=u59%(10*2)";
}




int main()
{
	compile_test();
	// init_char_maps();
	// string_tree_test();
	// simple_tests();
	// bracket_tests();
	// sequence_tests();
	// condition_tests();
	// new_operators_tests();
	return 0;
}

