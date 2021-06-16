@echo off
cls

g++ -O -o out/EnhancedDivideTreasure.exe main.cpp -I resources/INC -L resources/LIB -static-libgcc -static-libstdc++

pause
