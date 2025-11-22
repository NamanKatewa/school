@echo off
if not exist target mkdir target > nul 2>&1
g++ src/*.cpp -o target/inventory_system.exe
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation failed!
    goto :eof
)
echo.
echo Compilation successful!
echo.
target\inventory_system.exe