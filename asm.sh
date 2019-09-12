#!/bin/sh
rm base64.o
nasm -f elf64 -o base64.o base64.asm

