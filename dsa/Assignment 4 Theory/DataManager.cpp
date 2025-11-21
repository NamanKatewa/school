#include "DataManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

void DataManager::loadCityData(const std::string& filename, CityGraph& graph, AVLTree& tree) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }
    std::string line;
    std::getline(file, line); 

    std::map<int, CityNode> nodes;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        
        int srcID, destID, distance;
        std::string srcName, destName, zoneType;

        std::getline(ss, field, ','); srcID = std::stoi(field);
        std::getline(ss, srcName, ',');
        std::getline(ss, field, ','); destID = std::stoi(field);
        std::getline(ss, destName, ',');
        std::getline(ss, field, ','); distance = std::stoi(field);
        std::getline(ss, zoneType, ',');

        if (nodes.find(srcID) == nodes.end()) {
            nodes[srcID] = {srcID, srcName, zoneType};
            graph.addNode(nodes[srcID]);
            tree.insert(nodes[srcID]);
        }
        if (nodes.find(destID) == nodes.end()) {
            nodes[destID] = {destID, destName, zoneType};
            graph.addNode(nodes[destID]);
            tree.insert(nodes[destID]);
        }
        graph.addRoad(srcID, destID, distance);
    }
    file.close();
    std::cout << "Loaded " << nodes.size() << " city zones and their connections.\n";
}

void DataManager::loadTaskData(const std::string& filename, std::vector<std::pair<std::string, std::string>>& tasks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string taskA, taskB;
        std::getline(ss, taskA, ',');
        std::getline(ss, taskB, ',');
        tasks.push_back({taskA, taskB});
    }
    file.close();
}
