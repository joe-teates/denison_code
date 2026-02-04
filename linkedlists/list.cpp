// Joe Teates and Emma Salamon
// This file contains the code implementation of helper functions for a doubly linked list. 

#include "list.hpp"
#include <iostream>
using namespace std;

Node* listSearch(MyList& list, int& key) {
// listSearch iterates through a linked list for a particular node by checking the key property
    // Gets node to start from
    Node* current_node = list.head;
    // Check if the key matches, if not jump to next key and repeat until at end of list
    while(current_node != nullptr && current_node->key != key){
        current_node = current_node->next;
    }

    return current_node;
}

void listPrepend(MyList& list, Node& node) {
// listPrepend adds a node at the start of a list, shifting any existing elements one index to the right/back
    // set next and prev pointers of new node
    node.next = list.head;
    node.prev = nullptr;
    // if there are existing elements, update prev property for old head
    if (list.head != nullptr) {
        list.head->prev = &node;
    }
    // set new head for the list
    list.head = &node;
    return;
}

void listInsert(Node& node_x, Node& node_y) {
// This function adds a new node (node_x) to the list directly after node_y
    // set next and prev pointers of new node
    node_x.next = node_y.next;
    node_x.prev = &node_y;
    // if there is an element after node_y, update its prev pointer
    if (node_y.next != nullptr) {
        node_y.next->prev = &node_x;
    }
    // update node_y's next pointer
    node_y.next = &node_x;
    return;
}

void listDelete(MyList& list, Node& node) {
// This function deletes a node (node) from the list
    // if an element exists before node, make it's next skip over this node
    if (node.prev != nullptr) {
        node.prev->next = node.next;
    } else {
        // else this element is the head and so it needs to be updated
        list.head = node.next;
    }
    // check if an element exists after node, if it does update its prev pointer
    if (node.next != nullptr) {
        node.next->prev = node.prev;
    }
    // deallocate - should add a cleanup function but not in header
    delete &node;
    return;
}