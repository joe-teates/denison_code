// Joe Teates and Emma Salamon
// This file contains the testing code for correct implementation of a linked list. 

#include "list.hpp"
#include <iostream>
using namespace std;

int main(){
    // create a new list
    MyList mlist = MyList();
    // add elements 0 - 19
    for(int i = 0; i<20; i++){
        Node *node_to_add = new Node(i, i);
        listPrepend(mlist, *node_to_add);
    }

    
    // Remove even elements
    for(int i = 0; i<20; i+=2){
        // search for element with key i
        Node *node_to_delete = listSearch(mlist, i);
        // delete this element
        listDelete(mlist, *node_to_delete);
    }
    
    // check if elements were removed correctly
    Node* working_node = mlist.head;
    int last_node_value = working_node->value;
    bool is_correct = true;
    while(working_node != nullptr && is_correct){
        if(last_node_value < working_node->value || (working_node->value)%2 == 0) {
            is_correct = false;
        }
        
        working_node = working_node->next;
    }



    // check listInsert function
    
    // create a new list
    MyList mlist2 = MyList();
    // add odd elements 1, 3, 4, ..., 19
    for(int i = 1; i<20; i+=2){
        Node *node_to_add = new Node(i, i);
        listPrepend(mlist2, *node_to_add);
    }

    // insert evens
    for(int i = 1; i<20; i+=2){
        Node *existing_node = listSearch(mlist2, i);
        Node *node_to_add = new Node(i-1, i-1);
        listInsert(*node_to_add, *existing_node);
    }

    // check if list has correct values [19, 18, 17, ..., 0]
    working_node = mlist2.head;
    // goes from 19->0 bc of prepend not append
    int correct_node_value = 19;
    while(working_node != nullptr && is_correct){
        if(working_node->value != correct_node_value) {
            is_correct = false;
        }
        // go to next node and decrement correct value (prepend goes backwards)
        working_node = working_node->next;
        correct_node_value -= 1;
    }


    string to_print = string(is_correct ? "Correct!":"Incorrect");
    cout<<to_print<<"\n";

    // print list if needed
    //     Node* node_to_print = mlist.head;
    //     cout<<" [ ";
    //     while(node_to_print != nullptr){
    //         cout<< node_to_print->value << " ";
    //         node_to_print = node_to_print->next;
    //     }
    //     cout<<"] \n";


    return 0;
}