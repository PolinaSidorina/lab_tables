#include <vector>
#include <string>
#include <list>
#include "Polinom.h"
using namespace std;

struct Hash1 {
    int operator()(const string& _key) {
        int hash = 0;
        for (char c : _key) {
            hash /= 0.5;
            hash += c;
        }
        return hash%100;
    }
};
struct Hash2 {
    int operator()(const string& _key) {
        int hash = 0;
        for (char c : _key) {
            hash *= 3;
            hash += c;
        }
        return hash%100;
    }
};
template<typename HashFunc>
class HashTable {
private:
    vector<list<pair<string, Polinom>>> table;
    HashFunc hashFunc;

public:
    HashTable() : table(100) {}
    void addP(const string& _name, Polinom& _pol) {
        for (auto& i : table[hashFunc(_name) % 100]) {
            if (i.first == _name) {
                i.second = _pol;
                return;
            }
        }
        table[hashFunc(_name) % 100].emplace_back(_name, _pol);
    }
    Polinom* findP(const string& _name) {
        for (auto& i : table[hashFunc(_name) % 100]) {
            if (i.first == _name) return &i.second;
        }
        return nullptr;
    }
    void removeP(const string& name);
    void print();
};
template<typename HashFunc>
void HashTable<HashFunc>::removeP(const string& _name) {
    for (auto i = table[hashFunc(_name) % 100].begin(); i != table[hashFunc(_name) % 100].end(); i++) {
        if (i->first == _name) {
            table[hashFunc(_name) % 100].erase(i);
            return;
        }
    }
}
template<typename HashFunc>
void HashTable<HashFunc>::print() {
    for (int i = 0; i < 100; i++) {
        if (!table[i].empty()) {
            for (auto& j : table[i]) {
                cout << j.first << ": ";
                j.second.toString();//
                cout << "; ";
            }
            cout << endl;
        }
    }
}
