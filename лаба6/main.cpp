#include <iostream>
#include <stdexcept>
#include "tests.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    while (true) {
        cout << "\n=== Меню тестов ===" << endl;
        cout << "1. Перенос первого элемента в конец списка" << endl;
        cout << "2. Удаление элементов с одинаковыми соседями" << endl;
        cout << "3. Работа с уникальными списками" << endl;
        cout << "4. Обработка текста из файла" << endl;
        cout << "5. Анализ цен на сметану (не доделано)" << endl;
        cout << "0. Выход" << endl;

        int choice;
        cout << "\nВыберите опцию: ";
        cin >> choice;

        if (cin.fail()) { // проверка на некорректный ввод
            cin.clear(); // сбрасываем состояние потока
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем буфер ввода
            cerr << "Ошибка: Введите число от 0 до 4." << endl;
            continue; // возвращаемся к началу цикла
        }

        switch (choice) {
        case 1:
            testTask1();
            break;
        case 2:
            testTask2();
            break;
        case 3:
            testTask3();
            break;
        case 4:
            testTask4();
            break;
        case 0:
            cout << "Выход из тестов." << endl;
            return 0; // завершение тестов
        default:
            cerr << "Ошибка: Нет такой опции. Попробуйте снова." << endl;
            break;
        }

        // добавляем пустую строку для удобства чтения вывода
        cout << endl;
    }

    return 0;
}

