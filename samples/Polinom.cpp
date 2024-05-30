#include <valarray>
#include "Polinom.h"

Polinom::~Polinom() {
    head = nullptr;
}
void Polinom::add(int c, int deg) {
    Monom* nMonom = new Monom(c, deg);
    if (head == nullptr || deg > head->p) {
        nMonom->next = head;
        head = nMonom;
    }
    else {
        Monom* tmp = head;
        Monom* pr = nullptr;
        while (tmp != nullptr && tmp->p > deg) {
            pr = tmp;
            tmp = tmp->next;
        }
        if (tmp != nullptr && tmp->p == deg) {
            tmp->coeff += c;
            if (tmp->coeff == 0) {
                if (pr == nullptr) head = tmp->next;
                else pr->next = tmp->next;
            }
        }
        else {
            nMonom->next = tmp;
            if (pr == nullptr) head = nMonom;
            else pr->next = nMonom;
        }
    }
}
Polinom::Polinom(string s) {
    head = nullptr;
    if (s == "0") return;
    int c = 0;
    int sign = 1;
    string num_str = "";
    string degs = "000";
    for (int i = 0; i <= s.length(); i++) {
        if (i == s.length() || s[i] == '+' || s[i] == '-') {
            if (!num_str.empty()) {
                c = stoi(num_str) * sign;
                add(c, stoi(degs));
                num_str = "";
                degs = "000";
            }
            if (i < s.length() && s[i] == '-')  sign = -1;
            else sign = 1;
        }
        else if (isdigit(s[i])) num_str += s[i];
        else if (s[i] == 'x' || s[i] == 'y' || s[i] == 'z') {
            if (num_str.empty() && (i == 0 || s[i - 1] != '^')) num_str = "1";
            size_t pos;
            if (s[i] == 'x')  pos = 0;
            else if (s[i] == 'y') pos = 1;
            else  pos = 2;
            i++;
            if (i < s.length() && s[i] == '^') {
                i++;
                string exp = "";
                while (i < s.length() && isdigit(s[i])) exp += s[i++];
                i--;
                if (exp.empty()) degs[pos] = '1';
                else degs[pos] = exp[0];
            }
            else {
                degs[pos] = '1';
                i--;
            }
        }
    }
}
Polinom::Monom& Polinom::Iterator::operator*() {
    return *cur;
}
Polinom::Iterator& Polinom::Iterator::operator++() {
    if (cur) cur = cur->next;
    return *this;
}
bool Polinom::Iterator::operator!=(const Iterator& other) {
    return cur != other.cur;
}
Polinom::Iterator Polinom::begin() {
    return Iterator(head);
}
Polinom::Iterator Polinom::end() {
    return Iterator(nullptr);
}
void Polinom::toString() {
    if (head == nullptr) {
        cout << "0";
        return;
    }
    for (auto i = begin(); i != end(); ++i) {
        Monom monom = *i;
        if (i != begin() && monom.coeff > 0) cout << "+";
        if (monom.coeff != 1)  cout << monom.coeff;
        int degs = monom.p;
        int degX = degs / 100;
        int degY = (degs - degX * 100) / 10;
        int degZ = degs % 10;
        if (degX > 0) {
            if (degX == 1) cout << "x";
            else cout << "x^" << degX;
        }
        if (degY > 0) {
            if (degY == 1) cout << "y";
            else cout << "y^" << degY;
        }
        if (degZ > 0) {
            if (degZ == 1) cout << "z";
            else cout << "z^" << degZ;
        }
    }
}
Polinom Polinom::operator+(const Polinom& other) const {
    Polinom res;
    Monom* mon1 = this->head;
    Monom* mon2 = other.head;
    while (mon1 != nullptr || mon2 != nullptr) {
        if (mon1 == nullptr) {
            res.add(mon2->coeff, mon2->p);
            mon2 = mon2->next;
        }
        else if (mon2 == nullptr) {
            res.add(mon1->coeff, mon1->p);
            mon1 = mon1->next;
        }
        else if (mon1->p == mon2->p) {
            int newC = mon1->p + mon2->p;
            if (newC != 0)  res.add(newC, mon1->p);
            mon1 = mon1->next;
            mon2 = mon2->next;
        }
        else if (mon1->p > mon2->p) {
            res.add(mon1->coeff, mon1->p);
            mon1 = mon1->next;
        }
        else {
            res.add(mon2->coeff, mon2->p);
            mon2 = mon2->next;
        }
    }
    return res;
}
Polinom Polinom::operator*(int c) const {
    Polinom res;
    if (c == 0) return res;
    for (Monom* cur = head; cur != nullptr; cur = cur->next) res.add((cur->coeff) * c, cur->p);
    return res;
}
Polinom Polinom::operator*(const Polinom& other) const {
    Polinom res;
    for (Monom* cur1 = head; cur1 != nullptr; cur1 = cur1->next) {
        for (Monom* cur2 = other.head; cur2 != nullptr; cur2 = cur2->next) res.add((cur1->coeff) * (cur2->coeff), (cur1->p) + (cur2->p));
    }
    return res;
}
Polinom Polinom::operator-(const Polinom& other) const {
    Polinom res;
    Polinom ot = other * (-1);
    res = this->operator+(ot);
    return res;
}
bool Polinom::operator==(const Polinom& other) const {
    Monom* cur1 = head;
    Monom* cur2 = other.head;
    while (cur1 != nullptr && cur2 != nullptr) {
        if (((cur1->p) != (cur2->p)) || ((cur1->coeff) != (cur2->coeff))) return false;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    if (cur1 == nullptr && cur2 == nullptr) return true;
    return false;
}
double Polinom::calculate(double x, double y, double z) const {
    double result = 0;
    Monom* current = head;
    while (current != nullptr) {
        int termValue = current->coeff;
        termValue *= pow(x, (current->p) / 100);
        termValue *= pow(y, (current->p % 100) / 10);
        termValue *= pow(z, (current->p % 10));
        result += termValue;
        current = current->next;
    }
    return result;
}
