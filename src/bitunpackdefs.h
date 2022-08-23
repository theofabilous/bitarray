#include <stdint.h>


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
	Bytes 		= 2
} AtomFlags;


typedef struct AtomItem
{
	uint8_t class;
	uint16_t flags; // unsigned, bytes, etc.
	union
	{
		uint16_t size;
		uint16_t value;
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

#define DEFAULT_PARSE_ITEM() \
	{ .item_class = 0, .target = 0, .flags = 0, .repeat = 0 }



typedef struct ParseSpec
{
	ParseItem* items;
	int len;
} ParseSpec;
