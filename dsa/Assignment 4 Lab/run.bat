@echo off
g++ src/*.cpp -o target/main.exe -std=c++11
IF %ERRORLEVEL% NEQ 0 (
    echo Compilation failed!
    exit /b %ERRORLEVEL%
)
target\main.exe