#include "qsort.hpp"
#include <iostream>
using namespace std;


int main() {
    Item<int> list1[] = {{0,0},{21,21},{9,9},{6,6},{8,8},{20,20},{5,5},{4,4},{7,7},{11,11},{1,1},{3,3},{2,2}};
    int length = 13; 

    qsort(list1, 0, length-1);

    cout<<" [ ";
    for(int i = 0; i<length; i++){
        cout<<list1[i].key<<" ";
    }
    cout<<"] \n";



    return 0;
}