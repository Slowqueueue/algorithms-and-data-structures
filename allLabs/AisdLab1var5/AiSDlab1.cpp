#include <iostream>
#include <limits>
#include "list.h"

using namespace std;

template<typename T>
class Menu {
private:
    string _actionMenu[15] = {
        "1 - Размер списка",
        "2 - Очистить список",
        "3 - Проверка на пустоту",
        "4 - Проверка на содержание значения",
        "5 - Получить значение по индексу",
        "6 - Изменить значение по индексу",
        "7 - Получить индекс по значению",
        "8 - Добавить значение в конец",
        "9 - Добавить значение по индексу",
        "10 - Удалить значение",
        "11 - Удалить значение по индексу",
        "12 - Вывести список",
        "13 - Работа с прямым итератором",
        "14 - Работа с обратным итератором",
        "15 - Выход"
    };

    string _iteratorMenu[10] = {
        "Меню итератора:",
        "1 - Запрос прямого итератора",
        "2 - Запрос неустановленного прямого итератора",
        "3 - Перейти к следующему элементу (++)",
        "4 - Перейти к предыдущему элементу (--)",
        "5 - Прочитать значение (*)",
        "6 - Изменить значение (*)",
        "7 - Проверить на равенство (==)",
        "8 - Проверить на неравенство (!=)",
        "9 - Вернуться в главное меню"
    };

    string _reverseiteratorMenu[10] = {
        "Меню итератора:",
        "1 - Запрос обратного итератора",
        "2 - Запрос неустановленного обратного итератора",
        "3 - Перейти к предыдущему элементу (++)",
        "4 - Перейти к следующему элементу (--)",
        "5 - Прочитать значение (*)",
        "6 - Изменить значение (*)",
        "7 - Проверить на равенство (==)",
        "8 - Проверить на неравенство (!=)",
        "9 - Вернуться в главное меню"
    };

public:
    void showMainMenu() {
        cout << endl;
        for (const auto& item : _actionMenu)
            cout << item << endl;
    }

    void showIteratorMenu() {
        cout << endl;
        for (const auto& item : _iteratorMenu) {
            cout << item << endl;
        }
    }

    void showReverseIteratorMenu() {
        cout << endl;
        for (const auto& item : _reverseiteratorMenu) {
            cout << item << endl;
        }
    }

    void run() {
        int command;
        bool exit = false;

        List<T> list;
        typename List<T>::Iterator iter;
        typename List<T>::ReverseIterator reviter;

        while (!exit) {
            showMainMenu();
            cout << "Выберите действие: ";
            cin >> command;

            try {
                switch (command) {
                case 1: // Размер списка
                {
                    cout << "Размер списка: " << list.get_size() << endl;
                    break;
                }
                case 2: // Очистить список
                {
                    list.clear();
                    break;
                }
                case 3: // Проверка на пустоту
                {
                    cout << list.is_empty() << endl;
                    break;
                }
                case 4: {
                    cout << "Введите значение для поиска: ";
                    T value;
                    cin >> value;
                    cout << list.contains_value(value) << endl;
                    break;
                }
                case 5: // Получить значение по индексу
                { 
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    cout << list.get_value(index) << endl;
                    break;
                }
                case 6: // Изменить значение по индексу
                { 
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    cout << "Введите новое значение: ";
                    T value;
                    cin >> value;
                    cout << list.change_value(index, value) << endl;

                    break;
                }
                case 7: // Получить индекс по значению
                { 
                    cout << "Введите значение: ";
                    T value;
                    cin >> value;

                    cout << list.get_index(value) << endl;

                    break;
                }
                case 8: // Добавить значение в конец
                {
                    cout << "Введите значение: ";
                    T value;
                    cin >> value;
                    list.pushback(value);
                    break;
                }
                case 9: // Добавить значение по индексу
                { 
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    cout << "Введите значение: ";
                    T value;
                    cin >> value;
                    cout << list.add_node(index, value) << endl;
                    break;
                }
                case 10: // Удалить значение
                { 
                    cout << "Введите значение: ";
                    T value;
                    cin >> value;

                    cout << list.remove_by_value(value) << endl;
                    break;
                }
                case 11: // Удалить значение по индексу
                { 
                    cout << "Введите индекс: ";
                    int index;
                    cin >> index;
                    cout << list.remove_by_index(index) << endl;
                    break;
                }
                case 12: // Вывести список
                {
                    cout << "Содержимое списка:" << endl;
                    list.print();
                    break;
                }
                case 13: // Работа с прямым итератором
                {
                    handleIterator(list, iter);
                    break;
                }
                case 14: // Работа с обратным итератором
                {
                    handleReverseIterator(list, reviter);
                    break;
                }
                case 15: // Выход
                {
                    exit = true;
                    break;
                }
                default:
                {
                    cout << "Неверная команда. Попробуйте снова." << endl;
                }
                }
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
    }

    void handleIterator(List<T>& list, typename List<T>::Iterator& iter) {
        int command;
        bool exit = false;
        while (!exit) {
            showIteratorMenu();
            cout << "Выберите действие: ";
            cin >> command;

            try {
                switch (command) {
                case 1:
                {
                    iter = list.begin();
                    break;
                }
                case 2:
                {
                    iter = list.end();
                    break;
                }
                case 3: // ++
                {
                    ++iter;
                    break;
                }
                case 4: // --
                {
                    --iter;
                    break;
                }
                case 5: // *
                {
                    cout << "Текущее значение: " << *iter << endl;
                    break;
                }
                case 6: // Изменить значение
                { 
                    cout << "Введите новое значение: ";
                    T value;
                    cin >> value;
                    *iter = value;
                    cout << "Значение изменено" << endl;
                    break;
                }
                case 7: // ==
                {
                    cout << (iter == list.end()) << endl;
                    break;
                }
                case 8: // !=
                {
                    cout << (iter != list.end()) << endl;
                    break;
                }
                case 9: // Выход
                {
                    exit = true;
                    break;
                }
                default: 
                {
                    cout << "Неверная команда. Попробуйте снова." << endl;
                }
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        }
    }

    void handleReverseIterator(List<T>& list, typename List<T>::ReverseIterator& reviter) {
        int command;
        bool exit = false;
        while (!exit) {
            showReverseIteratorMenu();
            cout << "Выберите действие: ";
            cin >> command;

            try {
                switch (command) {
                case 1:
                {
                    reviter = list.rbegin();
                    break;
                }
                case 2:
                {
                    reviter = list.rend();
                    break;
                }
                case 3: // ++
                {
                    ++reviter;
                    break;
                }
                case 4: // --
                {
                    --reviter;
                    break;
                }
                case 5: // *
                {
                    cout << "Текущее значение: " << *reviter << endl;
                    break;
                }
                case 6: { // Изменить значение
                    cout << "Введите новое значение: ";
                    T value;
                    cin >> value;
                    *reviter = value;
                    cout << "Значение изменено" << endl;
                    break;
                }
                case 7: // ==
                {
                    cout << (reviter == list.rend()) << endl;
                    break;
                }
                case 8: // !=
                {
                    cout << (reviter != list.rend()) << endl;
                    break;
                }
                case 9: // Выход
                {
                    exit = true;
                    break;
                }
                default:
                    cout << "Неверная команда. Попробуйте снова." << endl;
                }
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    Menu<int> menu;
    menu.run();

    return 0;
}
