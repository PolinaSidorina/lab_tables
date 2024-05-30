#include "AVLTree.h"
#include <iostream>
using namespace std;

int AVLTree::height(AVLTreeNode* node) {
    if (node == nullptr)  return 0;
    else  return node->height;
}
int AVLTree::balance(AVLTreeNode* node) {
    if (node == nullptr)  return 0;
    else return height(node->left) - height(node->right);
}
AVLTreeNode* AVLTree::right(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}
AVLTreeNode* AVLTree::left(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}
AVLTreeNode* AVLTree::insert(AVLTreeNode* node, const string& _key, Polinom& _pol) {
    if (!node) return new AVLTreeNode(_key, _pol);
    if (_key < node->key) node->left = insert(node->left, _key, _pol);
    else if (_key > node->key)  node->right = insert(node->right, _key, _pol);
    else {
        node->pol = _pol;
        return node;
    }
    node->height = 1 + max(height(node->left), height(node->right));
    int balan = balance(node);
    if (balan > 1 && _key < node->left->key) return right(node);
    if (balan < -1 && _key > node->right->key) return left(node);
    if (balan > 1 && _key > node->left->key) {
        node->left = left(node->left);
        return right(node);
    }
    if (balan < -1 && _key < node->right->key) {
        node->right = right(node->right);
        return left(node);
    }
    return node;
}
AVLTreeNode* AVLTree::minNode(AVLTreeNode* node) {
    AVLTreeNode* current = node;
    while (current->left != nullptr) current = current->left;
    return current;
}
AVLTreeNode* AVLTree::remove(AVLTreeNode* node, const string& _key) {
    if (!node) return node;
    if (_key < node->key)  node->left = remove(node->left, _key);
    else if (_key > node->key) node->right = remove(node->right, _key);
    else {
        if (!node->left || !node->right) {
            AVLTreeNode* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else  *node = *temp;
            delete temp;
        }
        else {
            AVLTreeNode* temp = minNode(node->right);
            node->key = temp->key;
            node->pol = temp->pol;
            node->right = remove(node->right, temp->key);
        }
    }
    if (!node) return node;
    node->height = 1 + max(height(node->left), height(node->right));
    int balan = balance(node);
    if (balan > 1 && balance(node->left) >= 0)  return right(node);
    if (balan > 1 && balance(node->left) < 0) {
        node->left = left(node->left);
        return right(node);
    }
    if (balan < -1 && balance(node->right) <= 0) return left(node);
    if (balan < -1 && balance(node->right) > 0) {
        node->right = right(node->right);
        return left(node);
    }
    return node;
}
AVLTreeNode* AVLTree::find(AVLTreeNode* node, const string& _key) {
    while (node != nullptr && _key != node->key) {
        if (_key < node->key) node = node->left;
        else node = node->right;
    }
    return node;
}
void AVLTree::print(AVLTreeNode* node) {
    if (node != nullptr) {
        print(node->left);
        cout << node->key << ": ";
        node->pol.toString();//
        cout << endl;
        print(node->right);
    }
}
void AVLTree::addP(const std::string& _key, Polinom& _pol) {
    root = insert(root, _key, _pol);
}

void AVLTree::removeP(const string& _key) {
    root = remove(root, _key);
}
Polinom* AVLTree::findP(const string& _key) {
    AVLTreeNode* node = find(root, _key);
    if (node != nullptr) return &node->pol;
    else return nullptr;
}
void AVLTree::print() {
    print(root);
}
void deleteTree(AVLTreeNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}
AVLTree::~AVLTree() {
    deleteTree(root);
}
