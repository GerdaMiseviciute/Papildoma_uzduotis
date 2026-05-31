@echo off

if not exist build (
    mkdir build
)

cd build

cmake .. -G "MinGW Makefiles"
cmake --build .

REM run program from PROJECT ROOT context
cd ..

build\Objektinis-programavimas.exe

pause