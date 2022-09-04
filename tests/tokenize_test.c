// #include "../src/binunpack.h"
// #include "tokentree.h"
#include "stringtree.h"
#include "treecompile.h"
// #include "tokenhash.h"
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
//		"![$1]",
//		"$1=u10",
//		"$1=u32%10",
//		"!$33+u5",
//		"$1=u32*2",
		"$1100=!{B4*2}",
//		"$99==u32",
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
//		"$1=u32[B5+i7],$1=(u{32})[B5+i7]",
//		"$1=u32.[5]",
		"$1=B(m{0x0B |> u31,0b0101, 52, 52, u32})+u1",
        "$1=^m{0x0B,0b0101, 52, 52, u32}",
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
}


void verify_sizes_addrs()
{
	// printf("Sizeof codevalue: %zu\n", sizeof(CodeValue));
	// printf("Sizeof instruction: %zu\n", sizeof(Instruction));
	// Instruction x;
	// CodeValue* ptrs_arr[] =
	// {
	// 	&(x.values[0]),
	// 	&(x.values[1]),
	// 	&(x.values[2])
	// };
	// CodeValue* ptrs_un[] =
	// {
	// 	&(x.value),
	// 	0,
	// 	0
	// };
	// CodeValue* ptrs_bin[] =
	// {
	// 	&(x.left), 
	// 	&(x.right),
	// 	0
	// };
	// CodeValue* ptrs_tern[] =
	// {
	// 	&(x._1), 
	// 	&(x._2), 
	// 	&(x._3)
	// };
	// for(int i=0; i<3; i++)
	// {
	// 	printf("%d: %p\n", i, ptrs_arr[i]);
	// 	printf("%d: %p\n", i, ptrs_un[i]);
	// 	printf("%d: %p\n", i, ptrs_bin[i]);
	// 	printf("%d: %p\n", i, ptrs_tern[i]);
	// 	putchar('\n');
	// }
}


void compile_test()
{
	// verify_sizes_addrs();
	FMTS(fmts,
		"u(31+1)->$1=={00dc}",
		"(u(31)*5) || u32 *> 10",
		"$1=u32=>m{0x0B,0b0101, 52, 52, u32}"
		// "u32+r{u31+5}",
		// "i33+5{u31}-{000dc}>>7",
		// "0b1001+0x00AF"
		// "$(50+B4)=u59%(10*2)",
		// "$1=(u32 || 10 ?u1:u2)",
		// "$1=u($1)+u10*10",
		// "u32*10",
		// "u($1?(1:2))[$1+10]",
		// "u(32)[10]"
		// "u1"
		// "u(^i1)"
		// "$1=u(^i1)+u10*10",
		// "u(^i1)+u10*10"
		// "!($1==10?B4:B8)"
		// "u32->^u1==10"
		);
	const char* fmt;
	for(int i=0; ((fmt = fmts[i])[0]); i++)
	{
		printf("\n\n[INPUT]: %s\n\n", fmt);
		Tree* tree = make_single_token_tree(fmt, Quiet, false);
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

void compile_userinput()
{
	char fmt[256];
	char c;
	for(;;)
	{
		printf("Enter an expression: \n>> ");
		fgets(fmt, 256, stdin);
		fmt[ strlen(fmt) - 1 ] = '\0';
		Tree* tree = make_single_token_tree(fmt, Quiet, false);
		if(tree == NULL)
		{
			printf("Incorrectly formatted expression!\n");
			printf("Try again? (Y/n): \n>>");
			c = tolower(getchar());
			getchar();
			if(c != 'Y')
				break;
		}
		printf("\n--- Tree representation ---\n");
		print_tree(tree, true);
		debug_compile(tree);
		delete_tree(tree);
		printf("\nGo again? (Y/n): \n>>");
		c = tolower(getchar());
		getchar();
		if(c != 'y')
			break;
	}
}

void label_test()
{
	/*

	https://stackoverflow.com/questions/6421433/address-of-labels-msvc
	https://docs.microsoft.com/en-us/cpp/assembler/inline/inline-assembler?view=msvc-170
		> https://docs.microsoft.com/en-us/cpp/assembler/inline/jumping-to-labels-in-inline-assembly?view=msvc-170
	https://stackoverflow.com/questions/36983970/labels-as-values-in-clang

	*/
	char inp[256];
	static const void* lvl[] = {&&label0, &&label1, &&label2, &&label3, &&label4, &&label5};
	int idx;

	begin:
	printf("What label? [ 0, 1, 2, 3, 4, 5 ]\n");
	fgets(inp, 256, stdin);
	inp[ strlen(inp) - 1 ] = '\0';
	if(inp[0] == 'q')
	{
		printf("Quitting!\n");
		return;
	}
	idx = inp[0]-'0';
	if(idx > 5)
	{
		printf("idx two high! try again\n");
		goto begin;
	}
	printf("idx: %d\n", idx);
	goto *(lvl[idx]);

	label0:
	printf("LABEL0\n");
	goto begin;

	label1:
	printf("LABEL1\n");
	goto begin;

	label2:
	printf("LABEL2\n");
	goto begin;

	label3:
	printf("LABEL3\n");
	goto begin;

	label4:
	printf("LABEL4\n");
	goto begin;

	label5:
	printf("LABEL5\n");
	goto begin;
}




int main() 
{
	// label_test();
	// gperf_test();
	// compile_userinput();
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

