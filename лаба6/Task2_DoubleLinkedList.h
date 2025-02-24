#ifndef TASK2_DOUBLELINKEDLIST_H
#define TASK2_DOUBLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoubleLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Метод добавления элемента в конец списка
    void add(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    // Метод удаления элемента по значению
    void remove(const T& value) {
        if (!head) throw runtime_error("Список пуст. Удаление невозможно.");

        Node* current = head;

        while (current && current->data != value) {
            current = current->next;
        }

        if (!current) throw runtime_error("Элемент не найден в списке.");

        // Если удаляемый элемент — голова
        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr; // Если список стал пустым
            delete current;
            return;
        }

        // Если удаляемый элемент — хвост
        if (current == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
            delete current;
            return;
        }

        // Удаление элемента из середины
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
    }

    // Метод удаления элементов с одинаковыми соседями
    void removeWithIdenticalNeighbors() {
        if (!head || !head->next || !head->next->next) return; // Список слишком короткий

        Node* current = head->next;

        while (current && current->next) {
            if (current->prev->data == current->next->data) {
                Node* toDelete = current;

                // Переподключение соседей
                current->prev->next = current->next;
                current->next->prev = current->prev;

                current = current->next; // Переходим к следующему элементу
                delete toDelete;         // Удаляем текущий элемент
            }
            else {
                current = current->next; // Переходим к следующему элементу
            }
        }
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
