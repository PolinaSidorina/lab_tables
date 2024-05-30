#include "LinArr.h"

LinArr::LinArr() :
    size(0)
{};
void LinArr::addP(const string& _name, Polinom& _pol) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == _name) {
            table[i].second = _pol;
            return;
        }
    }
    if (size < 100) {
        table[size] = make_pair(_name, _pol);
        size++;
    }
    else throw out_of_range("error");
}
void LinArr::removeP(const string& _name) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == _name) {
            for (int j = i; j < size - 1; j++) table[j] = table[j + 1];
            size--;
            return;
        }
    }
}
Polinom* LinArr::findP(const string& _name) {
    for (int i = 0; i < size; i++) {
        if (table[i].first == _name) return &table[i].second;
    }
    return nullptr;
}
void LinArr::printTable() {
    for (int i = 0; i < size; i++) {
        cout << table[i].first << ": ";
        table[i].second.toString();//
        cout << endl;
    }
}