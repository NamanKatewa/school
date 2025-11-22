#ifndef CAMPUSPLANNER_H
#define CAMPUSPLANNER_H

#include "BuildingTree.h"
#include "CampusGraph.h"
#include "ExpressionTree.h"
#include <vector>

class CampusPlanner {
private:
    BuildingTree buildingTree;
    CampusGraph campusGraph;
    ExpressionTree expressionTree;
    std::vector<Building> buildings;

public:
    void loadBuildings();
    void constructCampusGraph();
    void listCampusLocations(int traversalType);
    void findOptimalPath(int start, int end);
    void planUtilityLayout();
    void evaluateEnergyExpression(const std::vector<std::string>& tokens);
    void addBuildingRecord(int id, const std::string& name, const std::string& details);
    void printAdjacencyTable();
};

#endif
