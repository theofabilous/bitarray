cmake_minimum_required(VERSION 3.21)
project(parse C)

add_library(parse STATIC
	tokenize.c
	tokentree.c
	stringtree.c
	treecompile.c)

include_directories(/usr/local/include)