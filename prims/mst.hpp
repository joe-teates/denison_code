
#pragma once


class Edge {

    public:
    int node1;
    int node2;

};

Edge* prims(int** adjMatrix, int numNodes);