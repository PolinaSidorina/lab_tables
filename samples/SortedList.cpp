#include "SortedList.h"

void SortedList::addP(const string& _name, Polinom& _pol) {
    for (auto i = table.begin(); i != table.end(); i++) {
        if (i->first == _name) {
            i->second = _pol;
            return;
        }
        else if (i->first > _name) {
            table.insert(i, make_pair(_name, _pol));
            return;
        }
    }
    table.emplace_back(_name, _pol);
}
void SortedList::removeP(const string& _name) {
    for (auto i = table.begin(); i != table.end(); i++) {
        if (i->first == _name) {
            table.erase(i);
            return;
        }
    }
}
Polinom* SortedList::findP(const string& _name) {
    for (auto& i : table) {
        if (i.first == _name) return &i.second;
    }
    return nullptr;
}
void SortedList::printTable() {
    for (auto& i : table) {
        cout << i.first << ": ";
        i.second.toString();//
        cout << endl;
    }
}