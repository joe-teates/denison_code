#include <iostream>
#include "msort.h"

const int LENGTH = 10;
using namespace std;

int main() {    
    int arr1[LENGTH] = {1,2,5,1,2,6,5,7457,4,34};
    int arr13[LENGTH] = {1,2,5,1,2,6,5,7457,4,34};

    int correct_arr1[LENGTH] = {1, 1, 2, 2, 4, 5, 5, 6, 34, 7457};

    int arr2[LENGTH] = {9,8,7,6,5,4,3,2,1,0};
    int arr23[LENGTH] = {9,8,7,6,5,4,3,2,1,0};

    int correct_arr2[LENGTH] = {0,1,2,3,4,5,6,7,8,9};
    mergesort(arr1, 0, 9);
    mergesort(arr2, 0, 9);
    mergesort3(arr13, 0, 9);
    mergesort3(arr23, 0, 9);


    for(int i = 0; i<LENGTH; i++){
        if(arr1[i] != correct_arr1[i] || arr2[i] != correct_arr2[i] || arr13[i] != correct_arr1[i] || arr23[i] != correct_arr2[i]){
            cout<<"WRONG!\n";
            throw;
        }
    }
    cout<<"CORRECT!\n";
    return 0;



}