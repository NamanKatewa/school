#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include "InventoryItem.h"
#include <string>
#include <iostream>

class SparseMatrix; 

class InventorySystem {
private:
    static const int MAX_ITEMS = 100;
    InventoryItem items[MAX_ITEMS];
    int itemCount;
    double priceQuantityTable[MAX_ITEMS][2];

    static const int MAX_NONZERO = 100;
    int sparseRow[MAX_NONZERO];
    int sparseCol[MAX_NONZERO];
    int sparseVal[MAX_NONZERO];
    int sparseCount;

public:
    InventorySystem();

    void addItemRecord(const InventoryItem &item);
    bool removeItemRecord(int itemID);
    int searchByItemID(int itemID) const;
    int searchByItemName(const std::string &name) const;
    void searchByItem() const;

    void managePriceQuantityRowMajor() const;
    void managePriceQuantityColumnMajor() const;

    void optimizeSparseStorage(const int fullMatrix[10][10], int rows, int cols);
    void printSparseMatrix() const;

    void printAllItems() const;

    void loadItemsFromCSV(const std::string& filename);
};

#endif