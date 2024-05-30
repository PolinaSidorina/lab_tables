#include "iostream"
#include <list>
#include <string>
#include "Polinom.h"
using namespace std;

class LinList {
private:
    list<pair<string, Polinom>> table;
public:
    void addP(const string& _name, Polinom& _pol);
    void removeP(const string& _name);
    Polinom* findP(const string& _name);
    void printTable();
};