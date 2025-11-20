@echo off
echo Compiling...
g++ -std=c++17 main.cpp Array.cpp ComplexityDemo.cpp SinglyLinkedList.cpp StackArray.cpp StackList.cpp QueueArray.cpp QueueList.cpp PostfixEvaluator.cpp SearchAlgorithms.cpp SortingAlgorithms.cpp BinarySearchTree.cpp -o main.exe
if %errorlevel% neq 0 (
    echo Compilation failed.
    exit /b %errorlevel%
)
echo Compilation successful.
echo Running...
echo.
main.exe
