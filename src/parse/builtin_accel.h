#ifndef INCLUDE_BUILTIN_ACCEL_H
#define INCLUDE_BUILTIN_ACCEL_H

/* 
see:
https://docs.microsoft.com/en-us/cpp/intrinsics/intrinsics-available-on-all-architectures

threads and atomic types:
	https://en.cppreference.com/w/c/language/atomic
	https://en.cppreference.com/w/c/thread

lesser known features:
	https://d3s.mff.cuni.cz/legacy/~holub/c_features.html

arrays vs pointers:
	https://c-faq.com/aryptr/index.html

	on why functions dont like 2d arrays:
	> https://c-faq.com/aryptr/pass2dary.html


*/

#include <stddef.h>

#if __STDC_VERSION__ >= 201112L
	#include <stdalign.h>
#else
	#define alignof(type) offsetof(struct { char c; type d; }, d)
#endif

#ifndef __GNUC__
#	define __typeof__ typeof
#endif

#define UINT_SIZE 	sizeof(unsigned int)
#define ULONG_SIZE	sizeof(unsigned long)
#define ULLONG_SIZE	sizeof(unsigned long long)

#define print_sizes() 						\
	printf("unsigned int: %zu\n"			\
		   "unsigned long: %zu\n"			\
		   "unsigned long long: %zu\n"		\
		   , UINT_SIZE, ULONG_SIZE, ULLONG_SIZE)

#if defined __has_builtin
#	if 	__has_builtin( __builtin_clz ) && 	\
		__has_builtin( __builtin_clzl ) && 	\
		__has_builtin( __builtin_clzll )
#		define __CLZ_U		__builtin_clz 	// unsigned int
#		define __CLZ_UL		__builtin_clzl 	// unsigned long
#		define __CLZ_ULL	__builtin_clzll	// unsigned long long
#	elif !(defined NO_BUILTINS)
#		define NO_BUILTINS
#	endif
#	if 	__has_builtin( __builtin_ctz ) && 	\
		__has_builtin( __builtin_ctzl ) && 	\
		__has_builtin( __builtin_ctzll )
#		define __CTZ_U		__builtin_ctz 	// unsigned int
#		define __CTZ_UL		__builtin_ctzl 	// unsigned long
#		define __CTZ_ULL	__builtin_ctzll // unsigned long long
#	elif !(defined NO_BUILTINS)
#		define NO_BUILTINS
#	endif
#endif

#ifdef NO_BUILTINS
#	error "GNU-style builtin functions are required for this library!"
#endif


#endif /* builtin_accel.h */