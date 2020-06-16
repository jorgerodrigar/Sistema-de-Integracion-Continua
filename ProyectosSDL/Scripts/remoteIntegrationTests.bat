@echo off

:: Finds and executes the .exe
cd ..
cd bin

:: Checks if the .exe was created
if not exist Main.exe (
    echo COULD NOT FIND Main.exe
    color 0C
    exit
)

:: Finds and executes .exe file.
Main.exe INTEGRATION_TEST