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
    cout << "������������ ������� 1: ������� ������� �������� � ����� ������ � ������ � �������� ����������/��������." << endl;

    SingleLinkedList<int> list;

    // ���� ���������� ���������
    list.add(10);
    list.add(20);
    list.add(30);

    cout << "�������� ������: ";
    list.print();

    // ���� �������� ������� �������� � �����
    list.moveFirstToEnd();
    cout << "������ ����� �������� ������� �������� � �����: ";
    list.print();

    // ���� �������� ��������
    cout << "������� ������� 20." << endl;
    list.remove(20);

    cout << "������ ����� �������� �������� 20: ";
    list.print();

    try {
        cout << "�������� ������� ������� 50 (�� ����������)." << endl;
        list.remove(50); // ������ ��������� ����������
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
    }

    cout << "\n=== ������ � ������ ����� ������ ===" << endl;

    SingleLinkedList<char> list2;

    // ���� ���������� ��������
    list2.add('a');
    list2.add('b');
    list2.add('c');
    list2.add('d');

    cout << "�������� ������: ";
    list2.print();

    // ���� �������� ������� �������� � �����
    list2.moveFirstToEnd();
    cout << "������ ����� �������� ������� �������� � �����: ";
    list2.print();

    // ���� �������� �������
    cout << "������� ������ 'b'." << endl;
    list2.remove('b');

    cout << "������ ����� �������� ������� 'b': ";
    list2.print();

    try {
        cout << "�������� ������� ������ 'z' (�� ����������)." << endl;
        list2.remove('z'); // ������ ��������� ����������
    }
    catch (const exception& e) {
        cerr << "������: " << e.what() << endl;
    }
}


void testTask2() {
    cout << "2. �������� ��������� � ����������� ��������." << endl;

    DoubleLinkedList<int> list;

    // ���� 1
    list.add(4);
    list.add(2);
    list.add(1);
    list.add(2);
    list.add(4);

    cout << "�������� ������: ";
    list.print();

    list.removeWithIdenticalNeighbors();
    cout << "������ ����� �������� ��������� � ����������� ��������: ";
    list.print();
    cout << endl;

    // ���� 2. ����� ������� ������
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

    cout << "�������� ������: ";
    list2.print();

    list2.removeWithIdenticalNeighbors();
    cout << "������ ����� �������� ��������� � ����������� ��������: ";
    list2.print();
    cout << endl;

    // ���� 3. ������ � ���������
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

    cout << "�������� ������: ";
    list3.print();

    list3.removeWithIdenticalNeighbors();
    cout << "������ ����� �������� ��������� � ����������� ��������: ";
    list3.print();
}



void testTask3() {
    cout << ". ������ � ����������� ��������." << endl;

    UniqueList<string> factory1, factory2, factory3;

    // ��������� �������� � ������ ������
    factory1.add("�������A");
    factory1.add("�������B");

    factory2.add("�������B");
    factory2.add("�������C");

    factory3.add("�������A");
    factory3.add("�������D");

    cout << "������ ������� 1: ";
    factory1.print();

    cout << "������ ������� 2: ";
    factory2.print();

    cout << "������ ������� 3: ";
    factory3.print();

    // ����������� ���� ������
    UniqueList<string> allFactories = factory1.Union(factory2).Union(factory3);

    cout << "������������ ������ ���� ������: ";
    allFactories.print();

    // ����������� ������ 1 � 3
    UniqueList<string> commonFactories = factory1.Intersect(factory3);

    cout << "����� �������� ����� �������� 1 � �������� 3: ";
    commonFactories.print();

    // ���������� ��������� ������� 2 �� ������������� ������
    UniqueList<string> exceptFactories = allFactories.Except(factory2);

    cout << "������ ����� ���������� ��������� ������� 2: ";
    exceptFactories.print();

    // �������� �� ������� ��������
    cout << "�������A ������������ � ������������ ������? "
        << (allFactories.Contains("�������A") ? "��" : "���") << endl;
}


void testTask4() {
    wcout << L"4. ��������� ������ �� �����." << endl;

    const wstring filename = L"text.txt";

    // ��������� ������� ����� � ������� ���, ���� �� �����������
    wifstream file(filename);
    if (!file.is_open()) {
        wcout << L"���� text.txt �����������. ������� ���� � ��������� �������..." << endl;
        wofstream outFile(filename);
        if (!outFile) {
            wcerr << L"������ ��� �������� ����� text.txt!" << endl;
            return;
        }

        // ��������� �������� ������ � ����
        outFile.imbue(locale("ru_RU.UTF-8"));
        outFile << L"������ ������ ��� �����\n"
            L"����� �� �������� ���������\n"
            L"������ ��������� �����\n";
        outFile.close();
        wcout << L"���� text.txt ������� ������." << endl;
    }

    try {
        TextProcessor processor(filename);
        processor.processText();
    }
    catch (const exception& e) {
        cerr << "������ ��� ��������� ������: " << e.what() << endl;
    }
}