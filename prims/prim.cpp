// Duc Le, Joe Teates
// prim.cpp
// This file contains our implementation for prim's algorithm to find a minimum spanning tree
// this algorithm works by starting with a node in a list then finding the lowest path to an
// adjacent node and adding that node to the list. Nodes are only added to the list if they 
// are not already in the list and can be connected by the lowest weight valid path.
#include "mst.hpp"
#include <queue>
#include <iostream>
#include <climits>
using namespace std;

// This Node struct is simply used to keep the priority queue in order. The Nodes labeled as
// numbers 0 to numNodes-1 must be associated with the discovered path of lowest weight.
struct Node{
    int num;
    int key;
    Node(int n, int k) : num(n), key(k) {}
};

// This function, prims, contains all the logic of our MST finding algorithm. Prims accepts
// a valid adjacency matrix of a directed graph where the indices are [u][v] where u and v 
// are ints and the edge is a directed edge from node u to v. This function returns a list of
// edges which is of length numNodes-1 (the length of a MST) where each element is an edge 
// object defined in mst.hpp.
Edge* prims(int** adjMatrix, int numNodes){
    // we are using the c++ std priority queue with a lambda function to keep elements ordered
    auto cmp = [](Node left, Node right) { return (left.key) > (right.key); };
    priority_queue<Node, vector<Node>, decltype(cmp)> pqueue(cmp);

    // confirm we have valid inputs
    if(numNodes<1 || adjMatrix==nullptr){
        return nullptr;
    }
    // initialize the return array
    Edge* ret = new Edge[numNodes-1];
    int edge_i = 0;
    
    // we use arrays to track if an element has been added to the MST and find their keys and 
    // parents in O(1).
    bool* inQ = new bool[numNodes]();
    int* keys = new int[numNodes];
    int* parents = new int[numNodes];
    for(int i = 0; i<numNodes; i++){
        parents[i] = -1;
        if(i==0){
            keys[i]=INT_MIN;
        }else{
            keys[i]=INT_MAX;
        }
    }

    pqueue.push(Node(0, INT_MIN));
    for(int i = 1; i<numNodes; i++){
        pqueue.push(Node(i, INT_MAX));
    }

    // while there are still edges left to check
    while(!pqueue.empty()) {
        // pop node with lowest connecting edge (will be in the MST by invariant)
        Node u = pqueue.top();
        pqueue.pop();
        inQ[u.num] = true;

        // Used to replace queue.decreaseKey (c++ std queue does not have a reheapify or decreaseKey)
        if(u.key > keys[u.num]){
            //not smallest key (added a copy)
            continue;
        }
        //for all adjacent v check for smaller v.key
        for(int v = 0; v<numNodes; v++){
            int weight = adjMatrix[u.num][v];
            if(weight < INT_MAX){ // edges of weight INT_MAX do not exist
                // Adjacent Node v
                if(!inQ[v] && weight < keys[v]){
                    // not in queue AND weight is less than previous edge connecting v to graph
                    keys[v] = weight;
                    parents[v] = u.num;
                    // decrease key
                    pqueue.push(Node(v, keys[v]));
                    // pushes v onto queue BUT does not remove old v - this is why if statement on line 67 is needed
                }

            }
        }
        // add u.pi and u to the mst to return
        if(parents[u.num]>=0){
            ret[edge_i].node1 = parents[u.num];
            ret[edge_i].node2 = u.num;
            edge_i++;
        }
    
    }
    // deallocate arrays used
    delete[] inQ;
    delete[] keys;
    delete[] parents;

    // only return mst if it is valid (should be of length n-1)
    if(edge_i < numNodes-1){
        return nullptr;
    }
    return ret;
}