#include <iostream>

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
    int m, size, isleaf;


    void split() {
        cout << "splitting\n";
        int mid = m / 2;
        key *tmpleft = new key[m / 2];
        for (int i = 0; i < m / 2; i++) {
            tmpleft[i] = keys[i];
        }
        key *tmpright = new key[m / 2];
        for (int i = 0; i < m / 2; i++) {
            tmpright[i] = keys[m / 2 + i + 1];
        }
        key midkey = keys[mid];
        midkey.right = new BtreeNode(m, tmpright, this);
        midkey.left = new BtreeNode(m, tmpleft, this);
        delete[] keys;
        if (parent == nullptr) {
            size = 0;
            keys = new key[++size];
            keys[0] = midkey;
        } else
            this->parent->insertkey(midkey);
        if (this->parent->getKeys()[0].left == this)
            this->parent->getKeys()[0].left = 0;
        else
            for (int i = 0; i < parent->getSize(); i++)
                if (this->parent->getKeys()[0].right == this)
                    this->parent->getKeys()[0].right = 0;
        delete this;
    }

    BtreeNode(int m, key *keys, BtreeNode *parent) {
        this->m = m;
        this->keys = keys;
        size = m / 2;
        this->parent = parent;
        isleaf = 1;
    }

public:

    ~BtreeNode() {
        delete[]keys;
        delete parent;
    }

    BtreeNode(int m, BtreeNode *parent) {
        this->m = m;
        keys = nullptr;
        size = 0;
        this->parent = parent;
    }

    void insertval(int input) {
        key newkey;
        newkey.left = nullptr;
        newkey.right = nullptr;
        newkey.val = input;
        if (size == 0) {
            keys = new key[++size];
            keys[0] = newkey;
            return;
        }
        key *tmp = new key[++size];
        int i = 0, j = 0;
        for (; j < size - 1; i++, j++) {
            if (keys[i].val > input) {
                tmp[j++] = newkey;
            }
            tmp[j] = keys[i];
        }
        if (j > i) {
            tmp[size - 1] = keys[size - 2];
        } else
            tmp[size - 1] = newkey;

        for (int i = 0; i < size; i++) {
            cout << (tmp[i].left == nullptr) << ' ' << (tmp[i].right == nullptr) << '\n';
        }
        keys = tmp;
        if (size == m)
            split();
    }

    void insertkey(key newkey) {
        if (size == 0) {
            keys = new key[++size];
            keys[0] = newkey;
            return;
        }
        key *tmp = new key[++size];
        int i = 0, j = 0;
        for (; j < size - 1; i++, j++) {
            if (keys[i].val > newkey.val) {
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
        if (size == m)
            split();
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
    if (node != nullptr) {
        printNode(node->getKeys()[0].left);
        for (int i = 0; i < node->getSize(); i++) {
            cout << node->getKeys()[i].val << ' ';
            printNode(node->getKeys()[i].right);
        }
    }
}


int main() {
    BtreeNode head(3, nullptr);
    head.insertval(8);
    head.insertval(44);
    head.insertval(1);
    printNode(&head);
    return 0;
}
