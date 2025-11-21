#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "Graph.h"
#include "AVLTree.h"

class UIManager {
public:
    void setupConsole();
    void clearScreen();
    void pauseScreen();
    void displayMenu();
    void handleDijkstra(CityGraph& graph);
    void handleAVLSearch(AVLTree& tree);
    int getUserChoice();
};

#endif