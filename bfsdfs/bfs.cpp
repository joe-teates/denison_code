// Joe Teates, Theo Wolf, Anthony Le
// bfs.cpp
// This file contains the implementation of breadth first search to return the shortest
// path from startNode to targetNode

#include "path.hpp"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

// path is the only function in this file
// path accepts the directed graph as a 2d array of 0s and 1s where 1s represent valid 
// edges and 0s being non-edges. The function starts by adding startNode to the working 
// queue and pops and pushes neighbors to the working queue as a fifo list representaion
// It is assumed that if this function does not return a nullpointer, it returns an array 
// of length numNodes but only the first n nodes are valid where list[n-1]=targetNode 
int* path(int** graph, int numNodes, int startNode, int targetNode) {
    queue<int> working_list;
    bool* visited = new bool[numNodes]();
    // parents to track the path taken
    int* parents = new int[numNodes];
    for (int i = 0; i < numNodes; i++) {
        parents[i] = -1;
    }

    working_list.push(startNode);
    visited[startNode] = true;

    while (!working_list.empty()) {
        int u = working_list.front();
        working_list.pop();

        for (int v = 0; v < numNodes; v++) {
            // edge is (u,v) 
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                parents[v] = u;
                working_list.push(v);
            }
        }
    }

    if (!visited[targetNode]) {
        // checked all nodes and still not visited
        return nullptr;
    }
    // just use a stack to go backwards from target using parents
    stack<int> path_stack;
    int curr = targetNode;

    while (curr != -1) {
        path_stack.push(curr);
        curr = parents[curr];
    }

    int* shortest_path = new int[numNodes];
    int i = 0;
    while (!path_stack.empty()) {
        shortest_path[i] = path_stack.top();
        path_stack.pop();
        i++;
    }
    // if this function returns an array it may not be full of valid values
    return shortest_path;
}