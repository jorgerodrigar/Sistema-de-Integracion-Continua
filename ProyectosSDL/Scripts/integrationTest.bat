@echo off

cd ..
cd bin

:: Finds and executes .exe file.
Main.exe INTEGRATION_TEST

:: Finds the output of the .exe and reads its second line (results).
cd ..
cd logs

for /f "skip=1" %%G IN (integrationTestsOutput.txt) DO if not defined integrationLine set "integrationLine=%%G"

if %integrationLine%==!!!FAILURES!!! (
    :: If the tests fail, shows the output.
    type integrationTestsOutput.txt
    color 0C
    echo INTEGRATION TESTS HAVE FAILED
    echo PUSH HAS BEEN CANCELLED
    pause
) else (
    :: If the tests pass, executes the integration tests.
    color 0A
    echo INTEGRATION TESTS HAVE PASSED
    echo.

    :: Goes to the original path to start the integration test .bat
    cd ..
    cd Scripts
    call finishPipeline.bat
)