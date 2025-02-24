#include "tests.h"
#include "Task1_SingleLinkedList.h"
#include "Task2_DoubleLinkedList.h"
#include "Task3_UniqueList.h"
#include "Task4_TextProcessor.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>

using namespace std;

void testTask1() {
    cout << "Тестирование задания 1: Перенос первого элемента в конец списка и работа с методами добавления/удаления." << endl;

    SingleLinkedList<int> list;

    // тест добавления элементов
    list.add(10);
    list.add(20);
    list.add(30);

    cout << "Исходный список: ";
    list.print();

    // тест переноса первого элемента в конец
    list.moveFirstToEnd();
    cout << "Список после переноса первого элемента в конец: ";
    list.print();

    // тест удаления элемента
    cout << "Удаляем элемент 20." << endl;
    list.remove(20);

    cout << "Список после удаления элемента 20: ";
    list.print();

    try {
        cout << "Пытаемся удалить элемент 50 (не существует)." << endl;
        list.remove(50); // должно выбросить исключение
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    cout << "\n=== Работа с другим типом данных ===" << endl;

    SingleLinkedList<char> list2;

    // тест добавления символов
    list2.add('a');
    list2.add('b');
    list2.add('c');
    list2.add('d');

    cout << "Исходный список: ";
    list2.print();

    // тест переноса первого элемента в конец
    list2.moveFirstToEnd();
    cout << "Список после переноса первого элемента в конец: ";
    list2.print();

    // тест удаления символа
    cout << "Удаляем символ 'b'." << endl;
    list2.remove('b');

    cout << "Список после удаления символа 'b': ";
    list2.print();

    try {
        cout << "Пытаемся удалить символ 'z' (не существует)." << endl;
        list2.remove('z'); // должно выбросить исключение
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}


void testTask2() {
    cout << "2. Удаление элементов с одинаковыми соседями." << endl;

    DoubleLinkedList<int> list;

    // тест 1
    list.add(4);
    list.add(2);
    list.add(1);
    list.add(2);
    list.add(4);

    cout << "Исходный список: ";
    list.print();

    list.removeWithIdenticalNeighbors();
    cout << "Список после удаления элементов с одинаковыми соседями: ";
    list.print();
    cout << endl;

    // тест 2. более сложный случай
    DoubleLinkedList<int> list2;
    list2.add(1);
    list2.add(4);
    list2.add(3);
    list2.add(4);
    list2.add(5);
    list2.add(6);
    list2.add(7);
    list2.add(6);
    list2.add(9);

    cout << "Исходный список: ";
    list2.print();

    list2.removeWithIdenticalNeighbors();
    cout << "Список после удаления элементов с одинаковыми соседями: ";
    list2.print();
    cout << endl;

    // тест 3. работа с символами
    DoubleLinkedList<char> list3;
    list3.add('a');
    list3.add('b');
    list3.add('c');
    list3.add('d');
    list3.add('c');
    list3.add('a');
    list3.add('d');
    list3.add('a');
    list3.add('b');

    cout << "Исходный список: ";
    list3.print();

    list3.removeWithIdenticalNeighbors();
    cout << "Список после удаления элементов с одинаковыми соседями: ";
    list3.print();
}



void testTask3() {
    cout << ". Работа с уникальными списками." << endl;

    UniqueList<string> factory1, factory2, factory3;

    // добавляем элементы в списки фабрик
    factory1.add("ФабрикаA");
    factory1.add("ФабрикаB");

    factory2.add("ФабрикаB");
    factory2.add("ФабрикаC");

    factory3.add("ФабрикаA");
    factory3.add("ФабрикаD");

    cout << "Список фабрики 1: ";
    factory1.print();

    cout << "Список фабрики 2: ";
    factory2.print();

    cout << "Список фабрики 3: ";
    factory3.print();

    // объединение всех фабрик
    UniqueList<string> allFactories = factory1.Union(factory2).Union(factory3);

    cout << "Объединенный список всех фабрик: ";
    allFactories.print();

    // пересечение фабрик 1 и 3
    UniqueList<string> commonFactories = factory1.Intersect(factory3);

    cout << "Общие элементы между фабрикой 1 и фабрикой 3: ";
    commonFactories.print();

    // исключение элементов фабрики 2 из объединенного списка
    UniqueList<string> exceptFactories = allFactories.Except(factory2);

    cout << "Список после исключения элементов фабрики 2: ";
    exceptFactories.print();

    // проверка на наличие элемента
    cout << "ФабрикаA присутствует в объединенном списке? "
        << (allFactories.Contains("ФабрикаA") ? "Да" : "Нет") << endl;
}


void testTask4() {
    wcout << L"4. Обработка текста из файла." << endl;

    const wstring filename = L"text.txt";

    // проверяем наличие файла и создаем его, если он отсутствует
    wifstream file(filename);
    if (!file.is_open()) {
        wcout << L"Файл text.txt отсутствует. Создаем файл с тестовыми данными..." << endl;
        wofstream outFile(filename);
        if (!outFile) {
            wcerr << L"Ошибка при создании файла text.txt!" << endl;
            return;
        }

        // добавляем тестовые данные в файл
        outFile.imbue(locale("ru_RU.UTF-8"));
        outFile << L"Пример текста для теста\n"
            L"Слова на проверку согласных\n"
            L"Глухие согласные буквы\n";
        outFile.close();
        wcout << L"Файл text.txt успешно создан." << endl;
    }

    try {
        TextProcessor processor(filename);
        processor.processText();
    }
    catch (const exception& e) {
        cerr << "Ошибка при обработке текста: " << e.what() << endl;
    }
}