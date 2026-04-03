// Joe Teates, Jack Rehbeck
// CS 271
// tests.cpp
// test file for b tree implementation

#include "b.hpp"
#include <iostream>
using namespace std;
#include <cassert>


//============================================================
// test functions
// Each function        tests a specific aspect of the b tree implementation
// testInsertAndSearch  tests basic implementation of insertion and searching
// testCopyConstructor  tests that all properties of a tree are conserved when copy constructor is used
// testAssignmentOperator   tests that all properties of a tree are conserved when assignment operator is used
// testInvariant        tests that the size, and inequality invariants of our b trees hold
// testSearchEdgeCases  tests certain edge cases when searching, nonexisting elements, searching empty tree
//============================================================

void testInsertAndSearch() {
    cout << "Testing insert and search\n";

    BTree<int> tree(3);

    tree.bInsert(10, 10);
    tree.bInsert(20, 20);
    tree.bInsert(5, 5);
    tree.bInsert(6, 6);
    tree.bInsert(12, 12);
    tree.bInsert(30, 30);
    tree.bInsert(7, 7);
    tree.bInsert(17, 17);

    assert(*tree.bSearch(10) == 10);
    assert(*tree.bSearch(20) == 20);
    assert(*tree.bSearch(5) == 5);
    assert(*tree.bSearch(6) == 6);
    assert(*tree.bSearch(12) == 12);
    assert(*tree.bSearch(30) == 30);
    assert(*tree.bSearch(7) == 7);
    assert(*tree.bSearch(17) == 17);

    cout << "PASS\n";
}

void testCopyConstructor() {
    cout << "Testing Copy Constructor\n";

    BTree<int> tree(2);
    tree.bInsert(1, 1);
    tree.bInsert(2, 2);
    tree.bInsert(3, 3);

    BTree<int> tree2(tree);

    assert(*tree2.bSearch(1) == 1);
    assert(*tree2.bSearch(2) == 2);
    assert(*tree2.bSearch(3) == 3);

    // make sure copy is independent
    tree.bInsert(4, 4);

    assert(tree2.bSearch(4) == nullptr);

    // make sure it deep copies
    for (int i = 5; i < 1000; i++) {
        tree.bInsert(i, i);
    }
    BTree<int> tree3(tree);
    for (int i = 1; i < 1000; i++) {
        assert(*tree3.bSearch(i)==i);
    }

    cout << "PASS\n";
}

void testAssignmentOperator() {
    cout << "Testing Assignment Operator\n";

    BTree<int> tree(2);
    tree.bInsert(1, 1);
    tree.bInsert(2, 2);
    tree.bInsert(3, 3);

    BTree<int> tree2(2);
    tree2.bInsert(4, 4);

    tree2 = tree;

    assert(*tree2.bSearch(1) == 1);
    assert(*tree2.bSearch(2) == 2);
    assert(*tree2.bSearch(3) == 3);
    assert(tree2.bSearch(4) == nullptr);

    // make sure trees are independent copies
    tree.bInsert(4, 4);
    assert(tree2.bSearch(4) == nullptr);

    // now check for deep copy
    for (int i = 5; i < 1000; i++) {
        tree.bInsert(i, i);
    }
    BTree<int> tree3(10);
    tree3 = tree;
    for (int i = 1; i < 1000; i++) {
        assert(*tree3.bSearch(i)==i);
    }
    cout << "PASS\n";
}


void recSizeChecker(Node<int>* node){
    // cout<<"Checking ("<<node->n<<") for "<<node->t<<"\n";
    assert(node->n >= node->t-1 && node->n < node->t*2);
    if(!node->leaf){
        for(int i = 0; i<node->n+1; i++){
            recSizeChecker(&node->children[i]);
        }
    }
}
void verifyNodeSizes(Node<int>* root){
    // function to check size of root then call recurisive recSizeChecker for all descendant nodes
    assert(root->n < root->t*2);
    if(!root->leaf){
        for(int i = 0; i<root->n+1; i++){
            recSizeChecker(&root->children[i]);
        }
    }

}

void testInvariant() {
    cout << "Testing Invariant\n";
    BTree<int> tree(3);

    for (int i = 0; i < 1000; i++) {
        tree.bInsert(i, i);
    }
    // search verifies less than greater then identities
    for (int i = 0; i < 1000; i++) {
        assert(*tree.bSearch(i)==i);
    }
    // verify, for all nodes that t-1 <= n <= 2t-1
    verifyNodeSizes(tree.root);

    // try diff t
    BTree<int> tree2(10);
    for (int i = 0; i < 1000; i++) {
        tree2.bInsert(i, i);
    }
    for (int i = 0; i < 1000; i++) {
        assert(*tree2.bSearch(i)==i);
    }
    // verify, for different t, t-1 <= n <= 2t-1
    verifyNodeSizes(tree2.root);

    cout << "PASS\n";
}

void testSearchEdgeCases() {
    cout << "Testing Insert edge cases\n";

    BTree<int> tree(3);

    tree.bInsert(10, 10);
    tree.bInsert(20, 20);
    tree.bInsert(5, 5);
    tree.bInsert(6, 6);
    tree.bInsert(12, 12);
    tree.bInsert(30, 30);
    tree.bInsert(7, 7);
    tree.bInsert(17, 17);

    assert(tree.bSearch(11) == nullptr);
    assert(tree.bSearch(13) == nullptr);
    assert(tree.bSearch(14) == nullptr);
    assert(tree.bSearch(15) == nullptr);

    //testing search on empty tree
    BTree<int> tree2(3);
    assert(tree.bSearch(0) == nullptr);
    cout << "PASS\n";
}

int main() {
    cout << "Running tests...\n\n";

    testInsertAndSearch();
    testCopyConstructor();
    testAssignmentOperator();
    testInvariant();
    testSearchEdgeCases();

    cout << "\nALL TESTS PASSED\n";

    return 0;
}