all:	src/inter.cpp
	g++	src/inter.cpp	-I	headers/	\
	-fpic	-shared	-o lib/libinterpreter.so
	g++	usr/example.cpp	-I	headers/	-L	lib/	\
	-linterpreter	-o	bin/inter
	export LD_LIBRARY_PATH=$(pwd)/lib/
	bin/inter