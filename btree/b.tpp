// Joe Teates, Jack Rehbeck
// CS 271
// b.tpp
// implementation file for our b tree

#include "b.hpp"
#include <iostream>
using namespace std;

// Node constructor
// initializes nodes with the values from given parameters. Nodes will contain multiple elements whose
// keys and values are stored in the keys and values arrays. These arrays, when initialized will be of
// size 2t-1 and the children array of 2t.
template<typename V>
Node<V>::Node(int t, int n, int* keys, V* values, bool leaf, Node* parent, Node* children){
    this->t = t;
    this->n = n;
    this->keys = keys;
    this->values = values;
    this->leaf = leaf;
    this->parent = parent;
    this->children = children;
}

// Node defualt constructor,
// initializes an empty node with empty arrays and t=0
template<typename V>
Node<V>::Node(){
    this->t = 0;
    this->n = 0;
    this->keys = nullptr;
    this->values = nullptr;
    this->leaf = true;
    this->parent = nullptr;
    this->children = nullptr;
}

// destructor
// deallocates all data in arrays - worth noting that as children is of type Node*, delete[] is recursive
template<typename V>
Node<V>::~Node() {
    delete[] keys;
    delete[] values;
    delete[] children;
}

// Node Copy constructor
// deep copies data from passed node
template<typename V>
Node<V>::Node(const Node<V>& node) {
    t = node.t;
    n = node.n;
    leaf = node.leaf;
    parent = nullptr;

    //initialize new array and fill
    if (node.keys != nullptr) {
        keys = new int[2 * t - 1];
        for(int i=0; i < n; i++){
            keys[i] = node.keys[i];
        }
    } else {
        keys = nullptr;
    }
    if (node.values != nullptr) {
        values = new V[2 * t - 1];
        for (int i=0; i < n; i++) {
            values[i] = node.values[i];
        }
    } else {
        values = nullptr;
    }

    // this is technically a recursive call and deep copies all children's data
    if (node.children != nullptr) {
        children = new Node<V>[2 * t];
        for (int i=0; i <= node.n; i++) {
            children[i] = node.children[i];
        }
    } else {
        children = nullptr;
    }
}

// Node Assignment operator
// same as copy constructor, except it deallocates old data
template<typename V>
Node<V>& Node<V>::operator=(const Node<V>& node) {
    if (this == &node) return *this;

    delete[] keys;
    delete[] values;
    delete[] children;

    t = node.t;
    n = node.n;
    leaf = node.leaf;
    parent = node.parent;


    if (node.keys != nullptr) {
        keys = new int[2 * t - 1];
        for(int i=0; i < n; i++){
            keys[i] = node.keys[i];
        }
    } else {
        keys = nullptr;
    }

    if (node.values != nullptr) {
        values = new V[2 * t - 1];
        for (int i=0; i < n; i++) {
            values[i] = node.values[i];
        }
    } else {
        values = nullptr;
    }

    if (node.children != nullptr) {
        children = new Node<V>[2 * t];
        for (int i=0; i < 2 * t; i++) {
            children[i] = node.children[i];
        }
    } else {
        children = nullptr;
    }
    return *this;
}

// BTree constructor
// Creates a new btree by initializing its root node with 0 elements and this->t=t
template<typename V>
BTree<V>::BTree(int t) {
    this->t = t;
    root = new Node<V>(t, 0, new int[2*t-1], new V[2*t-1], true, nullptr, new Node<V>[2*t]);
}

// BTree default constructor
// creates empty btree with no root or t
template<typename V>
BTree<V>::BTree() {
    t = 0;
    root = nullptr;
}
   
// BTree deletion
// deallocates all data in btree - note that delete root will be recursive as defined earlier
template<typename V>
BTree<V>::~BTree() {
    delete root;
}

// Btree copy constructor
// deep copies all data from passed valid btree
template<typename V>
BTree<V>::BTree(const BTree<V>& btree) {
    t = btree.t;
    if (btree.root != nullptr) {
        root = new Node<V>(*btree.root);
    } else {
        root = nullptr;
    }
}

//btree assignment operator
// deallocates previous data and then deep copies data
template<typename V>
BTree<V>& BTree<V>::operator=(const BTree<V>& btree) {
    if (this == &btree) return *this;
    delete root;

    t = btree.t;
    if (btree.root != nullptr) {
        root = new Node<V>(*btree.root);
    } else {
        root = nullptr;
    }
    return *this;
}

// Helper function, splitchild for inserting elements into btree
// This function works by being given a parent node that is not full
// and a child at index i that is full (|node_c_i| = 2t-1)
// it will split this child into two nodes and take the median element 
// and place it in the parent and shift over all greater elements, doing 
// the same with the children arary too
template<typename V>
static void splitChild(Node<V>* node, int i) {
    int t = node->t;
    // y is the already existing full node
    Node<V>& y = node->children[i];
    // z is the new node to be filled
    Node<V> z(t, 0, new int[2*t - 1], new V[2*t - 1], y.leaf, node, new Node<V>[2*t]);
    z.n = t-1;
    // send over 2nd half of elements
    for(int j=0; j<t-1; j++){
        z.keys[j] = y.keys[j+t];
        z.values[j] = y.values[j+t];
    }
    // send over kids too
    if(!y.leaf){
        for(int j=0; j<t; j++){
            z.children[j]=y.children[j+t];
        }
    }
    y.n = t-1;
    // shift over chlidren in parent to make room for new child
    for(int j = node->n; j>=i+1; j--){
        node->children[j+1] = node->children[j];
    }
    node->children[i+1] = z;
    for(int j = node->n-1; j>=i; j--){
        node->keys[j+1] = node->keys[j];
        node->values[j+1] = node->values[j];
    }
    node->keys[i] = y.keys[t-1];
    node->values[i] = y.values[t - 1];
    node->n = node->n+1;
}

// Helper function to insert into nodes that are not full
// This function, if a given node is a leaf, will insert an element in
// order at that node, or if it is not a leaf will find the correct subtree
// to insert at and split it then insert if it is full or just recursively 
// insert there if not full
template<typename V>
static void bInsertNonfull(Node<V>* node, int key, V value) {
    int t = node->t;
    int i = node->n-1;
    // cout<<"current value "<<node->keys[0]<<"\n";
    // cout<<"current is leaf:"<<node->leaf<<"\n";
    // cout<<"ATTEMPTING INSERT AT ";
    // for(int j = 0; j<node->n; j++){
    //     cout<<node->keys[j]<<"  ";
    // }
    // cout<<"\n";

    if(node->leaf){
        // cout<<"IS leaf\n";
        while (i>=0 && key<node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            node->values[i+1] = node->values[i];
            i--;
        }
        node->keys[i+1] = key;
        node->values[i+1] = value;
        node->n = node->n+1;
    }else{
        // cout<<"NOT leaf\n";
        while (i>=0 && key<node->keys[i]) {
            // cout<<"Less than "<<node->keys[i]<<"\n";
            i--;
        }
        // cout<<"Going to child at index: "<<i+1<<"\n";
        if(node->children[i+1].n == 2*t-1){
            splitChild(node, i+1);
            if(key>node->keys[i+1]){
                i++;
            }
        }
        bInsertNonfull(&(node->children[i+1]), key, value);
    }
}

// Insert function
// This is the main insert function for our btree
// If the root is full, this function creates a new root, increasing the height of our tree, then
// splits the old root and inserts from there given that now our root is not full. Otherwise it 
// just calls the recursive insert at notfull node of the root.
template<typename V>
void BTree<V>::bInsert(int key, V value) {
    Node<V>* current = root;

    if(current->n == 2*t - 1){
        Node<V>* s = new Node<V>(t, 0, new int[2*t-1], new V[2*t-1], false, nullptr, new Node<V>[2*t]);

        root = s;
        s->children[0] = Node<V>(*current);
        splitChild(s, 0);
        bInsertNonfull(s, key, value);
    }else{
        bInsertNonfull(current, key, value);
    }
}

// Search function
// This is our searching function for btrees and works by going through our in order list and 
// finding the element index or child index where our element to search for is. We keep going
// down the tree until we are at a leaf AND the element is not in the leaf node then return nullptr
// otherwise we find have found our element along the way and return its value.
template<typename V>
V* BTree<V>::bSearch(int key) {
    Node<V>* current = root;
    while(current!=nullptr){
        int i = 0;
        while(i<current->n && key>current->keys[i]){
            i++;
        }
        if (i<current->n && key==current->keys[i]) {
            return &current->values[i];
        }else if(current->leaf){
            return nullptr;
        }else{
            current = &current->children[i];
        }

    }
    return nullptr;
}

// Helper function printTree
// this function was used in testing to help visualize our tree
template<typename V>
void printTree(Node<V>* node, int level) {
    cout<<"Level "<<level<<": ";
    for(int j = 0; j<node->n;j++){
        cout<<node->keys[j]<<" ";
    }
    cout<<"\n";
    if(!node->leaf){
        for(int j = 0; j<node->n+1; j++){
            printTree(&node->children[j], level+1);
        }
    }

}