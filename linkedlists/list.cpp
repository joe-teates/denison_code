#include "list.hpp"
#include <iostream>
using namespace std;


// class Node{

//     public:

//     int key;
//     int value;
//     Node *prev;
//     Node *next;

//     Node(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}

// };

// class MyList{

//     public:

//     Node *head;

//     MyList() : head(nullptr) {}

// };


Node* listSearch(MyList& list, int& key) {
    Node* current_node = list.head;
    while(current_node != nullptr && current_node->key != key){
        current_node = current_node->next;
    }

    return current_node;
}

void listPrepend(MyList& list, Node& node) {
    node.next = list.head;
    node.prev = nullptr;
    if (list.head != nullptr) {
        list.head->prev = &node;
    }
    list.head = &node;
    return;
}

void listInsert(Node& node_x, Node& node_y) {
    node_x.next = node_y.next;
    node_x.prev = &node_y;
    if (node_y.next != nullptr) {
        node_y.next->prev = &node_x;
    }
    node_y.next = &node_x;
    return;
}

void listDelete(MyList& list, Node& node) {
    if (node.prev != nullptr) {
        node.prev->next = node.next;
    } else {
        list.head = node.next;
    }
    if (node.next != nullptr) {
        node.next->prev = node.prev;
    }
    delete &node;
    return;
}