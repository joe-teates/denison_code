

#include "path.hpp"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

// int* path(int** graph, int numNodes, int startNode, int targetNode) {
//     queue<int> working_list;
//     bool* visited = new bool[numNodes]();
//     visited[startNode] = true;
//     int* parents = new int[numNodes];
//     for (int i = 0; i < numNodes; i++) {
//         parents[i] = -1;
//     }
//     working_list.push(startNode);

//     while(working_list.size()>0) {
//         int check_adj_of = working_list.front();
//         working_list.pop();

//         for(int i = 0; i<numNodes; i++){
//             if(graph[check_adj_of][i]==1 && !visited[i]) {
//                 visited[i] = true;
//                 parents[i] = check_adj_of;
//                 working_list.push(i);
//             }
//         }
//     }

//     // find path
//     int curr = targetNode;
//     stack<int> path;
//     path.push(curr);
//     while(curr != startNode){
//         curr = parents[curr];
//     }
//     path.push(curr);
//     int* shortest_path = new int[numNodes];
//     int i = 0;
//     while(path.size()){
//         int top = path.top();
//         shortest_path[i] = top;
//         cout<<top<<" ";
//         i++;
//         path.pop();
//     }
//     cout<<"\n ";

//     return shortest_path;
// }



int* path(int** graph, int numNodes, int startNode, int targetNode) {
    queue<int> working_list;
    bool* visited = new bool[numNodes]();
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

    int* shortest_path = new int[numNodes];
    int i = 0;

    while (!path_stack.empty()) {
        shortest_path[i++] = path_stack.top();
        path_stack.pop();
    }

    return shortest_path;
}