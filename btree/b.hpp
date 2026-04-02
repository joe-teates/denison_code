
#pragma once

template<typename V>
class Node {

    public:

    int t;
    int n;
    int* keys;
    V* values;
    bool leaf;
    Node* parent;
    Node* children;

    Node(int t, int n, int* keys, V* values, bool leaf, Node* parent, Node* children);

    Node();

    ~Node();

    Node(const Node<V>& node);

    Node<V>& operator=(const Node<V>& node);
};


template<typename V>
class BTree {


    public:

    Node<V>* root;
    int t;

    BTree(int t);
    
    BTree();

    ~BTree();

    BTree(const BTree<V>& btree);

    BTree<V>& operator=(const BTree<V>& btree);
    
    void bInsert(int key, V value);

    void bDelete(int key);

    V* bSearch(int key);

};


#include "b.tpp"