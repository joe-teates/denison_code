// Joe Teates, Genevieve Cyrus, Emma Salamon
// This file contains the implementation of quicksort using two partitions

// This implementation works on lists of Item<V> and sorts lists based on the integer values
// of the key property in ascending order. It accomplishes this by recursively calling the 
// partition function which divides the list up into 3 parts based on two pivots chosen 
// at the end of the list.

using namespace std;
#include <iostream>

#pragma once

template<typename V>
Pair partition(Item<V> a[], int p, int r) {
// This function choses two items (pivots) to break up the given list into 3 parts based on the item's keys
// the first part from index 0 to i_Low consists of elements less than the lowest pivot
// the second (i_Low+2 to i_High) and third part (i_High+2 to r) contain elements between 
// the two and elements greater than both respectively. This function modifies the list in 
// place and then returns the indices of each pivot.
    // get pivot values
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
    // initialize indices to mark the section of the list that have been partitioned
    int i_Low = p-1;
    int i_High = p-1;
    for(int j = p; j<r-1; j++){
        if(a[j].key <= pivot_low){
            // a[j] should go into the first section
            i_Low++;
            i_High++;
            //swap a[i_Low] with a[j]
            Item<V> temp = a[j];
            a[j] = a[i_Low];
            a[i_Low] = temp;
            //if ilow!=iHigh swap a[j] with a[iHigh] to maintain first two sections
            if(i_Low!=i_High){
                temp = a[j];
                a[j] = a[i_High];
                a[i_High] = temp;
            }
        } else if(a[j].key <= pivot_high){
            // a[j] should go into the middle section
            i_High++;
            //swap just with i_High - only one swap needs to occur
            Item<V> temp = a[j];
            a[j] = a[i_High];
            a[i_High] = temp;
        }
        
    }
    // NOW mostly done swapping and pivots are just sitting at end
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
        // we have to double swap for the first pivot element
        Item<V> temp = a[r-1];
        a[r-1] = a[i_Low+1];
        a[i_Low+1] = temp;
        //swap the next highest a[i_High]<->a[r-1]
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
void qsort(Item<V> a[], int p, int r) {
// this function receives a list and sorts it using quicksort. It
// does this by partitioning the list into 3 sections and then
// recursively sorts each section individually.
// a should be a valid list of Items that will be sorted based on the 
// items' keys
    if (p < r) {
        // p and r are valid indices
        Pair parts = partition(a, p, r);
        qsort(a, p, parts.lower-1);
        qsort(a, parts.lower+1, parts.higher-1);
        qsort(a, parts.higher+1, r);
    }
}
