#include "CampusGraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>

struct Edge {
    int src, dest;
    double weight;
};

struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

void CampusGraph::constructFromData(const std::vector<Building> &buildings, const std::string &edgesFile) {
    this->buildings = buildings;
    adjList.resize(buildings.size() + 1);

    std::ifstream file(edgesFile);
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        int id1, id2;
        double distance;

        std::getline(ss, item, ',');
        id1 = std::stoi(item);
        std::getline(ss, item, ',');
        id2 = std::stoi(item);
        std::getline(ss, item, ',');
        distance = std::stod(item);

        adjList[id1].push_back({id2, distance});
        adjList[id2].push_back({id1, distance});
    }
}

void CampusGraph::printAdjacencyTable() const {
    std::cout << "+-" << std::string(15, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;
    std::cout << "| " << std::left << std::setw(15) << "Building ID" << "| " << std::left << std::setw(30) << "Connections" << " |" << std::endl;
    std::cout << "+-" << std::string(15, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;

    for (size_t i = 1; i < adjList.size(); ++i) {
        std::cout << "| " << std::left << std::setw(15) << i << "| ";
        std::stringstream connections;
        for (const auto& edge : adjList[i]) {
            connections << "(" << edge.first << ", " << edge.second << ") ";
        }
        std::cout << std::left << std::setw(29) << connections.str() << " |" << std::endl;
    }

    std::cout << "+-" << std::string(15, '-') << "-+-" << std::string(30, '-') << "-+" << std::endl;
}

std::vector<int> CampusGraph::dijkstra(int sourceID, int targetID, double &totalDistance) const {
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    std::vector<double> dist(adjList.size(), std::numeric_limits<double>::max());
    std::vector<int> prev(adjList.size(), -1);

    dist[sourceID] = 0;
    pq.push({0, sourceID});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == targetID) break;

        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            double weight = edge.second;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> path;
    if (dist[targetID] != std::numeric_limits<double>::max()) {
        totalDistance = dist[targetID];
        for (int at = targetID; at != -1; at = prev[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

std::vector<std::tuple<int, int, double>> CampusGraph::kruskalMST() const {
    std::vector<Edge> edges;
    for (size_t u = 1; u < adjList.size(); ++u) {
        for (const auto& edge : adjList[u]) {
            int v = edge.first;
            double weight = edge.second;
            if (u < v) {
                edges.push_back({(int)u, v, weight});
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    DSU dsu(buildings.size());
    std::vector<std::tuple<int, int, double>> mst;
    for (const auto& edge : edges) {
        if (dsu.find(edge.src) != dsu.find(edge.dest)) {
            dsu.unite(edge.src, edge.dest);
            mst.emplace_back(edge.src, edge.dest, edge.weight);
        }
    }
    return mst;
}
