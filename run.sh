#!/bin/bash

set -e

if [ $# -eq 1 ] && [ -e $1 ]
then
	./prog < $1 > out.asm
	nasm -f elf out.asm
	gcc -m32 out.o
	./a.out
elif [ $# -eq 0 ]
then
	rm -f out.asm out.o a.out
else
	exit 1
fi
