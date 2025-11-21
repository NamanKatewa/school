#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <string>
#include <vector>
#include "Graph.h"
#include "AVLTree.h"

class DataManager {
public:
    void loadCityData(const std::string& filename, CityGraph& graph, AVLTree& tree);
    void loadTaskData(const std::string& filename, std::vector<std::pair<std::string, std::string>>& tasks);
};

#endif