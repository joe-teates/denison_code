
#pragma once

template<typename V>
class Item {

    public:
    V value;
    int key;
    bool wasDeleted;
    bool isNull;

};


template<typename V>
class Hashtable {

    
    public:
    Item<V>* table;
    int size;
    void printTable();
    int hash(int key, int probe_i);
    
    Hashtable();
    
    Hashtable(int size);
    
    ~Hashtable();
    
    Hashtable(const Hashtable<V>& hashtable);
    
    Hashtable<V>& operator=(const Hashtable<V>& hashtable);
    
    void hashInsert(int key, V value);
    
    void hashDelete(int key);
    
    Item<V> hashSearch(int key);
    
};


#include "hashtable.tpp"