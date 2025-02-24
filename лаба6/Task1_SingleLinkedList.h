#ifndef TASK1_SINGLELINKEDLIST_H
#define TASK1_SINGLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class SingleLinkedList {
private:
    struct Node {
        T data;
        Node* next;
    };
    Node* head;

public:
    SingleLinkedList() : head(nullptr) {}

    ~SingleLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод добавления элемента в конец списка
    void add(const T& value) {
        Node* newNode = new Node{ value, nullptr };
        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) temp = temp->next;

        temp->next = newNode;
    }

    // Метод удаления элемента по значению
    void remove(const T& value) {
        if (!head) throw runtime_error("Список пуст. Удаление невозможно.");

        // Если удаляемый элемент находится в начале списка
        if (head->data == value) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            return;
        }

        // Поиск элемента и его удаление
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }

        if (!current->next) throw runtime_error("Элемент не найден в списке.");

        Node* toDelete = current->next;
        current->next = current->next->next;
        delete toDelete;
    }

    // Перемещение первого элемента в конец списка
    void moveFirstToEnd() {
        if (!head || !head->next) return; // Если список пустой или из одного элемента

        Node* first = head; // Сохраняем указатель на первый элемент
        head = head->next; // Смещаем голову на второй элемент

        Node* temp = head; // Ищем последний элемент
        while (temp->next) temp = temp->next;

        temp->next = first; // Присоединяем первый элемент к концу списка
        first->next = nullptr; // Устанавливаем его "следующий" указатель в nullptr
    }

    // Вывод списка на экран
    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

#endif
