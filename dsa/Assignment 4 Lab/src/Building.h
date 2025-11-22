#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <string>

class Building {
public:
    int buildingID;
    std::string buildingName;
    std::string locationDetails;

    Building(int id = 0, const std::string& name = "", const std::string& details = "");

    void printRow() const;
};

#endif
