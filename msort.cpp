// This is a program written by Joe Teates to sort a passed 
// list by merge sort. This file includes all code to first 
// split the code into chunks recursively (mergesort) and
// then recombine sortedly (merge). I used the native c arr
// object so I added LENGTH as a constant. 

#include <iostream>
using namespace std;
#include "msort.h"
const int LENGTH = 10;

void merge(int a[], int p, int q, int r){
// This function contains the actual logic for recombining the elements
// in the list. 
    // First we create a copy of the list to use without 
    // overwriting elements in the passed list.
    int copy_arr[LENGTH];
    for(int i = p; i<=r; i++){
        copy_arr[i]=a[i];
    }
    // [_ _ _ | _ _ _]
    // Get the starting index on the left side and right side
    // i is used as the index we are working on in the actual
    // list (list is sorted up to i)
    int left_index = p;
    int right_index = q+1;
    int i = p;
    // check to see if we have used all the elements in either
    // the left or right side
    while(left_index<=q && right_index <=r){
        // if not insert(overwrite) the lowest item first and
        // update the corresponding index
        if(copy_arr[left_index]<=copy_arr[right_index]){
            a[i] = copy_arr[left_index];
            left_index++;
        }else{
            a[i] = copy_arr[right_index];
            right_index++;
        }
        // increase the sorted index
        i++;
    }
    // leftovers
    while (left_index <= q) {
        a[i] = copy_arr[left_index];
        left_index++;
        i++;
    }

    while (right_index <= r) {
        a[i] = copy_arr[right_index];
        right_index++;
        i++;
    }
    return;

}


void mergesort(int a[], int p, int r){
// This function serves as the starting point for sorting
// your list. First input the list with p=0 and r=length - 1 (last index)
// and then the middle index is calculated and recursively, the list
// is sorted by combining small chunks of the original list together
    if(p>=r){
        return;
    }

    int middle_index = p + (r-p) / 2;
    // Sort left side
    mergesort(a, p, middle_index);
    // Sort right side
    mergesort(a, middle_index+1, r);
    // Put together
    merge(a, p, middle_index, r);
}



