#include "LinArr.h"
#include "LinList.h"
#include "SortedList.h"
#include "AVLTree.h"
#include "HashTable.h"

void addP(const string& _key, Polinom& _pol, LinArr& la, LinList& ll, SortedList& sl,AVLTree& avl, HashTable<Hash1>& ht1, HashTable<Hash2>& ht2) {
    la.addP(_key, _pol);
    ll.addP(_key, _pol);
    sl.addP(_key, _pol);
    avl.addP(_key, _pol);
    ht1.addP(_key, _pol);
    ht2.addP(_key, _pol);
}

void removeP(const string& _key, LinArr& la, LinList& ll, SortedList& sl, AVLTree& avl,HashTable<Hash1>& ht1, HashTable<Hash2>& ht2) {
    la.removeP(_key);
    ll.removeP(_key);
    sl.removeP(_key);
    avl.removeP(_key);
    ht1.removeP(_key);
    ht2.removeP(_key);
}
Polinom* findP(const string& _key, int tableType, LinArr& la, LinList& ll, SortedList& sl, AVLTree& avl,HashTable<Hash1>& ht1, HashTable<Hash2>& ht2) {
    switch (tableType) {
    case 1:
        return la.findP(_key);
    case 2:
        return ll.findP(_key);
    case 3:
        return sl.findP(_key);
    case 4:
        return avl.findP(_key);
    case 5:
        return ht1.findP(_key);
    case 6:
        return ht2.findP(_key);
    default:
        return nullptr;
    }
}
void printTable(int tableType, LinArr& la, LinList& ll, SortedList& sl, AVLTree& avl, HashTable<Hash1>& ht1,HashTable<Hash2>& ht2) {
    switch (tableType) {
    case 1:
        la.printTable();
        break;
    case 2:
        ll.printTable();
        break;
    case 3:
        sl.printTable();
        break;
    case 4:
        avl.print();
        break;
    case 5:
        ht1.print();
        break;
    case 6:
        ht2.print();
        break;
    default:
        break;
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    LinArr la;
    LinList ll;
    SortedList sl;
    AVLTree avl;
    HashTable<Hash1> ht1;
    HashTable<Hash2> ht2;
    while (true) {
        cout << "1. �������� �������\n2. ������� �������\n3. ����� �������\n4. �������� �������\n";
        int choice;
        cin >> choice;
        if (choice == 5) break;
        string key, str;
        Polinom* pol;
        int tableType;
        switch (choice) {
        case 1:
            cout << "������� ����:";
            cin >> key;
            cout << "������� �������:";
            cin.ignore();
            getline(cin, str);
            pol = new Polinom(str);
            addP(key, *pol, la, ll, sl, avl, ht1, ht2);
            break;
        case 2:
            cout << "������� ����:";
            cin >> key;
            removeP(key, la, ll, sl, avl, ht1, ht2);
            break;
        case 3:
            cout << "������� ����:";
            cin >> key;
            cout << "�������� ������� ��� ������ (1: �������� �� �������, 2: �������� �� ������, 3: ������������� �� �������, 4: ��� ������, 5: ���-������� 1, 6: ���-������� 2):";
            cin >> tableType;
            pol = findP(key, tableType, la, ll, sl, avl, ht1, ht2);
            if (pol) {
                cout << "����� �������:";
                pol->toString();//
                cout << endl;
            }
            else cout << "������� �� ������" << endl;
            break;
        case 4:
            cout << "�������� ������� ��� ��������� (1: �������� �� �������, 2: �������� �� ������, 3: ������������� �� �������, 4: ��� ������, 5: ���-������� 1, 6: ���-������� 2):";
            cin >> tableType;
            printTable(tableType, la, ll, sl, avl, ht1, ht2);
            break;
        default:
            cout << "������ �����" << endl;
            break;
        }
    }
    return 0;
}