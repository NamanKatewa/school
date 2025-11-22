#include "Building.h"
#include <iostream>
#include <iomanip>

Building::Building(int id, const std::string& name, const std::string& details)
    : buildingID(id), buildingName(name), locationDetails(details) {}

void Building::printRow() const {
    std::cout << "| " << std::left << std::setw(12) << buildingID
              << "| " << std::left << std::setw(20) << buildingName
              << "| " << std::left << std::setw(30) << locationDetails
              << " |" << std::endl;
}
