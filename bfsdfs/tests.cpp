
#include "path.hpp"
#include <iostream>
#include <cassert>
using namespace std;

int main(){

    int num_vertices = 5;
    int** graph = new int*[num_vertices]();
    for (int i = 0; i < num_vertices; i++) {
        graph[i] = new int[num_vertices]();
    }
    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][2] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;

    int* shortest = path(graph, num_vertices, 0, 4);
    int i = 0;
    assert(shortest != nullptr);
    while(shortest[i]!=4){
        cout<<shortest[i]<<", ";
        i++;
    }
    cout<<shortest[i]<<"\n";

    // for (int r = 0; r < num_vertices; r++) {
    //     for (int c = 0; c < num_vertices; c++) {
    //         cout<<graph[r][c]<<" ";
    //     }
    //     cout<<"\n";
    // }

    


    return 0;
}