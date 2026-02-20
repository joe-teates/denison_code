// Joe Teates, Genevieve Cyrus, Emma Salamon
// This file contains the tests of quicksort using two partitions

// This file tests to make sure qsort() works and also that the partition function
// works by maintaining the property that the first section of the list is less than the smallest pivot,
// the middle section is in between the two, and the final section is greater than the greatest pivot.

#include "qsort.hpp"
#include <iostream>
using namespace std;

template<typename V>
bool sortedAscendingly(Item<V> a[], int length) {
// sortedAscendingly is a helper function to check whether a list's elements are in ascending order (sorted)
    bool passed = true;
    int last_value = a[0].key;
    for(int i = 1; i<length&&passed; i++){
        // Check to make sure each value is less than or equal to the previous
        passed = last_value <= a[i].key;
        last_value = a[i].key;
    }
    return passed;
}

template<typename V>
bool isPartitioned(Item<V> a[], int length, Pair parts) {
// isPartitioned is a helper function to check whether a list's elements are partitioned
    bool passed = true;
    int i = 0;
    int current_pivot = parts.lower;
    // Check first section
    while(i<current_pivot && passed){
        passed = a[i].key <= a[current_pivot].key;
        i++;
    }
    // Check second section
    current_pivot = parts.higher;
    while(i<current_pivot && passed){
        passed = a[i].key <= a[current_pivot].key;
        i++;
    }
    // Check third and final section
    while(i<length && passed){
        passed = a[i].key >= a[current_pivot].key;
        i++;
    }
    return passed;
}

int main() {
    // Check sorting correctly
    Item<int> list1[] = {{0,0},{21,21},{9,9},{6,6},{8,8},{20,20},{5,5},{4,4},{7,7},{11,11},{1,1},{3,3},{2,2}};
    int length1 = 13; 

    qsort(list1, 0, length1-1);
    bool passed = sortedAscendingly(list1, length1);


    // Check qsort with different length
    Item<int> list2[] = {{0,0},{9,9},{6,6},{8,8},{5,5},{4,4},{7,7},{1,1},{3,3},{2,2}};
    int length2 = 10;
    qsort(list2, 0, length2-1);
    passed = passed && sortedAscendingly(list2, length2);

    // Check partition correctness

    Item<int> list3[] = {{12,12},{3,3},{15,15},{0,0},{9,9},{6,6},{14,14},{2,2},{11,11},{5,5},{8,8},{1,1},{13,13},{4,4},{10,10},{7,7}};
    int length3 = 16;
    Pair parts = partition(list3, 0, length3-1);
    passed = passed && isPartitioned(list3, length3, parts);

    string to_print = string(passed ? "Correct!":"Incorrect");

    cout<<"\n"<<to_print<<"\n";

    return 0;
}