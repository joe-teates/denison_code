#include "path.hpp"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

int* path(int** graph, int numNodes, int startNode, int targetNode) {
    stack<int> working_list;
    bool* visited = new bool[numNodes]();
    int* parents = new int[numNodes];
    for (int i = 0; i < numNodes; i++) {
        parents[i] = -1;
    }

    working_list.push(startNode);
    visited[startNode] = true;

    while (!working_list.empty()) {
        int u = working_list.top();
        working_list.pop();

        for (int v = 0; v < numNodes; v++) {
            if (graph[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                parents[v] = u;
                working_list.push(v);
            }
        }
    }

    if (!visited[targetNode]) {
        return nullptr;
    }

    stack<int> path_stack;
    int curr = targetNode;

    while (curr != -1) {
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