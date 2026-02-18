// template<typename V>
// class Item {

//     public:
//     int key;
//     V value;

// };

// class Pair {

//     public:
//     int lower;
//     int higher;

// };

using namespace std;
#include <iostream>

#pragma once

template<typename V>
Pair partition(Item<V> a[], int p, int r)
{
    int pivot_high = a[r].key;
    int pivot_low = a[r-1].key;
    if(pivot_high<pivot_low){
        // to make sure pivot_high>=pivot_low
        // swap locations
        Item<V> temp = a[r];
        a[r] = a[r-1];
        a[r-1] = temp;

        pivot_high = a[r].key;
        pivot_low = a[r-1].key;
    }
    // cout<<"pivot_High: "<<pivot_high<<"\n";
    // cout<<"pivot_Low: "<<pivot_low<<"\n";
    int i_Low = p-1;
    int i_High = p-1;
    for(int j = p; j<r-1; j++){
        if(a[j].key <= pivot_low){
            i_Low++;
            i_High++;
            //swap a[iLow] with j
            //if ilow!=iHigh swap a[j] with a[iHigh]
            Item<V> temp = a[j];
            a[j] = a[i_Low];
            a[i_Low] = temp;
            if(i_Low!=i_High){
                temp = a[j];
                a[j] = a[i_High];
                a[i_High] = temp;
            }

        } else if(a[j].key <= pivot_high){
            i_High++;
            //swap just with i_High
            Item<V> temp = a[j];
            a[j] = a[i_High];
            a[i_High] = temp;
        }
        
    }
    // NOW mostly done swapping and pivots are j sitting at end
    if(i_Low==i_High){
        // this means that list has no elements between them
        Item<V> temp = a[r-1];
        a[r-1] = a[i_Low+1];
        a[i_Low+1] = temp;

        temp = a[r];
        a[r] = a[i_Low+2];
        a[i_Low+2] = temp;
    }else{
        // there are elements in between
        // we have to double swap for the first element
        Item<V> temp = a[r-1];
        a[r-1] = a[i_Low+1];
        a[i_Low+1] = temp;
        //swap the next highest a[i_H]<->a[r-1]
        i_High++;
        temp = a[r-1];
        a[r-1] = a[i_High];
        a[i_High] = temp;

        // Done with first pivot now just one swap for second
        temp = a[r];
        a[r] = a[i_High+1];
        a[i_High+1] = temp;
    }
    Pair parts = {i_Low+1, i_High+1};
    return parts;
}

template<typename V>
void qsort(Item<V> a[], int p, int r)
{
    if (p < r)
    {
        Pair parts = partition(a, p, r);
        qsort(a, p, parts.lower-1);
        qsort(a, parts.lower+1, parts.higher-1);
        qsort(a, parts.higher+1, r);
    }
}
