// Joe Teates, Theo Wolf, Anthony Le
// dfs.cpp
// This file contains the implementation of depth first search to return a valid
// path from startNode to targetNode

#include "path.hpp"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

// path is the only function in this file
// path accepts the directed graph as a 2d array of 0s and 1s where 1s represent valid 
// edges and 0s being non-edges. The function starts by adding startNode to the working 
// stack and pops and pushes neighbors to the working stack as a lifo list representaion
// It is assumed that if this function does not return a nullptr, it returns an array 
// of length numNodes but only the first n nodes are valid where list[n-1]=targetNode 
int* path(int** graph, int numNodes, int startNode, int targetNode) {
    // using a stack now
    stack<int> working_list;
    bool* visited = new bool[numNodes]();
    int* parents = new int[numNodes];
    for (int i = 0; i < numNodes; i++) {
        parents[i] = -1;
    }

    working_list.push(startNode);
    visited[startNode] = true;
    while (!working_list.empty()) {
        // get last item put on stack
        int u = working_list.top();
        working_list.pop();

        for (int v = 0; v < numNodes; v++) {
            // edge u -> v
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
        // walk back through the graph to startNode
        path_stack.push(curr);
        curr = parents[curr];
    }

    int* found_path = new int[numNodes];
    int i = 0;
    while (!path_stack.empty()) {
        found_path[i] = path_stack.top();
        path_stack.pop();
        i++;
    }

    return found_path;
}