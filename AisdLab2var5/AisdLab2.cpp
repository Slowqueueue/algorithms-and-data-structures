#include "BST.h" 
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
	Tree<int, int> tree;
	Tree<int, int>::Iterator it = Tree<int, int>::Iterator(&tree);
	Tree<int, int>::ReverseIterator revit = Tree<int, int>::ReverseIterator(&tree);
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
		cout << "9. Определение критерия сбалансированности каждого узла" << endl;
		cout << "10.Меню итераторов" << endl;
		cout << "11.Вывод последовательности ключей по схеме LRT" << endl;
		cout << "12.Тестирование трудоемкости для случайного дерева" << endl;
		cout << "13.Тестирование трудоемкости для вырожденного дерева" << endl;
		cout << "14.Выход" << endl;
		int t;
		int value, key;
	
		cin >> t;
		switch (t)
		{
		case 1:
			cout << "-------------------------------" << endl;
			tree.Show();
			cout << "-------------------------------" << endl << endl;
			break;
		case 2:
			tree.Clear();
			it = tree.beg();
			revit = tree.rbeg();
			cout << endl;
			break;
		case 3:
			cout << tree.IsEmpty() << endl << endl;
			break;
		case 4:
			cin >> key;
			try
			{
				cout << tree.GetData(key) << endl;
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
				cout << tree.Replace(key, value) << endl;
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
			cout << tree.Insert(key, value) << endl << endl;
			break;
		case 7:
			cin >> key;
			cout << tree.Delete(key) << endl << endl;
			if (!useReverseiter && !it.is_off()) it = tree.beg();
			if (useReverseiter && !revit.is_rev_off()) revit = tree.rbeg();
			break;
		case 8:
			cout << tree.GetSize() << endl << endl;
			break;
		case 9:
			tree.FindCritStab();
			cout << endl;
			break;
		case 10: {
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
					it = tree.beg();
					useReverseiter = false;
					cout << endl;
					break;
				case 3:
					it = tree.end();
					useReverseiter = false;
					cout << endl;
					break;
				case 4:
					revit = tree.rbeg();
					useReverseiter = true;
					cout << endl;
					break;
				case 5:
					revit = tree.rend();
					useReverseiter = true;
					cout << endl;
					break;
				case 6:
					try {
						if (!useReverseiter) ++it;
						else ++revit;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
					cout << endl;
					break;
				case 7:
					try {
						if (!useReverseiter) --it;
						else --revit;
					}
					catch (TreeException e)
					{
						cerr << e.What() << endl;
					}
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
		case 11:
			tree.PostorderTraversal();
			cout << endl;
			break;
		case 12:
			int n;
			cout << "Введите размер дерева:" << endl;
			cin >> n;
			TestEffect::test_rand(n);
			cout << endl;
			break;
		case 13:
			int n2;
			cout << "Введите размер дерева:" << endl;
			cin >> n2;
			TestEffect::test_sort(n2);
			cout << endl;
			break;
		case 14:
			exit(0);
		default:
			cout << "Неверный номер команды" << endl << endl;
		}
	}
}
//Программа тестирования
void TestEffect::test_rand(int n)
{
	Tree<INT_64, int> tree;
	INT_64* m = new INT_64[n];
	for (int i = 0; i < n; i++)
	{
		m[i] = lrand();
		tree.Insert(m[i], 1);
	}
	tree.getCountNodesView();

	cout << "Размер дерева до: " << tree.GetSize() << endl;
	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++)
		if (i % 10 == 0)
		{
			tree.Delete(lrand());
			D += tree.getCountNodesView();
			tree.Insert(m[rand() % n], 1);
			I += tree.getCountNodesView();
			try
			{
				tree.GetData(lrand());
				S += tree.getCountNodesView();
			}
			catch (TreeException&) { S += tree.getCountNodesView(); }
		}
		else
		{
			int ind = rand() % n;
			tree.Delete(m[ind]);
			D += tree.getCountNodesView();
			INT_64 key = lrand();
			tree.Insert(key, 1);
			I += tree.getCountNodesView();
			m[ind] = key;
			try {
				tree.GetData(m[rand() % n]);
				S += tree.getCountNodesView();
			}
			catch (TreeException&) { S += tree.getCountNodesView(); }

		}

	cout << "Размер дерева после: " << tree.GetSize() << endl;
	cout << "1.39*log2(n)=" << 1.39 * (log(n) / log(2)) << endl;
	cout << "Вставка: " << I / (n / 2) << endl;
	cout << "Удаление: " << D / (n / 2) << endl;
	cout << "Поиск: " << S / (n / 2) << endl;
	delete[] m;
}

void TestEffect::test_sort(int n)
{
	if (n > 2000) {
		cout << "Максимальный размер вырожденного дерева - 2000 узлов" << endl;
		return;
	}
	Tree<INT_64, int> tree;
	INT_64* m = new INT_64[n];

	for (int i = 0; i < n; i++) {
		m[i] = i * 10000;
		if (n <= 2000) tree.Insert(m[i], 1);
	}
	tree.getCountNodesView();
	cout << "Размер дерева до: " << tree.GetSize() << endl;
	double I = 0;
	double D = 0;
	double S = 0;

	for (int i = 0; i < n / 2; i++)
	{
		if (i % 10 == 0)
		{
			int k = lrand() % (10000 * n);
			k = k + !(k % 2);
			tree.Delete(k);
			D += tree.getCountNodesView();
			tree.Insert(m[rand() % n], 1);
			I += tree.getCountNodesView();
			k = lrand() % (10000 * n);
			k = k + !(k % 2);
			try {
				tree.GetData(k);
				S += tree.getCountNodesView();
			}
			catch (TreeException&) { S += tree.getCountNodesView(); }
		}
		else
		{
			int ind = rand() % n;
			try
			{
				tree.GetData(m[rand() % n]);
				S += tree.getCountNodesView();
			}
			catch (TreeException&) { S += tree.getCountNodesView(); }
			tree.Delete(m[ind]);
			D += tree.getCountNodesView();
			int k = lrand() % (10000 * n);
			k = k + k % 2;
			tree.Insert(k, 1);
			I += tree.getCountNodesView();
			m[ind] = k;

		}
	}
	cout << "Размер дерева после: " << tree.GetSize() << endl;
	cout << "n/2=" << n / 2 << endl;
	cout << "Вставка: " << I / (n / 2) << endl;
	cout << "Удаление: " << D / (n / 2) << endl;
	cout << "Поиск: " << S / (n / 2) << endl;
	delete[] m;
}