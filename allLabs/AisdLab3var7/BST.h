#pragma once
#include <iostream>
#include <stack>
using namespace std;

class TreeException
{
	string code;
public:
	TreeException() { code = "Исключение"; }
	string What() { return code; }
};

template<class K, class T>
class Tree
{
public:
	class Node
	{
	public:
		K key;
		T data;
		int n;
		Node* left, *right, *parent;
		Node(K k, T d)	
		{
			key = k;
			data = d;
			left = right = parent = NULL;
			n = 1;
		}
	};
	Node* root;
	int size;
	int cnt;
public:
	Tree(); //Конструктор
	Tree(Tree<K, T>& t); //Конструктор копирования
	~Tree(); //Деструктор
	int GetSize(); //Опрос размера дерева
	void Clear(); //Очистка дерева
	bool IsEmpty(); //Проверка дерева на пустоту
	T GetData(K key); //Чтение данных по ключу
	bool Replace(K key, T val); //Запись данных по ключу
	bool Insert(K key, T val);//Включение данных по ключу
	bool Delete(K key); //Удаление данных по ключу
	void InOrderTraversal(); //Обход узлов дерева по схеме LTR
	bool RRWGK(K key); //Вставка в корень дерева элемента с ключом, большим заданного значения
	void Show(); //Вертикальная печать дерева
	int getCountNodesView(); //Число узлов, просмотренных пред. операцией
private:
	void CopyTree(Node* r);	//Вспомогательная функция для копирования дерева
	void _InOrder(Node* r); //Вспомогательная функция для обхода дерева
	void _Show(Node* r, int level); //Вспомогательная функция для вертикальной печати 	
	Node* _RRWGK_findGreaterNode(K key, Node* current, Node* lastLeft, std::stack<bool>* path_turn_ref, std::stack<Node*>* path_ref); //Вспомогательная функция для вставки в корень
	Node* _GetData(K key, Node* root); //Вспомогательная функция для чтения данных по ключу
	Node* _Insert(K key, T val, Node* root, bool* inserted); //Вспомогательная функция для записи данных по ключу
	Node* _Del(Node* targetReplaceWith, Node* current); //Вспомогательная функция для удаления данных по ключу
	Node* _Delete(Node* current, Node* targetParent, K key, bool* deleted); //Вспомогательная функция для удаления данных по ключу
	Node* BSTPredecessor(Node* x); //Ищем узел с предыдущим по значению ключом
	Node* BSTSuccessor(Node* x); //Ищем узел со следующим по значению ключом
	Node* Max(Node* t);	//Ищем узел с максимальным ключом
	Node* RParent(Node* t, Node* x);
	Node* Min(Node* t);	//Ищем узел с минимальным ключом
	Node* LParent(Node* t, Node* x);
public:
	class Iterator
	{
		Tree<K, T>* owner;
	public:
		Node* cur;
		Iterator(Tree<K, T>* treeOwner);
		T& operator *();
		void operator ++();
		void operator --();
		bool operator ==(const Iterator& iterator) const;
		bool operator !=(const Iterator& iterator) const;
	};
	Iterator beg();
	Iterator end();
	class ReverseIterator
	{
		Tree<K, T>* owner;
	public:
		Node* cur;
		ReverseIterator(Tree<K, T>* treeOwner);
		T& operator *();
		void operator ++();
		void operator --();
		bool operator ==(const ReverseIterator& reviterator) const;
		bool operator !=(const ReverseIterator& reviterator) const;
	};
	ReverseIterator rbeg();
	ReverseIterator rend();
};
//Конструктор
template <class K, class T>
Tree<K, T>::Tree() {
	root = NULL;
	size = 0;
	cnt = 0;
}
//Конструктор копирования
template <class K, class T>
Tree<K, T>::Tree(Tree<K, T>& t)
{
	root = NULL;
	size = 0;
	CopyTree(t.root);
}
//Вспомогательная функция для копирования дерева
template <class K, class T>
void Tree<K, T>::CopyTree(typename Tree<K, T>::Node* r)
{
	if (r == NULL)
		return;
	Insert(r->key, r->data);
	CopyTree(r->left);
	CopyTree(r->right);
}
//Деструктор
template <class K, class T>
Tree<K, T>::~Tree() {
	Clear();
}
//Очистка дерева
template <class K, class T>
void Tree<K, T>::Clear()
{
	if (IsEmpty()) return;
	stack<Node*> s1, s2;
	Node* t;
	s1.push(root);
	while (!s1.empty())
	{
		t = s1.top();
		s1.pop();
		s2.push(t);
		if (t->left != NULL)
			s1.push(t->left);
		if (t->right != NULL)
			s1.push(t->right);
		while (!s2.empty())
		{
			t = s2.top();
			s2.pop();
			delete t;
			size--;
		}
	}
	root = NULL;
	size = 0;
}
//Получение размера
template <class K, class T>
int Tree<K, T>::GetSize() {
	return size;
}
//Проверка на пустоту
template <class K, class T>
bool Tree<K, T>::IsEmpty()
{
	return (size == 0);
}
//Получение данных по ключу
template <class K, class T>
T Tree<K, T>::GetData(K key) {
	Node* targetNode = _GetData(key, root);
	if (targetNode == NULL) throw TreeException();
	return targetNode->data;
}
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::_GetData(K key, Node* current) {
	cnt++;
	if (current != NULL) {
		if (current->key != key) {
			if (key < current->key)
				return _GetData(key, current->left);
			else
				return _GetData(key, current->right);
		}
	}
	return current;
}
//Запись данных по ключу
template <class K, class T>
bool Tree<K, T>::Replace(K key, T val) {
	Node* targetNode = _GetData(key, root);
	if (targetNode == NULL) return false;
	targetNode->data = val;
	return true;
}
//Вставка
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::_Insert(K key, T val, Node* current, bool* inserted) {
	cnt++;
	if (current == NULL) {
		*inserted = true;
		root = new Node(key, val);
		size++;
		return root;
	}
	if (key == current->key) {
		*inserted = false;
		return NULL;
	}
	if (key < current->key && current->left == NULL) {
		*inserted = true;
		current->left = new Node(key, val);
		size++;
		return current->left;
	}
	else if (key < current->key && current->left != NULL) return _Insert(key, val, current->left, inserted);
	if (key > current->key && current->right == NULL) {
		*inserted = true;
		current->right = new Node(key, val);
		size++;
		return current->right;
	}
	else if (key > current->key && current->right != NULL) return _Insert(key, val, current->right, inserted);
	return NULL;
}
template <class K, class T>
bool Tree<K, T>::Insert(K key, T val) {
	bool inserted = false;
	_Insert(key, val, root, &inserted);
	return inserted;
}
//Удаление
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::_Delete(Node* current, Node* targetParent, K key, bool* deleted) {
	if (current == NULL) {
		*deleted = false;
		return NULL;
	}
	cnt++;
	if (key < current->key) {
		_Delete(current->left, current, key, deleted);
		return current;
	}
	if (key > current->key) {
		_Delete(current->right, current, key, deleted);
		return current;
	}
	if (*deleted == true) return current;
	*deleted = true;
	size--;
	if (current->left == NULL && current->right == NULL) {
		if (targetParent == NULL) root = NULL;
		else {
			if (targetParent->left == current) targetParent->left = NULL;
			if (targetParent->right == current) targetParent->right = NULL;
		}
		delete current;
		return NULL;
	}
	if (current->left == NULL && current->right != NULL) {
		Node* x = current->right;
		if (targetParent == NULL) root = current->right;
		else {
			if (targetParent->left == current) targetParent->left = current->right;
			if (targetParent->right == current) targetParent->right = current->right;
		}
		return x;
	}
	if (current->right == NULL && current->left != NULL) {
		Node* x = current->left;
		if (targetParent == NULL) root = current->left;
		else {
			if (targetParent->left == current) targetParent->left = current->left;
			if (targetParent->right == current) targetParent->right = current->left;
		}
		return x;
	}
	current->right = _Del(current->right, current);
	return current;
}
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::_Del(Node* targetReplaceWith, Node* current) {
	cnt++;
	if (targetReplaceWith->left != NULL) {
		targetReplaceWith->left = _Del(targetReplaceWith->left, current);
		return targetReplaceWith;
	}
	current->key = targetReplaceWith->key;
	current->data = targetReplaceWith->data;
	Node* x = targetReplaceWith->right;
	delete targetReplaceWith;
	return x;
}
template <class K, class T>
bool Tree<K, T>::Delete(K key) {
	bool deleted = false;
	_Delete(root, NULL, key, &deleted);
	return deleted;
}
//Вставка в корень дерева элемента с ключом, большим заданного значения
template <class K, class T>
bool Tree<K, T>::RRWGK(K key) {
	if (root == nullptr) return false;
	std::stack<Node*> path = std::stack<Node*>();
	std::stack<bool> path_turn = std::stack<bool>();

	Node* targetNode = _RRWGK_findGreaterNode(key, root, root, &path_turn, &path);
	if (targetNode == nullptr) return false;
	while (!path.empty() && path.top() != targetNode) {
		path.pop(); path_turn.pop();
	}
	if (path.empty()) return false;
	if (path.size() == 1) return true;
	path.pop(); path.pop();
	while (path.size() > 0) {
		bool turn_dir = path_turn.top();
		path_turn.pop();
		if (path_turn.top()) path.top()->right = turn_dir ? _rotateL(path.top()->right) : _rotateR(path.top()->right);
		else path.top()->left = turn_dir ? _rotateL(path.top()->left) : _rotateR(path.top()->left);
		path.pop();
	}
	root = path_turn.top() ? _rotateL(root) : _rotateR(root);
	return true;
}
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::_RRWGK_findGreaterNode(K key, Node* current, Node* lastLeft, std::stack<bool>* path_turn_ref, std::stack<Node*>* path_ref)
{
	if (current == nullptr) return nullptr;
	path_ref->push(current);
	if (current->key > key) {
		if (current->left != nullptr) {
			path_turn_ref->push(false);
			return _RRWGK_findGreaterNode(key, current->left, current, path_turn_ref, path_ref);
		}
		else return current;
	}
	else {
		if (current->right != nullptr) {
			path_turn_ref->push(true);
			return _RRWGK_findGreaterNode(key, current->right, lastLeft, path_turn_ref, path_ref);
		}
		else if (lastLeft->key > key) return lastLeft;
		else return nullptr;
	}
}
//Обход узлов дерева по схеме LTR
template <class K, class T>
void Tree<K, T>::InOrderTraversal()
{
	if (root != NULL) _InOrder(root);
	else cout << "Дерево пусто";
	cout << endl;
}
template <class K, class T>
void Tree<K, T>::_InOrder(typename Tree<K, T>::Node* r)
{
	if (r == NULL) return;
	_InOrder(r->left);
	cout << r->key << " ";
	_InOrder(r->right);
}
//Вертикальная печать
template <class K, class T>
void Tree<K, T>::Show() {
	if (root == NULL) {
		cout << "Дерево пусто" << endl;
		return;
	}
	_Show(root, 0);
}
template <class K, class T>
void  Tree<K, T>::_Show(typename Tree<K, T>::Node* r, int level) {
	if (r == NULL) return;
	_Show(r->right, level + 1);
	for (int i = 0; i < 3 * level; i++) cout << " ";
	cout << r->key << endl;
	_Show(r->left, level + 1);
	return;
}
//Функции для итератора
//Узел с предыдущим по значению ключом
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::BSTPredecessor(typename Tree<K, T>::Node* x) {
	if (x == NULL) return NULL;
	if (x->left != NULL) return Max(x->left);
	else return RParent(root, x);
}
//Узел с максимальным ключом
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::Max(typename Tree<K, T>::Node* t) {
	if (t == NULL) return NULL;
	while (t->right != NULL) t = t->right;
	return t;
}
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::RParent(typename Tree<K, T>::Node* t, typename Tree<K, T>::Node* x) {
	if (t == x) return NULL;
	if (x->key > t->key) {
		Node* rp = RParent(t->right, x);
		if (rp != NULL) return rp;
		else return t;
	}
	else return RParent(t->left, x);
}
//Узел со следующим по значению ключом
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::BSTSuccessor(typename Tree<K, T>::Node* x) {
	if (x == NULL) return NULL;
	if (x->right != NULL) return Min(x->right);
	else return LParent(root, x);
}
//Узел с минимальный ключом
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::Min(typename Tree<K, T>::Node* t) {
	if (t == NULL) return NULL;
	while (t->left != NULL) t = t->left;
	return t;
}
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::LParent(typename Tree<K, T>::Node* t, typename Tree<K, T>::Node* x) {
	if (t == x) return NULL;
	if (x->key < t->key)
	{
		Node* lp = LParent(t->left, x);
		if (lp != NULL) return lp;
		else return t;
	}
	else return LParent(t->right, x);
}
//Получение счетчика пройденных узлов
template <class K, class T>
int Tree<K, T>::getCountNodesView()
{
	int temp = cnt;
	cnt = 0;
	return temp;
}
//Итератор
//Конструктор итератора
template <class K, class T>
Tree<K, T>::Iterator::Iterator(Tree<K, T>* treeOwner) {
	owner = treeOwner;
	cur = NULL;
}
//В начало
template <class K, class T>
typename Tree<K, T>::Iterator Tree<K, T>::beg()
{
	Iterator iter = Iterator(this);
	Node* cur = root;
	if (cur != nullptr)
		while (cur->left != nullptr)
			cur = cur->left;
	iter.cur = cur;
	return iter;
}
//В конец
template <class K, class T>
typename Tree<K, T>::Iterator Tree<K, T>::end()
{
	Iterator iter = Iterator(this);
	Node* cur = root;
	if (cur != nullptr) {
		while (cur->right != nullptr)
			cur = cur->right;
		iter.cur = cur->right;
	}
	return iter;
}
//К предыдущему
template <class K, class T>
void Tree<K, T>::Iterator::operator--() {
	cur = owner->BSTPredecessor(cur);
}
//К следующему
template <class K, class T>
void Tree<K, T>::Iterator::operator++() {
	cur = owner->BSTSuccessor(cur);
}
//Доступ к данным текущего
template <class K, class T>
T& Tree<K, T>::Iterator::operator *() {
	if (cur == NULL)
		throw TreeException();
	return cur->data;
}
//Проверка на равенство прямых итераторов
template <class K, class T>
bool Tree<K, T>::Iterator::operator ==(const Iterator& iterator) const {
	return cur == iterator.cur;
}
//Проверка на неравенство прямых итераторов
template <class K, class T>
bool Tree<K, T>::Iterator::operator !=(const Iterator& iterator) const {
	return cur != iterator.cur;
}
//Обратный итератор
template <class K, class T>
Tree<K, T>::ReverseIterator::ReverseIterator(Tree<K, T>* treeOwner) {
	owner = treeOwner;
	cur = NULL;
}
//Запрос обратного итератора
template <class K, class T>
typename Tree<K, T>::ReverseIterator Tree<K, T>::rbeg()
{
	ReverseIterator iter = ReverseIterator(this);
	Node* cur = root;
	if (cur != nullptr)
		while (cur->right != nullptr)
			cur = cur->right;
	iter.cur = cur;
	return iter;
}
//Запрос "неустановленного" обратного итератора
template <class K, class T>
typename Tree<K, T>::ReverseIterator Tree<K, T>::rend()
{
	ReverseIterator iter = ReverseIterator(this);
	Node* cur = root;
	if (cur != nullptr) {
		while (cur->left != nullptr)
			cur = cur->left;
		iter.cur = cur->left;
	}
	return iter;
}
//К предыдущему
template <class K, class T>
void Tree<K, T>::ReverseIterator::operator--() {
	cur = owner->BSTSuccessor(cur);
}
//К следующему
template <class K, class T>
void Tree<K, T>::ReverseIterator::operator++() {
	cur = owner->BSTPredecessor(cur);
}
//Доступ к данным текущего
template <class K, class T>
T& Tree<K, T>::ReverseIterator::operator *() {
	if (cur == NULL)
		throw TreeException();
	return cur->data;
}
//Проверка на равенство обратных итераторов
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator ==(const ReverseIterator& reviterator) const {
	return cur == reviterator.cur;
}
//Проверка на неравенство обратных итераторов
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator !=(const ReverseIterator& reviterator) const {
	return cur != reviterator.cur;
}