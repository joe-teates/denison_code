// Joe Teates, Theo Wolf
// Code implementation file for an open addressing hashtable
// using a linear probing function

#ifndef HASH_TPP
#define HASH_TPP

#include <iostream>
#include <climits> 
#include <stdexcept>
using namespace std;

const int TABLE_CAPACITY = 1000;
const int NULL_VALUE = INT_MIN;
const int DELETED = INT_MIN+1;



template<typename V>
void Hashtable<V>::printTable() {
    cout<<"Hashtable:\n";
    for (int i = 0; i < this->size; i++) {
        // table[i] = hashtable.table[i];
        cout<<"\t"<<table[i]<<"\n";
    }
    cout<<"]\n";
}
template<typename V>
int Hashtable<V>::hash(int key, int probe_i){
    return (key + probe_i)% this->size;
}

template<typename V>
Hashtable<V>::Hashtable() {
    table = new V[TABLE_CAPACITY];
    size = TABLE_CAPACITY;
    for (int i = 0; i < this->size; i++) {
        table[i] = NULL_VALUE;
    }
}

template<typename V>
Hashtable<V>::Hashtable(int size) {
    table = new V[size];
    this->size = size;
    for (int i = 0; i < size; i++) {
        table[i] = NULL_VALUE;
    }
}


template<typename V>
Hashtable<V>::~Hashtable() {
    delete[] table;
}

template<typename V>
Hashtable<V>::Hashtable(const Hashtable<V>& hashtable){
    size = hashtable.size;
    table = new V[size];
    for (int i = 0; i < size; i++) {
        table[i] = hashtable.table[i];
    }

}

template<typename V>
Hashtable<V>& Hashtable<V>::operator=(const Hashtable<V>& hashtable) {
    if (this != &hashtable) {
        delete[] table;
        size = hashtable.size;
        table = new V[size];
        for (int i = 0; i < size; i++) {
            table[i] = hashtable.table[i];
        }
    }
    return *this;
}

template<typename V>
void Hashtable<V>::hashInsert(int key, V value) {
    int i = 0;
    do {
        int j = hash(key, i);
        if( table[j]==NULL_VALUE || table[j]==DELETED ){
            table[j] = value;
            return;
        }else{
            i++;
        }
    } while(i!=size);
    throw std::runtime_error("Hash table is full");
}

template<typename V>
void Hashtable<V>::hashDelete(int key) {
    int i = 0;
    int j = hash(key, i);
    while(i!=size && table[j]!=NULL_VALUE) {
        if( table[j]==key ){
            table[j] = DELETED;
            return;
        }else{
            i++;
        }
        j = hash(key, i);
    } 
}

template<typename V>
V Hashtable<V>::hashSearch(int key) {
    int i = 0;
    int j = hash(key, i);
    do {
        if( table[j]==key ){
            return table[j];
        }
        i++;
        j = hash(key, i);
    }while(i!=size && table[j]!=NULL_VALUE);
    return NULL_VALUE;
}



#endif