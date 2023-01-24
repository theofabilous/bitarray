#ifndef INCLUDE__TREECOMPILE__H
#define INCLUDE__TREECOMPILE__H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "tokentree.h"

#define BIT_PROG_STACK_SIZE 512
#define BIT_PROG_INSTR_SIZE 512





#define DECL_UPPER_BYTE_FOR_TYPE(type)			\
	static const size_t _upper_byte_##type = (0xFFULL << ((size_t)(sizeof(type) - 1)))

#define DECL_UPPER_BYTE_FOR_TYPE_2(type_1, type_2)			\
	static const size_t _upper_byte_##type_1##_##type_2 = 	\
		(0xFFULL << ((size_t)(sizeof(type_1 type_2) - 1)))

#define DECL_UPPER_BYTE_FOR_TYPE_3(type_1, type_2, type_3)			\
	static const size_t _upper_byte_##type_1##_##type_2##_##type_3 = 	\
		(0xFFULL << ((size_t)(sizeof(type_1 type_2 type_3) - 1)))

#define SQUISH_TYPE(type)							\
	_Generic( ((type) 0),							\
			unsigned int:		unsigned_int,		\
			unsigned long:		unsigned_long,		\
			unsigned long long: unsigned_long_long,	\
			unsigned char:		unsigned_char,		\
			default:			type				\
	)


DECL_UPPER_BYTE_FOR_TYPE(size_t);
DECL_UPPER_BYTE_FOR_TYPE(long);
DECL_UPPER_BYTE_FOR_TYPE_2(unsigned, long);
DECL_UPPER_BYTE_FOR_TYPE_3(unsigned, long, long);
DECL_UPPER_BYTE_FOR_TYPE(int);
DECL_UPPER_BYTE_FOR_TYPE_2(unsigned, int);

#define _8TH_BYTE 0xFF##00##00##00##00##00##00##00##ULL
#define _7TH_BYTE 0xFF##00##00##00##00##00##00##ULL
#define _6TH_BYTE 0xFF##00##00##00##00##00##ULL
#define _5TH_BYTE 0xFF##00##00##00##00##ULL
#define _4TH_BYTE 0xFF##00##00##00##ULL
#define _3RD_BYTE 0xFF##00##00##ULL
#define _2ND_BYTE 0xFF##00##ULL
#define _1ST_BYTE 0xFF##ULL

#define DECL_MIN_BYTE_WIDTH(type, macro_prefix) 		\
uint8_t _min_byte_width_ ## type (type val)                 \
{                                                           \
	uint8_t width=sizeof(type);                                   \
	size_t curr_mask = _ ## macro_prefix ## _BYTE;          \
	for(; width !=0 && !(val & curr_mask);                  \
		  --width, curr_mask >>= 8                          \
		){}                                                 \
	return width;                                           \
}


// DECL_MIN_BYTE_WIDTH(uint64_t , 8TH);
// DECL_MIN_BYTE_WIDTH(int64_t  , 8TH);
// DECL_MIN_BYTE_WIDTH(uint32_t , 4TH);
// DECL_MIN_BYTE_WIDTH(int32_t  , 4TH);
// DECL_MIN_BYTE_WIDTH(uint16_t , 2ND);
// DECL_MIN_BYTE_WIDTH(int16_t  , 2ND);
//
// uint8_t _min_byte_width_char(char val)
// { return ( val ? 1 : 0); }
// uint8_t _min_byte_width_unsigned_char(unsigned char val)
// { return ( val ? 1 : 0); }
// uint8_t _min_byte_width_int8_t(int8_t val)
// { return ( val ? 1 : 0); }
// uint8_t _min_byte_width_uint8_t(uint8_t val)
// { return ( val ? 1 : 0); }

uint8_t min_byte_width_u64(uint64_t val)
{
	uint8_t width=8;                   
	size_t curr_mask = _8TH_BYTE;

	for(; width !=0 && !(val & curr_mask); --width, curr_mask >>= 8){}

	return width;
}



typedef union push_result_t
{
	uint32_t value;
	struct {
		uint8_t error;
		uint8_t flags;
		union 
		{
			bool bool_v;
			uint16_t index_v;
		};
	};
} push_result_t;

// #define MAKE_PUSH_RESULT_OK(...)									\
// 	((push_result_t) { .error=0, .flags=0, .index_v = (__VA_ARGS__) })

#define PUSH_RET_INDEX(...)											\
	((push_result_t) { .error=0, .flags=0, .index_v = (__VA_ARGS__) })

#define PUSH_RET_BOOL(...)											\
	((push_result_t) { .error=0, .flags=0, .bool_v = (__VA_ARGS__) })

#define MAKE_PUSH_RESULT_ERR(...)										\
	((push_result_t) { .error = (__VA_ARGS__) })


static const uint8_t ERR_SUCCESS 		= 0;
static const uint8_t ERR_GENERIC_ERROR 	= 1;
static const uint8_t ERR_NOT_FOUND 		= 2;
static const uint8_t ERR_TREE_INVALID 	= 3;
static const uint8_t ERR_MEMORY 		= 4;
static const uint8_t ERR_PROG_SIZE 		= 5;
static const uint8_t ERR_STACK_SIZE 	= 6;
static const uint8_t ERR_NULL		 	= 7;
static const uint8_t ERR_VALUE		 	= 8;
static const uint8_t ERR_HANDLE_NORMALLY= 20;

#define PUSHERR_TYPE static const push_result_t
PUSHERR_TYPE PUSH_ERR_GENERIC_ERROR		= MAKE_PUSH_RESULT_ERR(ERR_GENERIC_ERROR);
PUSHERR_TYPE PUSH_ERR_NOT_FOUND 		= MAKE_PUSH_RESULT_ERR(ERR_NOT_FOUND);
PUSHERR_TYPE PUSH_ERR_TREE_INVALID 		= MAKE_PUSH_RESULT_ERR(ERR_TREE_INVALID);
PUSHERR_TYPE PUSH_ERR_MEMORY 			= MAKE_PUSH_RESULT_ERR(ERR_MEMORY);
PUSHERR_TYPE PUSH_ERR_PROG_SIZE 		= MAKE_PUSH_RESULT_ERR(ERR_PROG_SIZE);
PUSHERR_TYPE PUSH_ERR_STACK_SIZE 		= MAKE_PUSH_RESULT_ERR(ERR_STACK_SIZE);
PUSHERR_TYPE PUSH_ERR_NULL 				= MAKE_PUSH_RESULT_ERR(ERR_NULL);
PUSHERR_TYPE PUSH_ERR_VALUE 			= MAKE_PUSH_RESULT_ERR(ERR_VALUE);
PUSHERR_TYPE PUSH_ERR_HANDLE_NORMALLY 	= MAKE_PUSH_RESULT_ERR(ERR_HANDLE_NORMALLY);
#undef PUSHERR_TYPE

typedef union ByteCode
{
	uint8_t code;
	struct { uint8_t l_code: 6, flags: 2; };
} ByteCode;

static const ByteCode unpack_program_end = { .code = 0 };
/*
 * Maybe the flag could be if its a literal/was a read,
 * and then num_lz could just indicate the total size of the literal/read count
 *
 * If has_leading zeroes:
 * [ ... data[size] ... ] [ num_leading zeroes ] [ ptr neg lz size ]
 * Note: size is in bytes (since 5 bits, max size == 31)
 * 		 and num_lz has 8 bits, so if u read a 31 byte value that is all zeroes
 * 		 then num_lz = 0b11111111 bits = 255 bits = 31 bytes (perfect!)
 */ 
typedef union StackValue
{
	char _byte;
	unsigned char _ubyte;
	struct 
	{ 
		uint8_t size: 5, 
				flags: 3; 
	};
	struct 
	{
		uint8_t __size: 5,
				has_leading_zeroes: 1,
				is_negative: 1,
				is_ptr: 1;
	};
} StackValue;

typedef struct UnpackProgram
{
	uint16_t stack_ptr;
	uint16_t instruction_ptr;
	uint16_t flags;
	StackValue stack[BIT_PROG_STACK_SIZE];
	ByteCode instructions[BIT_PROG_INSTR_SIZE];
} UnpackProgram;

static inline bool
unpack_program_finalize(UnpackProgram* prog)
{
	prog->stack_ptr = 0;

	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE)
		return false;

	prog->instructions [
		prog->instruction_ptr
	] = unpack_program_end;

	prog->instruction_ptr = 0;
	prog->flags = 0;

	return true;
}

static inline bool
unpack_program_init(UnpackProgram* prog)
{
	if (prog == NULL)
		return false;

	prog->stack_ptr = 0;
	prog->instruction_ptr = 0;
	prog->flags = 0;

	return true;
}

static inline push_result_t
unpack_program_push_i0(UnpackProgram* prog, ByteCode code)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE)
		return PUSH_ERR_PROG_SIZE;

	code.flags = 0b00;
	prog->instructions [ prog->instruction_ptr++ ] = code;

	return PUSH_RET_INDEX(prog->instruction_ptr-1);
}

static inline push_result_t
unpack_program_push_il1(UnpackProgram* prog, ByteCode code1, ByteCode code2)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	code1.flags = 0b10;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}

static inline push_result_t
unpack_program_push_ir1(UnpackProgram* prog, ByteCode code1, ByteCode code2)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	code1.flags = 0b01;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}

static inline push_result_t
unpack_program_push_i2(UnpackProgram* prog, ByteCode code1, ByteCode code2, ByteCode code3)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-2)
		return PUSH_ERR_PROG_SIZE;

	code1.flags = 0b11;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;
	prog->instructions [ prog->instruction_ptr++ ] = code3;

	return PUSH_RET_INDEX(prog->instruction_ptr-3);
}




#endif /* INCLUDE__TREECOMPILE__H */
