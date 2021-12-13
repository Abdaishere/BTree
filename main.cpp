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
    BtreeNode() {}

    class key {
    public:
        int val;
        BtreeNode *right, *left;
    } *keys;

    BtreeNode *parent;
    int m, size,isleaf;

//    void split() {
//        if (parent == nullptr)
//            parent = new BtreeNode(m, nullptr);
//        parent->insertkey(keys[((m + 1) / 2)]);
//
//    }

    BtreeNode(int m, key *keys, BtreeNode *parent) {
        this->m = m;
        this->keys = keys;
        size = m / 2;
        this->parent = parent;
    }

public:

    BtreeNode(int m, BtreeNode *parent) {
        this->m = m;
        keys = nullptr;
        size = 0;
        this->parent = parent;
    }

    void insertkey(int input) {
        key *tmp = new key();
        key newkey;
        newkey.val = input;
        if (size == 0) {
            tmp->left = new BtreeNode(m, this);
            tmp->right = new BtreeNode(m, this);
            tmp->val = input;
            keys = new key[++size];
            keys[0] = *tmp;
            return;
        }
//        cout << "size :" << size << '\n';
        tmp = new key[++size];
        int i = 0, j = 0;
        for (; i < size - 1; i++, j++) {
            if (keys[i].val > input) {
                newkey.left = tmp[j - 1].right;
                newkey.right = new BtreeNode(m, this);
                tmp[j++] = newkey;
            }
            tmp[j] = keys[i];
        }
        if (j > i) {
            tmp[size - 1] = keys[size - 2];
        } else
            tmp[size - 1] = newkey;

        for (int i = 0; i < size - 1; i++) {
            tmp[i].right = tmp[i + 1].left;
        }
        keys = tmp;
//        for (int i = 0; i < size; i++) {
//            cout << keys[i].val << " ";
//        }
//        cout << '\n';
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

//
//void printNode(BtreeNode *node) {
//    if (node == nullptr)
//        return;
//    printNode(&node->getKeys()[0]);
//    for (int i = 0; i < node->getSize(); i++) {
//        cout << node->getKeys()[i]-><< " ";
//        printNode(&node->getChildren()[i + 1]);
//    }
//}


int main() {
    BtreeNode head(5, nullptr);
    head.insertkey(8);
    head.insertkey(44);
    head.insertkey(1);
    return 0;
}
