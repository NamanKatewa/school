#ifndef CITY_DATA_H
#define CITY_DATA_H

#include <string>

struct Edge {
    int destID;
    int weight;
};

struct CityNode {
    int id;
    std::string name;
    std::string zoneType;
};

#endif
