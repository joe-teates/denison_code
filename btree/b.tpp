
#include "b.hpp"
#include <iostream>


/*
    int t;
    int n;
    int* keys;
    V* values;
    bool leaf;
    Node* parent;
    Node* children;

    Node(int t, int n, int* keys, V* values, bool leaf, Node* parent, Node* children);

    Node();

    ~Node();

    Node(const Node<V>& node);

    Node<V>& operator=(const Node<V>& node);

*/
template<typename V>
Node<V>::Node(int t, int n, int* keys, V* values, bool leaf, Node* parent, Node* children){
    this->t = t;
    this->n = n;
    this->keys = keys;
    this->values = values;
    this->leaf = leaf;
    this->parent = parent;
    this->children = children;
}

template<typename V>
Node<V>::Node(){
    this->t = 0;
    this->n = 0;
    this->keys = nullptr;
    this->values = nullptr;
    this->leaf = false;
    this->parent = nullptr;
    this->children = nullptr;
}

template<typename V>
Node<V>::~Node() {
    delete[] keys;
    delete[] values;
    delete[] children;
}

template<typename V>
Node<V>::Node(const Node<V>& node) {
    t = node.t;
    n = node.n;
    leaf = node.leaf;
    parent = node.parent;

    if (node.keys != nullptr) {
        keys = new int[2 * t - 1];
        for(int i=0; i < n; i++){
            keys[i] = node.keys[i];
        }
    } else {
        keys = nullptr;
    }

    if (node.values != nullptr) {
        values = new V[2 * t - 1];
        for (int i=0; i < n; i++) {
            values[i] = node.values[i];
        }
    } else {
        values = nullptr;
    }

    if (node.children != nullptr) {
        children = new Node<V>[2 * t];
        for (int i=0; i < 2 * t; i++) {
            children[i] = node.children[i];
        }
    } else {
        children = nullptr;
    }
}

template<typename V>
Node<V>& Node<V>::operator=(const Node<V>& node) {
    if (this == &node) return *this;

    delete[] keys;
    delete[] values;
    delete[] children;

    t = node.t;
    n = node.n;
    leaf = node.leaf;
    parent = node.parent;


    if (node.keys != nullptr) {
        keys = new int[2 * t - 1];
        for(int i=0; i < n; i++){
            keys[i] = node.keys[i];
        }
    } else {
        keys = nullptr;
    }

    if (node.values != nullptr) {
        values = new V[2 * t - 1];
        for (int i=0; i < n; i++) {
            values[i] = node.values[i];
        }
    } else {
        values = nullptr;
    }

    if (node.children != nullptr) {
        children = new Node<V>[2 * t];
        for (int i=0; i < 2 * t; i++) {
            children[i] = node.children[i];
        }
    } else {
        children = nullptr;
    }
    return *this;
}

template<typename V>
BTree<V>::BTree(int t) {
    // Node(int t, int n, int* keys, V* values, bool leaf, Node* parent, Node* children)
    this->t = t;
    root = new Node<V>(t, 0, new int[2*t-1], new V[2*t-1], true, nullptr, new Node<V>[2*t]);
}


template<typename V>
BTree<V>::BTree() {
    t = 0;
    root = nullptr;
}
    

template<typename V>
BTree<V>::~BTree() {
    delete root;
}

template<typename V>
BTree<V>::BTree(const BTree<V>& btree) {
    t = btree.t;
    if (btree.root != nullptr) {
        root = new Node<V>(*btree.root);
    } else {
        root = nullptr;
    }
}

template<typename V>
BTree<V>& BTree<V>::operator=(const BTree<V>& btree) {
    if (this == &btree) return *this;
    delete root;

    t = btree.t;
    if (btree.root != nullptr) {
        root = new Node<V>(*btree.root);
    } else {
        root = nullptr;
    }
    return *this;
}


template<typename V>
static void splitChild(Node<V>* node, int i) {
    // std::cout<<"SPLITTING ";
    // for(int j = 0; j<node->children[i].n; j++){
    //     std::cout<<node->children[i].keys[j]<<"  ";
    // }
    // std::cout<<"\n";

    int t = node->t;
    Node<V>& y = node->children[i];
    Node<V> z(t, 0, new int[2*t - 1], new V[2*t - 1], y.leaf, node, new Node<V>[2*t]);
    z.n = t-1;
    for(int j=0; j<t-1; j++){
        z.keys[j] = y.keys[j+t];
        z.values[j] = y.values[j+t];
    }
    if(!y.leaf){
        for(int j=0; j<t; j++){
            z.children[j]=y.children[j+t];
        }
    }
    y.n = t-1;
    // shift over chlidren in X to make room for new child
    for(int j = node->n; j>=i+1; j--){
    for (int j = node->n; j >= i + 1; j--)
        node->children[j+1] = node->children[j];
    }
    node->children[i+1] = z;
    for(int j = node->n-1; j>=i; j--){
        node->keys[j+1] = node->keys[j];
        node->values[j+1] = node->values[j];
    }
    node->keys[i] = y.keys[t-1];
    node->values[i] = y.values[t - 1];
    node->n = node->n+1;
    // std::cout<<"split done\n";

}


template<typename V>
static void bInsertNonfull(Node<V>* node, int key, V value) {
    int t = node->t;
    int i = node->n-1;
    // std::cout<<"current value "<<node->keys[0]<<"\n";
    // std::cout<<"current is leaf:"<<node->leaf<<"\n";
    // std::cout<<"ATTEMPTING INSERT AT ";
    // for(int j = 0; j<node->n; j++){
    //     std::cout<<node->keys[j]<<"  ";
    // }
    // std::cout<<"\n";

    if(node->leaf){
        // std::cout<<"Node IS a leaf\n";
        while (i>=0 && key<node->keys[i]) {
            node->keys[i+1] = node->keys[i];
            node->values[i+1] = node->values[i];
            i--;
        }
        node->keys[i+1] = key;
        node->values[i+1] = value;
        node->n = node->n+1;
        // std::cout<<"New size: "<<node->n<<"\n";
    }else{
        // std::cout<<"Node is NOT a leaf\n";
        
        while (i>=0 && key<node->keys[i]) {
            // std::cout<<"Less than "<<node->keys[i]<<"\n";
            i--;
        }
        // std::cout<<"Going to child at index: "<<i+1<<"\n";
        if(node->children[i+1].n == 2*t-1){
            splitChild(node, i+1);
            if(key>node->keys[i+1]){
                i++;
            }
        }
        // Node<V>* xci = &(node->children[i]);
        bInsertNonfull(&(node->children[i+1]), key, value);
    }
}


template<typename V>
void BTree<V>::bInsert(int key, V value) {
    // std::cout<<"INSERTING ("<<key<<", "<<value<<") ##########\n";
    Node<V>* current = root;

    if(current->n == 2*t - 1){
        Node<V>* s = new Node<V>(t, 0, new int[2*t-1], new V[2*t-1], false, nullptr, new Node<V>[2*t]);

        root = s;
        s->children[0] = Node<V>(*current);
        splitChild(s, 0);
        // std::cout<<"split\n";
        // std::cout<<"\t"<<root->values[0]<<"\n";
        // std::cout<<root->children[0].n<<"\t"<<root->children[0].values[0]<<"\n";
        // std::cout<<root->children[1].n<<"\t"<<root->children[1].values[0]<<"\n";
        bInsertNonfull(s, key, value);
    }else{
        bInsertNonfull(current, key, value);
    }
    // std::cout<<"############################\n\n";

}


template<typename V>
V* BTree<V>::bSearch(int key) {
    Node<V>* current = root;
    while(current!=nullptr){
        int i = 0;
        while(i<current->n && key>current->keys[i]){
            i++;
        }
        if (i<current->n && key==current->keys[i]) {
            return &current->values[i];
        }else if(current->leaf){
            return nullptr;
        }else{
            current = &current->children[i];
        }

    }
    return nullptr;
}




// template<typename V>
// V* BTree<V>::bDelete(int key) {

// }