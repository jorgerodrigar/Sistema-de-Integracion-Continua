@echo off
:: Simple add + commit using git
set /p commitName=Enter commit name: 
git add .
git commit -m "%commitName%"

:: Calls the unit test task
echo CALLING UNIT TEST TASK
call unitTests.bat
pause