#include "BST.h" 
#include "RB.h"
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
	RbTree<int, int> Rbtree;
	RbTree<int, int>::Iterator it = RbTree<int, int>::Iterator(&Rbtree);;
	RbTree<int, int>::ReverseIterator revit = RbTree<int, int>::ReverseIterator(&Rbtree);

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
		cout << "9. Меню итераторов" << endl;
		cout << "10. Опрос числа просмотренных предыдущей операцией узлов дерева" << endl;
		cout << "11.Тестирование трудоемкости для случайного дерева" << endl;
		cout << "12.Тестирование трудоемкости для вырожденного дерева" << endl;
		cout << "13.Выход" << endl;
		int t;
		int value, key;

		cin >> t;
		switch (t)
		{
		case 1:
			cout << "-------------------------------" << endl;
			Rbtree.Show();
			cout << "-------------------------------" << endl << endl;
			break;
		case 2:
			Rbtree.Clear();
			it = Rbtree.beg();
			revit = Rbtree.rbeg();
			cout << endl;
			break;
		case 3:
			cout << Rbtree.IsEmpty() << endl << endl;
			break;
		case 4:
			cin >> key;
			try
			{
				cout << Rbtree.GetData(key) << endl;
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
				cout << Rbtree.Replace(key, value) << endl;
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
			cout << Rbtree.Insert(key, value) << endl << endl;
			break;
		case 7:
			cin >> key;
			cout << Rbtree.Delete(key) << endl << endl;
			if (!useReverseiter && !it.is_off()) it = Rbtree.beg();
			if (useReverseiter && !revit.is_rev_off()) revit = Rbtree.rbeg();
			break;
		case 8:
			cout << Rbtree.GetSize() << endl << endl;
			break;
		case 9: {
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
					it = Rbtree.beg();
					useReverseiter = false;
					cout << endl;
					break;
				case 3:
					it = Rbtree.end();
					useReverseiter = false;
					cout << endl;
					break;
				case 4:
					revit = Rbtree.rbeg();
					useReverseiter = true;
					cout << endl;
					break;
				case 5:
					revit = Rbtree.rend();
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
		case 10:
			cout << Rbtree.getCountNodesView() << endl << endl;
			break;
		case 11:
			int n;
			cout << "Введите размер дерева:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			cout << endl;
			break;
		case 12:
			int n2;
			cout << "Введите размер дерева:" << endl;
			cin >> n2;
			TestEffect::test_sort(n2);
			cout << endl;
			break;
		case 13:
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
	RbTree<INT_64, int> Rbtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		BSTtree.Insert(m[i], 1);
		Rbtree.Insert(m[i], 1);
	}
	BSTtree.getCountNodesView();

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
			Rbtree.Delete(lrand());
			D += BSTtree.getCountNodesView();
			Db += Rbtree.getCountNodesView();
			BSTtree.Insert(m[rand() % n], 1);
			Rbtree.Insert(m[rand() % n], 1);
			I += BSTtree.getCountNodesView();
			Ib += Rbtree.getCountNodesView();
			try
			{
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				Rbtree.GetData(m[rand() % n]);
				Sb += Rbtree.getCountNodesView();
			}
			catch (RbTreeException&) { Sb += Rbtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			BSTtree.Delete(m[ind]);
			Rbtree.Delete(m[ind]);
			D += BSTtree.getCountNodesView();
			Db += Rbtree.getCountNodesView();
			INT_64 key = lrand();
			BSTtree.Insert(key, 1);
			Rbtree.Insert(key, 1);
			I += BSTtree.getCountNodesView();
			Ib += Rbtree.getCountNodesView();
			m[ind] = key;
			try {
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				Rbtree.GetData(m[rand() % n]);
				Sb += Rbtree.getCountNodesView();
			}
			catch (RbTreeException&) { Sb += Rbtree.getCountNodesView(); };
		}
	cout << "BST-дерево" << endl;
	cout << "1.39*log2(n)=" << (log((double)n) / log(2.0)) * 1.39 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	cout << "RB-Дерево" << endl;
	cout << "1.002log2(n)=" << 1.002 * (log((double)n) / log(2.0)) << endl;
	cout << "Размер дерева после:" << Rbtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << Ib / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << Db / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << Sb / (n / 2) << endl;
	delete[] m;
}
//Программа тестирования вырожденного дерева
void TestEffect::test_sort(int n)
{
	Tree<INT_64, int> BSTtree;
	RbTree<INT_64, int> Rbtree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++)
	{
		m[i] = i * 10000;
		BSTtree.Insert(m[i], 1);
		Rbtree.Insert(m[i], 1);
	}
	BSTtree.getCountNodesView();

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
			BSTtree.Delete(k);
			Rbtree.Delete(k);
			D += BSTtree.getCountNodesView();
			Db += Rbtree.getCountNodesView();
			BSTtree.Insert(m[rand() % n], 1);
			Rbtree.Insert(m[rand() % n], 1);
			I += BSTtree.getCountNodesView();
			Ib += Rbtree.getCountNodesView();
			k = lrand() % (10000 * n);
			k = k + !(k % 2);
			try
			{
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				Rbtree.GetData(m[rand() % n]);
				Sb += Rbtree.getCountNodesView();
			}
			catch (RbTreeException&) { Sb += Rbtree.getCountNodesView(); };
		}
		else
		{
			int ind = rand() % n;
			BSTtree.Delete(m[ind]);
			Rbtree.Delete(m[ind]);
			D += BSTtree.getCountNodesView();
			Db += Rbtree.getCountNodesView();
			int k = lrand() % (10000 * n);
			k = k + k % 2;
			BSTtree.Insert(k, 1);
			Rbtree.Insert(k, 1);
			I += BSTtree.getCountNodesView();
			Ib += Rbtree.getCountNodesView();
			m[ind] = k;
			try {
				BSTtree.GetData(m[rand() % n]);
				S += BSTtree.getCountNodesView();
			}
			catch (TreeException&) { S += BSTtree.getCountNodesView(); }
			try
			{
				Rbtree.GetData(m[rand() % n]);
				Sb += Rbtree.getCountNodesView();
			}
			catch (TreeException&) { Sb += Rbtree.getCountNodesView(); };
		}
	cout << "BST-дерево" << endl;
	cout << "n/2=" << n / 2 << endl;
	cout << "Размер дерева после:" << BSTtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << I / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << D / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << S / (n / 2) << endl;
	cout << "RB-Дерево" << endl;
	cout << "1.002log2(n)=" << 1.002 * (log((double)n) / log(2.0)) << endl;
	cout << "Размер дерева после:" << Rbtree.GetSize() << endl;
	cout << "Трудоемкость вставки: " << Ib / (n / 2) << endl;
	cout << "Трудоемкость удаления: " << Db / (n / 2) << endl;
	cout << "Трудоемкость поиска: " << Sb / (n / 2) << endl;
	delete[] m;
}