#include <iostream>
#include <string>
#include "List.h"

using namespace std;

void displayMenu() {
    cout << "\n";
    cout << "         МЕНЮ ОПЕРАЦИЙ          \n";
    cout << " 1.  Добавить в начало          \n";
    cout << " 2.  Добавить по индексу        \n";
    cout << " 3.  Удалить по значению        \n";
    cout << " 4.  Удалить по индексу         \n";
    cout << " 5.  Получить по индексу        \n";
    cout << " 6.  Изменить по индексу        \n";
    cout << " 7.  Проверить наличие          \n";
    cout << " 8.  Найти индекс элемента      \n";
    cout << " 9.  Размер списка              \n";
    cout << " 10. Проверить на пустоту       \n";
    cout << " 11. Очистить список            \n";
    cout << " 12. Вывести список             \n";
    cout << " 13. Вывести (итератором)       \n";
    cout << " 14. Работа с итератором        \n";
    cout << " 0.  Выход                      \n";
    cout << "Выберите операцию: ";
}

void displayIteratorMenu() {
    cout << "\n";
    cout << "       ОПЕРАЦИИ ИТЕРАТОРА       \n";
    cout << " 1. Текущий элемент (*)         \n";
    cout << " 2. Следующий (++)              \n";
    cout << " 3. Проверить конец (==)        \n";
    cout << " 4. Проверить позицию (!=)      \n";
    cout << " 5. Сбросить в начало           \n";
    cout << " 0. Назад                       \n";
    cout << "Выберите операцию: ";
}

void interactiveIteratorMode(List<string>& list) {
    auto it = list.begin();
    auto endIt = list.end();

    int choice;
    do {
        displayIteratorMenu();
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << *it << endl;
                break;
            case 2:
                ++it;
                if (it == endIt) {
                    throw std::out_of_range("Exception");
                }
                cout << *it << endl;
                break;
            case 3:
                cout << (it == endIt ? "True" : "False") << endl;
                break;
            case 4:
                cout << (it != endIt ? "True" : "False") << endl;
                break;
            case 5:
                it = list.begin();
                cout << *it << endl;
                break;
            case 0:
                return;
            default:
                cout << "False" << endl;
            }
        }
        catch (const std::out_of_range&) {
            cout << "Exception" << endl;
        }
        catch (...) {
            cout << "Exception" << endl;
            it = list.begin();
        }
    } while (true);
}

int main() {
    setlocale(LC_ALL, "Russian");

    int initialCapacity;
    cout << "Введите размер списка: ";
    cin >> initialCapacity;

    try {
        List<string> list(initialCapacity);
        int choice;
        string value;
        size_t index;

        do {
            displayMenu();
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Введите значение: ";
                cin >> value;
                cout << (list.add(value) ? "True" : "False") << endl;
                break;
            case 2:
                cout << "Введите индекс и значение: ";
                cin >> index >> value;
                cout << (list.addAt(index, value) ? "True" : "False") << endl;
                break;
            case 3:
                cout << "Введите значение: ";
                cin >> value;
                cout << (list.remove(value) ? "True" : "False") << endl;
                break;
            case 4:
                cout << "Введите индекс: ";
                cin >> index;
                cout << (list.removeAt(index) ? "True" : "False") << endl;
                break;
            case 5:
                cout << "Введите индекс: ";
                cin >> index;
                try {
                    cout << list.get(index) << endl;
                }
                catch (...) {
                    cout << "Exception" << endl;
                }
                break;
            case 6:
                cout << "Введите индекс и значение: ";
                cin >> index >> value;
                cout << (list.set(index, value) ? "True" : "False") << endl;
                break;
            case 7:
                cout << "Введите значение: ";
                cin >> value;
                cout << (list.contains(value) ? "True" : "False") << endl;
                break;
            case 8:
                cout << "Введите значение: ";
                cin >> value;
                if (list.indexOf(value, index)) {
                    cout << index << endl;
                }
                else {
                    cout << "False" << endl;
                }
                break;
            case 9:
                cout << list.getSize() << endl;
                break;
            case 10:
                cout << (list.isEmpty() ? "True" : "False") << endl;
                break;
            case 11:
                list.clear();
                cout << "True" << endl;
                break;
            case 12:
                list.display();
                break;
            case 13:
                for (auto it = list.begin(); it != list.end(); ++it) {
                    cout << *it << " ";
                }
                cout << endl;
                break;
            case 14:
                if (list.isEmpty()) {
                    cout << "False" << endl;
                }
                else {
                    interactiveIteratorMode(list);
                }
                break;
            case 0:
                return 0;
            default:
                cout << "False" << endl;
            }
        } while (true);
    }
    catch (...) {
        cout << "Exception" << endl;
        return 1;
    }
}