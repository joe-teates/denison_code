
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
    this->leaf = true;
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
    parent = nullptr;

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
        for (int i=0; i <= node.n; i++) {
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
    std::cout<<"SPLITTING ";
    for(int j = 0; j<node->children[i].n; j++){
        std::cout<<node->children[i].keys[j]<<"  ";
    }
    std::cout<<"\n";

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
    for(int j = 0; j<node->n; j++){
        std::cout<<node->keys[j]<<"  ";
    }
    std::cout<<"\n";

    if(node->leaf){
        // std::cout<<"IS leaf\n";
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
        // std::cout<<"NOT leaf\n";
        
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
    std::cout<<"INSERTING ("<<key<<", "<<value<<") ##########\n";
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
// static void merge(Node<V>* node, int i) {
//     int t = node->t;
//     Node<V>& child = node->children[i];
//     Node<V>& sibling = node->children[i+1];

//     child->keys[t-1] = node->keys[i];
//     child->values[t-1] = node->values[i];

//     // copy sibling keys into child
//     for (int j = 0; j < sibling.n; j++) {
//         child.keys[j+t] = sibling.keys[j];
//         child.values[j+t] = sibling.values[j];
//     }
//     // copy sibling children into child (if not leaf)
//     if(!sibling->leaf){
//         for(int j = 0; j<sibling->n+1; j++){
//             child->children[child->n+j] = sibling->children[j];
//         }
//     }

//     // shift x keys left
//     for(int j = i; j<node->n; j++){
//         node->keys[j] = node->keys[j+1];
//         node->values[j] = node->values[j+1];
//     }
//     // shift x children left
//     for(int j = i+1; j<node->n+1; j++){
//         node->children[j] = node->children[j+1];
//     }
    
//     child->n += sibling->n + 1;
//     node->n -= 1;
// }

template<typename V>
static void merge(Node<V>* node, int i) {
    int t = node->t;

    Node<V>& child = node->children[i];
    Node<V>& sibling = node->children[i+1];

    // bring down middle key
    child.keys[child.n] = node->keys[i];
    child.values[child.n] = node->values[i];

    // copy sibling keys/values
    for (int j = 0; j < sibling.n; j++) {
        child.keys[j + child.n+1] = sibling.keys[j];
        child.values[j + child.n+1] = sibling.values[j];
    }

    // copy children
    if (!child.leaf) {
        for (int j = 0; j <= sibling.n; j++) {
            child.children[j + t] = sibling.children[j];
        }
    }

    // shift parent keys left
    for (int j = i; j < node->n - 1; j++) {
        node->keys[j] = node->keys[j+1];
        node->values[j] = node->values[j+1];
    }

    // shift children left
    for (int j = i+1; j < node->n; j++) {
        node->children[j] = node->children[j+1];
    }

    child.n += sibling.n + 1;
    node->n -= 1;
}


template<typename V>
static void plump(Node<V>* node, int i){
    int t = node->t;

    Node<V>& child = node->children[i];

    // borrow from left
    if (i != 0 && node->children[i-1].n >= t) {
        Node<V>& sibling = node->children[i-1];

        // shift elements right
        for (int j = child.n - 1; j >= 0; j--) {
            child.keys[j+1] = child.keys[j];
            child.values[j+1] = child.values[j];
        }
        //shift children
        if (!child.leaf) {
            for (int j = child.n; j >= 0; j--) {
                child.children[j+1] = child.children[j];
            }
        }
        //bring down
        child.keys[0] = node->keys[i-1];
        child.values[0] = node->values[i-1];
        
        if (!child.leaf) {
            child.children[0] = sibling.children[sibling.n];
        }
        //bring up
        node->keys[i-1] = sibling.keys[sibling.n-1];
        node->values[i-1] = sibling.values[sibling.n-1];

        child.n++;
        sibling.n--;

    // borrow from right
    } else if (i != node->n && node->children[i+1].n >= t) {
        Node<V>& sibling = node->children[i+1];

        child.keys[child.n] = node->keys[i];
        child.values[child.n] = node->values[i];

        if (!child.leaf) {
            child.children[child.n + 1] = sibling.children[0];
        }

        node->keys[i] = sibling.keys[0];
        node->values[i] = sibling.values[0];

        // shift sibling elements left
        for (int j = 0; j < sibling.n - 1; j++) {
            sibling.keys[j] = sibling.keys[j+1];
            sibling.values[j] = sibling.values[j+1];
        }

        if (!sibling.leaf) {
            for (int j = 0; j < sibling.n; j++) {
                sibling.children[j] = sibling.children[j+1];
            }
        }

        child.n++;
        sibling.n--;

    } else {
        if (i != node->n) {
            merge(node, i);
        } else {
            merge(node, i-1);
        }
    }
}

template<typename V> 
static std::pair<int, V> getPredecessor(Node<V>* node, int i){
    Node<V>* current = &node->children[i];
    while(!current->leaf){
        current = &current->children[current->n];
    }
    return {current->keys[current->n-1], current->values[current->n-1]};
}

template<typename V> 
static std::pair<int, V> getSuccessor(Node<V>* node, int i){
    Node<V>* current = &node->children[i+1];
    while(!current->leaf){
        current = &current->children[0];
    }
    return {current->keys[0], current->values[0]};
}
template<typename V> 
static void deleteFromLeaf(Node<V>* node, int i){
    // shift elements left
    for(int j = i; j<node->n-1; j++){
        node->keys[j] = node->keys[j+1];
        node->values[j] = node->values[j+1];
    }
    node->n--;
}

template<typename V> 
static void deleteFromNotLeaf(Node<V>* node, int i){
    int t = node->t;
    // if predecessor in node >= t size
    // delete and place it here
    if(node->children[i].n >=t){
        auto pred = getPredecessor(node, i);
        node->keys[i] = pred.first;
        node->values[i] = pred.second;
        recDelete(&node->children[i], pred.first);
    }else if(node->children[i+1].n >=t){
        // else if successor in node >= t size
        // delete and place it here
        auto succ = getSuccessor(node, i);
        node->keys[i] = succ.first;
        node->values[i] = succ.second;
        recDelete(&node->children[i+1], succ.first);
    } else {
        // both kids = t-1 -> combine both children into predecessor node WITH current (nodei)
        // THEN delete(node, i)
        int k = node->keys[i];
        merge(node, i);
        recDelete(&node->children[i], k);
    }
}

template<typename V>
static void recDelete(Node<V>* node, int key) {
    std::cout<<"ATTEMPTING DELETE ("<<key<<") AT ";
    for(int j = 0; j<node->n; j++){
        std::cout<<node->keys[j]<<"  ";
    }
    std::cout<<"("<<node->n<<")\n";
    int i = 0;
    while (i < node->n && key > node->keys[i]) {
        i++;
    }
    std::cout<<"Key at or child of index "<<i<<"\n";
    if (i < node->n && node->keys[i] == key) {
        //found key in node
        std::cout<<"found key in this node "<<i<<"\n";
        if (node->leaf) {
            deleteFromLeaf(node, i);
        } else {
            deleteFromNotLeaf(node, i);
        }
    } else {
        //not found but in subtree of child[i]
        if (node->leaf) {
            return;
        }

        int t = node->t;

        if (node->children[i].n < t) {
            plump(node, i);
        }
        if (i > node->n) {
            recDelete(&node->children[i-1], key);
        } else {
            recDelete(&node->children[i], key);
        }
    }
}

template<typename V>
void BTree<V>::bDelete(int key) {
    // printTree(root, 0);
    std::cout<<"DELETE ("<<key<<")\n";
    
    recDelete(root, key);

    if(root->n == 0){
        if(!root->leaf) {
            root = &(root->children[0]);
        }
    }
    // printTree(root, 0);

    // found key at leaf
    // if leaf has == t-1 then get immediate neighbor key and replace / shuffle over
            // shuffle - last/first key of left/right goes over and brings right/left child with it
            // must shift over all keys/values and children
        // if immediate neighbors all t-1 then combine left and right with key from parent in middle
    // if leaf has > t-1 then delete key 
    
    // found key at internal node


}


template<typename V>
void printTree(Node<V>* node, int level) {
/*      print(f'Level {level}', end=": ")
        for i in x.keys:
            print(i, end=" ")

        print()
        level += 1

        if len(x.children) > 0:
            for i in x.children:
                self.print_tree(i, level)*/
    std::cout<<"Level "<<level<<": ";
    for(int j = 0; j<node->n;j++){
        std::cout<<node->keys[j]<<" ";
    }
    std::cout<<"\n";
    if(!node->leaf){
        for(int j = 0; j<node->n+1; j++){
            printTree(&node->children[j], level+1);
        }
    }

}