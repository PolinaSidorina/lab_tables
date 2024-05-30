#include "LinList.h"

void LinList::addP(const string& _name, Polinom& _pol) {
    for (auto& i : table) {
        if (i.first == _name) {
            i.second = _pol;
            return;
        }
    }
    table.emplace_back(_name, _pol);
}
void LinList::removeP(const string& _name) {
    for (auto i = table.begin(); i != table.end(); i++) {
        if (i->first == _name) {
            table.erase(i);
            return;
        }
    }
}
Polinom* LinList::findP(const string& _name) {
    for (auto& i : table) {
        if (i.first == _name) return &i.second;
    }
    return nullptr;
}
void LinList::printTable() {
    for (auto& i : table) {
        cout << i.first << ": ";
        i.second.toString();//
        cout << endl;
    }
}
