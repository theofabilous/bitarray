#include <stdlib.h>
#include <string.h>

#include "treecompile.h"
#include "stringtree.h"
#include "common.h"

#define CHARS2(a, b) \
	(   ( ((uint16_t)(a)) << 8 ) | ( (uint16_t)(b) )   )

typedef struct StringSpec
{
	const char* key;
	const char* value;
	uint16_t flags;
} StringSpec;

#define NULL_SPEC ((StringSpec) {.key = "", .value = "", .flags = 0})

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



FLAG16(REQUIRE_SIMPLE, 	0);
FLAG16(UNARY_SPEC, 		1);
FLAG16(BINARY_SPEC, 	2);
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

const StringSpec SPECMAP[] =
{
	{"$", 	"GET_ENV",				UNARY_SPEC 	| REQUIRE_SIMPLE},
	{"@", 	"GET_FIELD",			UNARY_SPEC 	| REQUIRE_SIMPLE},
	{"{}", 	"RAW_VALUE", 			UNARY_SPEC 	| REQUIRE_SIMPLE},
	{"()", 	"-()-",					UNARY_SPEC 	| OTHER_SPECIAL},
	{"!", 	"SKIP",					UNARY_SPEC},
	{"B",	"BYTES",				UNARY_SPEC},
	{"u", 	"----",					BINARY_SPEC | READ_COLLAPSE},
	{"i", 	"----",					BINARY_SPEC | READ_COLLAPSE},
	{".", 	"----",					BINARY_SPEC | READ_COLLAPSE},
	{"^", 	"----",					BINARY_SPEC | READ_COLLAPSE},
	{"_R", 	"READ",					BINARY_SPEC},
	{"_P", 	"PEEK",					BINARY_SPEC},
	{"=", 	"ASSIGN",				BINARY_SPEC},
	{":=", 	"WALRUS_ASSIGN",		BINARY_SPEC},
	{"==", 	"EQUAL?", 				BINARY_SPEC},
	{"!=",	"NOT_EQUAL?",			BINARY_SPEC},
	{">",	"GREATER_THAN?",		BINARY_SPEC},
	{"<",	"LESS_THAN?",			BINARY_SPEC},
	{">=",	"GREATER_EQ?",			BINARY_SPEC},
	{"<=",	"LESS_EQ?",				BINARY_SPEC},
	{"&&", 	"OR?",					BINARY_SPEC},
	{"||", 	"AND?",					BINARY_SPEC},
	{":", 	"-----",				BINARY_SPEC | ACCESS_SPECIAL},
	{"->", 	"DO_UNTIL",				BINARY_SPEC | LOOP_SPECIAL},
	{"<-", 	"-----",				BINARY_SPEC},
	{"[]", 	"READ_ARRAY",			BINARY_SPEC | LOOP_SPECIAL},
	{"+",	"PLUS",					BINARY_SPEC},
	{"-", 	"MINUS",				BINARY_SPEC},
	{"*", 	"LOOP", 				BINARY_SPEC | LOOP_SPECIAL},
	{"**", 	"-----", 				BINARY_SPEC | LOOP_SPECIAL},
	{"?", 	"-----",				BINARY_SPEC | BOOL_CHECK},
	{"<<", 	"SHIFT_LEFT",			BINARY_SPEC},
	{">>", 	"SHIFT_RIGHT",			BINARY_SPEC},
	{"%", 	"ALIGN",				BINARY_SPEC},

	NULL_SPEC
};

static inline bool is_null_spec(StringSpec spec)
{ return spec.key[0] == '\0'; }

static StringTree strmap = { .init = false };

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


bool init_stringtables()
{
	if(strmap.init)
		return true;
	bool ok;
	init_stringtree(&strmap, NULL, 0);
	StringSpec spec = NULL_SPEC;
	for(int i=0; !( is_null_spec(SPECMAP[i]) ); i++)
	{
		spec = SPECMAP[i];
		ok = stringtree_add_str_str(&strmap, spec.key, spec.flags, spec.value);
		if(!ok)
		{
			printf("Error! @ %s\n", spec.key);
			return false;
			// exit(1);
		}
	}
	return true;

}

// FLAG16(CODE_REF, 0);
// FLAG16(CODE_STR, 1);
// FLAG16(CODE_I32, 2);

#define MAKESTR(v) ((CodeValue) {.type = StrType, .str_value=(v)})
#define MAKEGET(v) ((CodeValue) {.type = GetType, .i32_value=(v)})
#define MAKEREF(v) ((CodeValue) {.type = RefType, .i32_value=(v)})
#define MAKEJMP(v) ((CodeValue) {.type = RefType, .i32_value=(v)})



static inline bool
check_requires(
	Tree* tree,
	uint8_t flags,
	SearchResult res
	)
{
	DLOG(__func__, __LINE__);
	if(	((res.flags & REQUIRE_SIMPLE) && ((flags & TREE_SIMPLE) == 0))
		|| (res.flags & ACCESS_SPECIAL) )
	{
		printf("Require error\n");
		return false;
	}
	return true;
}



static inline int 
compile_binary_tree(
	Tree* tree, 
	CodeList* list, 
	uint8_t flags,
	SearchResult res
	)
{
	DLOG(__func__, __LINE__);
	int ret1, ret2;
	if(!res.valid)
		return NOT_FOUND;
	if(flags & TREE_BISIMPLE)
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= res.flags | BINARY_SPEC,
					.name 	= res.str_val,
					.left 	= MAKESTR(tree->left->str),
					.right 	= MAKESTR(tree->right->str)
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
					.spec 	= res.flags | BINARY_SPEC,
					.name 	= res.str_val,
					.left 	= MAKESTR(tree->left->str),
					.right 	= MAKEGET(ret1)
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
					.spec 	= res.flags | BINARY_SPEC,
					.name 	= res.str_val,
					.left 	= MAKEGET(ret1),
					.right 	= MAKESTR(tree->right->str)
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
					.spec 	= res.flags | BINARY_SPEC,
					.name 	= res.str_val,
					.left 	= MAKEGET(ret1),
					.right 	= MAKEGET(ret2)
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
	SearchResult res
	)
{
	DLOG(__func__, __LINE__);
	// printf("Compiling unary tree! %s\n", tree->str);
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
					.spec=res.flags | UNARY_SPEC,
					.name=res.str_val,
					.value=MAKESTR(tree->left->str)
				}
			)
		);
	}
	else
	{
		if((res.flags & UNARY_SPEC) == 0)
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
					.spec 	= res.flags | UNARY_SPEC,
					.name 	= res.str_val,
					.value 	= MAKEGET(ret)
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
	SearchResult res
	)
{
	DLOG(__func__, __LINE__);
	Tree* new_tree = tree;
	int ret1 = -1, ret2 = -1;
	if(res.flags & READ_COLLAPSE)
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
			return TREE_INVALID;
		ret2 = _compile_tokentree(new_tree, list);
		return ret2;
	}
	else if(res.flags & BOOL_CHECK)
	{
		ret1 = _compile_tokentree(tree->left, list);
		if(ret1 < 0)
			return ret1;
		ret1 = codelist_append(list, 
			(Instruction)
			{
				.spec = BINARY_SPEC,
				.name = "IF_JUMP",
				.left = MAKEGET(ret1)
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
			codelist_get(list, ret1)->right = MAKEREF(ret2+2);
			ret1 = codelist_append(list, 
				(Instruction)
				{
					.spec = UNARY_SPEC,
					.name = "JUMP"
				}
			);
			if(ret1 < 0) return ret1;
			ret2 = _compile_tokentree(tree->right->left, list);
			if(ret2 < 0) return ret2;
			codelist_get(list, ret1)->value = MAKEREF(ret2+1);
			return ret2;
		}
		else
		{
			ret2 = _compile_tokentree(tree->right, list);
			if(ret2 < 0)
				return ret2;
			codelist_get(list, ret1)->right = MAKEREF(ret2+1);
			return ret2;
		}
	}
	else if(res.flags & LOOP_SPECIAL)
	{
		if(tree->str[0] == '*' || tree->str[0] == '[')
		{
			if(!(flags & TREE_BINARY) || (flags & TREE_LEFT_ATOMIC))
				return TREE_INVALID;
			Instruction ins = { .spec = BINARY_SPEC, .name = res.str_val };
			if(flags & TREE_RIGHT_ATOMIC)
				ins.right = MAKESTR(tree->right->str);
			else
			{
				ret1 = _compile_tokentree(tree->right, list);
				if(ret1 < 0) return ret1;
				ins.right = MAKEGET(ret1);
			}
			ret1 = codelist_append(list, ins);
			if(ret1 < 0) return ret1;
			ret2 = _compile_tokentree(tree->left, list);
			if(ret2 < 0) return ret2;
			codelist_get(list, ret1)->left = MAKEREF(ret2);
			return ret2;
		}
	}
	else if(res.flags & OTHER_SPECIAL)
	{
		if(tree->str[0] == '(')
		{
			if((flags & TREE_BINARY) || (flags & TREE_ATOMIC))
				return TREE_INVALID;
			// if(flags & TREE_LEFT_ATOMIC)
			return _compile_tokentree(tree->left, list);
		}
		// if(tree->str[0] == '[')
		// {
		// 	if(!(flags & TREE_BINARY) || (flags & TREE_LEFT_ATOMIC))
		// 		return TREE_INVALID;
		// 	Instruction ins = { .spec = BINARY_SPEC, .name = "READ_ARRAY" };
		// 	if(flags & TREE_RIGHT_ATOMIC)
		// 		ins.right = MAKESTR(tree->right->str);
		// 	else
		// 	{
		// 		ret1 = _compile_tokentree(tree->right, list);
		// 		if(ret1 < 0) return ret1;
		// 		ins.right = MAKEGET(ret1);
		// 	}
		// 	ret1 = codelist_append(list, ins);
		// 	if(ret1 < 0) return ret1;
		// 	ret2 = _compile_tokentree(tree->left, list);
		// 	if(ret2 < 0) return ret2;
		// 	codelist_get(list, ret1)->left = MAKEREF(ret2);
		// 	return ret2;
		// }
	}
	return HANDLE_NORMALLY;
}



int _compile_tokentree(Tree* tree, CodeList* list)
{
	DLOG(__func__, __LINE__);
	SearchResult res;
	int ret1=-1, ret2=-1;
	uint8_t flags = get_tree_details(tree);
	// if(flags & TREE_ATOMIC)
	// 	return GENERIC_ERROR;
	if(flags & TREE_ATOMIC)
	{
		return codelist_append(list,
			((Instruction)
				{
					.spec = UNARY_SPEC,
					.name = "LOAD_CONST",
					.value = MAKESTR(tree->str)
				}
			)
		);
	}
	res = stringtree_find_str(&strmap, tree->str);
	if(!res.valid)
	{
		printf("Unknown symbol! %s\n", tree->str);
		return NOT_FOUND;
	}
	if(!check_requires(tree, flags, res))
	{
		printf("Require error! %s\n", tree->str);
		return TREE_INVALID;
	}
	if(res.flags & REQUIRE_SPECIAL)
	{
		ret1 = compile_special_tree(tree, list, flags, res);
		if(ret1 >= 0)
			return ret1;
		else if(ret1 != HANDLE_NORMALLY)
		{
			printf("Error special!\n");
			return ret1;
		}
	}
	if(flags & TREE_UNARY)
		return compile_unary_tree(tree, list, flags, res);
	else
	{
		BITASSERT((flags & TREE_BINARY));
		return compile_binary_tree(tree, list, flags, res);
	}
}



CodeList compile_tokentree(Tree* tree)
{
	DLOG(__func__, __LINE__);
	init_stringtables();
	CodeList list;
	init_codelist(&list);
	int idx = _compile_tokentree(tree, &list);
	if(idx >= 0)
	{
		Instruction ret = {
			.spec=UNARY_SPEC,
			.name="RETURN",
			.value = MAKEGET(idx)
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
	char buffleft[50];
	char buffright[50];
	const char* pleft;
	const char* pright;
	CodeValue target;
	for(int i=0; i<list->len; i++)
	{
		ins = list->items[i];
		if(ins.spec & UNARY_SPEC)
			target = ins.value;
		else if(ins.spec & BINARY_SPEC)
			target = ins.left;
		else
		{
			printf("%s ???\n", ins.name);
			continue;
		}
		switch(target.type)
		{
			case StrType:
				pleft = target.str_value;
				break;
			case RefType:
				sprintf(buffleft, "@%d", target.i32_value);
				pleft = buffleft;
				break;
			case GetType:
				sprintf(buffleft, "$%d", target.i32_value);
				pleft = buffleft;
				break;
			default:
				buffleft[0] = '\0';
				pleft = buffleft;
		}
		if(ins.spec & UNARY_SPEC)
		{
			buffright[0] = '\0';
			pright = buffright;
		}
		else
		{
			target = ins.right;
			switch(target.type)
			{
				case StrType:
					pright = target.str_value;
					break;
				case RefType:
					sprintf(buffright, "@%d", target.i32_value);
					pright = buffright;
					break;
				case GetType:
					sprintf(buffright, "$%d", target.i32_value);
					pright = buffright;
					break;
				default:
					buffright[0] = '\0';
					pright = buffright;
			}
		}
		printf("%-10d %-15s %-10s%s\n", i, ins.name, pleft, pright);
	}
}

void debug_compile(Tree* tree)
{
	CodeList list = compile_tokentree(tree);
	if(list.len < 0)
	{
		printf("Error compiling tree! Error code: %d\n", list.len);
		return;
	}
	printf("\n------ BYTECODE -----\n\n");
	print_codelist(&list);
	printf("\n---------------------\n");
}






