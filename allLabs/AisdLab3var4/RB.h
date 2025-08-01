#pragma once
#include <iostream>
#include <stack>
using namespace std;

class RbTreeException
{
	string code;
public:
	RbTreeException() { code = "����������"; }
	string What() { return code; }
};

template<class K, class T>
class RbTree : public Tree<K, T>
{
public:
	bool Insert(K key, T val);//��������� ������ �� �����
	bool Delete(K key); //�������� ������ �� �����
	void Show(); //������������ ������ ������
	T& GetData(K key); //������ ������ �� �����
private:
	void _Show(typename Tree<K,T>::Node* r, int level); //��������������� ������� ��� ������������ ������ 	
	bool _Insert(typename Tree <K, T>::Node*& t, K key, T val, typename Tree <K, T>::Side side); //��������������� ������� ��� ��������� ������
	void fixRBTree(typename Tree <K, T>::Node* x);	//C��������� ������� ������-������� ������
	bool isRed(typename Tree <K, T>::Node* node); //�������� �� ���� ����
	void setColor(typename Tree <K, T>::Node* node, bool color); //��������� ����� ����
	typename Tree<K, T>::Node* rotate(typename Tree <K, T>::Node* p, typename Tree <K, T>::Side side); //�������
	typename Tree<K, T>::Node* _GetData(K key, typename Tree<K, T>::Node* root); //��������������� ������� ��� ������ ������ �� �����
	typename Tree<K, T>::Node* successor(typename Tree<K, T>::Node* t); //����� ���������� �� ����� ����
	typename Tree<K, T>::Node* getParent(typename Tree <K, T>::Node* node); //������� ��������
	typename Tree<K, T>::Node* getLeft(typename Tree <K, T>::Node* node); //������� ������ �������
	typename Tree<K, T>::Node* getRight(typename Tree <K, T>::Node* node); //������� ������� �������
	typename Tree<K, T>::Node* min(typename Tree <K, T>::Node* t); //����� ���� � ����������� ������
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
	if (side == this->LEFT) // � ������ �������� ������
	{
		typename Tree <K, T>::Node* r = p->right; // Node* r - �������� ������
		p->right = r->left;
		if (r->left) r->left->parent = p;
		r->parent = p->parent; // ��� ���� �������� ��� r ������ ������ ������,
		if (!p->parent) //								���� ��� ������ � ���� p
		{
			this->root = r;
		}
		else if (p->parent->left == p) // ���� ����� ������� ������ p ��������� ��� �� ����,
		{
			p->parent->left = r;						// �� ����������� ��� �������� �������
		}
		else
		{
			p->parent->right = r;
		}
		r->left = p;		// ������ p ����� �������� ������� r
		p->parent = r;		//
		return r;
	}
	else // � ������ �������� ������� ����������
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

//�������
template <typename K, typename T>
bool RbTree<K, T>::_Insert(typename Tree <K, T>::Node*& t, K key, T val, typename Tree <K, T>::Side side) {
	if (!t)									// ��� ���������� ��������� ����
	{
		t = new typename Tree <K, T>::Node(key, val); // ������� ���
		return true;
	}
	if (isRed(t->left) && isRed(t->right)) // ����� ���� ����������, � ��� ����� � ������ ������� �������
	{
		t->color = RED;			// ���� ���� ����� �������
		t->left->color = BLACK;	// � ����� �������� ������ (�������� RB-������) 
		t->right->color = BLACK;
	}
	bool success; // ������� �� ������ �������
	if (t->key == key) // ���� ����� ���� ��� ���� � ������ ���� ������� false
	{
		return false;
	}
	else if (key < t->key) // ����� ���� �������� ���� ������ ����� � ����
	{
		success = _Insert(t->left, key, val, this->LEFT); // ��������� �����
		t->left->parent = t;
		if (isRed(t) && isRed(t->left) && (side == this->RIGHT)) // ���� ���� � ��� ����� ������� �������,
		{
			t = rotate(t, this->RIGHT);								// �� ������������ ������
		}
		if (isRed(t->left) && isRed(t->left->left))  // ���� ����� ������� � ����� ������� ������ ������� �������
		{
			t = rotate(t, this->RIGHT);	// ������������ ������
			t->color = BLACK;	// ������ ���� � ������
			t->right->color = RED; // � ��� ������� ������� � �������
		}
	}
	else
	{
		success = _Insert(t->right, key, val, this->RIGHT); // ����� ��������� ������
		t->right->parent = t;
		if (isRed(t) && isRed(t->right) && (side == this->LEFT)) // ���� ���� � ��� ������ ������� �������, � ������� �����,
		{
			t = rotate(t, this->LEFT);							// �� ������������ �����
		}
		if (isRed(t->right) && isRed(t->right->right))	// ���� ������ ������� � ������ ������� ������� ������� �������
		{
			t = rotate(t, this->LEFT);	// ������������ �����
			t->color = BLACK;	// ������ ���� � ������
			t->left->color = RED;	// � ������ ������� � �������
		}
	}
	this->cnt++;
	return success;
}

template <class K, class T>
bool RbTree<K, T>::Insert(K key, T val)
{
	this->cnt = 0;
	bool success = _Insert(this->root, key, val, this->LEFT); // ������� �� ��������� �����
	if (!success) return false;
	this->root->color = BLACK; // ������ ������ � ������
	this->size++;	// ��������� �������� ������� ������
	return true;
}

//C��������� ������� ������-������� ������
template <class K, class T>
void RbTree<K, T>::fixRBTree(typename Tree <K, T>::Node* x)
{
	while (x != this->root && isRed(x) == BLACK) // ���� �������� ���� x - �� ������ � �� ������
	{
		if (x == getLeft(getParent(x))) // ���� x - ����� ������� ������ ������ ����
		{
			typename Tree <K, T>::Node* sibling = getRight(getParent(x)); // �� ������ x ������ ������� ������� ������ x

			if (isRed(sibling) == RED) {		// ���� ���� x �������
				setColor(sibling, BLACK);		// ������ ����� ������
				setColor(getParent(x), RED);	// ������ ������ x �������
				rotate(getParent(x), this->LEFT); // � ������������ ����� �� ������ x
				sibling = getRight(getParent(x)); // ������ ���������� ������ ������� ������ x
			}

			if (!isRed(getLeft(sibling)) && !isRed(getRight(sibling))) { // ���� ��� ������� ����� ������
				setColor(sibling, RED); // ������ ����� �������
				x = getParent(x); // � x ���������� �������
			}
			else {
				if (isRed(getRight(sibling)) == BLACK) { // ���� ������ ������� ����� ������
					setColor(getLeft(sibling), BLACK); // ������ ������ ������� ����� ���� � ������
					setColor(sibling, RED); // � ����� ������ �������
					rotate(sibling, this->RIGHT); // ������������ ������ �� �����
					sibling = getRight(getParent(x)); // ���� ���������� ������ �������� ������ x
				}
				setColor(sibling, isRed(getParent(x))); // ���� ����� ���������� ������ ���� x
				setColor(getParent(x), BLACK); // ������ ������ x � ������
				setColor(getRight(sibling), BLACK); // � ������� ������ ����� � ������
				rotate(getParent(x), this->LEFT); // ������������ ����� �� �����
				x = this->root; // x ���������� ������
			}
		}
		else { // �����������
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

//��������
template <class K, class T>
bool RbTree<K, T>::Delete(K key) {
	this->cnt = 0;
	typename Tree <K, T>::Node* t = this->root, * x = NULL; // x - ��������������� ����������
	while (t != NULL && t->key != key) // ���� �� ����� �� ����� � NULL-��������� � ���� ����� �� ����� ���������
	{
		if (key < t->key) t = t->left; // ���� �������� ���� ������ �������� �� ���� �����
		else t = t->right;	// ����� ������
		this->cnt++;
	}
	if (t == NULL)	return false; // ���� ����� �� �����
	this->cnt++;
	if (t->left && t->right) // ���� ���� ������ � ����� �������
	{
		x = this->successor(t); // � x ���������� ��������� �� ����� ����
		t->key = x->key; // ������ t ���������� ���� x
		t->data = t->data; // ���������� ������
		t = x;	// � ��� ����
	}
	typename Tree <K, T>::Node* replacement = (t->left ? t->left : t->right); // ���� ���� ����� ������� - ���������� ���, ����� - �������

	if (replacement)
	{
		t->key = replacement->key;  // ������ � t ������ replacement
		t->data = replacement->data; // ������
		t->left = t->right = NULL; // ��������� �������� t
		t = replacement;
	}
	else if (!t->parent) // ���� � t ��� ������
	{
		this->root = NULL; // �������� ������
	}
	else
	{
		if (t->color == BLACK) // ���� t - ������, ��������������� RB-������ �������� ���������
			fixRBTree(t);

		if (t->parent) // ���� � t ���� ������
		{
			if (t == t->parent->left)	// ���� t - ����� ������� ������ t,
				t->parent->left = NULL; // �� �������� ������ ������� ������ t
			else if (t == t->parent->right) // ���� ������
				t->parent->right = NULL;	// ����������
			t->parent = NULL; // �������� ������ t
		}
	}
	delete t;
	this->size--;
	return true;
}
//������������ ������
template <class K, class T>
void RbTree<K, T>::Show() {
	if (this->root == NULL) {
		cout << "������ �����" << endl;
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
//��������� ������ �� �����
template<class K, class T>
typename Tree<K,T>::Node* RbTree<K, T>::_GetData(K key, typename Tree<K, T>::Node* current) {
	while (current != NULL && key != current->key) {
		this->cnt++;
		if (key < current->key)
			current = current->left;
		else
			current = current->right;
	}
	return current;
}
template<class K, class T>
T& RbTree<K, T>::GetData(K key) {
	this->cnt++;
	typename Tree<K, T>::Node* targetNode = _GetData(key, this->root);
	if (targetNode == NULL) throw RbTreeException();
	return targetNode->data;
}