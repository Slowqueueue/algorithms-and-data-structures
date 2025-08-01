#pragma once
#include <iostream>
#include <stack>
using namespace std;

class RbTreeException
{
	string code;
public:
	RbTreeException() { code = "Исключение"; }
	string What() { return code; }
};

template<class K, class T>
class RbTree : public Tree<K, T>
{
public:
	bool Insert(K key, T val); //Включение данных по ключу
	bool Delete(K key); //Удаление данных по ключу
	void Show(); //Вертикальная печать дерева
private:
	void _Show(typename Tree<K,T>::Node* r, int level); //Вспомогательная функция для вертикальной печати 	
	void fixRBTree(typename Tree <K, T>::Node* x);	//Cохранение свойств красно-черного дерева
	bool isRed(typename Tree <K, T>::Node* node); //Проверка на цвет узла
	void setColor(typename Tree <K, T>::Node* node, bool color); //Установка цвета узла
	typename Tree<K, T>::Node* rotate(typename Tree <K, T>::Node* p, typename Tree <K, T>::Side side); //Поворот
	typename Tree<K, T>::Node* successor(typename Tree<K, T>::Node* t); //Поиск следующего по ключу узла
	typename Tree<K, T>::Node* getParent(typename Tree <K, T>::Node* node); //Вернуть родителя
	typename Tree<K, T>::Node* getLeft(typename Tree <K, T>::Node* node); //Вернуть левого потомка
	typename Tree<K, T>::Node* getRight(typename Tree <K, T>::Node* node); //Вернуть правого потомка
	typename Tree<K, T>::Node* min(typename Tree <K, T>::Node* t); //Поиск узла с минимальным ключом
	typename Tree<K, T>::Node* leftParent(typename Tree <K, T>::Node* t, typename Tree <K, T>::Node* x);
	typename Tree<K, T>::Node* rightParent(typename Tree <K, T>::Node* t, typename Tree <K, T>::Node* x);
};

template <class K, class T>
typename Tree<K, T>::Node* RbTree<K, T>::leftParent(typename Tree<K, T>::Node* t, typename Tree<K, T>::Node* x)
{
	if (t == x) return NULL;
	this->cnt++;
	if (x->key < t->key)
	{
		this->cnt++;
		typename Tree<K, T>::Node* lp = leftParent(t->left, x);
		if (lp != NULL) return lp;
		else return t;
	}
	else return leftParent(t->right, x);
}

template <class K, class T>
typename Tree<K, T>::Node* RbTree<K, T>::rightParent(typename Tree<K, T>::Node* t, typename Tree<K, T>::Node* x)
{
	if (t == x) return NULL;
	this->cnt++;
	if (x->key > t->key) 
	{
		this->cnt++;
		typename Tree<K, T>::Node* rp = rightParent(t->right, x);
		if (rp != NULL) return rp;
		else return t;
	}
	else return rightParent(t->left, x);
}

template <class K, class T>
typename Tree <K, T>::Node* RbTree<K, T>::getLeft(typename Tree <K, T>::Node* node)
{
	return node ? node->left : NULL;
}

template <class K, class T>
typename Tree <K, T>::Node* RbTree<K, T>::getRight(typename Tree <K, T>::Node* node)
{
	return node ? node->right : NULL;
}

template <class K, class T>
typename Tree <K, T>::Node* RbTree<K, T>::getParent(typename Tree <K, T>::Node* node)
{
	return node ? node->parent : NULL;
}


template <class K, class T>
void RbTree<K, T>::setColor(typename Tree <K, T>::Node* node, bool color) {
	if (node) node->color = color;
}

template <class K, typename T>
typename Tree<K, T>::Node* RbTree<K, T>::rotate(typename Tree <K, T>::Node* p, typename Tree <K, T>::Side side)
{
	if (!p) return NULL;
	if (side == this->LEFT)
	{
		typename Tree <K, T>::Node* r = p->right;
		p->right = r->left;
		if (r->left) r->left->parent = p;
		r->parent = p->parent;
		if (!p->parent)
		{
			this->root = r;
		}
		else if (p->parent->left == p)
		{
			p->parent->left = r;
		}
		else
		{
			p->parent->right = r;
		}
		r->left = p;
		p->parent = r;
		return r;
	}
	else
	{
		typename Tree <K, T>::Node* l = p->left;
		p->left = l->right;
		if (l->right) l->right->parent = p;
		l->parent = p->parent;
		if (!p->parent)
		{
			this->root = l;
		}
		else if (p->parent->right == p)
		{
			p->parent->right = l;
		}
		else
		{
			p->parent->left = l;
		}
		l->right = p;
		p->parent = l;
		return l;
	}
}

template <class K, class T>
typename Tree<K, T>::Node* RbTree<K, T>::min(typename Tree<K, T>::Node* t)
{
	if (t == NULL) return NULL;
	while (t->left != NULL) { t = t->left; this->cnt++; }
	return t;
}

template <class K, class T>
typename Tree<K, T>::Node* RbTree<K, T>::successor(typename Tree<K, T>::Node* x)
{
	if (x == NULL) return NULL;
	if (x->right != NULL) return min(x->right);
	else return leftParent(this->root, x);
}

template <class K, class T>
bool RbTree<K, T>::isRed(typename Tree <K, T>::Node* node)
{
	return node ? (node->color == RED) : false;
}

//Вставка
template <typename K, typename T>
bool RbTree<K, T>::Insert(K key, T val) {
	typename Tree <K, T>::Node* current = this->root;
	typename Tree <K, T>::Node* parent = nullptr;
	typename Tree <K, T>::Side side = this->LEFT;

	while (current) {
		this->cnt++;
		parent = current;
		if (key == current->key) {
			return false;
		}
		else if (key < current->key) {
			current = current->left;
			side = this->LEFT;
		}
		else {
			current = current->right;
			side = this->RIGHT;
		}
	}

	typename Tree <K, T>::Node* newNode = new typename Tree <K, T>::Node(key, val);
	newNode->parent = parent;

	if (!parent) {
		this->root = newNode;
	}
	else if (key < parent->key) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	current = newNode;
	while (current != this->root && isRed(current->parent)) {
		parent = current->parent;
		typename Tree <K, T>::Node* grandparent = parent->parent;

		if (parent == grandparent->left) {
			typename Tree <K, T>::Node* uncle = grandparent->right;

			if (isRed(uncle)) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				current = grandparent;
			}
			else {
				if (current == parent->right) {
					current = parent;
					rotate(current, this->LEFT);
					parent = current->parent;
				}
				parent->color = BLACK;
				grandparent->color = RED;
				rotate(grandparent, this->RIGHT);
			}
		}
		else {
			typename Tree <K, T>::Node* uncle = grandparent->left;

			if (isRed(uncle)) {
				parent->color = BLACK;
				uncle->color = BLACK;
				grandparent->color = RED;
				current = grandparent;
			}
			else {
				if (current == parent->left) {
					current = parent;
					rotate(current, this->RIGHT);
					parent = current->parent;
				}
				parent->color = BLACK;
				grandparent->color = RED;
				rotate(grandparent, this->LEFT);
			}
		}
	}

	this->root->color = BLACK;
	this->size++;
	return true;
}

//Cохранение свойств красно-черного дерева
template <class K, class T>
void RbTree<K, T>::fixRBTree(typename Tree <K, T>::Node* x)
{
	while (x != this->root && isRed(x) == BLACK)
	{
		if (x == getLeft(getParent(x)))
		{
			typename Tree <K, T>::Node* sibling = getRight(getParent(x));

			if (isRed(sibling) == RED) {
				setColor(sibling, BLACK);
				setColor(getParent(x), RED);
				rotate(getParent(x), this->LEFT);
				sibling = getRight(getParent(x));
			}

			if (!isRed(getLeft(sibling)) && !isRed(getRight(sibling))) {
				setColor(sibling, RED);
				x = getParent(x);
			}
			else {
				if (isRed(getRight(sibling)) == BLACK) {
					setColor(getLeft(sibling), BLACK);
					setColor(sibling, RED);
					rotate(sibling, this->RIGHT);
					sibling = getRight(getParent(x));
				}
				setColor(sibling, isRed(getParent(x)));
				setColor(getParent(x), BLACK);
				setColor(getRight(sibling), BLACK);
				rotate(getParent(x), this->LEFT);
				x = this->root;
			}
		}
		else {
			typename Tree <K, T>::Node* sibling = getLeft(getParent(x));

			if (isRed(sibling) == RED) {
				setColor(sibling, BLACK);
				setColor(getParent(x), RED);
				rotate(getParent(x), this->RIGHT);
				sibling = getLeft(getParent(x));
			}

			if (isRed(getRight(sibling)) == BLACK &&
				isRed(getLeft(sibling)) == BLACK) {
				setColor(sibling, RED);
				x = getParent(x);
			}
			else {
				if (isRed(getLeft(sibling)) == BLACK) {
					setColor(getRight(sibling), BLACK);
					setColor(sibling, RED);
					rotate(sibling, this->LEFT);
					sibling = getLeft(getParent(x));
				}
				setColor(sibling, isRed(getParent(x)));
				setColor(getParent(x), BLACK);
				setColor(getLeft(sibling), BLACK);
				rotate(getParent(x), this->RIGHT);
				x = this->root;
			}
		}
	}
	setColor(x, BLACK);
}

//Удаление
template <class K, class T>
bool RbTree<K, T>::Delete(K key) {
	this->cnt = 0;
	typename Tree <K, T>::Node* t = this->root, * x = NULL;
	while (t != NULL && t->key != key)
	{
		if (key < t->key) t = t->left;
		else t = t->right;
		this->cnt++;
	}
	if (t == NULL)	return false;
	this->cnt++;
	if (t->left && t->right)
	{
		x = this->successor(t);
		t->key = x->key;
		t->data = t->data;
		t = x;
	}
	typename Tree <K, T>::Node* replacement = (t->left ? t->left : t->right);

	if (replacement)
	{
		t->key = replacement->key;
		t->data = replacement->data;
		t->left = t->right = NULL;
		t = replacement;
	}
	else if (!t->parent)
	{
		this->root = NULL;
	}
	else
	{
		if (t->color == BLACK)
			fixRBTree(t);

		if (t->parent)
		{
			if (t == t->parent->left)
				t->parent->left = NULL;
			else if (t == t->parent->right)
				t->parent->right = NULL;
			t->parent = NULL;
		}
	}
	delete t;
	this->size--;
	return true;
}
//Вертикальная печать
template <class K, class T>
void RbTree<K, T>::Show() {
	if (this->root == NULL) {
		cout << "Дерево пусто" << endl;
		return;
	}
	_Show(this->root, 0);
}
template <class K, class T>
void  RbTree<K, T>::_Show(typename Tree<K, T>::Node* r, int level) {
	if (r == NULL) return;
	_Show(r->right, level + 1);
	for (int i = 0; i < 3 * level; i++) cout << " ";
	cout << r->key << "(";
	if (r->color) cout << "RED";
	else cout << "BLACK";
	cout << ")" << endl;
	_Show(r->left, level + 1);
	return;
}