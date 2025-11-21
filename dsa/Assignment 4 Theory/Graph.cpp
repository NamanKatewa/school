#include "Graph.h"
#include <queue>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <limits>

const int INF = std::numeric_limits<int>::max();

CityGraph::CityGraph(int vertices) : V(vertices) {
    int max_id = 100 + V;
    adjMatrix.resize(max_id, std::vector<int>(max_id, INF));
    for (int i = 0; i < max_id; ++i) {
        adjMatrix[i][i] = 0;
    }
}

void CityGraph::addNode(const CityNode& node) {
    if (cityNodes.find(node.id) == cityNodes.end()) {
        cityNodes[node.id] = node;
        nameToId[node.name] = node.id;
        idToName[node.id] = node.name;
    }
}

void CityGraph::addRoad(int src, int dest, int weight) {
    adjList[src].push_back({dest, weight});
    adjList[dest].push_back({src, weight});

    if (src < adjMatrix.size() && dest < adjMatrix.size()) {
        adjMatrix[src][dest] = weight;
        adjMatrix[dest][src] = weight;
    }
}

int CityGraph::getId(const std::string& name) {
    if (nameToId.count(name)) {
        return nameToId[name];
    }
    return -1;
}

std::vector<std::string> CityGraph::getNodeNames() {
    std::vector<std::string> names;
    for(auto const& [id, name] : idToName) {
        names.push_back(name);
    }
    std::sort(names.begin(), names.end());
    return names;
}


void CityGraph::dijkstra(int startNode, int endNode) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::map<int, int> dist;
    std::map<int, int> parent;

    for (auto const& [id, node] : cityNodes) {
        dist[id] = INF;
    }

    dist[startNode] = 0;
    pq.push({0, startNode});

    while (!pq.empty()) {
        int u_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u_dist > dist[u]) {
            continue;
        }

        if (u == endNode) break;

        for (auto& edge : adjList[u]) {
            int v = edge.destID;
            int weight = edge.weight;
            if (dist.count(v) && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    if (!dist.count(endNode) || dist[endNode] == INF) {
        std::cout << "\n\x1B[31mError: \x1B[0mNo path found between " << idToName[startNode] << " and " << idToName[endNode] << ".\n";
        return;
    }

    std::cout << "\n\x1B[32mDijkstra's Shortest Path:\x1B[0m\n";
    std::cout << "--------------------------\n";
    std::cout << "Distance: \x1B[33m" << dist[endNode] << " km\x1B[0m\n";
    
    std::vector<int> path;
    int current = endNode;
    while (current != 0 && current != startNode) {
        path.push_back(current);
        if (parent.find(current) == parent.end()) {
             std::cout << "\n\x1B[31mError: \x1B[0mPath reconstruction failed. Is the graph connected?\n";
             return;
        }
        current = parent[current];
    }
    path.push_back(startNode);
    std::reverse(path.begin(), path.end());
    
    std::cout << "Route:    \x1B[36m";
    for (size_t i = 0; i < path.size(); ++i) {
        std::cout << idToName[path[i]] << (i == path.size() - 1 ? "" : " -> ");
    }
    std::cout << "\x1B[0m\n";
}

void CityGraph::floydWarshall() {

    int num_nodes_in_matrix = 15;
    std::vector<std::vector<int>> dist(num_nodes_in_matrix, std::vector<int>(num_nodes_in_matrix, INF));

    for(int i=0; i < num_nodes_in_matrix; ++i){
        for(int j=0; j < num_nodes_in_matrix; ++j){
            if (i == j) dist[i][j] = 0;
            else if (adjMatrix[i+100][j+100] != 0 && adjMatrix[i+100][j+100] != INF) {
                 dist[i][j] = adjMatrix[i+100][j+100];
            }
        }
    }


    for (int k = 0; k < num_nodes_in_matrix; k++) {
        for (int i = 0; i < num_nodes_in_matrix; i++) {
            for (int j = 0; j < num_nodes_in_matrix; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    std::cout << "\n\x1B[32mAll-Pairs Shortest Paths (Floyd-Warshall):\x1B[0m\n";
    std::cout << "---------------------------------------------\
";
    std::cout << std::left << std::setw(16) << "Intersection";
    for (int i = 0; i < num_nodes_in_matrix; ++i) {
        std::cout << std::setw(8) << idToName[i + 100].substr(0, 7);
    }
    std::cout << "\n" << std::string(16 + 8 * num_nodes_in_matrix, '-') << "\n";

    for (int i = 0; i < num_nodes_in_matrix; i++) {
        std::cout << std::left << std::setw(16) << idToName[i + 100];
        for (int j = 0; j < num_nodes_in_matrix; j++) {
            if (dist[i][j] == INF) {
                std::cout << std::setw(8) << "INF";
            } else {
                std::cout << std::setw(8) << dist[i][j];
            }
        }
        std::cout << "\n";
    }
}

void CityGraph::primMST() {
    if (adjList.empty()) {
        std::cout << "\n\x1B[31mError: \x1B[0mCannot compute MST. The graph is empty.\n";
        return;
    }

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::map<int, int> key;
    std::map<int, int> parent;
    std::map<int, bool> inMST;

    for (auto const& [id, node] : cityNodes) {
        key[id] = INF;
        parent[id] = -1;
        inMST[id] = false;
    }

    int startNode = adjList.begin()->first;
    pq.push({0, startNode});
    key[startNode] = 0;

    int totalCost = 0;
    std::vector<std::tuple<std::string, std::string, int>> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if(inMST[u]) continue;
        
        inMST[u] = true;
        
        if(parent[u] != -1) {
             totalCost += key[u];
             mstEdges.emplace_back(idToName[parent[u]], idToName[u], key[u]);
        }

        for (auto& edge : adjList[u]) {
            int v = edge.destID;
            int weight = edge.weight;
            if (cityNodes.count(v) && !inMST[v] && key[v] > weight) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    std::cout << "\n\x1B[32mMinimum Spanning Tree (Prim's Algorithm):\x1B[0m\n";
    std::cout << "------------------------------------------\n";
    std::cout << "Edges to connect all zones with minimum cost:\n";
    for (const auto& edge : mstEdges) {
        std::cout << "- \x1B[36m" << std::get<0>(edge) << "\x1B[0m to \x1B[36m" << std::get<1>(edge) << "\x1B[0m, Cost: \x1B[33m" << std::get<2>(edge) << " km\x1B[0m\n";
    }
    std::cout << "------------------------------------------\n";
    std::cout << "Total Minimum Cost: \x1B[33m" << totalCost << " km\x1B[0m\n";
}


void CityGraph::topologicalSort(const std::vector<std::pair<std::string, std::string>>& tasks) {
    std::map<std::string, std::list<std::string>> taskAdj;
    std::map<std::string, int> inDegree;

    for (const auto& task_pair : tasks) {
        taskAdj[task_pair.first].push_back(task_pair.second);
        inDegree[task_pair.second]++;
        if (inDegree.find(task_pair.first) == inDegree.end()) {
            inDegree[task_pair.first] = 0;
        }
    }

    std::queue<std::string> q;
    for (auto const& [task, degree] : inDegree) {
        if (degree == 0) {
            q.push(task);
        }
    }

    std::vector<std::string> result;
    while (!q.empty()) {
        std::string u = q.front();
        q.pop();
        result.push_back(u);

        if (taskAdj.count(u)) {
            for (const auto& v : taskAdj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }

    std::cout << "\n\x1B[32mConstruction Task Order (Topological Sort):\x1B[0m\n";
    std::cout << "---------------------------------------------\
";

    if (result.size() != inDegree.size()) {
        std::cout << "\x1B[31mError: A cycle was detected in the construction tasks. Cannot determine a valid order.\x1B[0m\n";
    } else {
        std::cout << "A valid order to perform the tasks is:\n";
        for (size_t i = 0; i < result.size(); ++i) {
            std::cout << "\x1B[36m" << result[i] << "\x1B[0m" << (i == result.size() - 1 ? "" : " -> ");
        }
        std::cout << "\n";
    }
}

int CityGraph::getIdByIndex(int index) {
    if (index < 0 || index >= idToName.size()) {
        return -1;
    }
    auto it = idToName.begin();
    std::advance(it, index);
    return it->first;
}

int CityGraph::getNodeCount() {
    return idToName.size();
}
