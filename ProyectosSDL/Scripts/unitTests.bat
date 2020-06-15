@echo off

cd ..
cd UnitTests
cd exes

:: Finds and executes .exe file.
UnitTests.exe

:: Finds the output of the .exe and reads its second line (results).
cd ..
cd ..
cd logs

for /f "skip=1" %%G IN (unitTestsOutput.txt) DO if not defined unitLine set "unitLine=%%G"

if %unitLine%==!!!FAILURES!!! (
    :: If the tests fail, shows the output.
    type unitTestsOutput.txt
    color 0C
    echo UNIT TESTS HAVE FAILED
    echo PUSH HAS BEEN CANCELLED
    pause
) else (
    :: If the tests pass, executes the integration tests.
    echo UNIT TESTS HAVE PASSED
    echo.

    :: Goes to the original path to start the integration test .bat
    cd ..
    cd Scripts
    call integrationTest.bat
)
