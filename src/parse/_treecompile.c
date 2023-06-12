#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "_treecompile.h"
#include "common.h"
#include "tokentree.h"

FLAG16(REQUIRE_SIMPLE, 	0);
FLAG16(UNARY_SPEC, 		1);
FLAG16(BINARY_SPEC, 	2);
FLAG16(TERNARY_SPEC, 	3);
FLAG16(NO_RETURN,		8);
FLAG16(MOD_SPECIAL,		10);
FLAG16(LOOP_SPECIAL,	11);
FLAG16(BOOL_CHECK, 		12);
FLAG16(READ_COLLAPSE, 	13);
FLAG16(ACCESS_SPECIAL, 	14);
FLAG16(OTHER_SPECIAL, 	15);
// FLAG16(REQUIRE_SPECIAL, 15);

static const uint16_t REQUIRE_SPECIAL = LOOP_SPECIAL | READ_COLLAPSE | BOOL_CHECK | OTHER_SPECIAL;

#define BIT_PROG_ALWAYS_PUSH 0

#if defined(__has_builtin)
	#if __has_builtin(__builtin_expect)
		#define SANITY_CHECK(...) 			\
			(__builtin_expect((__VA_ARGS__), false))
	#else
		#define SANITY_CHECK(...) (__VA_ARGS__)
	#endif
#else
		#define SANITY_CHECK(...) (__VA_ARGS__)
#endif

#define CHARS_2_NUM_VALUE(c1, c2) ( ((c1) << 8) | (c2) )

#define GET_RES_FLAGS(res) ((res)->compile_flags)
#define GET_RES_STR(res) ((res)->descr)
#define CHECK_RES_VALID(res) ((res) != NULL)
#define RESULT_IS_SPECIAL(...) ( (__VA_ARGS__)->compile_idx != 0 ) 

#define BIT_CONCAT2(x, y) 0b##x##y

/*
 * What if the generated code was really just
 * an array of indices that represent goto labels?
 * (Except for special cases like LOAD_CONST, etc.)
 *  --> optimization: if its a special case, set its byte code to 0
 *  and jump to the 0th label which handles special cases
 *  (probs prevents some branch mispredictions)
 */ 


push_result_t
compile_atomic_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
);

push_result_t
compile_unary_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
);

push_result_t
compile_binary_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
);

push_result_t
compile_special_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
);

push_result_t
_compile_token_tree (
	Tree* tree,
	UnpackProgram* prog
);

// push_result_t
// compile_many_tree (
// 	Tree* tree,
// 	UnpackProgram* prog,
// 	uint8_t tree_flags,
// 	HashToken* res
// );


ByteCode
tree_get_bytecode(Tree* tree, HashToken* tok);

ByteCode
tree_get_arg_bytecode(Tree* tree);



#define SANITY_CHECK_TOKEN(...)						\
	if SANITY_CHECK((__VA_ARGS__) == NULL)			\
		return PUSH_ERR_NOT_FOUND

#define SANITY_CHECK_NULL(...)						\
	if SANITY_CHECK((__VA_ARGS__) == NULL)			\
		return PUSH_ERR_NULL

#define SANITY_CHECK_ARITY(flags, arity_flag)		\
	if SANITY_CHECK(!( (flags) & (arity_flag) ))	\
		return PUSH_ERR_TREE_INVALID

#define PUSH_RESULT_TRY( result, ... )				\
	result = (__VA_ARGS__);							\
	if (result.error) return ret

push_result_t
tree_can_be_opcode_arg(Tree* tree)
{
	SANITY_CHECK_NULL(tree);
	SANITY_CHECK_NULL(tree->str);

	if (!(tree->flags & TREE_ATOMIC))
		return PUSH_RET_BOOL(false);

	const char* tree_str = tree->str;

	if ( SANITY_CHECK(*tree_str == '\0') )
		return PUSH_ERR_TREE_INVALID;

	/* if it starts with 0, either the value is actually 0
	 * (which means next char should be null char, otherwise
	 * the formatting is illformed (or its a literal?)
	 * otherwise its a prefix for a different base which,
	 * for now, shall always be pushed on the stack
	 */
	if (*tree_str == '0')
		return PUSH_RET_BOOL(*(tree_str+1) == '\0');

	char *end = NULL;
	unsigned long parsed_value = strtoul(tree_str, &end, 10);

	if (*end != '\0')
		return PUSH_ERR_TREE_INVALID;

	if (parsed_value == 0 || parsed_value > 255 || errno == ERANGE)
		return PUSH_RET_BOOL(false);

	return PUSH_RET_VALUE((uint8_t)parsed_value);
}

push_result_t
_compile_token_tree (
	Tree* tree,
	UnpackProgram* prog
)
{
	HashToken* res = NULL;
	push_result_t ret;
	uint8_t tree_flags = get_tree_details(tree);

	if (tree_flags & TREE_ATOMIC)
	{
		return compile_atomic_tree (
			tree,
			prog,
			tree_flags,
			NULL
		);
	}

	res = in_word_set(tree->str, strlen(tree->str));
	if (res == NULL)
		return PUSH_ERR_NOT_FOUND;

	/* ... check requires ... */

	if (RESULT_IS_SPECIAL(res))
	{
		ret = compile_special_tree(tree, prog, tree_flags, res);
		if (ret.error != ERR_HANDLE_NORMALLY) return ret;
	}

	if (tree_flags & TREE_UNARY)
		return compile_unary_tree(tree, prog, tree_flags, res);

	if (tree_flags & TREE_BINARY)
		return compile_binary_tree(tree, prog, tree_flags, res);

	return PUSH_ERR_TREE_INVALID; /* compile many tree? */
}


/* this should probably be done when creating the token tree,
 * should have a flag that indicates a numerical value is present
 * (or just assume its the case if its atomic/leaf and not the child of '' or {} ?)
 * and just store that value instead of the str
 * >>> Also shouldn't forget to store num_leading_zeroes, signed, ...
 */
/* ANOTHER NOTE:
 *		handle byte sequences that are of size > 8 bytes
 */
push_result_t
__compile_atomic_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
)
{
	push_result_t ret;

	if (res != NULL) return PUSH_ERR_GENERIC_ERROR;
	SANITY_CHECK_ARITY(tree_flags, TREE_ATOMIC);
	SANITY_CHECK_NULL(tree->str);

	const char* tree_str = tree->str;
	int base = 10;
	bool negative = false;
	uint8_t num_leading_zeroes = 0;
	unsigned long long parsed_value = 0;

	if (*tree_str == '-')
	{
		negative = true;
		tree_str++;
	}

	if (*tree_str == '\0') return PUSH_ERR_GENERIC_ERROR;

	if (*tree_str == '0')
	{
		tree_str++;
		switch (*tree_str)
		{
			case 'x':
				base = 16;
				break;
			case 'b':
				base = 2;
				break;
			case 'o':
				base = 8;
				break;
			default:
				if (*tree_str != '\0')
					return PUSH_ERR_VALUE;
				goto skip_parse;
				// num_leading_zeroes+=1;
		}
	}

	if (base != 10 && *tree_str == '\0') 
		return PUSH_ERR_VALUE;

	// uint32_t max_num_zeroes = 0xFF << (base >> 2);
	uint32_t max_num_zeroes = (0xFF+1)>>(base>>2);

	while( *(tree_str++) == '0' ) 
	{
		num_leading_zeroes++;		

		if (num_leading_zeroes >= max_num_zeroes)
			return PUSH_ERR_VALUE;
	}

	// num_leading_zeroes *= base>>1;
	num_leading_zeroes <<= (base>>2); /* lmao */

	if (*tree_str != '\0')
	{
		parsed_value = strtoull(tree_str, NULL, base);
		if (errno == ERANGE)
		{
			errno = 0;
			return PUSH_ERR_VALUE;
		}
	}
	
skip_parse:;

	uint64_t mask = _8TH_BYTE;
	
	PUSH_RESULT_TRY( ret, unpack_program_push_i(prog, (ByteCode){ ByteCode_left_arg_bit }) );
	
	push_result_t ret2;
	uint8_t i=8;
	while (!(parsed_value & mask))
	{
		mask >>= 8;
		i--;
	}

	if	(!mask)
	{
		if (num_leading_zeroes)
		{
			return unpack_program_push_2_u8_i (
				prog,
				0b00100000,
				num_leading_zeroes
			);
		}
		return unpack_program_push_u8_i(prog, 0);
	}



	/* .... TODO! ...... */
	return PUSH_ERR_GENERIC_ERROR;
	/* .... TODO! ...... */
}

push_result_t
compile_atomic_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
)
{
	push_result_t ret;

	/* sanity checks */
	const char* tree_str = tree->str;
	int base = 10;
	bool negative = false;
	uint8_t num_leading_zeroes = 0;
	unsigned long long parsed_value = 0;

	if (*tree_str == '-')
	{
		negative = true;
		tree_str++;
	}

}

push_result_t
compile_unary_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
)
{
	push_result_t ret;

	SANITY_CHECK_TOKEN(res);
	SANITY_CHECK_ARITY(tree_flags, TREE_UNARY);

	/* Either handle here  OR in can_be_opcode_arg OR in compile_atomic:
	 * 		handle literals (possibly add a new tree/node/token (say '...'))
	 *
	 * on second thought, prob should handle this is 'special_tree'
	 *
	 */

#if !BIT_PROG_ALWAYS_PUSH
	PUSH_RESULT_TRY( ret, tree_can_be_opcode_arg(tree->left) );

	if (ret.bool_v)
	{
		return unpack_program_push_il1 (
			prog,
			tree_get_bytecode(tree, res),
			tree_get_arg_bytecode(tree->left)
		);
	}
#endif
	PUSH_RESULT_TRY( ret, _compile_token_tree(tree->left, prog) );

	return unpack_program_push_i0 (
		prog,
		tree_get_bytecode(tree, res)
	);
}

/* Here's a thought:
 * can we assume that left hand operand of '=' or ':=' must always be
 * an env? (i think yes)
 */
push_result_t
compile_binary_tree (
	Tree* tree,
	UnpackProgram* prog,
	uint8_t tree_flags,
	HashToken* res
)
{
	push_result_t ret;

	SANITY_CHECK_TOKEN(res);
	SANITY_CHECK_ARITY(tree_flags, TREE_UNARY);

#if !BIT_PROG_ALWAYS_PUSH
	PUSH_RESULT_TRY( ret, tree_can_be_opcode_arg(tree->left) );

	bool left_can_be_arg = ret.bool_v;

	PUSH_RESULT_TRY( ret, tree_can_be_opcode_arg(tree->right) );

	if(ret.bool_v && left_can_be_arg)
	{
		return unpack_program_push_i2 (
			prog,
			tree_get_bytecode(tree, res),
			tree_get_arg_bytecode(tree->left),
			tree_get_arg_bytecode(tree->right)
		);
	}
#endif

	/* MAKE SURE ORDER IS RIGHT (forgor) */
	PUSH_RESULT_TRY( ret, _compile_token_tree(tree->left, prog) );

#if !BIT_PROG_ALWAYS_PUSH
	if (ret.bool_v) /* else if right can be arg */
	{
		return unpack_program_push_ir1 (
			prog,
			tree_get_bytecode(tree, res),
			tree_get_arg_bytecode(tree->right)
		);
	}
#endif

	PUSH_RESULT_TRY( ret, _compile_token_tree(tree->right, prog) );

	return unpack_program_push_i0 (
		prog,
		tree_get_bytecode(tree, res)
	);
}
