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

:: Calls the building test task
echo CALLING BUILDING TASK
echo.
call buildSolution.bat
