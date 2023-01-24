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

push_result_t
tree_can_be_opcode_arg(Tree* tree)
{
	if (tree == NULL)
		return PUSH_ERR_NULL;

	if (!(tree->flags & TREE_ATOMIC))
		return PUSH_RET_BOOL(false);
	/* ....... */
	/* todo */
	/* ....... */
	return PUSH_RET_BOOL(true);
}

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
push_result_t
compile_atomic_tree (
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
				num_leading_zeroes+=1;
		}
	}

	if (base != 10 && *tree_str == '\0') 
		return PUSH_ERR_GENERIC_ERROR;

	while( *(tree_str++) == '0' ) num_leading_zeroes++;

	/* handle number of leading zeroes having a 
	 * different meaning for different bases!!!!!!!! */

	/* remember to maybe handle size == 0?
	 * can either use this to save space if the const 0 is used
	 * (with/without leading zeroes?? idk yet)
	 * otherwise the size being zero could indicate some special flag thing
	 */

	/* this should maybe be a special instruction:
	 * as of now, values/literals/... can be of size <= 31 bytes
	 * so either:
	 *  - PUSH_CONST is a special instruction whose left operand is the spec
	 *  	(ptr, negative, size) and the right operand can span up to 31 bytes
	 *  - have a special instruction for bigger constants
	 *  - dedicate a smaller (in length) stack-like array in the Program struct
	 *  	to such values, and have a special instruction that pushes such constants onto the stack
	 *  	by indexing them
	 *  - something else..?
	 */

	if (num_leading_zeroes > 0xFF)
		return PUSH_ERR_VALUE;
	
	uint64_t parsed_value = 0;

	if (*tree_str != '\0')
	{
		parsed_value = strtoull(tree_str, NULL, base);
		if (errno == ERANGE)
		{
			errno = 0;
			return PUSH_ERR_VALUE;
		}
	}

	/* Instead of doing the 'check_min_byte_width' thing
	 * and then adding each byte in accordance,
	 * maybe we can just iterate (0xFF << i) and add the masked byte,
	 * and stop when its zero?
	 * this might be dick and balls in terms of byte order/endianness etc,
	 * its a thought but need to look into it */

	/* .... TODO! ...... */
	return PUSH_ERR_GENERIC_ERROR;
	/* .... TODO! ...... */
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
	
	PUSH_RESULT_TRY( ret, tree_can_be_opcode_arg(tree->left) );

	if (ret.bool_v)
	{
		return unpack_program_push_il1 (
			prog,
			tree_get_bytecode(tree, res),
			tree_get_arg_bytecode(tree->left)
		);
	}
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

	/* MAKE SURE ORDER IS RIGHT (forgor) */
	PUSH_RESULT_TRY( ret, _compile_token_tree(tree->left, prog) );

	if (ret.bool_v) /* else if right can be arg */
	{
		return unpack_program_push_ir1 (
			prog,
			tree_get_bytecode(tree, res),
			tree_get_arg_bytecode(tree->right)
		);
	}

	PUSH_RESULT_TRY( ret, _compile_token_tree(tree->right, prog) );

	return unpack_program_push_i0 (
		prog,
		tree_get_bytecode(tree, res)
	);
}
