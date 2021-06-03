@echo off
:loop
gen.exe
1.exe
2.exe
fc 1.out 2.out
if not errorlevel 1 goto loop
pause
:endl