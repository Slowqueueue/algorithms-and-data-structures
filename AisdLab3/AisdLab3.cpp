#include "BST.h" 
#include "AVL.h"
#include <conio.h>
#include <string>
namespace TestEffect
{
	void test_rand(int n);
	void test_sort(int n);
	typedef unsigned long long INT_64;
	INT_64 lrand() { return rand() << 16 | rand(); }
}

double IA = 0;
double DA = 0;
double SA = 0;

//Меню
void main() {
	AvlTree<int, int> Avltree;
	//AvlTree<int, int> betatree;
	//betatree.AvlInsert(10, 10, IA);
	//AvlTree<int, int> Avltree(betatree);

	AvlTree<int, int>::Iterator it = AvlTree<int, int>::Iterator(&Avltree);;
	AvlTree<int, int>::ReverseIterator revit = AvlTree<int, int>::ReverseIterator(&Avltree);

	bool useReverseiter = false;
	setlocale(LC_ALL, "RUS");
	Avltree.Insert(10, 10, IA); Avltree.Insert(20, 20, IA); Avltree.Insert(30, 30, IA);
	Avltree.Insert(40, 40, IA); Avltree.Insert(50, 50, IA);
	Avltree.Insert(60, 60, IA); Avltree.Insert(70, 70, IA);
	while (true)
	{
		cout << "1. Вертикальная печать дерева" << endl;
		cout << "2. Очистка дерева" << endl;
		cout << "3. Проверка на пустоту" << endl;
		cout << "4. Доступ к данным с заданным ключом" << endl;
		cout << "5. Включение данных с заданным ключом" << endl;
		cout << "6. Удаление данных с заданным ключом" << endl;
		cout << "7. Опрос размера дерева" << endl;
		cout << "8. Меню итераторов" << endl;
		cout << "9. Опрос числа просмотренных предыдущей операцией узлов дерева" << endl;
		cout << "10.Тестирование трудоемкости для случайного дерева" << endl;
		cout << "11.Тестирование трудоемкости для вырожденного дерева" << endl;
		cout << "12.Выход" << endl;
		int t;
		int value, key;

		cin >> t;
		switch (t)
		{
		case 1:
			cout << "-------------------------------" << endl;
			Avltree.Show();
			cout << "-------------------------------" << endl << endl;
			break;
		case 2:
			Avltree.Clear();
			it = Avltree.beg();
			revit = Avltree.rbeg();
			cout << endl;
			break;
		case 3:
			cout << Avltree.IsEmpty() << endl << endl;
			break;
		case 4:
			cin >> key;
			try
			{
				char c;
				int& datalink = Avltree.GetData(key, SA);
				cout << datalink << endl;
				cout << "Изменить значение? (y/n)" << endl;
				cin >> c;
				if (c == 'y') {
					cout << "Введите новое значение" << endl;
					cin >> value;
					datalink = value;
				}
			}
			catch (AvlTreeException e)
			{
				cerr << e.What() << endl;
			}
			cout << endl;
			break;
		case 5:
			cin >> key;
			cin >> value;
			cout << Avltree.Insert(key, value, IA) << endl << endl;
			break;
		case 6:
			cin >> key;
			cout << Avltree.Delete(key, DA) << endl << endl;
			if (!useReverseiter && !it.is_off()) it = Avltree.beg();
			if (useReverseiter && !revit.is_rev_off()) revit = Avltree.rbeg();
			break;
		case 7:
			cout << Avltree.GetSize() << endl << endl;
			break;
		case 8: {
			system("cls");
			bool exit = false;
			while (!exit) {
				cout << "1. Чтение данных текущего узла" << endl;
				cout << "2. Запрос прямого итератора" << endl;
				cout << "3. Запрос неустановленного прямого итератора" << endl;
				cout << "4. Запрос обратного итератора" << endl;
				cout << "5. Запрос неустановленного обратного итератора" << endl;
				cout << "6. Операция перехода к следующему(для обратного к предыдущему)" << endl;
				cout << "7. Операция перехода к предыдущему(для обратного к следующему)" << endl;
				cout << "8. Проверка состояния" << endl;
				cout << "9. Запись данных в текущий узел" << endl;
				cout << "10.Назад" << endl;

				int it_t;
				cin >> it_t;
				switch (it_t) {
				case 1:
					try
					{
						if (!useReverseiter) cout << *it << endl;
						else cout << *revit << endl;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 2:
					it = Avltree.beg();
					useReverseiter = false;
					cout << endl;
					break;
				case 3:
					it = Avltree.end();
					useReverseiter = false;
					cout << endl;
					break;
				case 4:
					revit = Avltree.rbeg();
					useReverseiter = true;
					cout << endl;
					break;
				case 5:
					revit = Avltree.rend();
					useReverseiter = true;
					cout << endl;
					break;
				case 6:
					if (!useReverseiter) ++it;
					else ++revit;
					cout << endl;
					break;
				case 7:
					if (!useReverseiter) --it;
					else --revit;
					cout << endl;
					break;
				case 8:
					if (!useReverseiter) cout << it.is_off() << endl;
					else cout << revit.is_rev_off() << endl;
					cout << endl;
					break;
				case 9:
					cin >> value;
					try {
						if (!useReverseiter) *it = value;
						else *revit = value;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 10:
					exit = true;
					system("cls");
					break;
				case 777:
					if (useReverseiter) useReverseiter = false;
					else useReverseiter = true;
					cout << endl;
					break;
				default:
					cout << "Неверный номер команды" << endl << endl;
					break;
				}
			}
		}
			  break;
		case 9:
			cout << Avltree.getCountNodesView() << endl << endl;
			break;
		case 10:
			int n;
			cout << "Введите размер дерева:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			cout << endl;
			break;
		case 11:
			int n2;
			cout << "Введите размер дерева:" << endl;
			cin >> n2;
			TestEffect::test_sort(n2);
			cout << endl;
			break;
		case 12:
			exit(0);
			break;
		default:
			cout << "Неверный номер команды" << endl << endl;
		}
	}
}
//Программа тестирования случайного дерева
void TestEffect::test_rand(int n)
{
	Tree<INT_64, int> BSTtree;
	AvlTree<INT_64, int> AVLtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		BSTtree.Insert(m[i], 1);
		AVLtree.Insert(m[i], 1, IA);
	}
	BSTtree.getCountNodesView();

	IA = 0;
	DA = 0;
	SA = 0;
	double I = 0;
	double D = 0;
	double S = 0;
	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)
		{
			BSTtree.Delete(lrand());
			AVLtree.Delete(lrand(), DA);
			D += BSTtree.getCountNodesView();
			BSTtree.Insert(m[rand() % n], 1);
			AVLtree.Insert(m[rand() % n], 1, IA);
			I += BSTtree.getCountNodesView();
			try
			{
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				AVLtree.GetData(m[rand() % n], SA);
			}
			catch (AvlTreeException&) { SA += AVLtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			BSTtree.Delete(m[ind]);
			AVLtree.Delete(m[ind], DA);
			D += BSTtree.getCountNodesView();
			INT_64 key = lrand();
			BSTtree.Insert(key, 1);
			AVLtree.Insert(key, 1, IA);
			I += BSTtree.getCountNodesView();
			m[ind] = key;
			try {
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				AVLtree.GetData(m[rand() % n], SA);
			}
			catch (AvlTreeException&) { SA += AVLtree.getCountNodesView(); };
		}
	cout << "AVL-Дерево" << endl;
	cout << "log2(n)+0.25=" << (log((double)n) / log(2.0)) + 0.25 << endl;
	cout << "Размер дерева после:" << AVLtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << IA / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << DA / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << SA / (n / 2) << endl;
	cout << "BST-дерево" << endl;
	cout << "1.39*log2(n)=" << (log((double)n) / log(2.0)) * 1.39 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	delete[] m;
}
//Программа тестирования вырожденного дерева
void TestEffect::test_sort(int n)
{
	Tree<INT_64, int> BSTtree;
	AvlTree<INT_64, int> AVLtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = i * 10000;
		if (n <= 2000) BSTtree.Insert(m[i], 1);
		AVLtree.Insert(m[i], 1, IA);
	}
	BSTtree.getCountNodesView();

	IA = 0;
	DA = 0;
	SA = 0;
	double I = 0;
	double D = 0;
	double S = 0;
	double SAtemp = 0;
	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)
		{
			int k = lrand() % (10000 * n);
			k = k + !(k % 2);
			if (n <= 2000) BSTtree.Delete(k);
			AVLtree.Delete(k, DA);
			D += BSTtree.getCountNodesView();
			if (n <= 2000) BSTtree.Insert(m[rand() % n], 1);
			AVLtree.Insert(m[rand() % n], 1, IA);
			I += BSTtree.getCountNodesView();
			k = lrand() % (10000 * n);
			k = k + !(k % 2);
			try
			{
				if (n <= 2000) BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				AVLtree.GetData(m[rand() % n], SA);
			}
			catch (AvlTreeException&) { SA += AVLtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			if (n <= 2000) BSTtree.Delete(m[ind]);
			AVLtree.Delete(m[ind], DA);
			D += BSTtree.getCountNodesView();
			int k = lrand() % (10000 * n);
			k = k + k % 2;
			if (n <= 2000) BSTtree.Insert(k, 1);
			AVLtree.Insert(k, 1, IA);
			I += BSTtree.getCountNodesView();
			m[ind] = k;
			try {
				if (n <= 2000) BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				AVLtree.GetData(m[rand() % n], SA);
			}
			catch (AvlTreeException&) { SA += AVLtree.getCountNodesView(); };
		}
	cout << "AVL-Дерево" << endl;
	cout << "log2(n)+0.25=" << (log((double)n) / log(2.0)) + 0.25 << endl;
	cout << "Размер дерева после:" << AVLtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << IA / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << DA / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << SA / (n / 2) << endl;
	cout << "BST-дерево" << endl;
	cout << "n/2=" << n / 2 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	delete[] m;
}