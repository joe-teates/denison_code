
#pragma once


template<typename V>
class Item {

    public:
    int key;
    V value;

};

class Pair {

    public:
    int lower;
    int higher;

};

template<typename V>
Pair partition(Item<V> a[], int p, int r);

template<typename V>
void qsort(Item<V> a[], int p, int r);

#include "qsort.tpp"