// Joe Teates and Emma Salamon
// This file contains the code implementation of helper functions for a single linked list. 


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
    // set next pointer of new node
    node.next = list.head;
    // update the list head
    list.head = &node;
    return;
}

void listInsert(Node& node_x, Node& node_y) {
// This function adds a new node (node_x) to the list directly after node_y
    // set next pointer of new node
    node_x.next = node_y.next;
    // update node_y's next pointer
    node_y.next = &node_x;
    return;
}

void listDelete(MyList& list, Node& node) {
// This function deletes a node (node) from the list. It does this by iterating through the list to 
// find the desired node and the previous node and updates those accordingly
    // get node to start from
    Node* current_node = list.head;
    Node* last_node = nullptr;
    bool found_node = false;
    // iterate through list until it finds the node to delete or hits end of list
    while(current_node != nullptr && !found_node) {
        if (current_node->key == node.key) {
            // found the node to delete, update next property of previous node to skip over the node
            last_node->next = current_node->next;
            // deallocate
            delete &node;
            // end loop
            found_node = true;
        }
        // iterate the last and current nodes
        last_node = current_node;
        current_node = current_node->next;
    }
    return;
}