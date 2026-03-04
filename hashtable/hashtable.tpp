// Joe Teates, Theo Wolf
// Code implementation file for an open addressing hashtable
// using a linear probing function
#ifndef HASH_TPP
#define HASH_TPP

#include <iostream>
#include <climits> 
#include <stdexcept>
using namespace std;

template<typename V>
void Hashtable<V>::printTable() {
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
    return (key + probe_i)% this->size;
}

template<typename V>
Hashtable<V>::Hashtable() {
    table = nullptr;
    size = 0;
}

template<typename V>
Hashtable<V>::Hashtable(int size) {
    table = new Item<V>[size];
    this->size = size;
    for (int i = 0; i < size; i++) {
        table[i].isNull = true;
        table[i].wasDeleted = false;
    }
}


template<typename V>
Hashtable<V>::~Hashtable() {
    delete[] table;
}

template<typename V>
Hashtable<V>::Hashtable(const Hashtable<V>& hashtable){
    size = hashtable.size;
    table = new Item<V>[size];
    for (int i = 0; i < size; i++) {
        table[i].value = hashtable.table[i].value;
        table[i].key = hashtable.table[i].key;
        table[i].wasDeleted = hashtable.table[i].wasDeleted;
        table[i].isNull = hashtable.table[i].isNull;
    }
}

template<typename V>
Hashtable<V>& Hashtable<V>::operator=(const Hashtable<V>& hashtable) {
    if (this != &hashtable) {
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
    int i = 0;
    do {
        int j = hash(key, i);
        if( table[j].isNull || table[j].wasDeleted ){
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
    for(int i = 0; i<size; i++){
        int j = hash(key, i);
        if(table[j].isNull){
            return;
        }
        if(table[j].key==key){
            // Node is not null and has not been deleted
            table[j].wasDeleted = true;
            return;
        }
    }
}

template<typename V>
Item<V> Hashtable<V>::hashSearch(int key) {
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
    return Item<V>{V{}, 0, false, true};
}

#endif