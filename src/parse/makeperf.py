from dataclasses import dataclass
from os import path
import subprocess
import shutil

def iter_members(e: type):
	yield from filter(
		lambda x: not x.startswith('__'),
		dir(e)
		)

def make_flags(e: type) -> None:
	for x in iter_members(e):
		setattr(e, x, 1 << getattr(e, x))

def print_flags(e: type) -> None:
	for x in iter_members(e):
		print(f"{e.__name__}.{x}: {getattr(e, x)}")

includes = [
	"stdint",
	"string",
	"stdbool"
]

typedef = True

delimiter = ","


class Tokenize:
	CheckNext       = 0
	NotAllowed      = 1
	IntegralPrefix  = 2
	ParensOpen      = 3
	ParensClose     = 4
	BracketLiteral  = 5
	TokenDigit      = 6

class TreeFlags:
	BinOp           = 0
	PreOp           = 1
	PostOp          = 2
	Digit           = 3
	Open            = 4
	Close           = 5
	Special         = 6
	Read            = 8
	# UnOp = 9
	

class CompileFlags:
	pass

class ii:
	def __init__(self, size, flag=True):
		self.size = size
		self.flag = flag

	def __repr__(self):
		return f"int{self.size}_t"

	def __str__(self):
		return ii.__repr__(self)

	def decl(self, name):
		return  f"{ii.__repr__(self)} {name}"

class u:
	def __init__(self, size, flag=True):
		self.size = size
		self.flag = flag

	def __repr__(self):
		return f"uint{self.size}_t"

	def __str__(self):
		return u.__repr__(self)

	def decl(self, name):
		return  f"{u.__repr__(self)} {name}"

class cstr:
	def __repr__(self):
		return "const char*"

	def __str__(self):
		return cstr.__repr__(self)

	def decl(self, name):
		return  f"{cstr.__repr__(self)} {name}"

class cbool:
	def __repr__(self):
		return "bool"

	def __str__(self):
		return cbool.__repr__(self)

	def decl(self, name):
		return f"{cbool.__repr__(self)} {name}"

class carray:
	def __init__(self, item, size):
		self.item = item
		self.size = size
	
	def decl(self, name):
		return f"{self.item.decl(name)}[{self.size}]"


@dataclass(slots=True)
class Result:
	name: cstr()                        # type: ignore
	precedence: u(8, False)             # type: ignore
	tokenize_flags: u(16)               # type: ignore
	tree_flags: u(16)                   # type: ignore
	compile_flags: u(16)                # type: ignore
	descr: cstr()                       # type: ignore
	max_search_size: u(8, False)        # type: ignore
	tree_idx: u(8, False) = 0           # type: ignore
	compile_idx: u(8, False) = 0        # type: ignore
	is_instr: cbool() = False           # type: ignore

	def __str__(self):
		s = ""
		# s = f"{self.name}"
		mi = len(Result.__annotations__) - 1
		for j, (name, dtype) in enumerate(Result.__annotations__.items()):
			val = getattr(self, name)
			if j == 0:
				if val[0] == "%" or "," in val:
					val = f'"{val}"{delimiter} '
				else:
					val += f'{delimiter} '
				s += f"{val}"
			else:
				match dtype:
					case cstr():
						val = '"' + val + '"'
						s += f"{val}"
					case (u(size=size) 
						| ii(size=size)) if dtype.flag:
						s += "{0:#0{zfill}b}".format(val, zfill=size)
					case cbool():
						s += "true" if val else "false"
					case _:
						s += f"{val}"
				if j < mi:
					s+=f"{delimiter} "
		return s


make_flags(Tokenize)
make_flags(TreeFlags)

LoopPrecedence          =   10
BitOpPrecedence         =   60
CompPrecedence          =   70
LogicalAndOrPrecedence  =   57
ReadPrecedence          =   100

READ_COLLAPSE_1         =   1
BOOL_CHECK_2            =   2
REPEAT_LOOP_3           =   3
SQUARE_BRACKET_4        =   4
RIGHT_ARROW_5           =   5
M_CURLY_BRACE_6         =   6
PARENS_OPEN_7           =   7
B_TO_BYTES_8            =   8

TREE_ALLOW_COMMAS_1     =   1     # m{} or l{}
TREE_COMMA_2            =   2     # ,
TREE_SQUARE_BRACKET_3   =   3
TREE_CURLY_BRACKET_4    =   4
TREE_PARENS_OPEN_5      =   5
TREE_PARENS_CLOSE_6     =   6
TREE_PREOP_7            =   7
TREE_POSTOP_8           =   8
TREE_BINOP_9            =   9

#	      precedence                   tree_flags           descr               tree_idx					    is_instr
#	name					tokenize_flags        compile_flags      max_search_size         compile_idx
_binops = [
	("+"  , 40,						0, TreeFlags.BinOp, 0, "PLUS", 			0, TREE_BINOP_9, 0,					False),
	("-"  , 40, 					0, TreeFlags.BinOp, 0, "MINUS", 		0, TREE_BINOP_9, 0, 				False),
	("="  , 1,						0, TreeFlags.BinOp, 0, "ASSIGN", 		0, TREE_BINOP_9, 0, 				False),
	("*"  , 40, 					0, TreeFlags.BinOp, 0, "MULTIPLY", 		0, TREE_BINOP_9, 0, 				False),
	("**" , LoopPrecedence, 		0, TreeFlags.BinOp, 0, "REPEAT", 		0, TREE_BINOP_9, REPEAT_LOOP_3, 	False),
	("*>" , LoopPrecedence, 		0, TreeFlags.BinOp, 0, "REPEAT", 		0, TREE_BINOP_9, REPEAT_LOOP_3, 	False),
	("%"  , 40, 					0, TreeFlags.BinOp, 0, "Modulo", 		0, TREE_BINOP_9, 0,					False),
	("%%" , 50, 					0, TreeFlags.BinOp, 0, "Align", 		0, TREE_BINOP_9, 0, 				False),
	(">"  ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "Greater", 		0, TREE_BINOP_9, 0, 				False),
	("<"  ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "Smaller", 		0, TREE_BINOP_9, 0, 				False),
	(">=" ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "GreEq", 		0, TREE_BINOP_9, 0, 				False),
	("<=" ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "SmEq", 			0, TREE_BINOP_9, 0, 				False),
	("==" ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "Eq", 			0, TREE_BINOP_9, 0, 				False),
	("!=" ,	CompPrecedence, 		0, TreeFlags.BinOp, 0, "NEq", 			0, TREE_BINOP_9, 0, 				False),
	(":=" , 89,						0, TreeFlags.BinOp, 0, "WalrusAssign", 	0, TREE_BINOP_9, 0, 				False),
	("<-" , LoopPrecedence, 		0, TreeFlags.BinOp, 0, "???", 			0, TREE_BINOP_9, 0, 				False),
	("->" , LoopPrecedence, 		0, TreeFlags.BinOp, 0, "DoWhile", 		0, TREE_BINOP_9, RIGHT_ARROW_5, 	False),
	("=>" , 20, 					0, TreeFlags.BinOp, 0, "MatchWith", 	0, TREE_BINOP_9, 0,					False),
	("<<" ,	BitOpPrecedence,		0, TreeFlags.BinOp, 0, "ShiftLeft", 	0, TREE_BINOP_9, 0, 				False),
	(">>" ,	BitOpPrecedence, 		0, TreeFlags.BinOp, 0, "ShiftRight", 	0, TREE_BINOP_9, 0, 				False),
	("|"  ,	BitOpPrecedence, 		0, TreeFlags.BinOp, 0, "BitOr", 		0, TREE_BINOP_9, 0, 				False),
	("&"  ,	BitOpPrecedence, 		0, TreeFlags.BinOp, 0, "BitAnd", 		0, TREE_BINOP_9, 0, 				False),
	("&&" , LogicalAndOrPrecedence, 0, TreeFlags.BinOp, 0, "And", 			0, TREE_BINOP_9, 0, 				False),
	("||" , LogicalAndOrPrecedence, 0, TreeFlags.BinOp, 0, "Or", 			0, TREE_BINOP_9, 0, 				False),
	("|>" , 90,						0, TreeFlags.BinOp, 0, "MatchCase", 	0, TREE_BINOP_9, 0, 				False),
	(":"  , 55, 					0, TreeFlags.BinOp, 0, "If_Else", 		0, TREE_BINOP_9, 0,					False),
	("?",	20, 					0, TreeFlags.BinOp,	0, "Conditional",	0, TREE_BINOP_9, BOOL_CHECK_2,		False) 
] # ("?",	20, 					0, TreeFlags.BinOp,	0, "Conditional",	TREE_BINOP_9,	 0, BOOL_CHECK_2) ]
_preops = [
	("u",	ReadPrecedence,			0, TreeFlags.PreOp, 0, "Unsigned",		0, TREE_PREOP_7, READ_COLLAPSE_1,	False),
	("i", 	ReadPrecedence, 		0, TreeFlags.PreOp, 0, "Signed", 		0, TREE_PREOP_7, READ_COLLAPSE_1, 	False),
	("b", 	ReadPrecedence, 		0, TreeFlags.PreOp, 0, "Bits", 			0, TREE_PREOP_7, READ_COLLAPSE_1, 	False),
	("^", 	80, 					0, TreeFlags.PreOp, 0, "Peek", 			0, TREE_PREOP_7, READ_COLLAPSE_1, 	False),
	("B", 	100, 					0, TreeFlags.PreOp, 0, "Bytes", 		0, TREE_PREOP_7, B_TO_BYTES_8,		False),
	("$", 	100, 					0, TreeFlags.PreOp, 0, "Env", 			0, TREE_PREOP_7, 0,					False),
	("@", 	100, 					0, TreeFlags.PreOp, 0, "Ref", 			0, TREE_PREOP_7, 0, 				False),
	("!", 	100, 					0, TreeFlags.PreOp, 0, "Skip", 			0, TREE_PREOP_7, 0, 				False)
]
_postops = [
	(".",	90,						0, TreeFlags.PostOp,0, "BigEndian",		0, TREE_POSTOP_8,READ_COLLAPSE_1,	False)
]


tokens = { v[0]: Result(*v) for v in (_binops + _preops + _postops) }


for i in range(10):
    si = str(i)
    tokens[si] = \
                Result(si,  0, Tokenize.TokenDigit,     TreeFlags.Digit,    0, "DIGIT",      0, 0,                     0,                False)
tokens['(']  =  Result('(', 0, Tokenize.ParensOpen,     TreeFlags.Open,     0, "ParensOpen", 0, TREE_PARENS_OPEN_5,    0,                False)
tokens['()'] =  Result('()',0, Tokenize.NotAllowed,     TreeFlags.Open,     0, "ParensOpen", 0, 0,                     PARENS_OPEN_7,    False)
tokens['m!'] =  Result('m!',0, Tokenize.NotAllowed,     0,                  0, "Match",      0, 0,                     M_CURLY_BRACE_6,  False)
tokens['[]'] =  Result('[]',0, Tokenize.NotAllowed,     0,                  0, "ReadArray",  0, 0,                     SQUARE_BRACKET_4, False)
for e in ('m{', 'l{'):
	tokens[e] = Result(e,   0, Tokenize.ParensOpen,     TreeFlags.Open,     0, "",           0, TREE_ALLOW_COMMAS_1,   0,                False)
for e in ('0x', '0b'):
	tokens[e] = Result(e,   0, Tokenize.IntegralPrefix, 0,                  0, "",           0, 0,                     0,                False)
for e in ")]}":
	tokens[e] = Result(e,   0, Tokenize.ParensClose,    TreeFlags.Close,    0, "Close",      0, TREE_PARENS_CLOSE_6,   0,                False)
tokens['{'] =   Result('{', 0, Tokenize.BracketLiteral, TreeFlags.Special,  0, "Special",    0, TREE_CURLY_BRACKET_4,  0,                False)
tokens['['] =   Result('[', 0, Tokenize.ParensOpen,     TreeFlags.Special,  0, "Special",    0, TREE_SQUARE_BRACKET_3, 0,                False)
tokens[','] =   Result(',', 0, 0,                       TreeFlags.Special,  0, "Special",    0, TREE_COMMA_2,          0,                False)

for e in "^bui.":
	tokens[e].tree_flags |= TreeFlags.Read


REQUIRE_SIMPLE =	1 << 0
UNARY_SPEC =		1 << 1
BINARY_SPEC =		1 << 2
TERNARY_SPEC =		1 << 3
NO_RETURN =		 	1 << 8
MOD_SPECIAL =		1 << 10
LOOP_SPECIAL =		1 << 11
BOOL_CHECK =		1 << 12
READ_COLLAPSE =		1 << 13
ACCESS_SPECIAL =	1 << 14
OTHER_SPECIAL =		1 << 15

old_compile = {
	"$": 	("GET_ENV",			UNARY_SPEC 	| REQUIRE_SIMPLE),
	"@": 	("GET_FIELD",		UNARY_SPEC 	| REQUIRE_SIMPLE),
	r"{}": 	("RAW_VALUE", 		UNARY_SPEC 	| REQUIRE_SIMPLE),
	"()": 	(None,				UNARY_SPEC 	| OTHER_SPECIAL),
	"!": 	("SKIP",			UNARY_SPEC 	| NO_RETURN),
	"B":	("BYTES",			UNARY_SPEC 	| OTHER_SPECIAL),
	"u": 	(None,				BINARY_SPEC | READ_COLLAPSE),
	"i": 	(None,				BINARY_SPEC | READ_COLLAPSE),
	".": 	(None,				BINARY_SPEC | READ_COLLAPSE),
	"^": 	(None,				BINARY_SPEC | READ_COLLAPSE),
	"_R": 	("READ",			BINARY_SPEC),
	"_P": 	("PEEK",			BINARY_SPEC),
	"=": 	("ASSIGN",			BINARY_SPEC | NO_RETURN),
	":=": 	("WALRUS_ASSIGN",	BINARY_SPEC),
	"==": 	("EQUAL?", 			BINARY_SPEC),
	"!=": 	("NOT_EQUAL?",		BINARY_SPEC),
	">": 	("GREATER_THAN?",	BINARY_SPEC),
	"<": 	("LESS_THAN?",		BINARY_SPEC),
	">=": 	("GREATER_EQ?",		BINARY_SPEC),
	"<=": 	("LESS_EQ?",		BINARY_SPEC),
	"&&": 	("AND?",			BINARY_SPEC),
	"||": 	("OR?",				BINARY_SPEC),
	":": 	(None,				BINARY_SPEC | ACCESS_SPECIAL),
	"->": 	("LOOP_WHILE",		BINARY_SPEC | LOOP_SPECIAL),
	"<-": 	(None,				BINARY_SPEC),
	"[]": 	("READ_ARRAY",		BINARY_SPEC | LOOP_SPECIAL),
	"+": 	("PLUS",			BINARY_SPEC),
	"-": 	("MINUS",			BINARY_SPEC),
	"*": 	("TIMES", 			BINARY_SPEC | LOOP_SPECIAL),
	"**": 	("LOOP", 			BINARY_SPEC | LOOP_SPECIAL),
	"*>": 	("LOOP", 			BINARY_SPEC | LOOP_SPECIAL),
	"?": 	(None,				BINARY_SPEC | BOOL_CHECK),
	"<<": 	("SHIFT_LEFT",		BINARY_SPEC),
	">>": 	("SHIFT_RIGHT",		BINARY_SPEC),
	"%": 	("MODULO",			BINARY_SPEC),
	"%%": 	("ALIGN",			BINARY_SPEC),
	"=>":	("MATCH_WITH",		BINARY_SPEC)
	# "m!":	("--",				OTHER_SPECIAL)
}



for tok, (opcode_name, flags) in old_compile.items():
	if not (is_instr := (opcode_name is not None)):
		opcode_name = f"--{tok}--"
	if tok in tokens:
		tokens[tok].descr = opcode_name
		tokens[tok].compile_flags = flags
		tokens[tok].is_instr = is_instr
	else:
		tokens[tok] = Result(tok, 0, Tokenize.NotAllowed, 0, flags, opcode_name, 0, 0, 0, is_instr)

for i in range(ord('a'), 1+ord('z')):
	if (tok := chr(i)+'!') not in tokens:
		tokens[tok] = Result(tok, 0, 0, 0, 
			UNARY_SPEC | OTHER_SPECIAL | MOD_SPECIAL, f"-{chr(i)}!-", 0, 0, 0, False)
		tok = (chr(i)).upper()+'!'
		tokens[tok] = Result(tok, 0, 0, 0, 
			UNARY_SPEC | OTHER_SPECIAL | MOD_SPECIAL, f"-{chr(i).upper()}!-", 0, 0, 0, False)

to_add = []
for k, v in tokens.items():
	length = len(k)
	currlen = length

	while (currlen > 1) and not (v.tokenize_flags & Tokenize.NotAllowed):
		substr = k[:currlen-1]
		if substr in tokens:
			currtok = tokens[substr]
			currtok.tokenize_flags |= Tokenize.CheckNext
			currtok.max_search_size = max(length, currtok.max_search_size)
		else:
			to_add.append(
                Result(
				    substr, 0, Tokenize.NotAllowed, 0, 0, "", length, 0, 0, False
				)
            )
		currlen -= 1

for e in to_add:
	tokens[e.name] = e


# working_dir = "../src/parse/"
working_dir = ""

token_output = path.realpath(f"{working_dir}tokens.gperf")
header_file = path.realpath(f"{working_dir}tokenhash.h")
c_file = path.realpath(f"{working_dir}tokenhash.c")
struct_name = "HashToken"

with open(token_output, "w") as f:
	f.write(f"%delimiters={delimiter}\n")
	f.write("%{\n")
	f.write('\n#include "tokenhash.h"\n')
	f.write("%}\n")
	f.write(f"struct {struct_name}\n" + "{\n")
	for name, dtype in Result.__annotations__.items():
		f.write(f"\t{dtype.decl(name)};\n")
	f.write("};\n%%\n")
	for tok in tokens.values():
		f.write(f"{tok}\n")

gperf_path = shutil.which("gperf")
assert gperf_path is not None

subprocess.run([
	gperf_path, 
    "-L", "ANSI-C", 
	"-t", 
	"-G", token_output, f"--output-file={c_file}"
	])

lines = None
with open(c_file, 'r') as f:
	lines = f.readlines()

with open(c_file, 'w') as f:
	i = 0
	l = lines[i]
	while i < len(lines):
		if (lines[i]).startswith(f"struct {struct_name}"):
			while lines[i][0] != '}':
				i += 1
			i += 1
			break
		else:
			f.write(lines[i])
		i += 1

	for l in lines[i:]:
		f.write(l)


with open(header_file, "w") as f:
	f.write("#ifndef INCLUDE_TOKENHASH_H\n#define INCLUDE_TOKENHASH_H\n\n")
	for inc in includes:
		f.write(f"#include <{inc}.h>\n")
	f.write(f"\nstruct {struct_name}\n" + "{\n")
	for name, dtype in Result.__annotations__.items():
		f.write(f"\t{dtype.decl(name)};\n")
	f.write("};\n\n")
	if typedef:
		f.write(f"typedef struct {struct_name} {struct_name};\n\n")
	f.write(f"{struct_name} * in_word_set (register const char* str, register unsigned int len);\n\n")
	f.write("#endif /* tokenhash.h */\n")



# print("\n\n\nDONE\n\n\n")




