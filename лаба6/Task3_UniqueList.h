#ifndef TASK3_UNIQUELIST_H
#define TASK3_UNIQUELIST_H

#include <iostream>
#include <set>
#include <stdexcept>

using namespace std;

template <typename T>
class UniqueList {
private:
    set<T> elements;

public:
    void add(const T& value) {
        elements.insert(value); // Автоматически игнорирует дубли
    }

    void remove(const T& value) {
        elements.erase(value);
    }

    UniqueList Union(const UniqueList& other) const {
        UniqueList result = *this;
        result.elements.insert(other.elements.begin(), other.elements.end());
        return result;
    }

    UniqueList Except(const UniqueList& other) const {
        UniqueList result = *this;
        for (const auto& elem : other.elements) {
            result.elements.erase(elem);
        }
        return result;
    }

    UniqueList Intersect(const UniqueList& other) const {
        UniqueList result;
        for (const auto& elem : elements) {
            if (other.elements.count(elem)) {
                result.add(elem);
            }
        }
        return result;
    }

    bool Contains(const T& value) const {
        return elements.count(value) > 0;
    }

    void print() const {
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

#endif
