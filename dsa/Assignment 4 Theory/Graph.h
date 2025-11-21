#ifndef GRAPH_H
#define GRAPH_H

#include "CityData.h"
#include <vector>
#include <list>
#include <map>
#include <string>

class CityGraph {
private:
    int V;
    std::map<int, std::list<Edge>> adjList;
    std::vector<std::vector<int>> adjMatrix;
    std::map<int, CityNode> cityNodes;
    std::map<std::string, int> nameToId;
    std::map<int, std::string> idToName;

public:
    CityGraph(int vertices);

    void addNode(const CityNode& node);

    void addRoad(int src, int dest, int weight);

    void dijkstra(int startNode, int endNode);

    void floydWarshall();

    void primMST();

    void topologicalSort(const std::vector<std::pair<std::string, std::string>>& tasks);

    int getId(const std::string& name);

    std::vector<std::string> getNodeNames();
    int getIdByIndex(int index);
    int getNodeCount();
};

#endif