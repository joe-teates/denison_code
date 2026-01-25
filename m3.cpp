// This is a program written by Joe Teates to sort a passed 
// list by merge sort. This file includes all code to first 
// split the code into chunks recursively (mergesort) and
// then recombine sortedly (merge). I used the native c arr
// object so I added LENGTH as a constant. This program only
// modifies the mergesort() function from the file msort.cpp
// and to use it in the testing_msort.cpp file I renamed it 
// to mergesort3 because it splits the list into 3 parts

#include <iostream>
using namespace std;
#include "msort.h"
const int LENGTH = 10;

// void merge(int a[], int p, int q, int r){
//     //copy list
//     int copy_arr[LENGTH];
//     for(int i = p; i<=r; i++){
//         copy_arr[i]=a[i];
//     }

//     int left_index = p;
//     int right_index = q+1;
//     int i = p;
//     while(left_index<=q && right_index <=r){
//         if(copy_arr[left_index]<=copy_arr[right_index]){
//             a[i] = copy_arr[left_index];
//             left_index++;
//         }else{
//             a[i] = copy_arr[right_index];
//             right_index++;
//         }
//         i++;
//     }
//     // leftovers
//     while (left_index <= q) {
//         a[i++] = copy_arr[left_index++];
//     }

//     while (right_index <= r) {
//         a[i++] = copy_arr[right_index++];
//     }
//     return;

// }
void mergesort3(int a[], int p, int r){
// This function serves as the starting point for sorting
// your list. First input the list with p=0 and r=length - 1 (last index)
// and then the middle index is calculated and recursively, the list
// is sorted by combining small chunks of the original list together

    if(p>=r){
        return;
    }
    // find an index for a third of the list
    int third = (r - p + 1) / 3;
    // (need this to make sure left hand side is not empty)
    if(third == 0){
        third = 1;
    }
    
    // setup indexes. For splitting into thirds we need to have 4 indexes,
    // [start, left_middle, right_middle, end]
    int left_middle  = p + third - 1;
    int right_middle = p + 2 * third - 1;
    if(right_middle >= r) {
        right_middle = r - 1;
    }

    // Sort individual peices
    mergesort(a, p, left_middle);
    mergesort(a, left_middle+1, right_middle);
    mergesort(a, right_middle+1, r);
    // Here we assumed that the list [start to left_middle] is sorted
    // and [left_middle to right_middle] is sorted so merge those
    merge(a, p, left_middle, right_middle);
    // now [start to right_middle] is sorted so combine that with the
    // list [right_middle to end] which is also assumed to be sorted
    merge(a, p, right_middle, r);
}