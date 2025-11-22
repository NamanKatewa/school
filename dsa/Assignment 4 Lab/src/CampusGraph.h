#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H

#include "Building.h"
#include <vector>
#include <string>
#include <tuple>

class CampusGraph {
private:
    std::vector<std::vector<std::pair<int, double>>> adjList;
    std::vector<Building> buildings;

public:
    void constructFromData(const std::vector<Building> &buildings, const std::string &edgesFile);
    void printAdjacencyTable() const;
    std::vector<int> dijkstra(int sourceID, int targetID, double &totalDistance) const;
    std::vector<std::tuple<int, int, double>> kruskalMST() const;
};

#endif
