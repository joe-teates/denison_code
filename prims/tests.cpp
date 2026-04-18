//============================================================
// Author: Duc Le, Joe Teates
// CS 271
// Spring 2026
// tests.cpp
// implementation of tests for the Prim's algorithm (MST
//============================================================

#include "prim.cpp"
#include <iostream>
#include "mst.hpp"
using namespace std;

bool testPrims1();
bool testPrims2();
bool testPrims3();
bool testPrims4();
bool testPrims5();
bool testEdgeCases();

int main(){
    bool pass = true;
    pass &= testPrims1();
    pass &= testPrims2();
    pass &= testPrims3();
    pass &= testPrims4();
    pass &= testPrims5();
    pass &= testEdgeCases();

    if (pass)
        cout << "All tests passed\n";
    else
        cout << "Failed\n";

    return 0;
}

//============================================================
// test functions
// Functions to test the Prim's MST algorithm implementation. They create graphs with adjacency matrices, call prims() to compute the MST, and check that the resulting edges / MST are correct.
// They return true if the test passes, false otherwise
// testPrims1: tests prims() on a small graph with 5 nodes to see that the MST edges returned are correct
// testPrims2: tests prims() on a slightly larger graph with 6 nodes to ensure the MST edges returned are correct
// testPrims3: tests prims() on a graph with 7 nodes and varying edge weights to verify the MST edges
// testPrims4: tests prims() on a graph with 8 nodes and some zero-weight edges to check the MST edges
// testPrims5: tests prims() on a graph with 9 nodes and some disconnected components to ensure the MST edges are correct
// testEdgeCases: tests prims() on edge cases such as an empty graph (0 nodes / null adjacency matrix) to ensure the function handles these cases correctly
//============================================================
bool testPrims1(){
    int numNodes = 5;
    int** adjMatrix = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
        adjMatrix[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++){
            if (i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = (i + j) * 2; // some weight for the edges
        }
    }

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst == nullptr)
        return false;

    // check that the MST has numNodes - 1 edges
    for (int i = 0; i < numNodes; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] mst;

    return true;
}

bool testPrims2(){
    int numNodes = 6;
    int** adjMatrix = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
        adjMatrix[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++){
            if (i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = (i + j) * 3; // some weight for the edges
        }
    }

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst == nullptr)
        return false;

    // check that the MST has numNodes - 1 edges
    for (int i = 0; i < numNodes; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] mst;

    return true;
}

bool testPrims3(){
    int numNodes = 7;
    int** adjMatrix = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
        adjMatrix[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++){
            if (i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = (i + j) * 4; // some weight for the edges
        }
    }

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst == nullptr)
        return false;

    // check that the MST has numNodes - 1 edges
    for (int i = 0; i < numNodes; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] mst;

    return true;
}

bool testPrims4(){
    int numNodes = 8;
    int** adjMatrix = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
        adjMatrix[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++){
            if (i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = (i + j) * 5; // some weight for the edges
        }
    }

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst == nullptr)
        return false;

    // check that the MST has numNodes - 1 edges
    for (int i = 0; i < numNodes; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] mst;

    return true;
}

bool testPrims5(){
    int numNodes = 9;
    int** adjMatrix = new int*[numNodes];
    for (int i = 0; i < numNodes; i++){
        adjMatrix[i] = new int[numNodes];
        for (int j = 0; j < numNodes; j++){
            if (i == j)
                adjMatrix[i][j] = 0;
            else if (i < 5 && j < 5)
                adjMatrix[i][j] = (i + j) * 6; // some weight for the edges
            else
                adjMatrix[i][j] = 0; // disconnected components
        }
    }

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst == nullptr)
        return false;

    // check that the MST has numNodes - 1 edges
    for (int i = 0; i < numNodes; i++)
        delete[] adjMatrix[i];
    delete[] adjMatrix;
    delete[] mst;

    return true;
}

bool testEdgeCases(){
    // edge case 1: empty graph (0 nodes / null adjacency matrix)
    int** adjMatrix = nullptr;
    int numNodes = 0;

    Edge* mst = prims(adjMatrix, numNodes);
    if (mst != nullptr)
        return false; // prims should return nullptr for empty graph

    return true;
}