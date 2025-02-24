#ifndef TASK4_TEXTPROCESSOR_H
#define TASK4_TEXTPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <locale>
#include <codecvt>
#include <stdexcept>

using namespace std;

class TextProcessor {
private:
    wstring filename;

    // множество глухих согласных букв (используем wchar_t для поддержки кириллицы)
    const set<wchar_t> deafConsonants = { L'п', L'ф', L'к', L'т', L'ш', L'с', L'х', L'ц', L'ч', L'щ'};

public:
    TextProcessor(const wstring& file) : filename(file) {}

    // метод для обработки текста и вывода результата
    void processText() const {
        wifstream file(filename);
        if (!file.is_open()) {
            wcerr << L"Ошибка: Не удалось открыть файл: " << filename << endl;
            return;
        }

        file.imbue(locale("ru_RU")); // устанавливаем локаль для чтения файла
        wcout << L"Файл успешно открыт: " << filename << endl;

        set<wchar_t> resultConsonants(deafConsonants); // начинаем с полного множества глухих согласных
        wstring word;
        int wordIndex = 1; // индекс текущего слова (1 — первое слово, 2 — второе и т.д.)

        wcout << L"Начальное множество глухих согласных: ";
        for (wchar_t ch : deafConsonants) {
            wcout << ch << L" ";
        }
        wcout << endl;

        while (file >> word) {
            wcout << L"\nСчитываем слово #" << wordIndex << L": " << word << endl;

            // приводим слово к нижнему регистру и убираем лишние символы
            for (auto& ch : word) {
                ch = towlower(ch); // приводим символ к нижнему регистру
            }
            word.erase(remove_if(word.begin(), word.end(), [](wchar_t ch) { return !iswalpha(ch); }), word.end());

            wcout << L"Слово после обработки: " << word << endl;

            set<wchar_t> currentWordConsonants;

            // собираем глухие согласные из текущего слова
            for (wchar_t ch : word) {
                if (deafConsonants.count(ch)) {
                    currentWordConsonants.insert(ch);
                }
            }

            wcout << L"Глухие согласные в текущем слове: ";
            for (wchar_t ch : currentWordConsonants) {
                wcout << ch << L" ";
            }
            wcout << endl;

            if (wordIndex % 2 == 1) { // нечетное слово
                if (!currentWordConsonants.empty()) { // проверяем, есть ли глухие согласные в текущем слове
                    set<wchar_t> intersection;
                    for (wchar_t ch : resultConsonants) {
                        if (currentWordConsonants.count(ch)) {
                            intersection.insert(ch);
                        }
                    }
                    resultConsonants = intersection; // оставляем только общие буквы
                }
                else {
                    resultConsonants.clear(); // если в слове нет глухих согласных, очищаем результат
                }
                wcout << L"Обновленное множество после нечетного слова: ";
                for (wchar_t ch : resultConsonants) {
                    wcout << ch << L" ";
                }
                wcout << endl;
            }
            else { // четное слово
                for (wchar_t ch : currentWordConsonants) {
                    resultConsonants.erase(ch); // убираем буквы, которые встречаются в четных словах
                }
                wcout << L"Обновленное множество после четного слова: ";
                for (wchar_t ch : resultConsonants) {
                    wcout << ch << L" ";
                }
                wcout << endl;
            }

            wordIndex++;
        }

        if (file.eof()) {
            wcout << L"\nДостигнут конец файла." << endl;
        }
        else if (file.fail()) {
            wcerr << L"\nОшибка: Поток находится в некорректном состоянии." << endl;
        }

        file.close();

        // выводим результат в алфавитном порядке
        if (!resultConsonants.empty()) {
            wcout << L"\nГлухие согласные в алфавитном порядке, которые входят в каждое нечетное слово и не входят хотя бы в одно четное слово: ";
            for (wchar_t ch : resultConsonants) {
                wcout << ch << L" ";
            }
            wcout << endl;
        }
        else {
            wcout << L"\nНет глухих согласных, которые соответствуют условиям задачи." << endl;
        }
    }
};

#endif
