@echo off
set cnt=1
:loop
gen.exe > 1.in
1.exe < 1.in > 1.out
2.exe < 1.in > 2.out
echo cnt:%cnt%
fc 1.out 2.out
set /a cnt=%cnt%+1
if not errorlevel 1 goto loop
pause
endl