@echo off
:: Simple add + commit using git
set /p commitName=Enter commit name:

:: Goes to the .git directory
cd ..
cd .. 
git add .
git commit -m "%commitName%"

:: Goes to the /Scripts directory
cd ProyectosSDL/Scripts

:: Calls the unit test task
echo CALLING UNIT TEST TASK
echo.
call unitTests.bat
