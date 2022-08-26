cmake_minimum_required(VERSION 3.21)
project(parse C)

add_library(parse STATIC
	src/tokenize.c
	src/tokentree.c)

include_directories(
	src
	/usr/local/include)