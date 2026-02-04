#ifndef LLIST
#define LLIST

class Node{

    public:

    int key;
    int value;
    Node *prev;
    Node *next;

    Node(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}

};

class MyList{

    public:

    Node *head;

    MyList() : head(nullptr) {}

};


Node* listSearch(MyList& list, int& key);

void listPrepend(MyList& list, Node& node);

void listInsert(Node& node_x, Node& node_y);

void listDelete(MyList& list, Node& node);

#endif