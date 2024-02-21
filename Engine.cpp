#include <iostream>
using namespace std;

struct tovar {
    int id;
    int q;
    tovar* next;
};

void AddLast(tovar*& shoes, int id, int q) {
    tovar* newtovar = new tovar;
    newtovar->id = id;
    newtovar->q = q;
    newtovar->next = NULL;

    if (shoes == NULL) {
        shoes = newtovar;
        return;
    }

    tovar* tmp = shoes;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = newtovar;
}

void AddFirst(tovar*& shoes, int id, int q) {
    tovar* newtovar = new tovar;
    newtovar->id = id;
    newtovar->q = q;
    newtovar->next = shoes;
    shoes = newtovar;
}

void AddBeforeLast(tovar*& shoes, int id, int q) {
    if (shoes == NULL || shoes->next == NULL) {
        AddFirst(shoes, id, q);
        return;
    }

    tovar* newtovar = new tovar;
    newtovar->id = id;
    newtovar->q = q;

    tovar* tmp = shoes;
    while (tmp->next->next != NULL) {
        tmp = tmp->next;
    }
    newtovar->next = tmp->next;
    tmp->next = newtovar;
}

void AddBeforeFirst(tovar*& shoes, int id, int q) {
    if (shoes == NULL) {
        AddFirst(shoes, id, q);
        return;
    }

    tovar* newtovar = new tovar;
    newtovar->id = id;
    newtovar->q = q;
    newtovar->next = shoes->next;
    shoes->next = newtovar;
}

void PrintList(tovar* shoes) {
    if (shoes == NULL) {
        cout << "This list is empty" << endl;
        return;
    }
    tovar* tmp = shoes;
    while (tmp != NULL) {
        cout << "Tovar id: " << tmp->id << ", q: " << tmp->q << endl;
        tmp = tmp->next;
    }
}

int main() {
    tovar* head = NULL;

    int id1 = 1;
    int q1 = 5;

    int id2 = 2;
    int q2 = 11;

    PrintList(head);
    cout << "++++++++++++++++++++++++++++++++++\n";

    AddLast(head, id1, q1);
    PrintList(head);
    cout << "===================================\n";

    AddLast(head, id2, q2);
    PrintList(head);
    cout << "===================================\n";

    AddFirst(head, 3, 7);
    PrintList(head);
    cout << "===================================\n";

    AddBeforeLast(head, 4, 8);
    PrintList(head);
    cout << "===================================\n";

    AddBeforeFirst(head, 0, 10);
    PrintList(head);

    return 0;
}