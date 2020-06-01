@echo off

:: Finds and executes the .exe
cd ..
cd bin

:: Checks if the .exe exists
if not exist HolaSDLDebug.exe (
    echo COULD NOT FIND THE PROJECT
    pause
    exit
)

:: Finds and executes .exe file.
HolaSDLDebug.exe TEST
echo.

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