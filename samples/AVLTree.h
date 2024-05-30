#include <string>
#include "Polinom.h"
using namespace std;

class AVLTreeNode {
public:
    string key;
    Polinom pol;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;
    AVLTreeNode(const string& _key, Polinom& _pol) {
        key = _key;
        pol = _pol;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
class AVLTree {
private:
    AVLTreeNode* root;
    int height(AVLTreeNode* node);
    int balance(AVLTreeNode* node);
    AVLTreeNode* right(AVLTreeNode* y);
    AVLTreeNode* left(AVLTreeNode* x);
    AVLTreeNode* minNode(AVLTreeNode* node);
    AVLTreeNode* insert(AVLTreeNode* node, const string& key, Polinom& value);
    AVLTreeNode* remove(AVLTreeNode* node, const string& key);
    AVLTreeNode* find(AVLTreeNode* node, const string& key);
    void print(AVLTreeNode* node);
public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void addP(const string& key, Polinom& pol);
    void removeP(const string& key);
    Polinom* findP(const string& key);
    void print();
};