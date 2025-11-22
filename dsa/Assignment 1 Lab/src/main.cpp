#include "InventorySystem.h"
#include "InventoryItem.h"
#include "SparseMatrix.h" // Include SparseMatrix
#include "colors.h"       // Include for colors
#include <iostream>
#include <limits> // For numeric_limits
#include <string>

// Function to clear the console
void clearConsole() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

// Function to pause execution and wait for user input
void pressEnterToContinue() {
    std::cout << "\n" << BOLD_YELLOW << "Press Enter to continue..." << RESET;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int main() {
    Color::setup(); // Initialize color support
    InventorySystem myInventory;
    myInventory.loadItemsFromCSV("data.csv"); // Load data from the generated CSV
    int choice;

    do {
        clearConsole();
        std::cout << BOLD_CYAN << "===== Inventory Management System =====" << RESET << std::endl;
        std::cout << GREEN << "1. Add Item" << RESET << std::endl;
        std::cout << GREEN << "2. Remove Item" << RESET << std::endl;
        std::cout << GREEN << "3. Search Item" << RESET << std::endl;
        std::cout << GREEN << "4. Display All Items" << RESET << std::endl;
        std::cout << YELLOW << "5. Manage Price-Quantity Table (Row-Major)" << RESET << std::endl;
        std::cout << YELLOW << "6. Manage Price-Quantity Table (Column-Major Simulation)" << RESET << std::endl;
        std::cout << MAGENTA << "7. Optimize Sparse Storage (Sample Data)" << RESET << std::endl;
        std::cout << MAGENTA << "8. Print Sparse Matrix" << RESET << std::endl;
        std::cout << RED << "0. Exit" << RESET << std::endl;
        std::cout << BOLD_WHITE << "Enter your choice: " << RESET;
        std::cin >> choice;

        // Clear the input buffer after reading an integer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                clearConsole();
                int id, qty;
                std::string name;
                double price;

                std::cout << "Enter Item ID: ";
                std::cin >> id;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Item Name: ";
                std::getline(std::cin, name);
                std::cout << "Enter Quantity: ";
                std::cin >> qty;
                std::cout << "Enter Price: ";
                std::cin >> price;

                myInventory.addItemRecord(InventoryItem(id, name, qty, price));
                pressEnterToContinue();
                break;
            }
            case 2: {
                clearConsole();
                int id;
                std::cout << "Enter Item ID to remove: ";
                std::cin >> id;
                myInventory.removeItemRecord(id);
                pressEnterToContinue();
                break;
            }
            case 3: {
                clearConsole();
                myInventory.searchByItem();
                pressEnterToContinue();
                break;
            }
            case 4: {
                clearConsole();
                myInventory.printAllItems();
                pressEnterToContinue();
                break;
            }
            case 5: {
                clearConsole();
                myInventory.managePriceQuantityRowMajor();
                pressEnterToContinue();
                break;
            }
            case 6: {
                clearConsole();
                myInventory.managePriceQuantityColumnMajor();
                pressEnterToContinue();
                break;
            }
            case 7: {
                clearConsole();
                // Sample dense matrix for rarely restocked products
                // In a real scenario, this would come from an external source or be larger.
                const int R_ROWS = 5;
                const int R_COLS = 5;
                int sampleDenseMatrix[R_ROWS * R_COLS] = {
                    1, 0, 0, 0, 2,
                    0, 0, 3, 0, 0,
                    0, 0, 0, 0, 0,
                    4, 0, 0, 0, 5,
                    0, 0, 6, 0, 0
                };
                
                SparseMatrix sm(R_ROWS, R_COLS);
                sm.buildFromDense(sampleDenseMatrix, R_ROWS, R_COLS);
                sm.print(); // Print from the dedicated SparseMatrix object

                std::cout << "\nNote: This demonstration uses a local SparseMatrix object." << std::endl;
                std::cout << "The InventorySystem's internal sparse storage is separate." << std::endl;
                std::cout << "To use the InventorySystem's internal sparse storage, its optimizeSparseStorage" << std::endl;
                std::cout << "method would need to be called with appropriate data, or the SparseMatrix" << std::endl;
                std::cout << "object could be integrated more directly." << std::endl;

                // Example of how to use InventorySystem's internal sparse storage if `optimizeSparseStorage`
                // were correctly adapted to accept a flexible 2D array or reference the SparseMatrix object.
                // For now, I'll pass a dummy fixed size array
                int dummyFullMatrix[10][10] = {
                    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                };
                myInventory.optimizeSparseStorage(dummyFullMatrix, 10, 10);

                pressEnterToContinue();
                break;
            }
            case 8: {
                clearConsole();
                myInventory.printSparseMatrix();
                pressEnterToContinue();
                break;
            }
            case 0: {
                std::cout << "Exiting program. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                pressEnterToContinue();
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
