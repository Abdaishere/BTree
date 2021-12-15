#include <iostream>

using namespace std;

int static caat = 0;

template<class T, int U>
class BTree {

    class key {
    public:
        T val;
        BTree *right, *left;
    } *keys;

    BTree *parent;
    int size;
    bool isleaf;
    int m = U;

    void split() {
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

        size = 0;
        if (parent == nullptr) {
            midkey.right = new BTree(tmpright, this);
            midkey.left = new BTree(tmpleft, this);
            isleaf = 0;
            keys = new key[++size];
            keys[0] = midkey;
        } else {
            midkey.right = new BTree(tmpright, parent);
            midkey.left = new BTree(tmpleft, parent);
            parent->insertkey(midkey);
            delete[]keys;
        }
    }

    BTree(key *keys, BTree *parent) {
        size = m / 2;
        isleaf = 1;
        for (int i = 0; i < size; i++) {
            if (keys[i].left != NULL) {
                keys[i].left->parent = this;
                isleaf = 0;
            }
            if (keys[i].right != NULL) {
                keys[i].right->parent = this;
                isleaf = 0;
            }
        }
        this->keys = keys;
        this->parent = parent;
    }

public:

    BTree(BTree *parent) {
        keys = nullptr;
        size = 0;
        isleaf = 1;
        if (parent != nullptr)
            parent->isleaf = 0;
        this->parent = parent;
    }

    void insertval(T input) {
        if (!this->isleaf)
            throw "cannot insert value in a none leaf node";
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
            if (j == i && keys[i].val > input) {
                tmp[j++] = newkey;
            }
            tmp[j] = keys[i];
        }
        if (j > i) {
            tmp[size - 1] = keys[size - 2];
        } else {
            tmp[size - 1] = newkey;
        }

        keys = tmp;
        if (size == m) {
            split();
        }
    }

    void Insert(T input) {
        BTree *curr = this;
        while (!curr->isleaf) {
            bool found = 0;
            for (int i = 0; i < curr->size; i++) {
                if (curr->keys[i].val > input) {
                    curr = curr->keys[i].left;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                curr = curr->keys[curr->size - 1].right;
            }
        }
        curr->insertval(input);
    }

    void insertkey(key newkey) {
        if (size == 0) {
            keys = new key[++size];
            keys[0] = newkey;
            return;
        }
        key *tmp = new key[++size];
        if (keys[0].val > newkey.val) {
            tmp[0] = newkey;
            for (int i = 1; i < size; i++) {
                tmp[i] = keys[i - 1];
            }
            tmp[1].left = tmp[0].right;
        } else if (keys[size - 2].val < newkey.val) {
            for (int i = 0; i < size - 1; i++) {
                tmp[i] = keys[i];
            }
            tmp[size - 1] = newkey;
            tmp[size - 2].right = tmp[size - 1].left;
        } else {
            int j = 0, i = 0;
            bool found = 0;
            for (; j < size; j++, i++) {
                if (j == i && keys[i].val > newkey.val) {
                    tmp[j++] = newkey;
                    tmp[i - 1].right = tmp[i].left;
                    found = 1;
                }
                tmp[j] = keys[i];
                if (found) {
                    found = 0;
                    tmp[j].left = tmp[i].right;
                }
            }
        }

        keys = tmp;
        if (size == m) {
            split();
        }
    }

    key *getKeys() const {
        return keys;
    }

    T getfrontkey() {
        return keys[0].val;
    }

    T getbackkey() {
        return keys[size - 1].val;
    }

    int getSize() const {
        return size;
    }


    bool getIsleaf() const {
        return isleaf;
    }

    void Print() {
        caat = 0;
        PrintNode(this);
    }


    void PrintNodeinorder(BTree *node) {
        if (!node->getIsleaf()) {
            PrintNodeinorder(node->getKeys()[0].left);
            for (int i = 0; i < node->getSize(); i++) {
                cout << node->getKeys()[i].val << ", "[i == node->getSize() - 1];
                PrintNodeinorder(node->getKeys()[i].right);
            }
        } else {
            for (int i = 0; i < node->getSize(); i++) {
                cout << node->getKeys()[i].val << ", "[i == node->getSize() - 1];
            }
        }
    }

    void PrintNode(BTree *node) {
        cout << cattt(caat++);
        for (int i = 0; i < node->getSize(); i++) {
            cout << node->getKeys()[i].val << ",\n"[i == node->getSize() - 1];
        }
        if (!node->getIsleaf()) {
            PrintNode(node->getKeys()[0].left);
            for (int i = 0; i < node->getSize(); i++) {
                PrintNode(node->getKeys()[i].right);
            }
        }
        caat--;
    }

    BTree() {
        keys = nullptr;
        size = 0;
        isleaf = 1;
        this->parent = nullptr;
    }

    string cattt(int i) {
        string catt = "";
        while (i--) {
            catt += ' ';
        }
        return catt;
    }
};

int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print(); // Should output the following on the screen:

    /*
    1,4
      0
      2,3
      5
    */

    // Construct a BTree of order 5, which stores char data
    BTree<char,5> t;

    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

    t.Print(); // Should output the following on the screen:

    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */

    return 0;
}
