#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<class K, class T>
class AVLTree : public Tree<K, T>
{
public:
	bool Insert(K key, T val);//¬ключение данных по ключу
	bool Delete(K key);//”даление данных по ключу
private:
	bool _Insert(typename Tree<K, T>::Node*& node, K key, T val, typename Tree<K, T>::Node** node_stack, int* dir_stack, int& dir);
	void BalanceInsert(typename Tree<K, T>::Node** node_stack, int* dir_stack, int& dir);
	typename Tree<K, T>::Node* _Delete(typename Tree<K, T>::Node* node, K key, typename Tree<K, T>::Node** node_stack, int* dir_stack, int& top, bool& found, bool& del);
	typename Tree<K, T>::Node* BalanceDelete(typename Tree<K, T>::Node* node, bool& del);
	typename Tree<K, T>::Node* RDel(typename Tree<K, T>::Node* t, bool& del);//RDel - однократный правый поворот дл€ операции удалени€
	typename Tree<K, T>::Node* LDel(typename Tree<K, T>::Node* t, bool& del);//LDel - однократный левый поворот дл€ операции удалени€
	typename Tree<K, T>::Node* RLDel(typename Tree<K, T>::Node* t, bool& del);//RLDel - двукратный поворот дл€ операции удалени€
	typename Tree<K, T>::Node* LRDel(typename Tree<K, T>::Node* t, bool& del);//LRDel - двукратный поворот дл€ операции удалени€
	typename Tree<K, T>::Node* LR(typename Tree<K, T>::Node* t);//LR-поворот
	typename Tree<K, T>::Node* RL(typename Tree<K, T>::Node* t);//RL-поворот
};

//¬ставка
template <typename K, typename T>
bool AVLTree<K, T>::Insert(K key, T val) {
	typename Tree<K, T>::Node** node_stack = new typename Tree<K, T>::Node* [this->size + 1];
	int* dir_stack = new int[this->size + 1];
	int dir = -1;
	bool inserted = _Insert(this->root, key, val, node_stack, dir_stack, dir);
	delete[] node_stack;
	delete[] dir_stack;
	return inserted;
}
template <typename K, typename T>
bool AVLTree<K, T>::_Insert(typename Tree<K, T>::Node*& node, K key, T val, typename Tree<K, T>::Node** node_stack, int* dir_stack, int& dir) {
	if (!node) {
		node = new typename Tree<K, T>::Node(key, val);
		if (this->root == nullptr) {
			this->root = node;
		}
		this->size++;
		return true;
	}
	if (key == node->key) {
		return false;
	}
	if (key > node->key) {
		this->cnt++;
		node_stack[++dir] = node;
		dir_stack[dir] = -1;
		if (_Insert(node->right, key, val, node_stack, dir_stack, dir)) {
			BalanceInsert(node_stack, dir_stack, dir);
			return true;
		}
		else return false;
	}
	else {
		this->cnt++;
		node_stack[++dir] = node;
		dir_stack[dir] = 1;
		if (_Insert(node->left, key, val, node_stack, dir_stack, dir)) {
			BalanceInsert(node_stack, dir_stack, dir);
			return true;
		}
		else return false;
	}
	return false;
}
template <typename K, typename T>
void AVLTree<K, T>::BalanceInsert(typename Tree<K, T>::Node** node_stack, int* dir_stack, int& dir) {
	bool h = true;
	while (dir >= 0)
	{
		if (h)
		{
			if (!node_stack[dir]) {
				dir--;
				continue;
			}
			node_stack[dir]->criteria += dir_stack[dir];
			typename Tree<K, T>::Node* buffer = node_stack[dir];
			switch (node_stack[dir]->criteria)
			{
			case 0:
				h = false;
				break;
			case 1:
			case -1:
				h = true;
				break;
			case 2:
				if (!node_stack[dir]->left) {
					h = false;
					break;
				}
				node_stack[dir]->criteria = 1;
				if (node_stack[dir]->left->criteria >= 0) {
					buffer = RDel(node_stack[dir], h);
				}
				else {
					if (!node_stack[dir]->left->right) {
						h = false;
						break;
					}
					buffer = LR(node_stack[dir]);
				}
				h = false;
				break;
			case -2:
				if (!node_stack[dir]->right) {
					h = false;
					break;
				}

				node_stack[dir]->criteria = -1;
				if (node_stack[dir]->right->criteria <= 0) {
					buffer = LDel(node_stack[dir], h);
				}
				else {
					if (!node_stack[dir]->right->left) {
						h = false;
						break;
					}
					buffer = RL(node_stack[dir]);
				}
				h = false;
				break;
			}
			if (dir == 0) {
				this->root = buffer;
			}
			else if (dir_stack[dir - 1] == -1) {
				if (node_stack[dir - 1]) {
					node_stack[dir - 1]->right = buffer;
				}
			}
			else {
				if (node_stack[dir - 1]) {
					node_stack[dir - 1]->left = buffer;
				}
			}
		}
		dir--;
	}
}
//”даление
template <class K, class T>
bool AVLTree<K, T>::Delete(K key) {
	typename Tree<K, T>::Node** node_stack = new typename Tree<K, T>::Node* [this->size + 1];
	int* dir_stack = new int[this->size + 1];
	int top = -1;
	bool del = true;
	bool found = false;
	this->root = _Delete(this->root, key, node_stack, dir_stack, top, found, del);
	while (top >= 0 && del) {
		node_stack[top]->criteria -= dir_stack[top];
		typename Tree<K, T>::Node* balanced = BalanceDelete(node_stack[top], del);
		if (top == 0) {
			this->root = balanced;
		}
		else {
			if (dir_stack[top - 1] == -1) {
				node_stack[top - 1]->right = balanced;
			}
			else {
				node_stack[top - 1]->left = balanced;
			}
		}
		top--;
	}
	delete[] node_stack;
	delete[] dir_stack;
	if (found) this->size--;
	return found;
}
template <class K, class T>
typename Tree<K, T>::Node* AVLTree<K, T>::_Delete(typename Tree<K, T>::Node* node, K key, typename Tree<K, T>::Node** node_stack, int* dir_stack, int& top, bool& found, bool& del)
{
	if (!node) return nullptr;
	this->cnt++;
	if (key < node->key) {
		node_stack[++top] = node;
		dir_stack[top] = 1;
		node->left = _Delete(node->left, key, node_stack, dir_stack, top, found, del);
	}
	else if (key > node->key) {
		node_stack[++top] = node;
		dir_stack[top] = -1;
		node->right = _Delete(node->right, key, node_stack, dir_stack, top, found, del);
	}
	else {
		found = true;
		if (!node->left && !node->right) {
			delete node;
			return nullptr;
		}
		else if (!node->left) {
			auto temp = node->right;
			delete node;
			return temp;
		}
		else if (!node->right) {
			auto temp = node->left;
			delete node;
			return temp;
		}
		else {
			if (!node->left->right) {
				this->cnt++;
				auto nd = node->left;
				nd->right = node->right;
				nd->criteria = node->criteria;
				delete node;
				node_stack[++top] = nd;
				dir_stack[top] = 1;
				return nd;
			}
			else {
				node_stack[++top] = node;
				dir_stack[top] = 1;
				auto parent = node->left;
				node_stack[++top] = parent;
				dir_stack[top] = -1;
				this->cnt++;
				while (parent->right->right) {
					parent = parent->right;
					node_stack[++top] = parent;
					dir_stack[top] = -1;
					this->cnt++;
				}
				auto successor = parent->right;
				node->key = successor->key;
				node->data = successor->data;
				parent->right = successor->left;
				delete successor;
				return node;
			}
		}
	}
	return node;
}
template <class K, class T>
typename Tree<K, T>::Node* AVLTree<K, T>::BalanceDelete(typename Tree<K, T>::Node* node, bool& del) {
	if (!node) return nullptr;

	switch (node->criteria) {
	case 0:
		del = true;
		return node;
	case -1:
	case 1:
		del = false;
		return node;
	case 2:
		if (!node->left) return node;
		node->criteria = 1;
		if (node->left->criteria >= 0) {
			return RDel(node, del);
		}
		else {
			if (!node->left->right) return node;
			return LRDel(node, del);
		}
	case -2:
		if (!node->right) return node;
		node->criteria = -1;
		if (node->right->criteria <= 0) {
			return LDel(node, del);
		}
		else {
			if (!node->right->left) return node;
			return RLDel(node, del);
		}
	default:
		return node;
	}
}
//RDel - однократный правый поворот дл€ операции удалени€
template <class K, class T>
typename Tree<K,T>::Node* AVLTree<K, T>::RDel(typename Tree<K,T>::Node* t, bool& del) {
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
//LDel - однократный левый поворот дл€ операции удалени€
template <class K, class T>
typename Tree<K,T>::Node* AVLTree<K, T>::LDel(typename Tree<K, T>::Node* t, bool& del) {
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
typename Tree<K,T>::Node* AVLTree<K, T>::RL(typename Tree<K, T>::Node* t) {
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
	return y;
}
//LR-поворот
template <class K, class T>
typename Tree<K,T>::Node* AVLTree<K, T>::LR(typename Tree<K, T>::Node* t) {
	typename Tree<K, T>::Node* x = t->left;
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
//ƒвукратный поворот RLDel
template <class K, class T>
typename Tree<K,T>::Node* AVLTree<K, T>::RLDel(typename Tree<K, T>::Node* t, bool& del) {
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
//ƒвукратный поворот LRDel
template <class K, class T>
typename Tree<K,T>::Node* AVLTree<K, T>::LRDel(typename Tree<K, T>::Node* t, bool& del) {
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