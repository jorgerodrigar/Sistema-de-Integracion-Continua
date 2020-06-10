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

echo.
:: Build the solution
echo BUILDING THE SOLUTION
devenv "..\ProyectosSDL.sln" /build Debug
echo.

:: Checks if the .exe was created
if not exist HolaSDLDebug.exe (
    echo COULD NOT BUILD THE PROJECT, CHECK YOUR DEVENV PATH OR COMPILATION ERRORS
    color 0C
    pause
    exit
)

:: Finds and executes .exe file.
HolaSDLDebug.exe UNIT_TEST

:: Finds the output of the .exe and reads its second line (results).
cd ..
cd logs

for /f "skip=1" %%G IN (unitTestsOutput.txt) DO if not defined unitLine set "unitLine=%%G"

if %unitLine%==!!!FAILURES!!! (
    :: If the tests fail, shows the output.
    type unitTestsOutput.txt
    color 0C
    echo UNIT TESTS HAVE FAILED.
    pause
) else (
    :: If the tests pass, executes the integration tests.
    echo UNIT TESTS HAVE PASSED.
    echo.

    :: Goes to the original path to start the integration test .bat
    cd ..
    cd Scripts
    call integrationTest.bat
)
