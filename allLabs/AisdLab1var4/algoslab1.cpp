#include "list.h"

void menu()
{
	system("cls");
	cout << "1. Добавить значение эл-та" << endl
		<< "2. Добавить значение эл-та по порядковому номеру" << endl
		<< "3. Проверить наличие эл-та по значению" << endl
		<< "4. Прочитать значение эл-та по порядковому номеру" << endl
		<< "5. Получить порядковый номер эл-та по значению" << endl
		<< "6. Изменить значение эл-та по порядковому номеру" << endl
		<< "7. Удалить эл-т по значению" << endl
		<< "8. Удалить эл-т по порядковому номеру" << endl
		<< "9. Очистить список" << endl
		<< "10. Печать списка" << endl
		<< "11. Узнать размер списка" << endl
		<< "12. Проверить список на пустоту" << endl
		<< "---------------------------------------Меню прямого итератора:-------------------------------" << endl
		<< "13. В начало" << endl
		<< "14. Шаг вперед" << endl
		<< "15. Запись в текущую позицию" << endl
		<< "16. Печать значения" << endl
		<< "17. Текущий статус итератора" << endl
		<< "---------------------------------------Меню обратного итератора:-------------------------------" << endl
		<< "18. В начало" << endl
		<< "19. Шаг вперед" << endl
		<< "20. Запись в текущую позицию" << endl
		<< "21. Печать значения" << endl
		<< "22. Текущий статус итератора" << endl
		<< "---------------------------------------Отладка:---------------------------------------" << endl
		<< "23. Наполнить список случайными числами" << endl
		<< "24. Узнать кол-во эл-тов, просмотренных в предыдущей операции (только для 2, 3, 8)" << endl
		<< "--------------------------------------------------------------------------------------\n" << endl
		<< "Ввод: ";
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int SIZE = 5;//размер списка
	List <int> I(SIZE);
	List <int>::Iterator iter(&I);
	List <int>::ReverseIterator reviter(&I);
	while (1)
	{
		int value;	//значение эл-та
		int por_num;//порядковый номер
		int sw;	//перключатель для меню
		menu();
		cin >> sw;
		switch (sw)
		{
		case 1:
			cout << "\nВведите число: ";
			cin >> value;
			if (I.add_val(value) == true) cout << "Число добавлено!\n";
			else cout << "Нет места\n";
			break;
		case 2:
			cout << "\nВведите число: ";
			cin >> value;
			cout << "Введите порядковый номер: ";
			cin >> por_num;
			if (I.add_val_by_num(value, por_num) == true) cout << "Число добавлено!\n";
			else cout << "Предыдущая позиция пуста, либо список полон\n";
			break;
		case 3:
			cout << "\nВведите число: ";
			cin >> value;
			if (I.check_value(value) == true) cout << "Найдено!\n";
			else cout << "Не найдено\n";
			break;
		case 4:
			try {
				cout << "\nВведите порядковый номер: ";
				cin >> por_num;
				cout << "Значение=" << I.read_val_by_num(por_num) << endl;
			}
			catch (int) { cout << "Не найдено" << endl; }
			break;
		case 5:
		{
			cout << "\nВведите число: ";
			cin >> value;
			int pnum = I.get_pos_by_val(value);
			if (pnum == -1) cout << "Не найдено" << endl;
			else cout << "Порядковый номер=" << pnum << endl;
			break;
		}
		case 6:
			cout << "\nВведите число: ";
			cin >> value;
			cout << "Введите порядковый номер: ";
			cin >> por_num;
			if (I.change_val_by_num(por_num, value) == true) cout << "Успешно!\n";
			else cout << "Позиция не найдена\n";
			break;
		case 7:
			cout << "\nВведите число: ";
			cin >> value;
			if (I.delete_val(value) == true) cout << "Успешно!\n";
			else cout << "Число не найдено\n";
			break;
		case 8:
			cout << "\nВведите порядковый номер: ";
			cin >> por_num;
			if (I.delete_val_by_num(por_num) == true) cout << "Успешно!\n";
			else cout << "Позиция не найдена\n";
			break;
		case 9:
			I.clear_list();
			break;
		case 10:
			I.print();
			break;
		case 11:
			cout << "\nРазмер=" << I.ret_size() << endl;
			break;
		case 12:
			if (I.check_list_empty() == true) cout << "Пусто\n";
			else cout << "Не пусто\n";
			break;
		case 13:
			if (iter.begin(&I) == true) cout << "\n\tУспешно!" << endl;
			else cout << "\n\tERROR: Список пуст" << endl;
			break;
		case 14:
			if (++iter == true) cout << "\n\tУспешно!" << endl;
			else cout << "\n\tERROR: Итератор не в списке" << endl;
			break;
		case 15:
			if (iter.end() == true) { cout << "\n\tERROR: Итератор не в списке" << endl; break; }
			else cout << "\n Значение="; cin >> *iter;
			break;
		case 16:
			if (iter.end() == true) cout << "\n\tERROR: Итератор не в списке" << endl;
			else cout << "\n Значение=" << *iter << endl;
			break;
		case 17:
			if (!iter.end()) cout << "\nИтератор в списке" << endl;
			else cout << "\nИтератор не в списке" << endl;
			break;
		case 18:
			if (reviter.Rbegin(&I) == true) cout << "\n\tУспешно!" << endl;
			else cout << "\n\tERROR: Список пуст" << endl;
			break;
		case 19:
			if (++reviter == true) cout << "\n\tУспешно!" << endl;
			else cout << "\n\tERROR: Итератор не в списке" << endl;
			break;
		case 20:
			if (reviter.Rend() == true) { cout << "\n\tERROR: Итератор не в списке" << endl; break; }
			else cout << "\n Значение="; cin >> *reviter;
			break;
		case 21:
			if (reviter.Rend() == true) cout << "\n\tERROR: Итератор не в списке" << endl;
			else cout << "\n Значение=" << *reviter << endl;
			break;
		case 22:
			if (!reviter.Rend()) cout << "\nИтератор в списке" << endl;
			else cout << "\nИтератор не в списке" << endl;
			break;
		case 23:
			I.clear_list();
			for (int i = 0; i < SIZE; i++) I.add_val(rand() / 100);
			I.print();
			break;
		case 24:
			cout << "\nЭл-тов в предыдущей операции (2, 3, 8) просмотрено: " << I.get_num_of_check_elem() << endl;
			break;
		}
		std::cin.ignore(32767, '\n');
		std::cout << "Press Enter to continue...";
		std::cin.ignore();
	}
	return 0;
}
