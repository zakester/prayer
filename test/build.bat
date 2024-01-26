@echo off
zig cc -std=c11 -D_CRT_SECURE_NO_WARNINGS test.c -o test.exe
test.exe
