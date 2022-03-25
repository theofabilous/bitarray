import itertools as itr

def expand_variadic(num, npl, f, rev=False):
	itrb = (f(i) for i in range(1, num+1))
	if rev:
		itrb = reversed(list(itrb))
	l = []
	acc = []
	for i, s in enumerate(itrb):
		if i != 0 and (not (i % npl)):
			l.append(", ".join(acc + [s]))
			acc = []
		else:
			acc.append(s)
	if(len(acc) != 0):
		l.append(", ".join(acc))
	return ", \\\n".join(l)

def get_arg_counter(num, npl):
	return "#define GET_NTH_ARG(" + \
		expand_variadic(num, npl, lambda i: f"_{i}") + ", NAME, ...)" + \
		" NAME"

def get_general_macro(prefix, num, npl):
	return f"#define {prefix}(...) " + \
	"GET_NTH_ARG(__VA_ARGS__, " + \
	expand_variadic(num, npl, 
		lambda i: f"{prefix}_{i}", rev=True) + ")(__VA_ARGS__)"

def get_macro_def_for(prefix, num, anpl, onpl, opr, wrap=lambda x:x):
	return f"#define {prefix}_{num}(" + \
		expand_variadic(num, anpl, lambda i: f"_{i}") + ") \\\n" + \
		wrap(expand_variadic(num, onpl, lambda i: opr(f"_{i}")))


def get_pair_wise_args(prefix, num, npl, f, w):
	pre_f = lambda i: f"_{(i*2)-1}, _{i*2}"
	return f"#define {prefix}_{num}(" + \
		expand_variadic(num, npl, lambda i: f"_{i}") + ") \\\n" + \
		w(expand_variadic(
				num // 2, npl // 3, lambda i, pr=pre_f: f( pr(i) ) ))
							

def get_compressed_args(arg_prefix, num, get_l=False):
	def rec_(i):
		if i==1:
			return f"#define {arg_prefix}_1 __EXPAND(_1, _2)"
		else:
			return f"#define {arg_prefix}_{i} " + \
				   f"__INCR_EXPAND(_{(i*2)-1}, _{i*2}, {arg_prefix}_{i-1})"
	l = [rec_(i) for i in range(1, (num // 2)+1)]
	if get_l: return l
	else: return "\n".join(l)

def get_all_pair_wise_args_compressed(aprefix, prefix, num):
	args = get_compressed_args(aprefix, num, True)
	defs = []
	for i, a in enumerate(args):
		defs.append( f"#define {prefix}_{(i+1)*2}(" + \
			expand_variadic((i+1)*2, 8, lambda i: f"_{i}") + ") \\\n" + \
			f"WRAP_BEGIN {aprefix}_{i+1} WRAP_END\n" )
	return "\n".join(defs)

'''
#define WRAP_BEGIN ((BinaryMapEntry[]) {
#define WRAP_END })

#define __EXPAND(x, y) ((BinaryMapEntry) x, y)
#define __INCR_EXPAND(x, y, ...) __VA_ARGS__, __EXPAND(x, y)

#define _ARGS_1_ __EXPAND(_1, _2)
#define _ARGS_2_ __INCR_EXPAND(_3, _4, _ARGS_1_)
#define _ARGS_3_ __INCR_EXPAND(_5, _6, _ARGS_2_)

_ARGS_3_ ===> 
((BinaryMapEntry) _1, _2), ((BinaryMapEntry) _3, _4), ((BinaryMapEntry) _5, _6)

'''



# def igroup(itrb, n):
# 	itrb_ = enumerate(itrb)
# 	gg = []
# 	acc = []
# 	while True:



# print(get_arg_counter(128, 12))
# print("\n")
# print(get_general_macro("_BINMAP", 128, 8))
# print("\n")
# print("\n\n")

# print("\n\n\n")
# wrap_pairs = lambda x: f"((BinaryMapEntry) {x})"

# for i in range(0, 129, 2):
# 	print(get_pair_wise_args("_BINMAP", i, 6, 
# 		wrap_pairs, lambda args,j=(i//2): f"{j}, {args}\n"))





# print(get_arg_counter(128, 12))
# print("\n")
# print(get_general_macro("__BINMAP", 128, 8))
# print("\n")
# print("\n\n")

# print("\n\n\n")
# wrap_pairs = lambda x: f"((BinaryMapEntry) {x})"

# p_1 = "((BinaryMapEntry[]) " + r"{"
# p_2 = r"}"

# for i in range(0, 129, 2):
# 	wrap_all = lambda args: f"{i//2}, " + p_1 + f"{args}" + p_2 + ")\n"
# 	print(get_pair_wise_args("__BINMAP", i, 6, 
# 		wrap_pairs, wrap_all))


print(get_compressed_args("_ARGS", 128))
print(get_all_pair_wise_args_compressed("_ARGS", "__BINMAP", 128))
