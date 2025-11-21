@echo off
cls
echo Compiling C++ code...
g++ main.cpp StudentSystem.cpp -o StudentSystem.exe -std=c++17 -Wall

if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b %errorlevel%
)

echo Compilation successful. Running program...
StudentSystem.exe

pause