// ------------------------------------------------ graphm.cpp -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/23/2024
// Date of Last Modification: 8/3/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implementation file for the GraphM class, providing functionality for a graph using adjacency matrix representation.
// --------------------------------------------------------------------------------------------------------------------
// This file contains the implementation of the GraphM class, including methods to build the graph from a file, find the shortest 
// paths using Dijkstra's algorithm, and display the graph or specific paths. It also includes private helper methods for 
// internal operations of the graph class.
// --------------------------------------------------------------------------------------------------------------------

#include "graphm.h"
#include <stack>

// Constructor
GraphM::GraphM() {
    size = 0; // Initialize size to 0
    // Initialize adjacency matrix and Dijkstra's table
    for (int i = 1; i < MAXNODES; ++i) {
        for (int j = 1; j < MAXNODES; ++j) {
            C[i][j] = INT_MAX; // Initialize all costs to infinity
            T[i][j].dist = INT_MAX; // Initialize all distances to infinity
            T[i][j].path = 0; // Initialize all paths to 0
            T[i][j].visited = false; // Initialize all nodes as unvisited
        }
    }
}

// Build the graph from a file
void GraphM::buildGraph(std::ifstream& infile) {
    infile >> size; // Read the number of nodes
    std::string name;
    std::getline(infile, name); // Move to the next line

    // Read node data and store in the data array
    for (int i = 1; i <= size; ++i) {
        std::getline(infile, name); // Read node data
        data[i] = NodeData(name); // Store node data
    }

    int from, to, weight;
    // Read edges and their weights from the file
    while (infile >> from >> to >> weight) {
        if (from == 0 && to == 0 && weight == 0) break; // Stop if end of input
        C[from][to] = weight; // Set the cost of the edge
    }
}

// Find the shortest path using Dijkstra's algorithm
void GraphM::findShortestPath() {
    // Loop through each node as the source node
    for (int source = 1; source <= size; ++source) {
        T[source][source].dist = 0; // Distance to itself is 0

        // Find the shortest path from the source to all other nodes
        for (int i = 1; i <= size; ++i) {
            int v = findMinDist(source); // Find the closest unvisited node
            if (v == 0) break; // No more vertices to process
            T[source][v].visited = true; // Mark the node as visited

            // Update the distances to the adjacent nodes
            for (int w = 1; w <= size; ++w) {
                if (!T[source][w].visited && C[v][w] != INT_MAX) {
                    if (T[source][w].dist > T[source][v].dist + C[v][w]) {
                        T[source][w].dist = T[source][v].dist + C[v][w]; // Update distance
                        T[source][w].path = v; // Update path
                    }
                }
            }
        }
    }
}

// Find the unvisited node with the smallest distance
int GraphM::findMinDist(int source) const {
    int minDist = INT_MAX; // Initialize minimum distance to infinity
    int minNode = 0; // Initialize minimum node to 0
    // Loop through all nodes to find the minimum distance
    for (int i = 1; i <= size; ++i) {
        if (!T[source][i].visited && T[source][i].dist < minDist) {
            minDist = T[source][i].dist; // Update minimum distance
            minNode = i; // Update minimum node
        }
    }
    return minNode; // Return the node with the smallest distance
}

// Display all shortest paths
void GraphM::displayAll() const {
    std::cout << "Description         From node   To node   Dijkstra's     Path\n";
    // Loop through all nodes and display the shortest paths
    for (int i = 1; i <= size; ++i) {
        std::cout << data[i] << "\n"; // Display node data
        for (int j = 1; j <= size; ++j) {
            if (i != j) {
                std::cout << "                      " << i << "         " << j << "        ";
                if (T[i][j].dist != INT_MAX) {
                    std::cout << T[i][j].dist << "            ";
                    std::stack<int> pathStack;
                    int pathNode = j;
                    // Store the path in a stack to reverse the order
                    while (pathNode != i) {
                        pathStack.push(pathNode);
                        pathNode = T[i][pathNode].path;
                    }
                    pathStack.push(i);
                    // Display the path from the stack
                    while (!pathStack.empty()) {
                        std::cout << pathStack.top() << " ";
                        pathStack.pop();
                    }
                }
                else {
                    std::cout << "----";
                }
                std::cout << "\n";
            }
        }
    }
}

// Display shortest path from fromNode to toNode
void GraphM::display(int fromNode, int toNode) const {
    std::cout << "   " << fromNode << "       " << toNode << "      ";
    if (T[fromNode][toNode].dist != INT_MAX) {
        std::cout << T[fromNode][toNode].dist << "          ";
        std::stack<int> pathStack;
        int pathNode = toNode;
        // Store the path in a stack to reverse the order
        while (pathNode != fromNode) {
            pathStack.push(pathNode);
            pathNode = T[fromNode][pathNode].path;
        }
        pathStack.push(fromNode);
        // Display the path from the stack
        while (!pathStack.empty()) {
            std::cout << pathStack.top() << " ";
            pathStack.pop();
        }
    }
    else {
        std::cout << "----";
    }
    std::cout << "\n";
}
