@echo off
gcc -std=c11 -D_CRT_SECURE_NO_WARNINGS src/main.c src/prayer.c src/julian.c src/solar.c -o prayer -lm
prayer.exe
