#include "InventoryItem.h"
#include <iostream>

InventoryItem::InventoryItem() : itemID(0), itemName(""), quantity(0), price(0.0) {}

InventoryItem::InventoryItem(int id, const std::string& name, int qty, double prc)
    : itemID(id), itemName(name), quantity(qty), price(prc) {}

int InventoryItem::getItemID() const {
    return itemID;
}

std::string InventoryItem::getItemName() const {
    return itemName;
}

int InventoryItem::getQuantity() const {
    return quantity;
}

double InventoryItem::getPrice() const {
    return price;
}

void InventoryItem::setItemID(int id) {
    itemID = id;
}

void InventoryItem::setItemName(const std::string& name) {
    itemName = name;
}

void InventoryItem::setQuantity(int qty) {
    quantity = qty;
}

void InventoryItem::setPrice(double prc) {
    price = prc;
}

#include <iomanip>

void InventoryItem::printItem() const {
    std::cout << std::left << std::setw(10) << itemID 
              << std::setw(20) << itemName 
              << std::setw(15) << quantity 
              << std::setw(10) << price << std::endl;
}