#include <iostream>
#include <string>
using namespace std;

// Структура, описывающая элемент списка
struct Element {
    string name;
    int age;
    double salary;
    Element* next; 
};

// Функция для добавления элемента в начало списка
void AddFirst(Element*& head, string name, int age, double salary) {
    Element* newElement = new Element;
    newElement->name = name;
    newElement->age = age;
    newElement->salary = salary;
    newElement->next = head;
    head = newElement;
}

// Функция для добавления элемента в конец списка
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

    // Находим последний элемент в списке
    Element* tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    tmp->next = newElement;
}

// Функция для добавления элемента в список после заданного элемента
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

// Функция для добавления элемента в список перед заданным элементом
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

// Функция для удаления из списка элемента с заданным именем
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

// Функция для вывода содержания списка на экран
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

    // Добавление элементов в список
    AddLast(head, "Alice", 25, 35000.0);
    AddLast(head, "Bob", 30, 42000.0);
    AddFirst(head, "Charlie", 22, 30000.0);

    // Вывод содержания списка на экран
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // Добавление элемента после указанного элемента
    AddAfter(head, "Bob", "David", 27, 40000.0);

    // Вывод содержания списка на экран после добавления элемента
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // Добавление элемента перед указанным элементом
    AddBefore(head, "Bob", "Eva", 29, 45000.0);

    // Вывод содержания списка на экран после добавления Eva
    cout << "\n----------------------------------------\n";
    PrintList(head);

    // Удаление элемента по имени
    RemoveByName(head, "Charlie");

    // Вывод содержания списка на экран после удаления Charlie
    cout << "\n----------------------------------------\n";
    PrintList(head);

    return 0;
}