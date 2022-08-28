#include <stdlib.h>
#include <string.h>

#include "treecompile.h"
#include "stringtree.h"
#include "common.h"

#define DO_SIMPLE_COLLAPSE

typedef struct StringSpec
{
	const char* key;
	const char* value;
	uint16_t flags;
} StringSpec;

#define NULL_SPEC ((StringSpec) {.key = "", .value = "", .flags = 0})

FLAG16(READ_NODE, 0);
FLAG16(READ_COLLAPSE, 1);
FLAG16(READ_MOD, 2);
FLAG16(UNARY_NODE, 3);
FLAG16(BINARY_NODE, 4);
FLAG16(NEED_SIMPLE_COLLAPSE, 5);
FLAG16(MIGHT_SIMPLE_COLLAPSE, 6);

FLAG16(UNARY_SPEC, 0);
FLAG16(BINARY_SPEC, 1);

static const int GENERIC_ERROR = -1;
static const int NOT_FOUND = -2;
static const int TREE_INVALID = -3;



const StringSpec UNARY_TREES[] =
{
	{"$", 	"GET_ENV",			UNARY_SPEC | NEED_SIMPLE_COLLAPSE},
	{"@", 	"GET_FIELD",		UNARY_SPEC | NEED_SIMPLE_COLLAPSE},
	{"{}", 	"RAW_VALUE", 		UNARY_SPEC | NEED_SIMPLE_COLLAPSE},
	{"u", 	"READ",				UNARY_SPEC | READ_NODE | READ_COLLAPSE | MIGHT_SIMPLE_COLLAPSE},
	{"i", 	"READ",				UNARY_SPEC | READ_NODE | READ_COLLAPSE},
	{".", 	"BIGENDIAN",		UNARY_SPEC | READ_MOD | READ_COLLAPSE},
	{"^", 	"PEEK",				UNARY_SPEC | READ_MOD | READ_COLLAPSE},
	{"!", 	"SKIP",				UNARY_SPEC},
	{"B",	"BYTES",			UNARY_SPEC},
	NULL_SPEC
};

const StringSpec BINARY_TREES[] =
{
	{"=", 	"ASSIGN",				BINARY_SPEC},
	{"==", 	"CHECK_EQUALS", 		BINARY_SPEC},
	{"&&", 	"BOOL_AND",				BINARY_SPEC},
	{"||", 	"BOOL_OR",				BINARY_SPEC},
	{"->", 	"DO_UNTIL",				BINARY_SPEC},
	{"<-", 	"----",					BINARY_SPEC},
	{"[]", 	"READ_ARRAY",			BINARY_SPEC},
	{"+",	"PLUS",					BINARY_SPEC},
	{"-", 	"MINUS",				BINARY_SPEC},
	{"*", 	"REPEAT", 				BINARY_SPEC},
	{"?", 	"CONDITIONAL",			BINARY_SPEC},
	{":", 	"IF_ELSE",				BINARY_SPEC},
	{"<<", 	"SHIFT_LEFT",			BINARY_SPEC},
	{">>", 	"SHIFT_RIGHT",			BINARY_SPEC},
	{"%", 	"ALIGN",				BINARY_SPEC},
	{"!=",	"CHECK_NOT_EQUAL",		BINARY_SPEC},
	NULL_SPEC
};

// };

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
	// SearchResult res;
	init_stringtree(&strmap, NULL, 0);
	StringSpec spec = NULL_SPEC;
	for(int i=0; !(is_null_spec(UNARY_TREES[i])); i++)
	{
		spec = UNARY_TREES[i];
		ok = stringtree_add_str_str(&strmap, spec.key, spec.flags, spec.value);
		if(!ok)
		{
			printf("Error! @ %s\n", spec.key);
			return false;
			// exit(1);
		}
	}
	for(int i=0; !( is_null_spec(BINARY_TREES[i]) ); i++)
	{
		spec = BINARY_TREES[i];
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

FLAG16(CODE_REF, 0);
FLAG16(CODE_STR, 1);
FLAG16(CODE_I32, 2);

#define MAKESTR(v) ((CodeValue) {.type=0, .str_value=(v)})
#define MAKEREF(v) ((CodeValue) {.type=5, .i32_value=(v)})


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
			case 0:
				pleft = target.str_value;
				break;
			case 1:
				sprintf(buffleft, "@%d", target.i32_value);
				pleft = buffleft;
				break;
			case 5:
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
				case 0:
					pright = target.str_value;
					break;
				case 1:
					sprintf(buffright, "@%d", target.i32_value);
					pright = buffright;
					break;
				case 5:
					sprintf(buffright, "$%d", target.i32_value);
					pright = buffright;
					break;
				default:
					buffright[0] = '\0';
					pright = buffright;
			}
		}
		printf("%d: %-15s %-10s%s\n", i, ins.name, pleft, pright);
	}
}


static inline int 
compile_binary_tree(
	Tree* tree, 
	CodeList* list, 
	uint8_t flags,
	SearchResult res
	)
{
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
					.right 	= MAKEREF(ret1)
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
					.left 	= MAKEREF(ret1),
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
					.left 	= MAKEREF(ret1),
					.right 	= MAKEREF(ret2)
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
			return TREE_INVALID;
		ret = _compile_tokentree(tree->left, list);
		if(ret < 0)
			return ret;
		return codelist_append(list,
			((Instruction)
				{
					.spec 	= res.flags | UNARY_SPEC,
					.name 	= res.str_val,
					.value 	= MAKEREF(ret)
				}
			)
		);
	}
}



int _compile_tokentree(Tree* tree, CodeList* list)
{
	SearchResult res;
	int ret1=-1, ret2=-1;
	uint8_t flags = get_tree_details(tree);
	if(flags & TREE_ATOMIC)
	{
		return GENERIC_ERROR;
		// if((tree->flags & 1) == 0)
		// {
		// 	printf("Invalid tree! %s\n", tree->str);
		// 	return TREE_INVALID;
		// }
		// return codelist_append(list, 
		// 	make_load_const(tree->str, 0, list->len));
	}
	res = stringtree_find_str(&strmap, tree->str);
	if(!res.valid)
		return NOT_FOUND;
	if(flags & TREE_UNARY)
		return compile_unary_tree(tree, list, flags, res);
	// if(flags & TREE_SIMPLE)
	// {
	// 	if((tree->left->flags & 1) == 0)
	// 	{
	// 		printf("Invalid tree! %s\n", tree->str);
	// 		return TREE_INVALID;
	// 	}
	// 	return codelist_append(list,
	// 		((Instruction)
	// 			{
	// 				.spec=res.flags | UNARY_SPEC,
	// 				.name=res.str_val,
	// 				.value=MAKESTR(tree->left->str)
	// 			}
	// 		)
	// 	);
	// }
	// else if(flags & TREE_UNARY)
	// {
	// 	if((res.flags & UNARY_SPEC) == 0)
	// 		return TREE_INVALID;
	// 	ret1 = _compile_tokentree(tree->left, list);
	// 	if(ret1 < 0)
	// 		return ret1;
	// 	return codelist_append(list,
	// 		((Instruction)
	// 			{
	// 				.spec 	= res.flags | UNARY_SPEC,
	// 				.name 	= res.str_val,
	// 				.value 	= MAKEREF(ret1)
	// 			}
	// 		)
	// 	);
	// }
	else
	{
		BITASSERT((flags & TREE_BINARY));
		return compile_binary_tree(tree, list, flags, res);
	}
}



CodeList compile_tokentree(Tree* tree)
{
	init_stringtables();
	CodeList list;
	init_codelist(&list);
	int idx = _compile_tokentree(tree, &list);
	if(idx >= 0)
	{
		Instruction ret = {
			.spec=UNARY_SPEC,
			.name="RETURN",
			.value = ((CodeValue)
				{
					.type=1,
					.i32_value=idx
				}
			)
		};
		idx = codelist_append(&list, ret);
	}
	if(idx < 0)
		list.len = idx;
	return list;
}

void debug_compile(Tree* tree)
{
	CodeList list = compile_tokentree(tree);
	if(list.len <= 0)
	{
		printf("Error compiling tree! Error code: %d\n", list.len);
		return;
	}
	printf("\n------ BYTECODE -----\n\n");
	print_codelist(&list);
	printf("\n---------------------\n");
}






