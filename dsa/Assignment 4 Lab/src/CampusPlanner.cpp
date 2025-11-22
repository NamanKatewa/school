#include "CampusPlanner.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <iomanip>

void CampusPlanner::loadBuildings() {
    std::ifstream file("buildings.csv");
    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        int id;
        std::string name, details;

        std::getline(ss, item, ',');
        id = std::stoi(item);
        std::getline(ss, name, ',');
        std::getline(ss, details, ',');

        Building b(id, name, details);
        buildings.push_back(b);
        buildingTree.insertBuilding(b);
    }
}

void CampusPlanner::listCampusLocations(int traversalType) {
    switch (traversalType) {
        case 1:
            std::cout << "\n\033[1;36mIn-order Traversal\033[0m\n";
            buildingTree.inorderTraversal();
            break;
        case 2:
            std::cout << "\n\033[1;36mPre-order Traversal\033[0m\n";
            buildingTree.preorderTraversal();
            break;
        case 3:
            std::cout << "\n\033[1;36mPost-order Traversal\033[0m\n";
            buildingTree.postorderTraversal();
            break;
        default:
            std::cout << "\033[1;31mInvalid choice.\033[0m\n";
    }
}

void CampusPlanner::constructCampusGraph() {
    campusGraph.constructFromData(buildings, "edges.csv");
}

void CampusPlanner::findOptimalPath(int start, int end) {
    double totalDistance = 0;
    std::vector<int> path = campusGraph.dijkstra(start, end, totalDistance);

    if (path.empty()) {
        std::cout << "\033[1;31mNo path found between " << start << " and " << end << ".\033[0m\n";
    } else {
        std::cout << "\n\033[1;36mShortest Path from " << start << " to " << end << "\033[0m\n";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        std::cout << "\nTotal distance: " << totalDistance << std::endl;
    }
}

void CampusPlanner::planUtilityLayout() {
    std::vector<std::tuple<int, int, double>> mst = campusGraph.kruskalMST();
    double totalWeight = 0;

    std::cout << "+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+" << std::endl;
    std::cout << "| " << std::left << std::setw(10) << "Vertex 1" << "| " << std::left << std::setw(10) << "Vertex 2" << "| " << std::left << std::setw(10) << "Weight" << " |" << std::endl;
    std::cout << "+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+" << std::endl;

    for (const auto& edge : mst) {
        totalWeight += std::get<2>(edge);
        std::cout << "| " << std::left << std::setw(10) << std::get<0>(edge)
                  << "| " << std::left << std::setw(10) << std::get<1>(edge)
                  << "| " << std::left << std::setw(10) << std::get<2>(edge)
                  << " |" << std::endl;
    }

    std::cout << "+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+-" << std::string(10, '-') << "-+" << std::endl;
    std::cout << "Total MST weight: " << totalWeight << std::endl;
}

void CampusPlanner::evaluateEnergyExpression(const std::vector<std::string>& tokens) {
    try {
        expressionTree.buildFromPostfix(tokens);
        std::cout << "In-order expression: ";
        expressionTree.printInorder();
        std::cout << "Result: " << expressionTree.evaluate() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\033[1;31mError: " << e.what() << "\033[0m\n";
    }
}

void CampusPlanner::addBuildingRecord(int id, const std::string& name, const std::string& details) {
    Building newBuilding(id, name, details);
    buildings.push_back(newBuilding);
    buildingTree.insertBuilding(newBuilding);
    
    std::ofstream file("buildings.csv", std::ios_base::app);
    file << id << "," << name << "," << details << std::endl;

    std::cout << "\033[1;32mBuilding added successfully.\033[0m\n";
}

void CampusPlanner::printAdjacencyTable() {
    campusGraph.printAdjacencyTable();
}
