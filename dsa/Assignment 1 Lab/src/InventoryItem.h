#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include <string>

class InventoryItem {
private:
    int itemID;
    std::string itemName;
    int quantity;
    double price;

public:
    InventoryItem();
    InventoryItem(int id, const std::string& name, int qty, double prc);

    int getItemID() const;
    std::string getItemName() const;
    int getQuantity() const;
    double getPrice() const;

    void setItemID(int id);
    void setItemName(const std::string& name);
    void setQuantity(int qty);
    void setPrice(double prc);

    void printItem() const;
};

#endif