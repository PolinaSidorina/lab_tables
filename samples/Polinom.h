#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "iostream"
#include <string>
using namespace std;

class Polinom {
private:
    struct Monom {
        int coeff;
        int p;//p-degree
        Monom* next;
        Monom(int c, int deg) {
            coeff = c;
            p = deg;
            next = nullptr;
        }
    };
    Monom* head;
public:
    Polinom(){
        head = nullptr;
    };
    Polinom(string pol);
    ~Polinom();
    void add(int c, int deg);
    class Iterator {
    private:
        Monom* cur;
    public:
        Iterator(Monom* cur = nullptr) : cur(cur) {}
        Monom& operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& other);
    };
    Iterator begin();
    Iterator end();
    void toString();
    Polinom operator+(const Polinom& other) const;
    Polinom operator-(const Polinom& other) const;
    Polinom operator*(const Polinom& other) const;
    Polinom operator*(int c) const;
    bool operator==(const Polinom& other) const;
    double calculate(double x, double y, double z) const;
};

#endif
