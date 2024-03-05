#include <iostream>
#include <string>
using namespace std;

// ���������, ����������� ������� ������
struct Element {
    string name;
    int age;
    double salary;
    Element* next; 
};

// ������� ��� ���������� �������� � ������ ������
void AddFirst(Element*& head, string name, int age, double salary) {
    Element* newElement = new Element;
    newElement->name = name;
    newElement->age = age;
    newElement->salary = salary;
    newElement->next = head;
    head = newElement;
}

// ������� ��� ���������� �������� � ����� ������
void AddLast(Element*& head, string name, int age, double salary) {
    Element* newElement = new Element;
    newElement->name = name;
    newElement->age = age;
    newElement->salary = salary;
    newElement->next = NULL; 

    if (head == NULL) {
        head = newElement;
        return;
    }

    // ������� ��������� ������� � ������
    Element* tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = newElement;
}

// ������� ��� ���������� �������� � ������ ����� ��������� ��������
void AddAfter(Element* head, string targetName, string newName, int newAge, double newSalary) {
    Element* current = head;
    while (current != NULL) {
        if (current->name == targetName) {
            Element* newElement = new Element;
            newElement->name = newName;
            newElement->age = newAge;
            newElement->salary = newSalary;
            newElement->next = current->next;
            current->next = newElement;
            return;
        }
        current = current->next;
    }
    cout << "Element with name " << targetName << " not found" << endl;
}

// ������� ��� ���������� �������� � ������ ����� �������� ���������
void AddBefore(Element*& head, string targetName, string newName, int newAge, double newSalary) {
    if (head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    if (head->name == targetName) {
        AddFirst(head, newName, newAge, newSalary);
        return;
    }

    Element* prev = NULL;
    Element* current = head;
    while (current != NULL && current->name != targetName) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "Element with name " << targetName << " not found" << endl;
        return;
    }

    Element* newElement = new Element;
    newElement->name = newName;
    newElement->age = newAge;
    newElement->salary = newSalary;
    newElement->next = current;
    prev->next = newElement;
}

// ������� ��� �������� �� ������ �������� � �������� ������
void RemoveByName(Element*& head, string targetName) {
    if (head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    if (head->name == targetName) {
        Element* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Element* prev = NULL;
    Element* current = head;
    while (current != NULL && current->name != targetName) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        cout << "Element with name " << targetName << " not found" << endl;
        return;
    }

    prev->next = current->next;
    delete current;
}

// ������� ��� ������ ���������� ������ �� �����
void PrintList(Element* head) {
    if (head == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    Element* current = head;
    while (current != NULL) {
        cout << "Name: " << current->name << ", Age: " << current->age << ", Salary: " << current->salary << endl;
        current = current->next;
    }
}

int main() {
    Element* head = NULL;

    // ���������� ��������� � ������
    AddLast(head, "Alice", 25, 35000.0);
    AddLast(head, "Bob", 30, 42000.0);
    AddFirst(head, "Charlie", 22, 30000.0);

    // ����� ���������� ������ �� �����
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // ���������� �������� ����� ���������� ��������
    AddAfter(head, "Bob", "David", 27, 40000.0);

    // ����� ���������� ������ �� ����� ����� ���������� ��������
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // ���������� �������� ����� ��������� ���������
    AddBefore(head, "Bob", "Eva", 29, 45000.0);

    // ����� ���������� ������ �� ����� ����� ���������� Eva
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // �������� �������� �� �����
    RemoveByName(head, "Charlie");

    // ����� ���������� ������ �� ����� ����� �������� Charlie
    cout << "\n----------------------------------------\n";
    PrintList(head);

    return 0;
}