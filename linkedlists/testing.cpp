#include "list.hpp"
#include <iostream>
using namespace std;


int main(){
    MyList mlist = MyList();
    for(int i = 0; i<20; i++){
        Node *node_to_add = new Node(i, i);
        listPrepend(mlist, *node_to_add);
    }

    for(int i = 0; i<20; i+=2){
        // Remove even elements
        Node *node_to_delete = listSearch(mlist, i);
        listDelete(mlist, *node_to_delete);
    }

    // Node* node_to_print = mlist.head;
    // cout<<" [ ";
    // while(node_to_print != nullptr){
    //     cout<< node_to_print->value << " ";
    //     node_to_print = node_to_print->next;
    // }
    // cout<<"] \n";


    Node* working_node = mlist.head;
    int last_node_value = working_node->value;
    bool is_correct = true;
    while(working_node != nullptr && is_correct){
        if(last_node_value < working_node->value || (working_node->value)%2 == 0) {
            is_correct = false;
        }
        
        working_node = working_node->next;
    }
    string to_print = string(is_correct ? "Correct!":"Incorrect");
    cout<<to_print<<"\n";


    return 0;
}