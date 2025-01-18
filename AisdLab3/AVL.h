#pragma once
#include <iostream>
#include <stack>
using namespace std;

class AvlTreeException
{
	string code;
public:
	AvlTreeException() { code = "Исключение"; }
	string What() { return code; }
};

template<class K, class T>
class AvlTree : public Tree<K, T>
{
public:
	bool Insert(K key, T val, double& IA);//Включение данных по ключу
	bool Delete(K key, double& DA); //Удаление данных по ключу
	void Show(); //Вертикальная печать дерева
	T& GetData(K key, double& SA); //Чтение данных по ключу
private:
	void _Show(typename Tree<K,T>::Node* r, int level); //Вспомогательная функция для вертикальной печати 	
	typename Tree<K, T>::Node* _GetData(K key, typename Tree<K, T>::Node* root, double& SA); //Вспомогательная функция для чтения данных по ключу
	typename Tree<K, T>::Node* RDel(typename Tree<K, T>::Node* t, bool& del);	//RDel - однократный правый поворот для операции удаления
	typename Tree<K, T>::Node* LDel(typename Tree<K, T>::Node* t, bool& del);	//LDel - однократный левый поворот для операции удаления
	typename Tree<K, T>::Node* RLDel(typename Tree<K, T>::Node* t, bool& del);	//RLDel - двукратный поворот для операции удаления
	typename Tree<K, T>::Node* LRDel(typename Tree<K, T>::Node* t, bool& del);	//LRDel - двукратный поворот для операции удаления
	typename Tree<K, T>::Node* LR(typename Tree<K, T>::Node* t);	//LR-поворот
	typename Tree<K, T>::Node* RL(typename Tree<K, T>::Node* t);	//RL-поворот
};
//Вставка
template <typename K, typename T>
bool AvlTree<K, T>::Insert(K key, T val, double& IA) {
	//Вводим два дополнительных стека
	//Стек для хранения проиденных элементов
	typename Tree<K, T>::Node** node_stack = new typename Tree<K, T>::Node * [this->size + 1];
	//Стек для хранения направления движения (влево от вершины или вправо)
	int* dir_stack = new int[this->size + 1];
	//Счётчик, отражающий количество элементов в стеках
	int dir = -1;
	//Элемент для хранения текущего значения
	typename Tree<K, T>::Node* t = this->root;
	//Ищем место вставки
	while (t)
	{
		this->cnt++;
		IA++;
		//Если ключи равны, то очищаем память и и возвращаем false
		if (key == t->key) {
			delete[] node_stack;
			delete[] dir_stack;
			return false;
		}
		//Сравниваем ключи и перемещаемся по дереву
		if (key > t->key) {
			node_stack[++dir] = t;
			dir_stack[dir] = -1; //-1 - движение вправо
			t = t->right;
		}
		else
		{
			node_stack[++dir] = t;
			dir_stack[dir] = 1; //1 означает движение влево
			t = t->left;
		}
	}
	//Создаем новый элемент
	t = new typename Tree<K, T>::Node(key, val);
	//Вставляем элемент
	if (!this->root) this->root = t;
	else
	{
		if (dir_stack[dir] == -1) node_stack[dir]->right = t;
		else node_stack[dir]->left = t;
	}
	bool h = true; //Критерий увеличения высоты
	while (dir + 1)
	{
		if (h)
		{
			//Корректируем значение коэффицента сбалансированности
			node_stack[dir]->criteria += dir_stack[dir];
			typename Tree<K, T>::Node* buffer = node_stack[dir];
			switch (node_stack[dir]->criteria)
			{
			case 0:
				h = 0;
				break;
			case 1:
				h = 1;
				break;
			case -1:
				h = 1;
				break;
			case 2:
				node_stack[dir]->criteria = 1;
				if ((node_stack[dir]->left->criteria >= 0)) buffer =
					RDel(node_stack[dir], h);
				else buffer = LR(node_stack[dir]);
				h = 0;
				break;
			case -2:
				node_stack[dir]->criteria = -1;
				if ((node_stack[dir]->right->criteria <= 0)) buffer =
					LDel(node_stack[dir], h);
				else buffer = RL(node_stack[dir]);
				h = 0;
				break;
			}
			//Корректируем общую структуру дерева
			if (!dir) this->root = buffer;
			else if (dir_stack[dir - 1] == -1) node_stack[dir - 1]->right = buffer;
			else node_stack[dir - 1]->left = buffer;
		}
		dir--;
	}
	//Очищаем память
	delete[] node_stack;
	delete[] dir_stack;
	this->size++;
	return true;
}
//Удаление
template <class K, class T>
bool AvlTree<K, T>::Delete(K key, double& DA) {
	//Выделяем память под стеки
	typename Tree<K, T>::Node** node_stack = new typename Tree<K, T>::Node * [this->size];
	int* dir_stack = new int[this->size];
	int top = -1; //Указатель на вершину стека

	if (!this->root) return false;

	typename Tree<K, T>::Node* t = this->root;
	//Ищем необходимый ключ
	while (t)
	{
		this->cnt++;
		DA++;
		if (key == t->key) break;

		node_stack[++top] = t;
		if (key < t->key) {
			dir_stack[top] = 1; //1 - пошли налево
			t = t->left;
		}
		else {
			dir_stack[top] = -1; //-1 - пошли направо
			t = t->right;
		}
	}
	if (!t) return false;

	bool isroot = false;
	if (t == this->root) isroot = true;

	bool del = true;

	//Случай, когда удаляемая вершина терминальная
	if ((t->right == NULL) && (t->left == NULL)) {
		delete t;
		if (isroot) this->root = NULL;
		else {
			if (dir_stack[top] == -1) node_stack[top]->right = NULL;
			else node_stack[top]->left = NULL;
		}
	}
	else
		//Случай, когда нет левого сына
		if ((t->right != NULL) && (t->left == NULL)) {
			if (isroot) this->root = t->right;
			else {
				if (dir_stack[top] == -1) node_stack[top]->right = t->right;
				else node_stack[top]->left = t->right;
			}
			delete t;
		}
		else
			//Случай, когда нет правого сына
			if ((t->right == NULL) && (t->left != NULL)) {
				if (isroot) this->root = t->left;
				else
				{
					if (dir_stack[top] == -1) node_stack[top]->right = t->left;
					else node_stack[top]->left = t->left;
				}
				delete t;
			}
			else
				//Случай, когда есть оба сына
				if ((t->right != NULL) && (t->left != NULL)) {
					//У левой вершины нет правого сына
					if (t->left->right == NULL) {
						this->cnt++;
						DA++;

						typename Tree<K, T>::Node* nd = t->left;
						nd->right = t->right;

						nd->criteria = t->criteria; //Перерасчёт коэффицентов сбалансированности

						node_stack[++top] = nd;

						dir_stack[top] = 1;

						if (!top) this->root = nd;
						else {
							if (dir_stack[top - 1] == 1) node_stack[top - 1]->left = nd;
							else node_stack[top - 1]->right = nd;
						}
						delete t;
					}
					else {
						node_stack[++top] = t;
						dir_stack[top] = 1;
						this->cnt++;
						DA++;
						typename Tree<K, T>::Node* nd = t->left;
						node_stack[++top] = nd;
						dir_stack[top] = -1;
						this->cnt++;
						DA++;
						nd = nd->right;
						while (nd->right)
						{
							this->cnt++;
							DA++;
							node_stack[++top] = nd;
							dir_stack[top] = -1;
							nd = nd->right;
						}
						t->data = nd->data;
						t->key = nd->key;

						if (nd->left == NULL) node_stack[top]->right = NULL;
						else node_stack[top]->right = nd->left;
						delete nd;
					}
				}
	this->size--;
	while (top + 1)
	{
		if (del)
		{
			//Корректируем критерии сбалансированности
			node_stack[top]->criteria -= dir_stack[top];
			typename Tree<K, T>::Node* buffer = node_stack[top];
			//Теперь анализируем текущее состояние
			switch (node_stack[top]->criteria)
			{
			case 0:
				del = true;
				buffer = node_stack[top];
				break;
			case -1:
				del = false;
				buffer = node_stack[top];
				break;
			case 1:
				del = false;
				buffer = node_stack[top];
				break;
			case 2: //Разбалансировка узла
				node_stack[top]->criteria = 1;
				if ((node_stack[top]->left->criteria >= 0)) buffer =
					RDel(node_stack[top], del);
				else buffer = LRDel(node_stack[top], del);
				break;
			case -2: //Разбалансировка узла
				node_stack[top]->criteria = -1;
				if ((node_stack[top]->right->criteria <= 0)) buffer =
					LDel(node_stack[top], del);
				else buffer = RLDel(node_stack[top], del);
				break;
			}
			//Теперь необходимо поддержать общую структуру дерева в целостности
			if (!top) this->root = buffer;
			else if (dir_stack[top - 1] == -1) node_stack[top - 1]->right =
				buffer;
			else node_stack[top - 1]->left = buffer;

		}
		top--;
	}
	//Очищаем за собой память
	delete[] node_stack;
	delete[] dir_stack;
	return true;
}
//Вертикальная печать
template <class K, class T>
void AvlTree<K, T>::Show() {
	if (this->root == NULL) {
		cout << "Дерево пусто" << endl;
		return;
	}
	_Show(this->root, 0);
}
template <class K, class T>
void  AvlTree<K, T>::_Show(typename Tree<K, T>::Node* r, int level) {
	if (r == NULL) return;
	_Show(r->right, level + 1);
	for (int i = 0; i < 3 * level; i++) cout << " ";
	cout << r->key << "(" << r->criteria << ")" << endl;
	_Show(r->left, level + 1);
	return;
}
//Получение данных по ключу
template<class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::_GetData(K key, typename Tree<K, T>::Node* current, double& SA) {
	while (current != NULL && key != current->key) {
		SA++;
		this->cnt++;
		if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}
template<class K, class T>
T& AvlTree<K, T>::GetData(K key, double& SA) {
	SA++;
	this->cnt++;
	typename Tree<K, T>::Node* targetNode = _GetData(key, this->root, SA);
	if (targetNode == NULL) throw AvlTreeException();
	return targetNode->data;
}
//RDel - однократный правый поворот для операции удаления
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::RDel(typename Tree<K,T>::Node* t, bool& del) {
	typename Tree<K, T>::Node* x = t->left;
	t->left = x->right;
	x->right = t;
	if (x->criteria == 1) {
		x->criteria = t->criteria = 0;
		del = true;
	}
	else if (x->criteria == 0) {
		x->criteria = -1;
		t->criteria = 1;
		del = false;
	}
	return x;
}
//LDel - однократный левый поворот для операции удаления
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::LDel(typename Tree<K, T>::Node* t, bool& del) {
	typename Tree<K, T>::Node* x = t->right;
	t->right = x->left;
	x->left = t;
	if (x->criteria == -1) {
		x->criteria = t->criteria = 0;
		del = true;
	}
	else if (x->criteria == 0) {
		x->criteria = 1;
		t->criteria = -1;
		del = false;
	}
	return x;
}
//RL-поворот
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::RL(typename Tree<K, T>::Node* t) {
	typename Tree<K, T>::Node* x = t->right;
	typename Tree<K, T>::Node* y = x->left;
	x->left = y->right;
	y->right = x;
	t->right = y->left;
	y->left = t;
	if (y->criteria == 0) {
		y->criteria = 0;
		t->criteria = 0;
		x->criteria = 0;
	}
	else if (y->criteria == 1) {
		y->criteria = 0;
		t->criteria = 0;
		x->criteria = -1;
	}
	else if (y->criteria == -1) {
		y->criteria = 0;
		t->criteria = 1;
		x->criteria = 0;
	}
	else {
		cout << "Ошибка RL поворота";
	}
	return y;
}
//LR-поворот
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::LR(typename Tree<K, T>::Node* t) {
	typename Tree<K, T>::Node* x = t->left;
	if ((!x) || (!x->right)) { cout << "Ошибка LR поворота"; }
	typename Tree<K, T>::Node* y = x->right;
	x->right = y->left;
	y->left = x;
	t->left = y->right;
	y->right = t;
	if (y->criteria == 0) {
		y->criteria = 0;
		t->criteria = 0;
		x->criteria = 0;
	}
	else if (y->criteria == 1) {
		y->criteria = 0;
		t->criteria = -1;
		x->criteria = 0;
	}
	else if (y->criteria == -1) {
		y->criteria = 0;
		t->criteria = 0;
		x->criteria = 1;
	}
	return y;
}
//Двукратный поворот RLDel
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::RLDel(typename Tree<K, T>::Node* t, bool& del) {
	typename Tree<K, T>::Node* x = t->right;

	typename Tree<K, T>::Node* y = x->left;
	t->right = y->left;
	y->left = t;
	x->left = y->right;
	y->right = x;
	if (y->criteria == 1) {
		x->criteria = -1;
		t->criteria = 0;
	}
	else if (y->criteria == -1) {
		x->criteria = 0;
		t->criteria = 1;
	}
	else x->criteria = t->criteria = 0;
	y->criteria = 0;
	del = true;
	return y;
}
//Двукратный поворот LRDel
template <class K, class T>
typename Tree<K,T>::Node* AvlTree<K, T>::LRDel(typename Tree<K, T>::Node* t, bool& del) {
	typename Tree<K, T>::Node* x = t->left;
	typename Tree<K, T>::Node* y = x->right;
	t->left = y->right;
	y->right = t;
	x->right = y->left;
	y->left = x;
	if (y->criteria == 1) {
		x->criteria = 0;
		t->criteria = -1;
	}
	else if (y->criteria == -1) {
		x->criteria = 1;
		t->criteria = 0;
	}
	else x->criteria = t->criteria = 0;
	y->criteria = 0;
	del = true;
	return y;
}