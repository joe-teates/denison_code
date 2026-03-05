// Joe Teates Theo Wolf
// This file contains the implementation of our open addressing hashtable data structure
// using linear probing. The table consists of Item<V> objects with properties of value, key,
// isNull, and wasDeleted to describe their state. If an object has been deleted it will only 
// have the wasDeleted property == true and not isNull.

#ifndef HASH_TPP
#define HASH_TPP

#include <iostream>
#include <climits> 
#include <stdexcept>
using namespace std;

template<typename V>
void Hashtable<V>::printTable() {
// This function is to print out our table and only used during testing
    cout<<"Hashtable:\n";
    for (int i = 0; i < this->size; i++) {
        if(table[i].isNull){
            cout<<"\t_\n";

        }else if(table[i].wasDeleted){
            cout<<"\tdeleted\n";
        }else{
            cout<<"\t"<<table[i].value<<"\n";
        }
    }
    cout<<"]\n";
}

template<typename V>
int Hashtable<V>::hash(int key, int probe_i){
// The hash function is how the keys of inserted objects will be mapped to where
// they should go in the table. The second parameter, probe_i, is used as a linear
// probe to add a certain amount to the initial location
    return (key + probe_i)% this->size;
}

template<typename V>
Hashtable<V>::Hashtable() {
// default constructor. This initializes an empty hashtable with nothing in it
    table = nullptr;
    size = 0;
}

template<typename V>
Hashtable<V>::Hashtable(int size) {
// This constructor is how the hashtable is supposed to be used where size is the size
// of the created hashtable. This determines both the amount of elements that can be
// stored and the specific computation of the hash function
    table = new Item<V>[size];
    this->size = size;
    for (int i = 0; i < size; i++) {
        // set all objects to null
        table[i].isNull = true;
        table[i].wasDeleted = false;
    }
}


template<typename V>
Hashtable<V>::~Hashtable() {
// Deconstructor to deallocate our table
    delete[] table;
}

template<typename V>
Hashtable<V>::Hashtable(const Hashtable<V>& hashtable){
// Copy constructor. Takes a valid hashtable as parameter and copies each object 
// from it into this hashtable.
    // Get size first
    size = hashtable.size;
    table = new Item<V>[size];
    for (int i = 0; i < size; i++) {
        // Copy all properties of all objects
        table[i].value = hashtable.table[i].value;
        table[i].key = hashtable.table[i].key;
        table[i].wasDeleted = hashtable.table[i].wasDeleted;
        table[i].isNull = hashtable.table[i].isNull;
    }
}

template<typename V>
Hashtable<V>& Hashtable<V>::operator=(const Hashtable<V>& hashtable) {
// Assignment operator. This works just like the copy constructor, however, instead of creating 
// a whole new object, we delete the old one and then loop through all objects in other 
// hashtable
    if (this != &hashtable) {
        // make sure to not delete yourself
        delete[] table;
        size = hashtable.size;
        table = new Item<V>[size];
        for (int i = 0; i < size; i++) {
            table[i].value = hashtable.table[i].value;
            table[i].key = hashtable.table[i].key;
            table[i].wasDeleted = hashtable.table[i].wasDeleted;
            table[i].isNull = hashtable.table[i].isNull;
        }
    }
    return *this;
}

template<typename V>
void Hashtable<V>::hashInsert(int key, V value) {
// Insertion function. This function takes the key and value of a new object to be inserted 
// into the hashtable and attempts to place it at hash(key). If this spot is filled it keeps 
// looking at the spot directly after until it wraps all the way around to the start or we 
// reach a null node. A null node means that no objects following could be the object we 
// are looking for. Linear probing is accomplished by using the probe_i parameter mentioned 
// earlier in the hash function
    int i = 0;
    do {
        // get index to attempt to place into 
        int j = hash(key, i);
        if( table[j].isNull || table[j].wasDeleted ){
            // no elements at this place
            table[j].value = value;
            table[j].key = key;
            table[j].wasDeleted = false;
            table[j].isNull = false;
            return;
        }else{
            i++;
        }
    } while(i!=size);
    throw std::runtime_error("Hash table is full");
}

template<typename V>
void Hashtable<V>::hashDelete(int key) {
// Deletion function. This function, similarly to insertion, will look for an object at 
// its usual hash and if it doesnt find it, it will search the next place and so on until
// reaching a null object. Objects that are tombstones (wasDeleted==true) will be ignored
    for(int i = 0; i<size; i++){
        int j = hash(key, i);
        if(table[j].isNull){
            // No further objects can be the one we are looking for
            return;
        }
        if(!table[j].wasDeleted && table[j].key==key){
            // We have found the node and it is not null and has not been deleted
            table[j].wasDeleted = true;
            return;
        }
    }
}

template<typename V>
Item<V> Hashtable<V>::hashSearch(int key) {
// Search function. This function searching the hashtable for an object with a key. Like
// the previous functions we check consecutive objects until we wrap around the tree or 
// hit a null object.
    for(int i = 0; i<size; i++){
        int j = hash(key, i);
        if(table[j].isNull){
            // Found a null node (cannot be null and deleted)
            // Stop searching, return null item
            return Item<V>{V{}, 0, false, true};
        }
        if(!table[j].wasDeleted && table[j].key==key){
            // Found the node, return it
            return table[j];
        }
    }
    // wrapped around, return null node
    return Item<V>{V{}, 0, false, true};
}

#endif