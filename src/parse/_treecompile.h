#ifndef INCLUDE__TREECOMPILE__H
#define INCLUDE__TREECOMPILE__H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "tokentree.h"

#define BIT_PROG_STACK_SIZE 512
#define BIT_PROG_INSTR_SIZE 512



#define _8TH_BYTE 0xFF##00##00##00##00##00##00##00##ULL
#define _7TH_BYTE 0xFF##00##00##00##00##00##00##ULL
#define _6TH_BYTE 0xFF##00##00##00##00##00##ULL
#define _5TH_BYTE 0xFF##00##00##00##00##ULL
#define _4TH_BYTE 0xFF##00##00##00##ULL
#define _3RD_BYTE 0xFF##00##00##ULL
#define _2ND_BYTE 0xFF##00##ULL
#define _1ST_BYTE 0xFF##ULL

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
			uint16_t u16_v;
		};
	};
} push_result_t;

#define PUSH_RET_INDEX(...)											\
	((push_result_t) { .error=0, .flags=0, .index_v = (__VA_ARGS__) })

#define PUSH_RET_VALUE(...)											\
	((push_result_t) { .error=0, .flags=0, .u16_v = (__VA_ARGS__) })

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
} ByteCode;

static const uint8_t ByteCode_flag_mask = 0b11000000;
static const uint8_t ByteCode_code_mask = 0b00111111;

static const uint8_t ByteCode_left_arg_bit 	= 1<<7;
static const uint8_t ByteCode_right_arg_bit = 1<<6;

static const uint8_t ByteCode_no_args_mask		= ByteCode_code_mask;
static const uint8_t ByteCode_left_arg_mask		= ByteCode_left_arg_bit 	| ByteCode_code_mask;
static const uint8_t ByteCode_right_arg_mask	= ByteCode_right_arg_bit 	| ByteCode_code_mask;
static const uint8_t ByteCode_two_args_mask		= 0xFF;

#if BIT_PROG_USE_BITFIELDS
	#define BYTECODE_FMT_CODE(l_code, flags)					\
		(((flags) & 0b11) << 6) | ((l_code) & 0b111111)
#else
	#define BYTECODE_FMT_CODE(l_code, flags)					\
		(((flags) & 0b11) << 6) | ((l_code) & 0b111111)
#endif



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
	char s_char;
	unsigned char u_char;
	struct 
	{ 
		uint8_t size: 5, 
				flags: 3; 
	};
	struct 
	{
		uint8_t: 5,
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
unpack_program_push_u8_i(UnpackProgram* prog, uint8_t code)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE)
		return PUSH_ERR_PROG_SIZE;

	(prog->instructions [ prog->instruction_ptr++ ]).code = code;

	return PUSH_RET_INDEX(prog->instruction_ptr-1);
}

static inline push_result_t
unpack_program_push_2_u8_i(UnpackProgram* prog, uint8_t code1, uint8_t code2)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	(prog->instructions [ prog->instruction_ptr++ ]).code = code1;
	(prog->instructions [ prog->instruction_ptr++ ]).code = code2;

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}

static inline push_result_t
unpack_program_push_u16_i(UnpackProgram* prog, uint16_t code)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	(prog->instructions [ prog->instruction_ptr++ ]).code = (code >> 8);
	(prog->instructions [ prog->instruction_ptr++ ]).code = (0xFF & code);

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}


static inline push_result_t
unpack_program_push_i(UnpackProgram* prog, ByteCode code)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE)
		return PUSH_ERR_PROG_SIZE;

	prog->instructions [ prog->instruction_ptr++ ] = code;

	return PUSH_RET_INDEX(prog->instruction_ptr-1);
}

static inline push_result_t
unpack_program_push_i0(UnpackProgram* prog, ByteCode code)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE)
		return PUSH_ERR_PROG_SIZE;

	code.code &= ByteCode_no_args_mask;
	prog->instructions [ prog->instruction_ptr++ ] = code;

	return PUSH_RET_INDEX(prog->instruction_ptr-1);
}

static inline push_result_t
unpack_program_push_il1(UnpackProgram* prog, ByteCode code1, ByteCode code2)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	// code1.flags = 0b10;
	code1.code &= ByteCode_left_arg_mask;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}

static inline push_result_t
unpack_program_push_ir1(UnpackProgram* prog, ByteCode code1, ByteCode code2)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-1)
		return PUSH_ERR_PROG_SIZE;

	// code1.flags = 0b01;
	code1.code &= ByteCode_right_arg_mask;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;

	return PUSH_RET_INDEX(prog->instruction_ptr-2);
}

static inline push_result_t
unpack_program_push_i2(UnpackProgram* prog, ByteCode code1, ByteCode code2, ByteCode code3)
{
	if (prog->instruction_ptr >= BIT_PROG_INSTR_SIZE-2)
		return PUSH_ERR_PROG_SIZE;

	// code1.flags = 0b11;
	code1.code &= ByteCode_two_args_mask;
	prog->instructions [ prog->instruction_ptr++ ] = code1;
	prog->instructions [ prog->instruction_ptr++ ] = code2;
	prog->instructions [ prog->instruction_ptr++ ] = code3;

	return PUSH_RET_INDEX(prog->instruction_ptr-3);
}




#endif /* INCLUDE__TREECOMPILE__H */
