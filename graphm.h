// ------------------------------------------------ graphm.h -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/23/2024
// Date of Last Modification: 8/3/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Header file for the GraphM class, providing the structure for a graph using adjacency matrix representation.
// --------------------------------------------------------------------------------------------------------------------
// This file contains the class definition of GraphM, including public methods for building the graph, finding the shortest 
// path using Dijkstra's algorithm, and displaying the graph. It also includes private methods and structures used for 
// internal operations of the graph class.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h" // Include the NodeData class
#include "constants.h" // Include the constants
#include <iostream> // Include for I/O operations
#include <climits> // Include for INT_MAX

// Class representing a graph using adjacency matrix
class GraphM {
public:
    GraphM(); // Constructor
    void buildGraph(std::ifstream&); // Build the graph from a file
    void findShortestPath(); // Find shortest paths using Dijkstra's algorithm
    void displayAll() const; // Display all shortest paths
    void display(int fromNode, int toNode) const; // Display shortest path from one node to another

private:
    // Struct representing a table entry for Dijkstra's algorithm
    struct TableType {
        bool visited; // If the node has been visited
        int dist; // Shortest distance from the source node
        int path; // Previous node in the shortest path
    };

    NodeData data[MAXNODES]; // Array of node data
    int C[MAXNODES][MAXNODES]; // Cost adjacency matrix
    int size; // Number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; // Table used for Dijkstra's algorithm

    int findMinDist(int source) const; // Helper function to find the unvisited node with the smallest distance
};

#endif
