@echo off
g++ main.cpp WeatherSystem.cpp -o WeatherApp.exe -std=c++11
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    .\WeatherApp.exe
) ELSE (
    echo Compilation failed!
)
pause