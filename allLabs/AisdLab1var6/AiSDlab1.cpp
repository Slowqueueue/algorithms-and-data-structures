#include "list.h"
#include "Exception.h"
#include <iostream>
#include <conio.h>
using namespace std;

void main()
{
	setlocale(LC_ALL, "Russian");

	//int val24 = 24;
	//List <int> listdemo;
	List <int> list;
	//listdemo.Add(val24);
	//List <int> list(listdemo);
	List<int>::Iterator Iter(list);
	int k, val;
	char c;
	while (1)
	{
		cout << endl << "Меню:" << endl
			<< "1 - Добавить значение в конец списка" << endl
			<< "2 - Добавить значение в список по индексу" << endl
			<< "3 - Получить значение по индексу" << endl
			<< "4 - Удалить значение по индексу" << endl
			<< "5 - Изменить значение по индексу" << endl
			<< "6 - Получить индекс по значению" << endl
			<< "7 - Удалить значение из списка" << endl
			<< "8 - Проверить существование значения в списке" << endl
			<< "9 - Очистить список" << endl
			<< "q - Получить размер списка" << endl
			<< "w - Проверить список на пустоту" << endl
			<< "e - Вывести список на экран" << endl
			<< "r - Установить итератор на начало" << endl
			<< "t - Вывести текущее значение итератора" << endl
			<< "y - Инкрементировать итератор" << endl
			<< "u - Проверить состояние итератора" << endl
			<< "i - Вывести количество итераций (для кейсов 2, 4, 8)" << endl
			<< "0 - Выход" << endl;
		c = _getch();
		try
		{
			switch (c)
			{
			case '1':	//добавление в конец
			{
				cout << endl << "Введите значение: " << endl;
				cin >> val;
				list.Add(val);
				cout << endl << "Значение добавлено" << endl;
				break;
			}
			case '2':	//добавление по индексу
			{
				cout << endl << "Введите индекс: " << endl;
				cin >> k;

				cout << "Введите значение:" << endl;
				cin >> val;

				list.InsertByIndex(k, val);
				cout << endl << "Значение добавлено" << endl;
				break;
			}
			case '3':	//получение по индексу
			{
				cout << endl << "Введите индекс: " << endl;
				cin >> k;
				cout << endl << list.GetByIndex(k) << endl;
				break;
			}
			case '4':	//удаление по индексу
			{
				cout << endl << "Введите индекс: " << endl;
				cin >> k;
				list.DeleteByIndex(k);
				cout << endl << "Значение удалено" << endl;
				Iter.begin();
				break;
			}
			case '5':	//изменение значения по индексу
			{
				cout << endl << "Введите индекс: " << endl;
				cin >> k;

				cout << "Введите значение: " << endl;
				cin >> val;

				list.Change(k, val);
				cout << endl << "Значение изменено" << endl;
				break;
			}
			case '6':	//получение индекса по заданному значению
			{
				cout << endl << "Введите значение: " << endl;
				cin >> val;

				cout << endl << list.GetByValue(val) << endl;
				break;
			}
			case '7':	//удаление заданного значения из списка	
			{
				cout << endl << "Введите значение: " << endl;
				cin >> val;
				list.DeleteByValue(val);
				cout << endl << "Значение удалено" << endl;
				Iter.begin();
				break;
			}
			case '8':	//проверка наличия заданного значения	
			{
				cout << endl << "Введите значение: " << endl;
				cin >> val;

				cout << endl << list.IsValue(val) << endl;
				break;
			}
			case '9':	//очистка списка		
			{
				list.Clear();
				cout << endl << "Список очищен" << endl;
				Iter.begin();
				break;
			}
			case 'q':	//запрос размера списка	
			{
				cout << endl << list.GetCount() << endl;
				break;
			}
			case 'w':	//проверка списка на пустоту	
			{
				cout << endl << list.IsEmpty() << endl;
				break;
			}
			case 'e':	//вывод списка на экран	
			{
				if (list.GetCount() == 0)
					cout << endl << "Список пуст" << endl;
				else
				{
					cout << endl;
					for (int i = 0; i < list.GetCount(); i++) cout << list.GetByIndex(i) << " ";
					cout << endl;
				}
				break;
			}
			case 'r':	//установка итератора на начало				
			{				
				Iter.begin();
				cout << endl << "Итератор установлен на начало" << endl;
				break;
			}
			case 't':	//получить/изменить текущее значение						
			{								
				int val = *Iter;
				cout << endl << val << endl;
				while (1)
				{
					cout << "Изменить значение? (y/n)" << endl;
					char buf = _getch();
					if (buf == 'y')
					{
						cout << "Введите новое значение: ";
						cin >> val;
						*Iter = val;
						break;
					}
					if (buf == 'n')
						break;
				}
				break;
			}
				case 'y':	//инкрементирование итератора		
				{
					Iter.next();
					cout << endl << "Итератор инкрементирован" << endl;
					break;
				}
				case 'u':	//проверка состояния итератора					
				{				
					cout << endl << !Iter.end() << endl;
					break;
				}
				case 'i':	//вывод количества итераций (для кейсов 2,4,8)
				{
					cout << endl << list.GetTest() << endl;
					break;
				}
				case '0':
				{
					int exitcode = 0;
					list.Add(exitcode);
					return;
				}
			}
		}
		catch (Exception* ex)
		{
			ex->PrintError();
			delete ex;
		}
	}
}