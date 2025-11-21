@echo off
g++ main.cpp HospitalSystem.cpp -o HospitalApp.exe -std=c++11
IF %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    .\HospitalApp.exe
) ELSE (
    echo Compilation failed!
)
pause