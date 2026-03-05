// Joe Teates, Theo Wolf
// Testing file for checking accuracy of all methods of hashtable class

#include <iostream>
#include "hashtable.hpp"

using namespace std;

void testInsertAndSearch() {
// this function tests that insertion works and that search finds the values 
// associated with these objects. Also checks for error handling when adding too many objects
    Hashtable<int> ht(10);

    ht.hashInsert(1, 100);
    ht.hashInsert(2, 200);
    ht.hashInsert(3, 300);

    Item<int> item1 = ht.hashSearch(1);
    Item<int> item2 = ht.hashSearch(2);
    Item<int> item3 = ht.hashSearch(3);

    bool passed = !item1.isNull && !item2.isNull && !item3.isNull;
    passed = passed && item1.value == 100 && item2.value == 200 && item3.value == 300;

    cout << string(passed ? "Insert and Search test passed.\n" : "Insert and Search test failed\n");

    // Add too many objects
    try{
        for(int i = 0; i<10; i++){
            ht.hashInsert(i,i);
        }
        cout<<"Failed to throw error after adding too many values\n";
    }catch(std::runtime_error){
        cout<<"Correctly threw error after adding too many values\n";
    }
}

void testDelete() { 
// testDelete tests whether or not the deletion function works by searching for an object
// before and after it should be deleting and verifying the correct properties.
    Hashtable<int> ht(10);
    ht.hashInsert(5, 5);
    // find the node
    Item<int> beforeDelete = ht.hashSearch(5);
    bool passed = !beforeDelete.isNull;

    // delete the node
    ht.hashDelete(5);
    Item<int> afterDelete = ht.hashSearch(5);
    passed = passed && afterDelete.isNull;

    cout << string(passed ? "Delete test passed.\n":"Delete failed\n");
}

void testProbing() {
// testProbing checks to see if insertion works when objects will have colliding hashing 
// locations. Also to make sure the search and deletion functions deal with probing correctly
// we delete two of these and search for the 3rd item.
    Hashtable<int> ht(5);

    // Force probing (hash = key%size)
    // Sorry these will only work for my hashing function
    ht.hashInsert(1, 100);
    ht.hashInsert(6, 600); 
    ht.hashInsert(11, 1100);

    Item<int> item1 = ht.hashSearch(1);
    Item<int> item2 = ht.hashSearch(6);
    Item<int> item3 = ht.hashSearch(11);

    bool passed = !item1.isNull && !item2.isNull && !item3.isNull;
    passed = passed && item1.value == 100 && item2.value == 600 && item3.value == 1100;

    // Check if search still works after deletion
    ht.hashDelete(1);
    ht.hashDelete(6);
    passed = passed && ht.hashSearch(6).isNull;
    Item<int> item4 = ht.hashSearch(11);
    passed = passed && !item4.isNull && item4.value == 1100;

    
    cout << string(passed ? "Probing test passed.\n":"Probing failed/search or deletion failed\n");
}

void testCopyConstructor() {
// testCopyConstructor just works to verify two hashtables are the same after using copy constructor
    Hashtable<int> ht1(10);
    ht1.hashInsert(1, 1);
    ht1.hashInsert(2, 2);
    ht1.hashInsert(3, 3);
    ht1.hashInsert(4, 4);
    ht1.hashInsert(12, 12);
    ht1.hashInsert(22, 22);

    Hashtable<int> ht2(ht1);

    int values[] = {1,2,3,4,12,22};
    bool passed = ht1.size == ht2.size;
    for(int i = 0; i<6; i++){
        Item<int> val_1 = ht1.hashSearch(values[i]);
        Item<int> val_2 = ht2.hashSearch(values[i]);
        passed = passed && val_1.value == val_2.value && val_1.key == val_2.key && val_1.wasDeleted == val_2.wasDeleted && val_1.isNull == val_2.isNull;
    }
    

    cout << string(passed ?"copy constructor test passed.\n":"Copy constructor test failed\n");
}

void testAssignmentOperator() {
// This function works the same as copy constructor to verify two hashtables are equivalent after use
    Hashtable<int> ht1(10);
    ht1.hashInsert(1, 1);
    ht1.hashInsert(2, 2);
    ht1.hashInsert(3, 3);
    ht1.hashInsert(4, 4);
    ht1.hashInsert(12, 12);
    ht1.hashInsert(22, 22);


    Hashtable<int> ht2(5);
    ht2 = ht1;
    bool passed = ht1.size == ht2.size;
    int values[] = {1,2,3,4,12,22};
    bool passed = ht1.size == ht2.size;
    for(int i = 0; i<6; i++){
        Item<int> val_1 = ht1.hashSearch(values[i]);
        Item<int> val_2 = ht2.hashSearch(values[i]);
        passed = passed && val_1.value == val_2.value && val_1.key == val_2.key && val_1.wasDeleted == val_2.wasDeleted && val_1.isNull == val_2.isNull;
    }
    cout << string(passed ?"Assignment operator test passed.\n":"Assingment operator test failed");
}

int main() {
// main function to run all tests
    testInsertAndSearch();
    testDelete();
    testProbing();
    testCopyConstructor();
    testAssignmentOperator();

    return 0;
}