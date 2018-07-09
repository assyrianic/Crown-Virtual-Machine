#!/bin/bash
cd "$(dirname "$0")"
gcc			-Wextra -Wall -std=c99 -Os -c	tagha_api.c
ar			cr libtaghagcc.a	tagha_api.o

#gcc			-Wextra -Wall -std=c99 -Os -S -masm=intel tagha_api.c

rm	tagha_api.o


gcc			-Wextra -Wall -std=c++11 -Os -c	tagha_api_cpp.cpp -L. -ltagha
ar			cr libtaghacpp.a	tagha_api_cpp.o

rm	tagha_api_cpp.o


clang-3.5			-Wextra -Wall -std=c99 -Os -c	tagha_api.c
ar			cr libtaghaclang.a	tagha_api.o

rm	tagha_api.o
