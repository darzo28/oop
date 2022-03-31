@echo off

SET MyProgram="%~1"
             
REM Missing arguments
%MyProgram% 16 10 && goto err
echo Test 1 passed

REM Wrong number
%MyProgram% 16 10 1Z && goto err
echo Test 2 passed

REM Wrong input radix
%MyProgram% 1 10 11 && goto err
echo Test 3 passed

REM Wrong output radix
%MyProgram% 16 37 11 && goto err
echo Test 4 passed

REM Overflow
%MyProgram% 16 10 FFFFFFFF && goto err
echo Test 5 passed

REM Convert
%MyProgram% 16 10 FF > out.txt || goto err
SET /p Result=< out.txt
echo Out: %Result% Expected: 255

%MyProgram% 10 16 999 > out.txt || goto err
SET /p Result=< out.txt
echo Out: %Result% Expected: 3E7

%MyProgram% 2 10 1010 > out.txt || goto err
SET /p Result=< out.txt
echo Out: %Result% Expected: 10

%MyProgram% 10 2 11 > out.txt || goto err
SET /p Result=< out.txt
echo Out: %Result% Expected: 1011

%MyProgram% 10 2 -11 > out.txt || goto err
SET /p Result=< out.txt
echo Out: %Result% Expected: -1011

echo All tests passed successfuly
exit /B 0

:err
echo Test failed
exit /B 1