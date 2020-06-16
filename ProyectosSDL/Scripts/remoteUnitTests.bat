@echo off

:: Finds and executes the .exe
cd ..
cd UnitTests
cd exes

:: Checks if the .exe was created
if not exist UnitTests.exe (
    echo COULD NOT FIND UnitTests.exe
    color 0C
    exit
)

:: Finds and executes .exe file.
UnitTests.exe
