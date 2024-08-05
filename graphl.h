// ------------------------------------------------ graphl.h -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/30/2024
// Date of Last Modification: 8/3/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Header file for the GraphL class, providing the structure for a graph using adjacency list representation.
// --------------------------------------------------------------------------------------------------------------------
// This file contains the class definition of GraphL, including public methods for building the graph, performing depth-first 
// search, and displaying the graph. It also includes private methods and structures used for internal operations of the graph class.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h" // Include the NodeData class
#include "constants.h" // Include the constants
#include <list> // Include for list operations
#include <vector> // Include for vector operations

// Class representing a graph using adjacency list
class GraphL {
public:
    GraphL(); // Constructor
    ~GraphL(); // Destructor
    void buildGraph(std::ifstream&); // Build the graph from a file
    void displayGraph() const; // Display the graph
    void depthFirstSearch(); // Perform depth-first search

private:
    // Struct representing an edge node in the adjacency list
    struct EdgeNode {
        int adjGraphNode; // Index of the adjacent graph node
        EdgeNode* nextEdge; // Pointer to the next edge node
    };

    // Struct representing a graph node
    struct GraphNode {
        EdgeNode* edgeHead; // Pointer to the head of the edge list
        NodeData* data; // Data associated with the node
        bool visited; // If the node has been visited
    };

    GraphNode graph[MAXNODES]; // Array of graph nodes
    int size; // Number of nodes in the graph

    void makeEmpty(); // Helper function to empty the graph
    void dfsHelper(int v); // Helper function for depth-first search
};

#endif
