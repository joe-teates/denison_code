#include <iostream>
#include <cassert>
#include "b.hpp"
using namespace std;

void testInsertAndSearch() {
    cout << "Test: insert + search\n";

    BTree<int> tree(3);

    tree.bInsert(10, 100);
    // cout<<"10\n";
    tree.bInsert(20, 200);
    // cout<<"20\n";
    tree.bInsert(5, 50);
    // cout<<"5\n";
    tree.bInsert(6, 60);
    // cout<<"6\n";
    tree.bInsert(12, 120);
    // cout<<"12\n";
    tree.bInsert(30, 300);
    // cout<<"30\n";
    tree.bInsert(7, 70);
    // cout<<"7\n";
    tree.bInsert(17, 170);
    // cout<<"17\n";

    assert(tree.bSearch(10) && *tree.bSearch(10) == 100);
    assert(tree.bSearch(20) && *tree.bSearch(20) == 200);
    assert(tree.bSearch(5)  && *tree.bSearch(5)  == 50);
    assert(tree.bSearch(6)  && *tree.bSearch(6)  == 60);
    assert(tree.bSearch(12) && *tree.bSearch(12) == 120);
    assert(tree.bSearch(30) && *tree.bSearch(30) == 300);
    assert(tree.bSearch(7)  && *tree.bSearch(7)  == 70);
    assert(tree.bSearch(17) && *tree.bSearch(17) == 170);

    std::cout << "PASS\n\n";
}

void testCopyConstructor() {
    std::cout << "Test: copy constructor\n";

    BTree<int> tree(2);

    tree.bInsert(1, 10);
    tree.bInsert(2, 20);
    tree.bInsert(3, 30);

    BTree<int> copy(tree);

    assert(copy.bSearch(1) && *copy.bSearch(1) == 10);
    assert(copy.bSearch(2) && *copy.bSearch(2) == 20);
    assert(copy.bSearch(3) && *copy.bSearch(3) == 30);

    // modify original, ensure copy is independent
    tree.bInsert(4, 40);

    assert(copy.bSearch(4) == nullptr);

    std::cout << "PASS\n\n";
}

void testAssignmentOperator() {
    std::cout << "Test: assignment operator\n";

    BTree<int> tree1(2);
    tree1.bInsert(100, 1);
    tree1.bInsert(200, 2);

    BTree<int> tree2(2);
    tree2.bInsert(999, 9);

    tree2 = tree1;

    assert(tree2.bSearch(100) && *tree2.bSearch(100) == 1);
    assert(tree2.bSearch(200) && *tree2.bSearch(200) == 2);
    assert(tree2.bSearch(999) == nullptr);

    tree1.bInsert(300, 3);

    assert(tree2.bSearch(300) == nullptr);

    std::cout << "PASS\n\n";
}

void testStressInsert() {
    std::cout << "Test: stress insert\n";

    BTree<int> tree(3);

    for (int i = 0; i < 1000; i++) {
        tree.bInsert(i, i * 10);
    }

    for (int i = 0; i < 1000; i++) {
        assert(tree.bSearch(i) && *tree.bSearch(i) == i * 10);
    }

    std::cout << "PASS\n\n";
}

int main() {
    std::cout << "Running B-Tree tests...\n\n";

    testInsertAndSearch();
    testCopyConstructor();
    testAssignmentOperator();
    testStressInsert();

    std::cout << "ALL TESTS PASSED 🎉\n";

    return 0;
}