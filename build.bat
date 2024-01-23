@echo off
zig cc -std=c11 -D_CRT_SECURE_NO_WARNINGS src/main.c src/prayer.c src/julian.c src/solar.c src/time_utils.c -o prayer.exe -lm
prayer.exe --help
