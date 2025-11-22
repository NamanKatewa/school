#include "InventorySystem.h"
#include "colors.h"
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>

InventorySystem::InventorySystem() : itemCount(0), sparseCount(0) {
    for (int i = 0; i < MAX_ITEMS; ++i) {
        priceQuantityTable[i][0] = 0.0;
        priceQuantityTable[i][1] = 0;
    }
}

void InventorySystem::addItemRecord(const InventoryItem &item) {
    if (itemCount < MAX_ITEMS) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i].getItemID() == item.getItemID()) {
                std::cout << "Error: Item with ID " << item.getItemID() << " already exists." << std::endl;
                return;
            }
        }
        items[itemCount] = item;
        priceQuantityTable[itemCount][0] = item.getPrice();
        priceQuantityTable[itemCount][1] = item.getQuantity();
        itemCount++;
        std::cout << "Item added successfully." << std::endl;
    } else {
        std::cout << "Error: Inventory is full. Cannot add more items." << std::endl;
    }
}

bool InventorySystem::removeItemRecord(int itemID) {
    int index = searchByItemID(itemID);
    if (index != -1) {
        for (int i = index; i < itemCount - 1; ++i) {
            items[i] = items[i + 1];
            priceQuantityTable[i][0] = priceQuantityTable[i+1][0];
            priceQuantityTable[i][1] = priceQuantityTable[i+1][1];
        }
        itemCount--;
        std::cout << "Item with ID " << itemID << " removed successfully." << std::endl;
        return true;
    }
    std::cout << "Error: Item with ID " << itemID << " not found." << std::endl;
    return false;
}

int InventorySystem::searchByItemID(int itemID) const {
    for (int i = 0; i < itemCount; ++i) {
        if (items[i].getItemID() == itemID) {
            return i;
        }
    }
    return -1;
}

int InventorySystem::searchByItemName(const std::string &name) const {
    for (int i = 0; i < itemCount; ++i) {
        if (items[i].getItemName() == name) {
            return i;
        }
    }
    return -1;
}

void InventorySystem::searchByItem() const {
    std::cout << "Search by (1) ID or (2) Name? Enter choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter Item ID: ";
        int id;
        std::cin >> id;
        int index = searchByItemID(id);
        if (index != -1) {
            std::cout << "Item Found: ";
            items[index].printItem();
        } else {
            std::cout << "Item with ID " << id << " not found." << std::endl;
        }
    } else if (choice == 2) {
        std::cout << "Enter Item Name: ";
        std::string name;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::getline(std::cin, name);
        int index = searchByItemName(name);
        if (index != -1) {
            std::cout << "Item Found: ";
            items[index].printItem();
        } else {
            std::cout << "Item with Name '" << name << "' not found." << std::endl;
        }
    } else {
        std::cout << "Invalid choice." << std::endl;
    }
}

void InventorySystem::managePriceQuantityRowMajor() const {
    std::cout << "Price-Quantity Table (Row-Major):" << std::endl;
    for (int i = 0; i < itemCount; ++i) {
        std::cout << "Item " << items[i].getItemID() << ": (Price: " << priceQuantityTable[i][0] 
                  << ", Quantity: " << priceQuantityTable[i][1] << ")" << std::endl;
    }
}

void InventorySystem::managePriceQuantityColumnMajor() const {
    std::cout << "Price-Quantity Table (Column-Major simulation):" << std::endl;
    std::cout << "Prices:" << std::endl;
    for (int i = 0; i < itemCount; ++i) {
        std::cout << "  Item " << items[i].getItemID() << ": " << priceQuantityTable[i][0] << std::endl;
    }
    std::cout << "Quantities:" << std::endl;
    for (int i = 0; i < itemCount; ++i) {
        std::cout << "  Item " << items[i].getItemID() << ": " << priceQuantityTable[i][1] << std::endl;
    }
}

void InventorySystem::optimizeSparseStorage(const int fullMatrix[10][10], int rows, int cols) {
    sparseCount = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (fullMatrix[i][j] != 0) {
                if (sparseCount < MAX_NONZERO) {
                    sparseRow[sparseCount] = i;
                    sparseCol[sparseCount] = j;
                    sparseVal[sparseCount] = fullMatrix[i][j];
                    sparseCount++;
                } else {
                    std::cout << "Warning: Sparse storage capacity reached. Not all non-zero entries stored." << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << "Sparse storage optimized." << std::endl;
}

void InventorySystem::printSparseMatrix() const {
    std::cout << "Sparse Matrix (row, col, value) triplets:" << std::endl;
    if (sparseCount == 0) {
        std::cout << "  No sparse entries." << std::endl;
        return;
    }
    for (int i = 0; i < sparseCount; ++i) {
        std::cout << "  (" << sparseRow[i] << ", " << sparseCol[i] << ", " << sparseVal[i] << ")" << std::endl;
    }
}

#include <iomanip>

void InventorySystem::printAllItems() const {
    std::cout << BOLD_WHITE << "All Inventory Items:" << RESET << std::endl;
    if (itemCount == 0) {
        std::cout << "  No items in inventory." << std::endl;
        return;
    }
    std::cout << BOLD_YELLOW 
              << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Name" 
              << std::setw(15) << "Quantity" 
              << std::setw(10) << "Price" 
              << RESET << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    for (int i = 0; i < itemCount; ++i) {
        items[i].printItem();
    }
}

void InventorySystem::loadItemsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); 

    int itemsLoaded = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> seglist;

        while(std::getline(ss, segment, ',')) {
            seglist.push_back(segment);
        }

        if (seglist.size() == 4) {
            try {
                int id = std::stoi(seglist[0]);
                std::string name = seglist[1];
                int quantity = std::stoi(seglist[2]);
                double price = std::stod(seglist[3]);

                InventoryItem item(id, name, quantity, price);
                addItemRecord(item);
                itemsLoaded++;
            } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Warning: Skipping malformed line in CSV: " << line << std::endl;
        }
    }
    std::cout << "Loaded " << itemsLoaded << " items from " << filename << std::endl;
    file.close();
}
