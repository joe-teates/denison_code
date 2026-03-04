// Joe Teates, Theo Wolf
// Testing file for checking accuracy of all methods of hashtable class

#include "hashtable.hpp"
#include <iostream>
using namespace std;


int main () {

    Hashtable<int> ht = Hashtable<int>(10);
    cout<<"made a table of length"<<ht.size<<"\n";
    cout<<"Printing Table\n";
    
    
    ht.hashInsert(1,1);
    ht.hashInsert(2,2);
    ht.hashInsert(3,3);
    ht.hashInsert(4,4);
    ht.hashInsert(12,12);
    ht.printTable();

    ht.hashDelete(1);
    ht.hashDelete(2);
    ht.printTable();

    cout<<ht.hashSearch(12)<<"\n";
    
    return 0;
}