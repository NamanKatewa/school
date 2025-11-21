#include "DataManager.h"
#include "UIManager.h"
#include "Graph.h"
#include "AVLTree.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
    UIManager ui;
    ui.setupConsole();

    const int NUM_INTERSECTIONS = 15;
    CityGraph graph(NUM_INTERSECTIONS);
    AVLTree tree;
    std::vector<std::pair<std::string, std::string>> constructionTasks;

    DataManager dataManager;
    dataManager.loadCityData("city_network.csv", graph, tree);
    dataManager.loadTaskData("construction_tasks.csv", constructionTasks);
    ui.pauseScreen();

    int choice;
    do {
        ui.clearScreen();
        ui.displayMenu();
        choice = ui.getUserChoice();

        switch (choice) {
            case 1:
                ui.handleDijkstra(graph);
                break;
            case 2:
                graph.floydWarshall();
                break;
            case 3:
                graph.primMST();
                break;
            case 4:
                graph.topologicalSort(constructionTasks);
                break;
            case 5:
                ui.handleAVLSearch(tree);
                break;

            case 6:
                std::cout << "\n\x1B[32mThank you for using the Smart City Navigation System!\x1B[0m\n";
                break;
            default:
                std::cout << "\n\x1B[31mInvalid choice. Please try again.\x1B[0m\n";
        }

        if (choice != 6) {
            ui.pauseScreen();
        }

    } while (choice != 6);

    return 0;
}
