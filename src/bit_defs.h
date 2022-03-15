/*

Ugly macro definitions that pollute the main header file

*/

// Just so IDE/editor doesn't complain
#include <stdlib.h>

// Temporary empty instruction
// to place in indented blocks, case statements,
// goto labels, etc.
#define __PASS__ ((void) 0)

// Handle function pointer macro option
#ifdef BITARRAY_OOP
	#if BITARRAY_OOP > 0
		#define __BITARRAY_USE_OOP 1
	#endif
#endif

// Define type that holds the bitarray size
#ifndef BITARRAY_SIZE_T
#define BITARRAY_SIZE_T size_t
#endif

typedef BITARRAY_SIZE_T bitarray_size_t;

uint8_t _bitarray_ssize_t = sizeof(bitarray_size_t);
uint8_t _bitarray_ssize_t_bits = sizeof(bitarray_size_t)<<3;


// Used for the following definitions...
const bitarray_size_t BITARRAY_S_ONE = (bitarray_size_t) 1;
const bitarray_size_t BITARRAY_S_ZERO = (bitarray_size_t) 0;
const bitarray_size_t BITARRAY_S_THREE = (bitarray_size_t) 0b11;

// Defined first as macros so they can be composed
// Otherwise IDE/editor/compiler complains about non-constexprs
#define BITARRAY_UMASK_AMT ((sizeof(bitarray_size_t)<<3)-4)
#define BITARRAY_UMASK (((bitarray_size_t)0xF) << (BITARRAY_UMASK_AMT))
#define BITARRAY_LMASK ~(BITARRAY_UMASK)
#define BITARRAY_MAX_BYTES ((BITARRAY_LMASK) >> 3)

bitarray_size_t bitarray_umask = BITARRAY_UMASK;
uint8_t bitarray_umask_amt = BITARRAY_UMASK_AMT;
bitarray_size_t bitarray_lmask = BITARRAY_LMASK;
bitarray_size_t bitarray_max_bytes = BITARRAY_MAX_BYTES;

// The 4 MSBs in bitarray->size are flags
// Init the mask values instead of computing them each time
bitarray_size_t BITARRAY_MEM_ERR_FLAG = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+3));
bitarray_size_t BITARRAY_ILL_ERR_FLAG = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+2));
bitarray_size_t BITARRAY_FLAG1 = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT+1));
bitarray_size_t BITARRAY_FLAG2 = (BITARRAY_S_ONE << (BITARRAY_UMASK_AMT));
bitarray_size_t BITARRAY_ERR_MASK = (BITARRAY_S_THREE << (BITARRAY_UMASK_AMT+2));

#undef BITARRAY_UMASK_AMT
#undef BITARRAY_UMASK
#undef BITARRAY_LMASK
#undef BITARRAY_MAX_BYTES
