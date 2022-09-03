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
	"string"
]

typedef = True

delimiter = ","


class TokenizeFlags:
	CheckNext = 0

class TreeFlags:
	BinOp = 0
	PreOp =  1
	PostOp = 2
	Digit = 3
	Open = 4
	Close = 5
	Special = 6
	Read = 8
	# UnOp = 9
	

class CompileFlags:
	pass

class i:
	def __init__(self, size, flag=True):
		self.size = size
		self.flag = flag

	def __repr__(self):
		return f"int{self.size}_t"

	def __str__(self):
		return i.__repr__(self)

	def decl(self, name):
		return  f"{i.__repr__(self)} {name}"

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

class carray:
	def __init__(self, item, size):
		self.item = item
		self.size = size
	
	def decl(self, name):
		return f"{self.item.decl(name)}[{self.size}]"


@dataclass(slots=True)
class Result:
	name: cstr()
	precedence: u(8, False)
	tokenize_flags: u(16)
	tree_flags: u(16)
	compile_flags: u(16)
	descr: cstr()
	max_search_size: u(8, False)
	compile_idx: u(8, False) = 0

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
					case u(size=size) | i(size=size) if dtype.flag:
						s += "{0:#0{zfill}b}".format(val, zfill=size)
					case _:
						s += f"{val}"
				if j < mi:
					s+=f"{delimiter} "
		return s

		# return f"{self.name}, {self.precedence}, {self.tokenize_flags}, {self.tree_flags}, {self.compile_flags}, \"{self.descr}\""

make_flags(TokenizeFlags)
make_flags(TreeFlags)
# make_fla
# print_flags(TreeFlags)

BitOpPrecedence = 60
CompPrecedence = 70
LogicalAndOrPrecedence = 57

binops = [
	("+", 40, "PLUS"),
	("-", 40, "MINUS"),
	("=", 1, "ASSIGN"),
	("*", 10, "REPEAT"),
	("**", 10, "REPEAT"),
	("%", 50, "Align"),
	(">", 	CompPrecedence, "Greater"),
	("<", 	CompPrecedence, "Smaller"),
	(">=", 	CompPrecedence, "GreEq"),
	("<=", 	CompPrecedence, "SmEq"),
	("==", 	CompPrecedence, "Eq"),
	("!=", 	CompPrecedence, "NEq"),
	(":=", 89, "WalrusAssign"),
	("<-", 10, "???"),
	("->", 10, "DoWhile"),
	("<<", 	BitOpPrecedence, "ShiftLeft"),
	(">>", 	BitOpPrecedence, "ShiftRight"),
	("|", 	BitOpPrecedence, "BitOr"),
	("&", 	BitOpPrecedence, "BitAnd"),
	("&&", LogicalAndOrPrecedence, "And"),
	("||", LogicalAndOrPrecedence, "Or"),
	("|>", 90, "MatchCase"),
	(":", 55, "If_Else"),
	("?", 20, "Conditional")
]

def binopify(binops):
	for tok, prec, desc in binops:
		yield Result(tok, prec, 0, TreeFlags.BinOp, 0, desc, 0)


ReadPrecedence = 100

preops = [
	("u", ReadPrecedence, "Unsigned"),
	("i", ReadPrecedence, "Signed"),
	("b", ReadPrecedence, "Bits"),
	("^", 80, "Peek"),
	("B", 100, "Bytes"),
	("$", 100, "Env"),
	("@", 100, "Ref"),
	("!", 100, "Skip")
]

postops = [
	(".", 90, "BigEndian"),
]

def preopify(preops):
	for tok, prec, desc in preops:
		yield Result(tok, prec, 0, TreeFlags.PreOp, 0, desc, 0 )

def postopify(postops):
	for tok, prec, desc in postops:
		yield Result(tok, prec, 0, TreeFlags.PostOp, 0, desc, 0 )

# tokens = {
# 	v.name: v for v in ( 
# 		list(binopify(binops)) +
# 		list(preopify(preops)) +
# 		list(postopify(postops))
# 		)
# }

READ_COLLAPSE_1 = 1
BOOL_CHECK_2 = 2
REPEAT_LOOP_3 = 3
SQUARE_BRACKET_4 = 4
RIGHT_ARROW_5 = 5
M_CURLY_BRACE_6 = 6
PARENS_OPEN_7 = 7
B_TO_BYTES_8 = 8


_binops = [
	("+", 40, 0, TreeFlags.BinOp, 0, "PLUS", 0, 0),
	("-", 40, 0, TreeFlags.BinOp, 0, "MINUS", 0, 0),
	("=", 1, 0, TreeFlags.BinOp, 0, "ASSIGN", 0, 0),
	("*", 10, 0, TreeFlags.BinOp, 0, "REPEAT", 0, REPEAT_LOOP_3),
	("**", 10, 0, TreeFlags.BinOp, 0, "REPEAT", 0, REPEAT_LOOP_3),
	("%", 50, 0, TreeFlags.BinOp, 0, "Align", 0, 0),
	(">", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "Greater", 0, 0),
	("<", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "Smaller", 0, 0),
	(">=", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "GreEq", 0, 0),
	("<=", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "SmEq", 0, 0),
	("==", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "Eq", 0, 0),
	("!=", 	CompPrecedence, 0, TreeFlags.BinOp, 0, "NEq", 0, 0),
	(":=", 89, 0, TreeFlags.BinOp, 0, "WalrusAssign", 0, 0),
	("<-", 10, 0, TreeFlags.BinOp, 0, "???", 0, 0),
	("->", 10, 0, TreeFlags.BinOp, 0, "DoWhile", 0, RIGHT_ARROW_5),
	("<<", 	BitOpPrecedence, 0, TreeFlags.BinOp, 0, "ShiftLeft", 0, 0),
	(">>", 	BitOpPrecedence, 0, TreeFlags.BinOp, 0, "ShiftRight", 0, 0),
	("|", 	BitOpPrecedence, 0, TreeFlags.BinOp, 0, "BitOr", 0, 0),
	("&", 	BitOpPrecedence, 0, TreeFlags.BinOp, 0, "BitAnd", 0, 0),
	("&&", LogicalAndOrPrecedence, 0, TreeFlags.BinOp, 0, "And", 0, 0),
	("||", LogicalAndOrPrecedence, 0, TreeFlags.BinOp, 0, "Or", 0, 0),
	("|>", 90, 0, TreeFlags.BinOp, 0, "MatchCase", 0, 0),
	(":", 55, 0, TreeFlags.BinOp, 0, "If_Else", 0, 0),
	("?", 20, 0, TreeFlags.BinOp, 0, "Conditional", 0, BOOL_CHECK_2)
]

_preops = [
	("u", ReadPrecedence, 	0, TreeFlags.PreOp, 0, "Unsigned", 	0, READ_COLLAPSE_1),
	("i", ReadPrecedence, 	0, TreeFlags.PreOp, 0, "Signed", 	0, READ_COLLAPSE_1),
	("b", ReadPrecedence, 	0, TreeFlags.PreOp, 0, "Bits", 		0, READ_COLLAPSE_1),
	("^", 80, 				0, TreeFlags.PreOp, 0, "Peek", 		0, READ_COLLAPSE_1),
	("B", 100, 				0, TreeFlags.PreOp, 0, "Bytes", 	0, B_TO_BYTES_8),
	("$", 100, 				0, TreeFlags.PreOp, 0, "Env", 		0, 0),
	("@", 100, 				0, TreeFlags.PreOp, 0, "Ref", 		0, 0),
	("!", 100, 				0, TreeFlags.PreOp, 0, "Skip", 		0, 0)
]

_postops = [
	(".", 90,				0, TreeFlags.PostOp, 0, "BigEndian", 0, READ_COLLAPSE_1)
]

# tokens = {
# 	v.name: v for v in
# 	map(lambda t: Result(*t), (_binops + _preops + _postops))
# }

tokens = {
	v[0]: Result(*v) for v in
	(_binops + _preops + _postops)
}



for i in range(10):
	tokens[str(i)] = Result(str(i), 0, 0, TreeFlags.Digit, 0, "DIGIT", 0)

tokens['('] = Result('(', 0, 0, TreeFlags.Open, 0, "ParensOpen", 0, 0)
tokens['()'] = Result('()', 0, 0, TreeFlags.Open, 0, "ParensOpen", 0, PARENS_OPEN_7)
tokens['m!'] = Result('m!', 0, 0, 0, 0, "Match", 0, M_CURLY_BRACE_6)
tokens['[]'] = Result('[]', 0, 0, 0, 0, "ReadArray", 0, SQUARE_BRACKET_4)

for e in ")]}":
	tokens[e] = Result(e, 0, 0, TreeFlags.Close, 0, "Close", 0)

for e in "{[,":
	tokens[e] = Result(e, 0, 0, TreeFlags.Special, 0, "Special", 0)

for e in "^bui.":
	tokens[e].tree_flags |= TreeFlags.Read

for k, v in tokens.items():
	length = len(k)
	currlen = length
	while currlen > 1:
		if (substr := k[:currlen-1]) in tokens:
			tokens[substr].tokenize_flags |= TokenizeFlags.CheckNext
			tokens[substr].max_search_size = max(length, tokens[substr].max_search_size)
		currlen -= 1

# print(tokens)
# exit()



token_output = path.realpath("../src/parse/tokens.gperf")
header_file = path.realpath("../src/parse/tokenhash.h")
c_file = path.realpath("../src/parse/tokenhash.c")
struct_name = "HashToken"

with open(token_output, "w") as f:
	f.write(f"%delimiters={delimiter}\n")
	# if includes or typedef:
	f.write("%{\n")
	f.write('\n#include "tokenhash.h"\n')
	# if typedef:
	# 	f.write(f"typedef struct {struct_name} {struct_name};\n")
	f.write("%}\n")
	f.write(f"struct {struct_name}\n" + "{\n")
	for name, dtype in Result.__annotations__.items():
		# f.write(f"\t{dtype} {name};\n")
		f.write(f"\t{dtype.decl(name)};\n")
	f.write("};\n%%\n")
	for tok in tokens.values():
		f.write(f"{tok}\n")

gperf_path = shutil.which("gperf")

# gperf -L C -t -G ../src/parse/tokens.gperf --output-file=../src/parse/tokenhash.h
subprocess.run([
	gperf_path, "-L", "C", 
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
	# for f in lines:
	# 	if f.startswith("struct ")


with open(header_file, "w") as f:
	f.write("#ifndef INCLUDE_TOKENHASH_H\n#define INCLUDE_TOKENHASH_H\n\n")
	for inc in includes:
		f.write(f"#include <{inc}.h>\n")
	f.write(f"\nstruct {struct_name}\n" + "{\n")
	for name, dtype in Result.__annotations__.items():
		# f.write(f"\t{dtype} {name};\n")
		f.write(f"\t{dtype.decl(name)};\n")
	f.write("};\n\n")
	if typedef:
		f.write(f"typedef struct {struct_name} {struct_name};\n\n")
	f.write(f"{struct_name} * in_word_set (register const char* str, register unsigned int len);\n\n")
	f.write("#endif /* tokenhash.h */\n")





print("\n\n\nDONE\n\n\n")














