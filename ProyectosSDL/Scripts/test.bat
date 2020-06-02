@echo off
:: CHANGE THIS PATH IF YOUR DEVENV.EXE IS IN ANOTHER PATH
SET PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\

:: Finds and executes the .exe
cd ..
cd bin

:: Delete the previous .exe
if exist HolaSDLDebug.exe (
    echo DELETING PREVIOUS .EXE
    del HolaSDLDebug.exe
)

:: Build the solution
devenv "..\ProyectosSDL.sln" /build Debug
echo.

:: Checks if the .exe was created
if not exist HolaSDLDebug.exe (
    echo COULD NOT BUILD THE PROJECT, CHECK YOUR DEVENV PATH OR COMPILATION ERRORS
    pause
    exit
)

:: Finds and executes .exe file.
HolaSDLDebug.exe TEST

:: Finds the output of the .exe and reads its second line (results).
cd ..
cd logs

for /f "skip=1" %%G IN (testOutput.txt) DO if not defined line set "line=%%G"

if %line%==!!!FAILURES!!! (
    :: If the tests fail, shows the output.
    type testOutput.txt
    echo UNIT TESTS HAVE FAILED.
) else (
    :: If the tests pass, executes the integration tests.
    echo UNIT TESTS HAVE PASSED.
    echo.
)

pause