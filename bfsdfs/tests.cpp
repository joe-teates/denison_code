
#include "path.hpp"
#include <iostream>
#include <cassert>
using namespace std;


void checkValidPaths(){
    cout<<"Testing valid edges\n";
    // Test implementation on two graphs
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

    int* valid_path = path(graph, num_vertices, 0, 4);
    int i = 0;
    assert(valid_path != nullptr);

    // Create a new graph with some edges
    num_vertices = 15;
    int** graph2 = new int*[num_vertices]();
    for (int i = 0; i < num_vertices; i++) {
        graph2[i] = new int[num_vertices]();
    }
    for (int i = 0; i < num_vertices - 1; i++) {
        graph2[i][i + 1] = 1;
    }
    // add extra edges
    graph2[0][2] = 1;
    graph2[3][7] = 1;
    graph2[5][10] = 1;
    graph2[8][14] = 1;
    graph2[0][1] = 1;
    graph2[0][2] = 1;
    
    valid_path = path(graph2, num_vertices, 0, 14);
    i = 1;
    int last_node = 0;
    assert(valid_path!=nullptr);
    while(valid_path[i]!=14){
        assert(graph2[last_node][valid_path[i]] == 1);
        last_node = valid_path[i];
        i++;
    }
    cout<<"Pass\n";
}

int main(){

    // Test that all given transitions are valid edges
    checkValidPaths();
    return 0;
}