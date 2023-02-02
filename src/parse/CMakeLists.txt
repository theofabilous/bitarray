cmake_minimum_required(VERSION 3.21)
project(parse C)

add_library(parse STATIC
	tokenize.c
	tokentree.c
	# treecompile.c
	_treecompile.c
	tokenhash.c
	vm.c
)

include_directories(/usr/local/include)
