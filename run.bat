@echo off
gcc -std=c11 -D_CRT_SECURE_NO_WARNINGS main.c -o main -lm
main.exe
