// ------------------------------------------------ graphl.cpp -------------------------------------------------------
// Programmer Name: Forrest Zhang
// Course Section Number: CSS 343
// Creation Date: 7/30/2024
// Date of Last Modification: 8/3/2024
// --------------------------------------------------------------------------------------------------------------------
// Purpose: Implementation file for the GraphL class, providing functionality for a graph using adjacency list representation.
// --------------------------------------------------------------------------------------------------------------------
// This file contains the implementation of the GraphL class, including methods to build the graph from a file, perform 
// depth-first search, and display the graph. It also includes private helper methods for internal operations of the graph class.
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h"

// Constructor
GraphL::GraphL() {
    size = 0; // Initialize size to 0
    // Initialize all graph nodes
    for (int i = 1; i < MAXNODES; ++i) {
        graph[i].edgeHead = nullptr; // Initialize edge head to nullptr
        graph[i].data = nullptr; // Initialize data to nullptr
        graph[i].visited = false; // Initialize visited to false
    }
}

// Destructor
GraphL::~GraphL() {
    makeEmpty(); // Empty the graph
}

// Make the graph empty
void GraphL::makeEmpty() {
    // Loop through all nodes to delete edges and data
    for (int i = 1; i <= size; ++i) {
        EdgeNode* current = graph[i].edgeHead;
        while (current != nullptr) {
            EdgeNode* toDelete = current; // Pointer to delete
            current = current->nextEdge; // Move to the next edge
            delete toDelete; // Delete the edge
        }
        graph[i].edgeHead = nullptr; // Reset edge head
        delete graph[i].data; // Delete node data
        graph[i].data = nullptr; // Reset data
    }
}

// Build graph from file
void GraphL::buildGraph(std::ifstream& infile) {
    makeEmpty(); // Empty the graph

    infile >> size; // Read the number of nodes
    std::string name;
    std::getline(infile, name); // Move to next line

    // Read node data and store in the graph nodes
    for (int i = 1; i <= size; ++i) {
        std::getline(infile, name); // Read node data
        graph[i].data = new NodeData(name); // Store node data
    }

    int from, to;
    // Read edges and their adjacent nodes from the file
    while (infile >> from >> to) {
        if (from == 0 && to == 0) break; // Stop if end of input
        EdgeNode* newEdge = new EdgeNode{ to, graph[from].edgeHead }; // Create new edge
        graph[from].edgeHead = newEdge; // Add edge to the list
    }
}

// Display the graph
void GraphL::displayGraph() const {
    std::cout << "Graph:\n";
    // Loop through all nodes and display their edges
    for (int i = 1; i <= size; ++i) {
        std::cout << "Node " << i << "       " << *graph[i].data << "\n";
        EdgeNode* current = graph[i].edgeHead;
        // Loop through all edges of the current node
        while (current != nullptr) {
            std::cout << "  edge " << i << " " << current->adjGraphNode << "\n";
            current = current->nextEdge; // Move to the next edge
        }
    }
}

// Depth-first search
void GraphL::depthFirstSearch() {
    std::cout << "Depth-first ordering: ";
    // Reset visited flag for all nodes
    for (int i = 1; i <= size; ++i) {
        graph[i].visited = false; // Reset visited
    }
    // Perform DFS for each unvisited node
    for (int i = 1; i <= size; ++i) {
        if (!graph[i].visited) {
            dfsHelper(i); // Perform DFS
        }
    }
    std::cout << "\n";
}

// Helper for depth-first search
void GraphL::dfsHelper(int v) {
    graph[v].visited = true; // Mark node as visited
    std::cout << v << " ";
    EdgeNode* current = graph[v].edgeHead;
    // Loop through all edges of the current node
    while (current != nullptr) {
        if (!graph[current->adjGraphNode].visited) {
            dfsHelper(current->adjGraphNode); // Visit adjacent node
        }
        current = current->nextEdge; // Move to the next edge
    }
}
