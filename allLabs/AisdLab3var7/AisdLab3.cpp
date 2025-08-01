#include "BST.h" 
#include "RND.h"
#include <conio.h>
#include <string>
namespace TestEffect
{
	void test_rand(int n);
	void test_sort(int n);
	typedef unsigned long long INT_64;
	INT_64 lrand() { return rand() << 16 | rand(); }
}

//Меню
void main() {
	RNDTree<int, int> RNDtree;
	RNDTree<int, int>::Iterator it = RNDTree<int, int>::Iterator(&RNDtree);;
	RNDTree<int, int>::ReverseIterator revit = RNDTree<int, int>::ReverseIterator(&RNDtree);

	bool useReverseiter = false;
	setlocale(LC_ALL, "RUS");
	while (true)
	{
		cout << "1. Вертикальная печать дерева" << endl;
		cout << "2. Очистка дерева" << endl;
		cout << "3. Проверка на пустоту" << endl;
		cout << "4. Доступ к данным с заданным ключом" << endl;
		cout << "5. Запись данных с заданным ключом" << endl;
		cout << "6. Включение данных с заданным ключом" << endl;
		cout << "7. Удаление данных с заданным ключом" << endl;
		cout << "8. Опрос размера дерева" << endl;
		cout << "9. Запрос прямого итератора" << endl;
		cout << "10.Запрос неустановленного прямого итератора" << endl;
		cout << "11.Запрос обратного итератора" << endl;
		cout << "12.Запрос неустановленного обратного итератора" << endl;
		cout << "13.Меню прямого итератора" << endl;
		cout << "14.Меню обратного итератора" << endl;
		cout << "15.Тестирование трудоемкости для случайного дерева" << endl;
		cout << "16.Тестирование трудоемкости для вырожденного дерева" << endl;
		cout << "17.Выход" << endl;
		int t;
		int value, key;

		cin >> t;
		switch (t)
		{
		case 1:
			cout << "-------------------------------" << endl;
			RNDtree.Show();
			cout << "-------------------------------" << endl << endl;
			break;
		case 2:
			RNDtree.Clear();
			cout << endl;
			it = RNDtree.beg();
			revit = RNDtree.rbeg();
			break;
		case 3:
			cout << RNDtree.IsEmpty() << endl << endl;
			break;
		case 4:
			cin >> key;
			try
			{
				cout << RNDtree.GetData(key) << endl;
			}
			catch (TreeException e)
			{
				cerr << e.What() << endl;
			}
			cout << endl;
			break;
		case 5:
			cin >> key;
			cin >> value;
			try
			{
				cout << RNDtree.Replace(key, value) << endl;
			}
			catch (TreeException e)
			{
				cerr << e.What() << endl;
			}
			cout << endl;
			break;
		case 6:
			cin >> key;
			cin >> value;
			cout << RNDtree.Insert(key, value) << endl << endl;
			break;
		case 7:
			cin >> key;
			cout << RNDtree.Delete(key) << endl << endl;
			it = RNDtree.beg();
			revit = RNDtree.rbeg();
			break;
		case 8:
			cout << RNDtree.GetSize() << endl << endl;
			break;
		case 9:
			it = RNDtree.beg();
			cout << endl;
			break;
		case 10:
			it = RNDtree.end();
			cout << endl;
			break;
		case 11:
			revit = RNDtree.rbeg();
			cout << endl;
			break;
		case 12:
			revit = RNDtree.rend();
			cout << endl;
			break;
		case 13: {
			system("cls");
			bool exit = false;
			while (!exit) {
				cout << "Меню прямого итератора" << endl;
				cout << "1.Чтение данных текущего узла" << endl;
				cout << "2.Оператор инкремента (++)" << endl;
				cout << "3.Оператор декремента (--)" << endl;
				cout << "4.Проверить на конец (==)" << endl;
				cout << "5.Проверить на не конец (!=)" << endl;
				cout << "6.Запись данных в текущий узел" << endl;
				cout << "7.Назад" << endl;
				int it_t;
				cin >> it_t;
				switch (it_t) {
				case 1:
					try
					{
						cout << *it << endl;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 2:
					try {
						++it;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 3:
					try {
						--it;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 4:
					cout << (it == RNDtree.end()) << endl;
					cout << endl;
					break;
				case 5:
					cout << (it != RNDtree.end()) << endl;
					cout << endl;
					break;
				case 6:
					cin >> value;
					try {
						*it = value;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 7:
					exit = true;
					system("cls");
					break;
				default:
					cout << "Неверный номер команды" << endl << endl;
					break;
				}
			}
		}
			break;
		case 14: {
			system("cls");
			bool exit = false;
			while (!exit) {
				cout << "Меню обратного итератора" << endl;
				cout << "1.Чтение данных текущего узла" << endl;
				cout << "2.Оператор инкремента (++)" << endl;
				cout << "3.Оператор декремента (--)" << endl;
				cout << "4.Проверить на конец (==)" << endl;
				cout << "5.Проверить на не конец (!=)" << endl;
				cout << "6.Запись данных в текущий узел" << endl;
				cout << "7.Назад" << endl;
				int it_t;
				cin >> it_t;
				switch (it_t) {
				case 1:
					try
					{
						cout << *revit << endl;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 2:
					try {
						++revit;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 3:
					try {
						--revit;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 4:
					cout << (revit == RNDtree.rend()) << endl;
					cout << endl;
					break;
				case 5:
					cout << (revit != RNDtree.rend()) << endl;
					cout << endl;
					break;
				case 6:
					cin >> value;
					try {
						*revit = value;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 7:
					exit = true;
					system("cls");
					break;
				default:
					cout << "Неверный номер команды" << endl << endl;
					break;
				}
			}
		}
			break;
		case 15:
			int n;
			cout << "Введите размер дерева:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			cout << endl;
			break;
		case 16:
			int n2;
			cout << "Введите размер дерева:" << endl;
			cin >> n2;
			TestEffect::test_sort(n2);
			cout << endl;
			break;
		case 17:
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
	RNDTree<INT_64, int> RNDtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		BSTtree.Insert(m[i], 1);
		RNDtree.Insert(m[i], 1);
	}
	BSTtree.getCountNodesView();
	RNDtree.getCountNodesView();

	double Ib = 0;
	double Db = 0;
	double Sb = 0;
	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)
		{
			BSTtree.Delete(lrand());
			RNDtree.Delete(lrand());
			D += BSTtree.getCountNodesView();
			Db += RNDtree.getCountNodesView();
			BSTtree.Insert(m[rand() % n], 1);
			RNDtree.Insert(m[rand() % n], 1);
			I += BSTtree.getCountNodesView();
			Ib += RNDtree.getCountNodesView();
			try
			{
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				RNDtree.GetData(m[rand() % n]);
				Sb += RNDtree.getCountNodesView();
			}
			catch (TreeException&) { Sb += RNDtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			BSTtree.Delete(m[ind]);
			RNDtree.Delete(m[ind]);
			D += BSTtree.getCountNodesView();
			Db += RNDtree.getCountNodesView();
			INT_64 key = lrand();
			BSTtree.Insert(key, 1);
			RNDtree.Insert(key, 1);
			I += BSTtree.getCountNodesView();
			Ib += RNDtree.getCountNodesView();
			m[ind] = key;
			try {
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				RNDtree.GetData(m[rand() % n]);
				Sb += RNDtree.getCountNodesView();
			}
			catch (TreeException&) { Sb += RNDtree.getCountNodesView(); };
		}
	cout << "BST-дерево" << endl;
	cout << "1.39*log2(n)=" << (log((double)n) / log(2.0)) * 1.39 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	cout << "RND-дерево" << endl;
	cout << "1.39*log2(n)=" << (log((double)n) / log(2.0)) * 1.39 << endl;
	cout << "Размер дерева после:" << RNDtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << Ib / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << Db / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << Sb / (n / 2) << endl;
	delete[] m;
}
//Программа тестирования вырожденного дерева
void TestEffect::test_sort(int n)
{
	if (n > 2000) cout << "Максимальный размер вырожденного BST дерева - 2000 узлов" << endl;
	Tree<INT_64, int> BSTtree;
	RNDTree<INT_64, int> RNDtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = i * 10000;
		if (n <= 2000) BSTtree.Insert(m[i], 1);
		RNDtree.Insert(m[i], 1);
	}
	BSTtree.getCountNodesView();
	RNDtree.getCountNodesView();

	double Ib = 0;
	double Db = 0;
	double Sb = 0;
	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)
		{
			int k = lrand() % (10000 * n);
			k = k + !(k % 2);
			if (n <= 2000) BSTtree.Delete(k);
			RNDtree.Delete(k);
			D += BSTtree.getCountNodesView();
			Db += RNDtree.getCountNodesView();
			if (n <= 2000) BSTtree.Insert(m[rand() % n], 1);
			RNDtree.Insert(m[rand() % n], 1);
			I += BSTtree.getCountNodesView();
			Ib += RNDtree.getCountNodesView();
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
				RNDtree.GetData(m[rand() % n]);
				Sb += RNDtree.getCountNodesView();
			}
			catch (TreeException&) { Sb += RNDtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			if (n <= 2000) BSTtree.Delete(m[ind]);
			RNDtree.Delete(m[ind]);
			D += BSTtree.getCountNodesView();
			Db += RNDtree.getCountNodesView();
			int k = lrand() % (10000 * n);
			k = k + k % 2;
			if (n <= 2000) BSTtree.Insert(k, 1);
			RNDtree.Insert(k, 1);
			I += BSTtree.getCountNodesView();
			Ib += RNDtree.getCountNodesView();
			m[ind] = k;
			try {
				if (n <= 2000) BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				RNDtree.GetData(m[rand() % n]);
				Sb += RNDtree.getCountNodesView();
			}
			catch (TreeException&) { Sb += RNDtree.getCountNodesView(); };
		}
	cout << "BST-дерево" << endl;
	cout << "n/2=" << n / 2 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	cout << "RND-дерево" << endl;
	cout << "1.39*log2(n)=" << (log((double)n) / log(2.0)) * 1.39 << endl;
	cout << "Размер дерева после:" << RNDtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << Ib / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << Db / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << Sb / (n / 2) << endl;
	delete[] m;
}