@echo off

:: Finds and executes the .exe
cd ..
cd bin

:: Checks if the .exe was created
if not exist HolaSDLDebug.exe (
    echo COULD NOT BUILD THE PROJECT, CHECK YOUR DEVENV PATH OR COMPILATION ERRORS
    color 0C
    exit
)

:: Finds and executes .exe file.
HolaSDLDebug.exe UNIT_TEST
