@echo off
echo Compiling project...
g++ -std=c++17 main.cpp Graph.cpp AVLTree.cpp DataManager.cpp UIManager.cpp -o SmartCity.exe

if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b %errorlevel%
)

echo Compilation successful.
echo Running SmartCity.exe...
SmartCity.exe

exit /b 0
