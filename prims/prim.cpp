#include "mst.hpp"
#include <queue>
#include <stack>
#include <iostream>
#include <climits>
using namespace std;

struct Node{
    int num;
    int key;
    int parent;
    Node(int n, int k, int p) : num(n), key(k), parent(p) {}
};

Edge* prims(int** adjMatrix, int numNodes){
    auto cmp = [](Node left, Node right) { return (left.key) > (right.key); };
    priority_queue<Node, vector<Node>, decltype(cmp)> pqueue(cmp);

    Edge* ret = new Edge[numNodes-1];
    int edge_i = 0;
    
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

    pqueue.push(Node(0, INT_MIN, -1));
    for(int i = 1; i<numNodes; i++){
        pqueue.push(Node(i, INT_MAX, -1));
    }

    while(!pqueue.empty()) {
        Node u = pqueue.top();
        pqueue.pop();
        inQ[u.num] = true;

        if(u.key > keys[u.num]){
            //not smallest key (added a copy)
            continue;
        }
        //for all adjacent v check for smaller v.key
        for(int v = 0; v<numNodes; v++){
            int weight = adjMatrix[u.num][v];
            if(weight < INT_MAX){
                // Adjacent Node v
                if(!inQ[v] && weight < keys[v]){
                    // not in queue AND weight is less than previous
                    keys[v] = weight;
                    parents[v] = u.num;
                    // decrease key
                    pqueue.push(Node(v, keys[v], u.num));
                }

            }
        }
        if(parents[u.num]>=0){
            ret[edge_i].node1 = parents[u.num];
            ret[edge_i].node2 = u.num;
            edge_i++;
        }
    }
    return ret;
}