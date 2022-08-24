#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


typedef enum AtomClass
{
	AtomLiteral = 0,
	AtomRef = 1,
	AtomEnv = 2,
	AtomRead = 4
} AtomClass;


typedef enum AtomFlags
{
	Unsigned 	= 0,
	Signed 		= 1,
	Bytes 		= 2,
	SizeIsAtom	= 1 << 15
} AtomFlags;


typedef struct AtomItem
{
	uint8_t class;
	uint16_t flags; // unsigned, bytes, etc.
	union
	{
		uint16_t size;
		uint16_t value;
		struct AtomItem* complex_val;
	};
} AtomItem;


typedef enum ExprClass
{
	ExprAtom = 0,
	ExprUnary = (1 << 14),
	ExprBinary = (1 << 15)
} ExprClass;


typedef enum ExprOp
{
	Align 	= ExprUnary 	| (1 << 0),
	ToBytes = ExprUnary 	| (1 << 1),
	Negate 	= ExprUnary 	| (1 << 2),

	Plus 	= ExprBinary 	| (1 << 3),
	Minus 	= ExprBinary	| (1 << 4),
	Times	= ExprBinary	| (1 << 5),
	ShiftL 	= ExprBinary	| (1 << 6),
	ShiftR	= ExprBinary	| (1 << 7)
} ExprOp;


typedef struct ExprItem
{
	uint16_t spec;
	union
	{
		AtomItem* atom; // not an op
		struct ExprItem* item; // unary op
		struct // binary op
		{
			struct ExprItem *left, *right;
		};
	};
} ExprItem;


typedef enum ItemClass
{
	IsAtom 		= 1,
	IsSequence 	= 2,
	IsExpr 		= 3,
	IsBool 		= 4
} ItemClass;


typedef struct SequenceItem
{
	uint8_t item_class;
	uint16_t eval_order; // indicate if get len before
	AtomItem atom_type;
	union
	{
		ExprItem len_expr;
		AtomItem len;
	};
} SequenceItem;


// typedef struct AssignItem
// {
// 	uint8_t target;
// 	uint8_t item_class;
// 	union
// 	{
// 		AtomItem atom;
// 		ExprItem expr;
// 	};
// } AssignItem;




typedef struct BoolBlock 
{
	uint8_t item_class;
	union
	{
		SequenceItem sequence;
		AtomItem atom;
		ExprItem expr;
		// AssignItem assign;
	};
} BoolBlock;



typedef enum BoolClass
{
	BoolUnary = (1 << 14),
	BoolBinary = (1 << 15)
} BoolClass;


typedef enum BoolOp
{
	BoolTrue 	= BoolUnary		| (1 << 0),
	BoolNot		= BoolUnary		| (1 << 1),

	BoolEq		= BoolBinary	| (1 << 2),
	BoolNe		= BoolBinary	| (1 << 3),
	BoolGr		= BoolBinary	| (1 << 4),
	BoolGe		= BoolBinary	| (1 << 5),
	BoolLt		= BoolBinary	| (1 << 6),
	BoolLe		= BoolBinary	| (1 << 7),

	BoolElse	= BoolBinary	| (1 << 13)

} BoolOp;


typedef struct BoolItem
{
	uint16_t spec; // class and op
	struct
	{
		union
		{
			ExprItem iftrue;
			ExprItem left, right;
		};
		BoolBlock *block_if, *block_else; // arrays of instructions
	};
} BoolItem;


typedef enum ItemFlags
{
	HasAssign 	= 1,
	HasRepeat	= 2
} ItemFlags;


typedef struct ParseItem
{
	uint8_t item_class;
	uint8_t target;
	uint8_t flags;
	uint8_t repeat;
	union
	{
		SequenceItem sequence;
		AtomItem atom;
		ExprItem expr;
		// AssignItem assign;
		BoolItem boolexpr;
	};
} ParseItem;


typedef struct ParseSpec
{
	ParseItem* items;
	int len;
} ParseSpec;


#define DEFAULT_PARSE_ITEM() \
	{ .item_class = 0, .target = 0, .flags = 0, .repeat = 0 }



// typedef struct Value
// {
// 	uint16_t spec;
// 	union
// 	{
// 		uint8_t env_index;
// 		int64_t num_literal;
// 		struct
// 		{
// 			uint8_t ptrn_flags;
// 			uint8_t pattern[16];
// 		} pattern;
// 		struct
// 		{
// 			uint8_t unop;
// 			struct Value* unoperand;
// 		} unary_expr;
// 		struct
// 		{
// 			uint8_t binop;
// 			struct Value *left, *right;
// 		} binary_expr;
// 		struct
// 		{
// 			uint8_t read_flags;
// 			struct Value* read_size;
// 		} read;
// 	};
// } Value;

// typedef struct Instruction
// {
// 	uint16_t spec;
// 	union
// 	{
// 		Value* get_value;
// 		Value* skip_value;
// 		struct
// 		{
// 			Value* target_index;
// 			Value* assign_value;
// 		} assign;
// 		struct
// 		{

// 		};
// 	};
// } Instruction;

#define FLAG32(name, shift) \
	static const uint32_t name = 1 << shift

#define FLAG16(name, shift) \
	static const uint16_t name = 1 << shift

#define FLAG8(name, shift) \
	static const uint8_t name = 1 << shift

FLAG32(GET_ENV, 0);
FLAG32(LITERAL, 1);
FLAG32(PATTERN, 2);
FLAG32(UNARY_EXP, 3);
FLAG32(BINARY_EXP, 4);
FLAG32(READ, 5);
FLAG32(SEQUENCE, 6);
FLAG32(ASSIGN, 7);
FLAG32(MATCH, 8);

FLAG32(ALLOCATED, 31);


FLAG8(READ_SIGNED, 1);
FLAG8(READ_BINARY, 2);
FLAG8(READ_BIGENDIAN, 3);


FLAG8(UNARY_NEG, 1);
FLAG8(UNARY_BYTES, 2);

FLAG8(BINARY_ALIGN, 1);
FLAG8(BINARY_PLUS, 2);
FLAG8(BINARY_MINUS, 3);
FLAG8(BINARY_SHIFTL, 4);
FLAG8(BINARY_SHIFTR, 5);


typedef struct Instruction
{
	uint32_t spec;
	union
	{
		uint8_t env_index;
		int64_t num_literal;

		struct
		{
			uint8_t pattern_flags;
			uint8_t pattern[16];
		} pattern;

		struct
		{
			uint8_t unop;
			struct Instruction* unoperand;
		} unary_expr;

		struct
		{
			uint8_t binop;
			struct Instruction *left, *right;
		} binary_expr;

		struct
		{
			uint8_t read_flags;
			struct Instruction* read_size;
		} read;

		struct
		{
			struct Instruction* item;
			struct Instruction* len; 
		} sequence;

		struct
		{
			struct Instruction *target, *value;
		} assign;

		struct
		{
			uint8_t match_flags;
			struct Instruction* match_pattern;
			struct Instruction *match_success, *match_fail;
		} match;
	};
} Instruction;

#define INSTDEFAULT() \
	((Instruction) { .spec = 0 })

#define INSTALLOC() (Instruction*) malloc(sizeof(Instruction))


void delete_instruction(Instruction* inst)
{
	// ...
	return;
}



static inline bool alloc_assign(Instruction* dest)
{
	dest->assign.target = INSTALLOC();
	if(dest->assign.target == NULL)
		return false;
	dest->assign.value = INSTALLOC();
	if(dest->assign.value == NULL)
	{
		free(dest->assign.target);
		return NULL;
	}
	dest->assign.target->spec |= ALLOCATED;
	dest->assign.value->spec |= ALLOCATED;
	dest->spec |= ASSIGN;
	return true;
}


static inline bool alloc_read(Instruction* dest)
{
	dest->read.read_size = INSTALLOC();
	if(dest->read.read_size == NULL)
		return false;
	dest->spec |= READ;
	dest->read.read_size->spec |= ALLOCATED;
	return true;
}


static inline bool alloc_unop(Instruction* dest)
{
	dest->unary_expr.unoperand = INSTALLOC();
	if(dest->unary_expr.unoperand == NULL)
		return false;
	dest->spec |= UNARY_EXP;
	dest->unary_expr.unoperand->spec |= ALLOCATED;
	return true;
}

static inline bool alloc_binop(Instruction* dest, bool alloc_left)
{
	if(alloc_left)
	{
		dest->binary_expr.left = INSTALLOC();
		if(dest->binary_expr.left == NULL)
			return false;
		dest->binary_expr.right = INSTALLOC();
		if(dest->binary_expr.right == NULL)
		{
			free(dest->binary_expr.left);
			return false;
		}
		dest->spec |= BINARY_EXP;
		dest->binary_expr.left->spec |= ALLOCATED;
		dest->binary_expr.right->spec |= ALLOCATED;
		return true;	
	}
	else
	{
		dest->binary_expr.right = INSTALLOC();
		if(dest->binary_expr.right == NULL)
			return false;
		dest->spec |= BINARY_EXP;
		dest->binary_expr.right->spec |= ALLOCATED;
		return true;
	}

}




typedef struct TargetStack
{
	Instruction* targets[100];
	Instruction** top;
	uint8_t len;
} TargetStack;

void set_top_addr(TargetStack* stack, Instruction** ptr)
{
	stack->top = ptr;
}


bool push_target(TargetStack* stack, Instruction* target)
{
	if(stack->len == 100)
		return false;
	stack->targets[stack->len] = target;
	*(stack->top) = target;
	stack->len++;
	return true;
}

Instruction* peek_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	return stack->targets[stack->len - 1];
}

Instruction* pop_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	Instruction* ret = stack->targets[stack->len - 1];
	stack->targets[--stack->len] = NULL;
	*(stack->top) = stack->targets[stack->len - 1];
	return ret;
}

Instruction* rem_target(TargetStack* stack)
{
	if(!stack->len || stack->len > 100)
		return NULL;
	Instruction* ret = stack->targets[stack->len - 1];
	stack->targets[--stack->len] = NULL;
	return ret;
}

typedef struct UnpackSpec
{
	Instruction* items;
	int len;
} UnpackSpec;


