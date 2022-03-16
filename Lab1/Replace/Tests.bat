@echo off

SET MyProgram="%~1"
             
REM Empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" "" "" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Reading missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" "" "" && goto err
echo Test 2 passed

REM Replace substring
%MyProgram% input.txt "%TEMP%\output.txt" "a" "BB" || goto err
fc input-out.txt "%TEMP%\output.txt" || goto err
echo Test 3 passed

REM Replace substring
%MyProgram% input2.txt "%TEMP%\output.txt" "1231234" "B" || goto err
fc input2-out.txt "%TEMP%\output.txt" || goto err
echo Test 4 passed

REM Empty search string, program must copy file
%MyProgram% input.txt "%TEMP%\output.txt" "" "B" || goto err
fc input.txt "%TEMP%\output.txt" || goto err
echo Test 5 passed

echo All tests passed successfuly
exit /B 0

:err
echo Test failed
exit /B 1