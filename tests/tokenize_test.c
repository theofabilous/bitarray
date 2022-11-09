// #include "../src/binunpack.h"
// #include "tokentree.h"
#include "treecompile.h"
// #include "tokenhash.h"
#include <stdio.h>

#include "builtin_accel.h"

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



void compile_test()
{
	// verify_sizes_addrs();
	FMTS(fmts,
		// "u(31+1)->$1=={00dc}",
		// "(u(31)*5) || u32 *> 10",
		// "$1=u32=>m{0x0B |> 1,0b0101 |> 2, 52 |> 3, 52 |> 4, 0x001 |> 5}",
		// "$25=u(i31%%2)%5",
		"b16=>m{0x0B |> u31, u32 |> i16}",
		"u32=>m{0x0B, 0b001, 35}"
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


void align_tests()
{
	char c = 'a', *cp = &c;
	short s = 1, *sp = &s;
	int i = 2, *ip = &i;
	long l = 3, *lp = &l;
	long long ll = 4, *llp = &ll;

	unsigned char buff[8];
	void** ptr;

	memcpy(buff, &cp, 8);
	ptr = (void **) buff;

	uint8_t big_buff[128];

	typedef struct X
	{
		char c[3];
		size_t val;
		void* p;
		short s;
	} X;
	X x = { .c = {'a', 'b', '\0'}, .val = ((size_t) -1), .p = NULL, .s = 2 };

	printf("\n\nsizeof X: %zu\n", sizeof(X));
	printf("offsets: c=%zu, val=%zu, p=%zu, s=%zu\n",
		offsetof(X, c), offsetof(X, val), offsetof(X, p),
		offsetof(X, s));
	printf("Summed sizes: %zu\n", sizeof(x.c) + sizeof(x.val) + sizeof(x.p) + sizeof(x.s));
	printf("Address of first member: %p\n", &(x.c));
	printf("Address of last member: %p\n", &(x.s));
	size_t diff = ((void*)&(x.s)) - ((void*)&(x.c));
	size_t diff_w_size = diff + sizeof(x.s);
	printf("Diff: %zu, diff w/size: %zu\n", diff, diff_w_size);

	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		x.c, x.val, x.p, x.s);

	memcpy(big_buff, &x, sizeof(X));

	X* xp = (typeof(xp)) big_buff;
	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		xp->c, xp->val, xp->p, xp->s);

	memcpy(big_buff, &x, diff_w_size);
	xp = (typeof(xp)) big_buff;
	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		xp->c, xp->val, xp->p, xp->s);

	X xx = { .c = {'A', 'B', '\0'}, .val = ((size_t) 5050505050), .p = (void*) 0xFFFF, .s = 200 };
	memcpy(big_buff + diff_w_size, &xx, diff_w_size);

	xp = ((void*) big_buff + diff_w_size);
	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		xp->c, xp->val, xp->p, xp->s);

	xp->s = 201;
	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		xp->c, xp->val, xp->p, xp->s);

	xp = ((void*) big_buff);
	printf("c: %s, val: %zu, *p: %p, s: %hd\n",
		xp->c, xp->val, xp->p, xp->s);

	#define P printf

	#define print_size(x) 					\
		_Generic( (x), 						\
			int*:	P("ptr!\n"),	\
			char:	P("char!\n")	\
			)
			// // default:  printf("%d\n", 0)		\
			// )

	int a1[1];
	print_size(a1);

	int a2[2];
	print_size(a2);

	int a_[10];
	print_size(a_);

	print_size(c);


}



int main() 
{
	// #define r_alignof(type) offsetof(struct { char c; type d; }, d)

	// printf("alignof int: %zu\n", r_alignof(int));
	// printf("alignof char: %zu\n", r_alignof(char));
	// printf("alignof short: %zu\n", r_alignof(short));
	// printf("alignof long: %zu\n", r_alignof(long));

	// unsigned char buff[8];

	// int y = 3;
	// int *x = &y;
	// printf("*x = %p\n", x);
	// memcpy(buff, &x, 8);
	// int** ptr = buff;
	// printf("ptr = %p\n", *ptr);

	align_tests();




	// print_sizes();
	#if defined __has_builtin
		#if __has_builtin (__builtin_ctzll)
			printf("Has builtin ctzll!\n");
		#else
			printf("No builtin ctzll!\n");
		#endif
	#else
		printf("No builtins!\n");
	#endif
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

