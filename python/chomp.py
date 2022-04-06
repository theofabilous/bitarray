
def println(l: list):
	tuple(map(lambda x: print(x), l))

def str_to_hex(s: str):
	val = 0
	for c in s:
		val |= ord(c)
		val <<= 8
	return hex(val >> 8)

def get_lots_of_zeroes(n, npl):
	str_l = [
		','.join(['0' for _ in range(npl)])
		for _ in range(n // npl)
	]
	return ',\n'.join(str_l)




FORMATS = []

for i in (8, 16, 32, 64):
	FORMATS.append(f"u{i}")
	FORMATS.append(f"i{i}")

VALUES = list(map(
	str_to_hex, FORMATS
	))

println(FORMATS)
println(VALUES)

ZEROES = get_lots_of_zeroes(32, 16)
print(ZEROES)



