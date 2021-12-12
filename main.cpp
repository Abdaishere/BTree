#include <iostream>
#include <cmath>

using namespace std;

//template<class T>
//class key {
//    T val;
//    key *next;
//public:
//    key(T val){
//        this->val = val;
//        next = nullptr;
//    }
//    key *getnext() {
//        return next;
//    }
//
//    void insert(T input) {
//        key *curr = this;
//        while (curr->next != nullptr && curr->next->val <= input) {
//            curr = curr->next;
//        }
//        key<T> *newkey = new key(input);
//        newkey->val = input;
//        newkey->next = curr->next;
//        curr->next = newkey;
//    }
//
//    void print() {
//        key *curr = this;
//        while (curr->next != nullptr){
//            std::cout<<curr->val<<' ';
//            curr = curr->next;
//        }
//    }
//};


//template<class int>
class BtreeNode {
    BtreeNode(){}
    key *keys;
    BtreeNode *parent;
    int m, size;

    void split(){
        if (parent == nullptr)
            parent = new BtreeNode(m, nullptr);
        parent->insertkey(keys[((m + 1)/2)]);

    }

public:

    BtreeNode(int m, BtreeNode *parent) {
        this->m = m;
        keys = nullptr;
        size = 0;
        this->parent = parent;
    }

    void insertkey(int input) {
        int *tmp = new int[++size];
        bool f = 0;

        for (int i = 0, j = 0; i < size - 1; j++,i++) {
            if (!f && keys[i] > input) {
                tmp[j++] = input;
                f = 1;
            }
            tmp[j] = keys[i];
        }
        if (f)
            tmp[size - 1] = keys[size - 2];
        else
            tmp[size - 1] = input;

        keys = tmp;
        BtreeNode *tmpchildren = new BtreeNode[size + 1];
        for (int i = 0; i < size + 1; i++) {
            tmpchildren[i] = children[i];
        }
        tmpchildren[size] = *new BtreeNode(m, this);

        children = tmpchildren;
        if (size == m) {
//           split();
            cout << "splitting required\n";
        }
    }

    key *getKeys() const {
        return keys;
    }

    void setKeys(key *keys) {
        BtreeNode::keys = keys;
    }

    BtreeNode *getParent() const {
        return parent;
    }

    void setParent(BtreeNode *parent) {
        BtreeNode::parent = parent;
    }

    int getM() const {
        return m;
    }

    void setM(int m) {
        BtreeNode::m = m;
    }

    int getSize() const {
        return size;
    }

    void setSize(int size) {
        BtreeNode::size = size;
    }

};

void printNode(BtreeNode *node) {
    if (node == nullptr)
        return;
    printNode(&node->getKeys()[0]);
    for (int i = 0; i < node->getSize(); i++) {
        cout << node->getKeys()[i]-> << " ";
        printNode(&node->getChildren()[i + 1]);
    }
}

class key{
    int val;
    BtreeNode *right,*left;
public:
    int getVal() const {
        return val;
    }

    void setVal(int val) {
        key::val = val;
    }

    BtreeNode *getRight() const {
        return right;
    }

    void setRight(BtreeNode *right) {
        key::right = right;
    }

    BtreeNode *getLeft() const {
        return left;
    }

    void setLeft(BtreeNode *left) {
        key::left = left;
    }
};

int main() {
    BtreeNode head(5, nullptr);
    head.insertkey(8);
    head.insertkey(2);
    head.insertkey(1);

    BtreeNode child(5, &head);
    child.insertkey(0);
    head.getChildren()[0] = child;

    BtreeNode child1(5, &head);
    child1.insertkey(2);
    head.getChildren()[1] = child1;

    BtreeNode child2(5, &head);
    child2.insertkey(3);
    head.getChildren()[2] = child2;

    BtreeNode child3(5, &head);
    child3.insertkey(9);

    head.getChildren()[3] = child3;
    printNode(&head);
    return 0;
}
