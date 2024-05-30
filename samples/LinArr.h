#include "iostream"
#include <string>
#include "Polinom.h"

using namespace std;
class LinArr {
private:
    pair<string,Polinom> table[100];
    int size;
public:
    LinArr();
    void addP(const string& _name, Polinom& _pol);
    void removeP(const string& _name);
    Polinom* findP(const string& _name);
    void printTable();
};
