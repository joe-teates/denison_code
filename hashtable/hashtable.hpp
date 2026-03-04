
#pragma once


template<typename V>
class Hashtable {

    
    public:
    V* table;
    int size;
    
    void printTable();
    
    Hashtable();
    
    Hashtable(int size);
    
    ~Hashtable();
    
    Hashtable(const Hashtable<V>& hashtable);
    
    Hashtable<V>& operator=(const Hashtable<V>& hashtable);
    
    void hashInsert(int key, V value);
    
    void hashDelete(int key);
    
    V hashSearch(int key);
    private:
    int hash(int key, int probe_i);
    
};


#include "hashtable.tpp"