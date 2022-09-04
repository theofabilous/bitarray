#include <stdlib.h>
#include <string.h>

#include "treecompile.h"
#include "common.h"

#define CHARS2(a, b) \
	(   ( ((uint16_t)(a)) << 8 ) | ( (uint16_t)(b) )   )

// #define COMPILE_LOG
// #define COMPILE_DEBUG
// #define COMPILE_SHOWTREE

#ifdef COMPILE_LOG
	#define DLOG(f, l) printf("Func: %s, line: %d, str: %s\n", f, l, tree->str)
#elif defined(COMPILE_DEBUG)
	#define DLOG(f, l) \
		printf("Func: %s, line: %d, str: %s\n", f, l, tree->str); \
		print_tree(tree, true)
#elif defined(COMPILE_SHOWTREE)
		#define DLOG(f, l) \
			print_tree(tree, true)
#else
	#define DLOG(f, l) ((void) 0)
#endif


// #define WHILE_LOOP_USE_IFN_JUMP


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

static const int GENERIC_ERROR = -1;
static const int NOT_FOUND = -2;
static const int TREE_INVALID = -3;
static const int MEMORY_ERROR = -4;
static const int HANDLE_NORMALLY = -20;

enum CodeValueType
{
	StrType = 0,
	GetType = 1,
	RefType = 2
};

// #define GET_RES_FLAGS(res) ((res).flags)
// #define GET_RES_STR(res) ((res).str_val)
// #define CHECK_RES_VALID(res) ((res).valid)

#define GET_RES_FLAGS(res) ((res)->compile_flags)
#define GET_RES_STR(res) ((res)->descr)
#define CHECK_RES_VALID(res) ((res) != NULL)


void init_codelist(CodeList* list)
{
	list->len = 0;
	list->registers = 0;
	memset(list->items, 0, 200*sizeof(Instruction));
}

static inline int codelist_append(CodeList* list, Instruction instruction)
{
	if(list->len >= 200)
		return -1;
	list->items[(list->len)] = instruction;
	return (list->len)++;
}

static inline Instruction* codelist_get(CodeList* list, int i)
{
	if(i >= list->len)
		return NULL;
	return &(list->items[i]);
}

static inline bool codelist_set(CodeList* list, Instruction instruction, int i)
{
	if(i >= 200)
		return false;
	if(i >= list->len)
		list->len = i+1;
	list->items[i] = instruction;
	return true;
}


static inline bool codelist_shift(CodeList* list, int i, int amt)
{
	if(list->len + amt > 200 || i >= list->len) // need another check
		return false;
	for(int j=(list->len-1); j>=i; j--)
		list->items[j+amt] = list->items[j];
	return true;
}

static inline bool codelist_insert(CodeList* list, int i, Instruction instruction)
{
	if(i >= list->len || list->len >= 200 || !codelist_shift(list, i, 1))
		return false;
	list->items[i] = instruction;
	return true;
}

static inline bool codelist_swap(CodeList* list, int i, int j)
{
	if(i == j || i >= list->len || j >= list->len)
		return false;
	Instruction ins = list->items[j];
	list->items[j] = list->items[i];
	list->items[i] = ins;
	return true;
}


#define MAKESTR(v) ((CodeValue) {.type = StrType, .str_value=(v)})
#define MAKEGET(v) ((CodeValue) {.type = GetType, .i32_value=(v)})
#define MAKEREF(v) ((CodeValue) {.type = RefType, .i32_value=(v)})
#define MAKEJMP(v) ((CodeValue) {.type = RefType, .i32_value=(v)})


static inline bool
check_requires(
	Tree* tree,
	uint8_t flags,
	HashToken* res
	)
{
	DLOG(__func__, __LINE__);
	if(	((GET_RES_FLAGS(res) & REQUIRE_SIMPLE) && ((flags & TREE_SIMPLE) == 0))
		|| (GET_RES_FLAGS(res) & ACCESS_SPECIAL) )
	{
		printf("Require error\n");
		return false;
	}
	return true;
}


static inline int
compile_many_tree(
	Tree* tree,
	CodeList* list,
	uint8_t flags,
	HashToken* res
	)
{
	DLOG(__func__, __LINE__);
	if(tree->num_children < 0)
		return TREE_INVALID;
	int ret2 = list->len, ret1 = codelist_append(list,
		(Instruction)
		{
			.spec = BINARY_SPEC,
			.name = "DO_ALL",
			.values = { MAKEREF(ret2+1) }
		}
	);
	if(ret1 < 0) return ret1;
	for(int i=0; i<tree->num_children; i++)
	{
		if( (tree->children[i] == NULL) ||
			((ret2 = _compile_tokentree(tree->children[i], list)) < 0)
			 )
			return ret2;
	}
	codelist_get(list, ret1)->values[1] = MAKEREF(ret2);
	return ret2;
}



static inline int 
compile_binary_tree(
	Tree* tree, 
	CodeList* list, 
	uint8_t flags,
	HashToken* res
	)
{
	DLOG(__func__, __LINE__);
	int ret1, ret2;
	if(flags & TREE_BISIMPLE)
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= GET_RES_FLAGS(res) | BINARY_SPEC,
					.name 	= GET_RES_STR(res),
					// .left 	= MAKESTR(tree->left->str),
					// .right 	= MAKESTR(tree->right->str)
					.values = {MAKESTR(tree->left->str), MAKESTR(tree->right->str)}
				}
			)
		);
	else if(flags & TREE_LEFT_ATOMIC)
	{
		ret1 = _compile_tokentree(tree->right, list);
		if(ret1 < 0)
			return ret1;
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= GET_RES_FLAGS(res) | BINARY_SPEC,
					.name 	= GET_RES_STR(res),
					// .left 	= MAKESTR(tree->left->str),
					// .right 	= MAKEGET(ret1)
					.values = {MAKESTR(tree->left->str), MAKEGET(ret1)}
				}
			)
		);
	}
	else if(flags & TREE_RIGHT_ATOMIC)
	{
		ret1 = _compile_tokentree(tree->left, list);
		if(ret1 < 0)
			return ret1;
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= GET_RES_FLAGS(res) | BINARY_SPEC,
					.name 	= GET_RES_STR(res),
					.values = {MAKEGET(ret1), MAKESTR(tree->right->str)}
				}
			)
		);
	}
	else
	{
		ret1 = _compile_tokentree(tree->left, list);
		if(ret1 < 0)
			return ret1;
		ret2 = _compile_tokentree(tree->right, list);
		if(ret2 < 0)
			return ret2;
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= GET_RES_FLAGS(res) | BINARY_SPEC,
					.name 	= GET_RES_STR(res),
					// .left 	= MAKEGET(ret1),
					// .right 	= MAKEGET(ret2)
					.values = {MAKEGET(ret1), MAKEGET(ret2)}
				}
			)
		);
	}
}


static inline int
compile_unary_tree(
	Tree* tree, 
	CodeList* list, 
	uint8_t flags,
	HashToken* res
	)
{
	DLOG(__func__, __LINE__);
	int ret=-1;
	if(flags & TREE_SIMPLE)
	{
		if((tree->left->flags & 1) == 0)
		{
			printf("Invalid tree! %s\n", tree->str);
			return TREE_INVALID;
		}
		return codelist_append(list,
			((Instruction)
				{
					.spec=GET_RES_FLAGS(res) | UNARY_SPEC,
					.name=GET_RES_STR(res),
					.values = {MAKESTR(tree->left->str)}
				}
			)
		);
	}
	else
	{
		if((GET_RES_FLAGS(res) & UNARY_SPEC) == 0)
		{
			printf("Invalid tree! %s\n", tree->str);
			return TREE_INVALID;
		}
		ret = _compile_tokentree(tree->left, list);
		if(ret < 0)
			return ret;
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= GET_RES_FLAGS(res) | UNARY_SPEC,
					.name 	= GET_RES_STR(res),
					.values = {MAKEGET(ret)}
				}
			)
		);
	}
}

static inline int
compile_special_tree(
	Tree* tree,
	CodeList* list,
	uint8_t flags,
	HashToken* res
	)
{
	/* GNU extension */
	static void* gotos[] = {
		&&DO_NOTHING_0,
		&&READ_COLLAPSE_1,
		&&BOOL_CHECK_2,
		&&REPEAT_LOOP_3,
		&&SQUARE_BRACKET_4,
		&&RIGHT_ARROW_5,
		&&M_CURLY_BRACE_6,
		&&PARENS_OPEN_7,
		&&B_TO_BYTES_8
	};

	Tree* new_tree = tree;
	int ret1 = -1, ret2 = -1, temp = 0;
	goto *(gotos[res->compile_idx]);

	DO_NOTHING_0:
	return HANDLE_NORMALLY;

	// ui^.
	READ_COLLAPSE_1:
	{
		char c;
		Tree* code_tree = (Tree*) malloc(sizeof(Tree));
		if(code_tree == NULL)
			return MEMORY_ERROR;
		*code_tree = (Tree)
		{
			.flags = 0,
			.str = {'\0', 'l', 0},
			.left = NULL,
			.right = NULL
		};
		char code[3] = {'_', 'R', '\0'};

		while(tree != NULL)
		{
			switch(( c = tree->str[0] ))
			{
				case 'u':
				case 'i':
					code_tree->str[0] = c;
					break;
				case '^':
					code[1] = 'P';
					break;
				case '.':
					code_tree->str[1] = 'b';
					break;
				default:
					goto exit_loop;
			}
			tree = tree->left;
		}
		exit_loop:
		new_tree->flags=0;
		strcpy(new_tree->str, code);
		new_tree->left = code_tree;
		new_tree->right = tree;
		
		if(!(code_tree->str[0]))
		{
			// if()
			return TREE_INVALID;
		}
		ret2 = _compile_tokentree(new_tree, list);
		return ret2;
	}

	// ?
	BOOL_CHECK_2:
	{
		ret1 = _compile_tokentree(tree->left, list);
		if(ret1 < 0)
			return ret1;
		ret1 = codelist_append(list, 
			(Instruction)
			{
				.spec = BINARY_SPEC | NO_RETURN,
				.name = "IF_JUMP",
				// .left = MAKEGET(ret1)
				.values = { MAKEGET(ret1) }
			}
		);
		if(ret1 < 0)
			return ret1;
		if(tree->right == NULL)
			return TREE_INVALID;
		const char* str = tree->right->str;
		if(str[0] == ':' && tree->str[1] == '\0')
		{
			if(flags & TREE_RIGHT_ATOMIC)
				return TREE_INVALID;
			ret2 = _compile_tokentree(tree->right->right, list);
			if(ret2<0)
				return ret2;
			temp = codelist_append(list,
				(Instruction)
				{
					.spec = BINARY_SPEC,
					.name = "SET_REGISTER",
					// .right = MAKEGET(ret2)
					.values = { {}, MAKEGET(ret2) }
				});
			if(temp < 0) return temp;
			// codelist_get(list, ret1)->right = MAKEREF(ret2+2);
			codelist_get(list, ret1)->values[1] = MAKEREF(ret2+2);
			ret1 = codelist_append(list, 
				(Instruction)
				{
					.spec = UNARY_SPEC | NO_RETURN,
					.name = "JUMP"
				}
			);
			if(ret1 < 0) return ret1;
			ret2 = _compile_tokentree(tree->right->left, list);
			if(ret2 < 0) return ret2;
			// codelist_get(list, temp)->left = MAKEREF(ret2);
			// codelist_get(list, ret1)->value = MAKEREF(ret2+1);
			codelist_get(list, temp)->values[0] = MAKEREF(ret2);
			codelist_get(list, ret1)->values[0] = MAKEREF(ret2+1);
			return ret2;
		}
		else
		{
			ret2 = _compile_tokentree(tree->right, list);
			if(ret2 < 0)
				return ret2;
			// codelist_get(list, ret1)->right = MAKEREF(ret2+1);
			codelist_get(list, ret1)->values[1] = MAKEREF(ret2+1);
			return ret2;
		}
	}

	// *
	REPEAT_LOOP_3:
	{
		if(!(flags & TREE_BINARY) || (flags & TREE_LEFT_ATOMIC))
			return TREE_INVALID;
		Instruction ins = { .spec = TERNARY_SPEC, .name = GET_RES_STR(res) };
		if(!temp)
		{
			// ins._1 = MAKEREF(list->len+1);
			ins.values[0] = MAKEREF(list->len+1);
		}
		if(flags & TREE_RIGHT_ATOMIC)
		{
			// ins._3 = MAKESTR(tree->right->str);
			ins.values[2] = MAKESTR(tree->right->str);
		}
		else
		{
			ret1 = _compile_tokentree(tree->right, list);
			if(ret1 < 0) return ret1;
			// ins._3 = MAKEGET(ret1);
			ins.values[2] = MAKEGET(ret1);
		}
		// if(temp)
		// 	ins._1 = MAKEREF(list->len+1);
		ret1 = codelist_append(list, ins);

		if(ret1 < 0) return ret1;
		ret2 = _compile_tokentree(tree->left, list);
		if(ret2 < 0) return ret2;

		if(!(codelist_get(list, ret2)->spec & NO_RETURN))
		{
			ret2 = codelist_append(list, 
				(Instruction)
				{
					.spec = UNARY_SPEC | NO_RETURN,
					.name = "YIELD",
					.values = { MAKEGET(ret2) }
				}
			);
			if(ret2 < 0) return ret2;
		}
		// if(ret2 == ins._1.i32_value)
		if(ret2 == ins.values[0].i32_value)
		{
			Instruction *insp = codelist_get(list, ret1);
			insp->spec = BINARY_SPEC;
			// insp->right = insp->_3;
			insp->values[1] = insp->values[2];
			return ret2;
		}
		// codelist_get(list, ret1)->_2 = MAKEREF(ret2);
		codelist_get(list, ret1)->values[1] = MAKEREF(ret2);
		return ret2;
	}

	// [
	SQUARE_BRACKET_4:
	{
		if(!(flags & TREE_BINARY) || (flags & TREE_LEFT_ATOMIC))
			return TREE_INVALID;
		Instruction ins = { .spec = TERNARY_SPEC, .name = GET_RES_STR(res) };
		if(flags & TREE_RIGHT_ATOMIC)
		{
			// ins._3 = MAKESTR(tree->right->str);
			ins.values[2] = MAKESTR(tree->right->str);
		}
		else
		{
			ret1 = _compile_tokentree(tree->right, list);
			if(ret1 < 0) return ret1;
			// ins._3 = MAKEGET(ret1);
			ins.values[2] = MAKEGET(ret1);
		}
		ret1 = _compile_tokentree(tree->left, list);
		if(ret1 < 0) return ret1;
		Instruction *temp_ins = codelist_get(list, ret1);
		// ins._1 = temp_ins->left;
		// ins._2 = temp_ins->right;
		ins.values[0] = temp_ins->values[0];
		ins.values[1] = temp_ins->values[1];
		if(!codelist_set(list, ins, ret1))
			return GENERIC_ERROR;
		return ret1;
	}

	// ->
	RIGHT_ARROW_5:
	{
		if(!(flags & TREE_BINARY) || (flags & TREE_LEFT_ATOMIC) || (flags & TREE_RIGHT_ATOMIC))
			return TREE_INVALID;
		ret1 = list->len;
		ret2 = _compile_tokentree(tree->right, list);
		if(ret2 < 0) return ret2;

		#ifndef WHILE_LOOP_USE_IFN_JUMP
			ret2 = codelist_append(list,
				(Instruction)
				{
					.spec = UNARY_SPEC,
					.name = "NOT",
					.values = { MAKEGET(ret2) }
				}
			);
		#endif

		temp = codelist_append(list,
			(Instruction)
			{ 
				.spec = BINARY_SPEC | NO_RETURN, 

				#ifdef WHILE_LOOP_USE_IFN_JUMP
					.name = "IFN_JUMP",
				#else
					.name = "IF_JUMP",
				#endif
				.values = { MAKEGET(ret2) }
			}
		);
		if(temp < 0) return ret2;
		ret2 = _compile_tokentree(tree->left, list);
		if(ret2 < 0) return ret2;
		if(!(codelist_get(list, ret2)->spec & NO_RETURN))
		{
			ret2 = codelist_append(list, 
				(Instruction)
				{
					.spec = UNARY_SPEC | NO_RETURN,
					.name = "YIELD",
					.values = { MAKEGET(ret2) }
				}
			);
			if(ret2 < 0) return ret2;
		}
		ret2 = codelist_append(list,
			(Instruction)
			{
				.spec = UNARY_SPEC | NO_RETURN,
				.name = "JUMP",
				.values = { MAKEREF(ret1) }
			}
		);
		if(ret2 < 0) return ret2;
		codelist_get(list, temp)->values[1] = MAKEREF(ret2 + 1);
		return ret2;
	}

	// m{
	M_CURLY_BRACE_6:
	{
		if(!(flags & TREE_MANY))
			return TREE_INVALID;
		int first = list->len+1, last;
		ret1 = codelist_append(list,
			(Instruction)
			{
				.spec = TERNARY_SPEC,
				.name = "MATCH_BEGIN",
				// ._1 = MAKEREF(first)
				.values = {MAKEREF(first)}
			}
		);
		if(ret1 < 0) return ret1;
		Tree* temp;
		for(int i=0; i<tree->num_children; i++)
		{
			temp = tree->children[i];
			flags = get_tree_details(temp);
			if(!(flags & TREE_BINARY) || !(flags & TREE_LEFT_ATOMIC))
				return TREE_INVALID;
		}

		// ... ? i think, idk im drunk
	}

	// (
	PARENS_OPEN_7:
	{
		if((flags & TREE_BINARY) || (flags & TREE_ATOMIC))
			return TREE_INVALID;
		// if(flags & TREE_LEFT_ATOMIC)
		return _compile_tokentree(tree->left, list);
	}

	// B
	B_TO_BYTES_8:
	{
		if((flags & TREE_BINARY) || (flags & TREE_ATOMIC))
			return TREE_INVALID;
		// res = stringtree_find_str(&strmap, "<<");
		res = in_word_set("<<", 2);
		BITASSERT((CHECK_RES_VALID(res)));
		Instruction ins =
		{
			.spec = GET_RES_FLAGS(res) | BINARY_SPEC,
			.name = GET_RES_STR(res),
			// .right = MAKESTR("3")
			.values = { {}, MAKESTR("3") }
		};
		if(flags & TREE_LEFT_ATOMIC)
		{
			// ins.left = MAKESTR(tree->left->str);
			ins.values[0] = MAKESTR(tree->left->str);
		}
		else
		{
			ret1 = _compile_tokentree(tree->left, list);
			if(ret1 < 0) return ret1;
			// ins.left = MAKEGET(ret1);
			ins.values[0] = MAKEGET(ret1);
		}
		return codelist_append(list, ins);
	}

}


int _compile_tokentree(Tree* tree, CodeList* list)
{
	DLOG(__func__, __LINE__);
	HashToken* res;
	int ret1=-1, ret2=-1;
	uint8_t flags = get_tree_details(tree);
	if(flags & TREE_ATOMIC)
	{
		return codelist_append(list,
			((Instruction)
				{
					.spec = UNARY_SPEC,
					.name = "LOAD_CONST",
					// .value = MAKESTR(tree->str)
					.values = {MAKESTR(tree->str)}
				}
			)
		);
	}
	// res = stringtree_find_str(&strmap, tree->str);
	res = in_word_set(tree->str, strlen(tree->str));
	if(!CHECK_RES_VALID(res))
	{
		printf("Unknown symbol! %s\n", tree->str);
		return NOT_FOUND;
	}
	if(!check_requires(tree, flags, res))
	{
		printf("Require error! %s\n", tree->str);
		return TREE_INVALID;
	}
	if(GET_RES_FLAGS(res) & REQUIRE_SPECIAL)
	{
		ret1 = compile_special_tree(tree, list, flags, res);
		if(ret1 >= 0)
			return ret1;
		else if(ret1 != HANDLE_NORMALLY)
		{
			printf("Error special! %d\n", ret1);
			return ret1;
		}
	}
	if(flags & TREE_UNARY)
		return compile_unary_tree(tree, list, flags, res);
	else if(flags & TREE_BINARY)
	{
		// BITASSERT((flags & TREE_BINARY));
		return compile_binary_tree(tree, list, flags, res);
	}
	else
	{
		return compile_many_tree(tree, list, flags, res);
	}
}



CodeList compile_tokentree(Tree* tree)
{
	DLOG(__func__, __LINE__);
	// init_stringtables();
	CodeList list;
	init_codelist(&list);
	int idx = _compile_tokentree(tree, &list);
	if(idx >= 0 &&
		!(codelist_get(&list, idx)->spec & NO_RETURN)
	  )
	{
		Instruction ret = {
			.spec=UNARY_SPEC,
			.name="RETURN",
			// .value = MAKEGET(idx)
			.values = {MAKEGET(idx)}
		};
		idx = codelist_append(&list, ret);
	}
	else if(idx >= 0)
	{
		Instruction ret = {
			.spec=UNARY_SPEC,
			.name="END",
			// .value = MAKEGET(idx)
			.values = {MAKESTR("0")}
		};
		idx = codelist_append(&list, ret);
	}
	if(idx < 0)
		list.len = idx;
	return list;
}

void print_codelist(CodeList* list)
{
	Instruction ins;
	char buffs[3][50];
	CodeValue target;
	int num_targets = 0;
	for(int i=0; i<list->len; i++)
	{
		ins = list->items[i];
		if(ins.spec & UNARY_SPEC)
			num_targets = 1;
		else if(ins.spec & BINARY_SPEC)
			num_targets = 2;
		else if(ins.spec & TERNARY_SPEC)
			num_targets = 3;
		for(int j=0; j<3; j++)
		{
			if(j>=num_targets)
			{
				buffs[j][0] = '\0';
				continue;
			}
			target = ins.values[j];
			switch(target.type)
			{
				case StrType:
					sprintf(buffs[j], "%s", target.str_value);
					break;
			case RefType:
				sprintf(buffs[j], "@%d", target.i32_value);
				break;
			case GetType:
				sprintf(buffs[j], "$%d", target.i32_value);
				break;
			default:
				buffs[j][0] = '\0';
			}
		}
		printf("%-10d %-15s %-10s%-10s%s\n", i, ins.name, buffs[0], buffs[1], buffs[2]);
	}
}

void debug_compile(Tree* tree)
{
	CodeList list = compile_tokentree(tree);
	if(list.len < 0)
	{
		printf("Error compiling tree! Error code: %lld\n", list.len);
		return;
	}
	printf("\n------ BYTECODE -----\n\n");
	print_codelist(&list);
	printf("\n---------------------\n");
}






