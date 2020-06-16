@echo off
:: CHANGE THIS PATH IF YOUR DEVENV.EXE IS IN ANOTHER PATH
set ORIGINAL_PATH=%PATH% 
set PATH=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\

:: Finds and executes the .exe
cd ..
cd bin

:: Delete the previous .exe
if exist Main.exe (
    echo DELETING PREVIOUS .EXE
    del Main.exe
)

cd ..
cd UnitTests
cd exes

:: Delete the previous .exe
if exist UnitTests.exe (
    echo DELETING PREVIOUS .EXE
    del UnitTests.exe
)

cd ..

echo.
:: Build the solution
echo BUILDING THE SOLUTION
devenv /Build Debug /Project Tracker "..\ProyectosSDL.sln"
devenv /Build Debug /Project Moonace "..\ProyectosSDL.sln"
devenv /Build Debug /Project UnitTests "..\ProyectosSDL.sln"
devenv /Build Debug /Project Main "..\ProyectosSDL.sln"
echo.

:: Recovers the original user defined path
set PATH=%ORIGINAL_PATH% 

cd ..
cd bin

:: Checks if the .exe was created
if not exist Main.exe (
    echo COULD NOT BUILD THE MAIN PROJECT, CHECK YOUR DEVENV PATH OR COMPILATION ERRORS
    color 0C
    pause
    exit
)

cd ..
cd UnitTests
cd exes

:: Checks if the .exe was created
if not exist UnitTests.exe (
    echo COULD NOT BUILD THE UNIT TESTS PROJECT, CHECK YOUR DEVENV PATH OR COMPILATION ERRORS
    color 0C
    pause
    exit
)

cd ..
cd ..
cd Scripts

call unitTests.bat