#pragma once
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>
using namespace std;

#define BLACK false
#define RED true

class TreeException
{
	string code;
public:
	TreeException() { code = "����������"; }
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
		Node* left, *right, *parent;
		bool color;
		Node(K k, T d)
		{
			key = k;
			data = d;
			left = right = parent = NULL;
			color = RED;
		}
	};
	Node* root;
	int size;
	int cnt;
	enum Side {LEFT, RIGHT};
public:
	Tree(); //�����������
	Tree(Tree<K, T>& t); //����������� �����������
	~Tree(); //����������
	int GetSize(); //����� ������� ������
	void Clear(); //������� ������
	bool IsEmpty(); //�������� ������ �� �������
	T GetData(K key); //������ ������ �� �����
	bool Replace(K key, T val); //������ ������ �� �����
	bool Insert(K key, T val);//��������� ������ �� �����
	bool Delete(K key); //�������� ������ �� �����
	void InOrderTraversal(); //����� �� LTR
	void VerticalPrint(); //������������ ������ ������
	void HorisontalPrint(); //�������������� ������ ������
	int getCountNodesView(); //����� �����, ������������� ����. ���������
private:
	void CopyTree(Node* r);	//��������������� ������� ��� ����������� ������
	void _InOrder(Node* r); //��������������� ������� ��� ������ ������
	void _VerticalPrint(Node* r, int level); //��������������� ������� ��� ������������ ������ 	
	void _HorisontalPrint(Node* r, int level, int start, int width, vector<string>& treeString); //��������������� ������� ��� �������������� ������ ������
	int _GetHeight(Node* node);
	Node* BSTPredecessor(Node* x); //���� ���� � ���������� �� �������� ������
	Node* BSTSuccessor(Node* x); //���� ���� �� ��������� �� �������� ������
	Node* Max(Node* t);	//���� ���� � ������������ ������
	Node* RParent(Node* t, Node* x);
	Node* Min(Node* t);	//���� ���� � ����������� ������
	Node* LParent(Node* t, Node* x);
public:
	class Iterator
	{
		Tree<K, T>* owner;
	public:
		Node* cur;
		Iterator(Tree<K, T>* treeOwner);
		bool is_off();
		T& operator *();
		void operator ++();
		void operator --();
		bool operator ==(Iterator& iterator);
		bool operator !=(Iterator& iterator);
	};
	Iterator beg();
	Iterator end();
	class ReverseIterator
	{
		Tree<K, T>* owner;
	public:
		Node* cur;
		ReverseIterator(Tree<K, T>* treeOwner);
		bool is_rev_off();
		T& operator *();
		void operator ++();
		void operator --();
		bool operator ==(ReverseIterator& reviterator);
		bool operator !=(ReverseIterator& reviterator);
	};
	ReverseIterator rbeg();
	ReverseIterator rend();
};
//�����������
template <class K, class T>
Tree<K, T>::Tree() {
	root = NULL;
	size = 0;
	cnt = 0;
}
//����������� �����������
template <class K, class T>
Tree<K, T>::Tree(Tree<K, T>& t)
{
	root = NULL;
	size = 0;
	CopyTree(t.root);
}
//��������������� ������� ��� ����������� ������
template <class K, class T>
void Tree<K, T>::CopyTree(typename Tree<K, T>::Node* r)
{
	if (r == NULL)
		return;
	Insert(r->key, r->data);
	CopyTree(r->left);
	CopyTree(r->right);
}
//����������
template <class K, class T>
Tree<K, T>::~Tree() {
	Clear();
}
//������� ������
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
//��������� �������
template <class K, class T>
int Tree<K, T>::GetSize() {
	return size;
}
//�������� �� �������
template <class K, class T>
bool Tree<K, T>::IsEmpty()
{
	return (size == 0);
}
//��������� ������ �� �����
template<class K, class T>
T Tree<K, T>::GetData(K key) {
	Node* current = root;
	while (current != nullptr) {
		cnt++;
		if (key == current->key) {
			return current->data;
		}
		else if (key < current->key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	throw TreeException();
}
//������ ������ �� �����
template<class K, class T>
bool Tree<K, T>::Replace(K key, T val) {
	Node* current = root;
	while (current != nullptr) {
		if (key == current->key) {
			current->data = val;
			return true;
		}
		else if (key < current->key) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	return false;
}
//�������
template <class K, class T>
bool Tree<K, T>::Insert(K key, T val) {
	Node* current = root;
	Node* parent = nullptr;
	bool inserted = false;

	if (root == nullptr) {
		root = new Node(key, val);
		size++;
		return true;
	}

	while (current != nullptr) {
		cnt++;
		if (key == current->key) {
			return false;
		}
		else if (key < current->key) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}
	}

	Node* newNode = new Node(key, val);
	if (key < parent->key) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	size++;
	return true;
}
//��������
template <class K, class T>
bool Tree<K, T>::Delete(K key) {
	Node* current = root;
	Node* parent = nullptr;
	bool deleted = false;

	while (current != nullptr) {
		cnt++;
		if (key == current->key) {
			break;
		}
		else if (key < current->key) {
			parent = current;
			current = current->left;
		}
		else {
			parent = current;
			current = current->right;
		}
	}

	if (current == nullptr) {
		return false;
	}

	deleted = true;
	size--;

	if (current->left == nullptr && current->right == nullptr) {
		if (parent == nullptr) {
			delete root;
			root = nullptr;
		}
		else {
			if (parent->left == current) {
				parent->left = nullptr;
			}
			else {
				parent->right = nullptr;
			}
			delete current;
		}
	}
	else if (current->left == nullptr) {
		if (parent == nullptr) {
			root = current->right;
		}
		else {
			if (parent->left == current) {
				parent->left = current->right;
			}
			else {
				parent->right = current->right;
			}
		}
		delete current;

	}
	else if (current->right == nullptr) {
		if (parent == nullptr) {
			root = current->left;
		}
		else {
			if (parent->left == current) {
				parent->left = current->left;
			}
			else {
				parent->right = current->left;
			}
		}
		delete current;
	}
	else {
		Node* successor = current->right;
		Node* successorParent = current;
		while (successor->left != nullptr) {
			successorParent = successor;
			successor = successor->left;
		}

		current->key = successor->key;
		current->data = successor->data;

		if (successorParent->left == successor) {
			successorParent->left = successor->right;
		}
		else {
			successorParent->right = successor->right;
		}
		delete successor;
	}

	return deleted;
}
//����������� �������� ������������

//LTR
template <class K, class T>
void Tree<K, T>::InOrderTraversal()
{
	if (root != NULL) _InOrder(root);
	else cout << "������ �����";
	cout << endl;
}
//��������������� ������� ��� ������������ ������
template <class K, class T>
void Tree<K, T>::_InOrder(typename Tree<K, T>::Node* r)
{
	if (r == NULL) return;
	_InOrder(r->left);
	cout << r->key << " ";
	_InOrder(r->right);
}
//������������ ������
template <class K, class T>
void Tree<K, T>::VerticalPrint() {
	if (root == NULL) {
		cout << "������ �����" << endl;
		return;
	}
	_VerticalPrint(root, 0);
}
template <class K, class T>
void  Tree<K, T>::_VerticalPrint(typename Tree<K, T>::Node* r, int level) {
	if (r == NULL) return;
	_VerticalPrint(r->right, level + 1);
	for (int i = 0; i < 3 * level; i++) cout << " ";
	cout << r->key << endl;
	_VerticalPrint(r->left, level + 1);
	return;
}
//�������������� ������
template <class K, class T>
void Tree<K, T>::HorisontalPrint() {
	if (root == NULL) {
		cout << "������ �����" << endl;
		return;
	}

	int height = _GetHeight(root); // �������� ������ ������ ��� �������������
	int width = pow(2, height) - 1; // ��������� ������ ��� ���������

	vector<string> treeString(height, string(width, ' ')); // �������������� ������ �����

	_HorisontalPrint(root, 0, 0, width, treeString);

	for (int i = 0; i < height; ++i) {
		cout << treeString[i] << endl;
	}
}
template <class K, class T>
void  Tree<K, T>::_HorisontalPrint(typename Tree<K, T>::Node* r, int level, int start, int width, vector<string>& treeString) {
	if (r == NULL) return;

	int nodePosition = start + width / 2; // ��������� ������� ����

	// ����������� ���� � ������
	stringstream ss;
	ss << r->key;
	string keyString = ss.str();

	// ��������� ���� � ������
	int keyLength = keyString.length();
	int startPos = nodePosition - keyLength / 2;

	// ���������� ���� � treeString
	if (level < treeString.size() && startPos >= 0 && (startPos + keyLength) <= treeString[level].length()) {
		for (int i = 0; i < keyLength; ++i) {
			treeString[level][startPos + i] = keyString[i];
		}
	}

	_HorisontalPrint(r->left, level + 1, start, width / 2, treeString);
	_HorisontalPrint(r->right, level + 1, nodePosition + 1, width / 2, treeString);
}
template <class K, class T>
int Tree<K, T>::_GetHeight(typename Tree<K, T>::Node* node) {
	if (node == nullptr) {
		return 0;
	}
	return 1 + max(_GetHeight(node->left), _GetHeight(node->right));
}
//������� ��� ���������
//���� � ���������� �� �������� ������
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::BSTPredecessor(typename Tree<K, T>::Node* x) {
	if (x == NULL) return NULL;
	if (x->left != NULL) return Max(x->left);
	else return RParent(root, x);
}
//���� � ������������ ������
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
//���� �� ��������� �� �������� ������
template <class K, class T>
typename Tree<K, T>::Node* Tree<K, T>::BSTSuccessor(typename Tree<K, T>::Node* x) {
	if (x == NULL) return NULL;
	if (x->right != NULL) return Min(x->right);
	else return LParent(root, x);
}
//���� � ����������� ������
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
//��������� �������� ���������� �����
template <class K, class T>
int Tree<K, T>::getCountNodesView()
{
	int temp = cnt;
	cnt = 0;
	return temp;
}
//��������
//����������� ���������
template <class K, class T>
Tree<K, T>::Iterator::Iterator(Tree<K, T>* treeOwner) {
	owner = treeOwner;
	cur = NULL;
}
//� ������
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
//� �����
template <class K, class T>
typename Tree<K, T>::Iterator Tree<K, T>::end()
{
	Iterator iter = Iterator(this);
	Node* cur = root;
	if (cur != nullptr)
		while (cur->right != nullptr)
			cur = cur->right;
	iter.cur = cur->right;
	return iter;
}
//� �����������
template <class K, class T>
void Tree<K, T>::Iterator::operator--() {
	cur = owner->BSTPredecessor(cur);
}
//� ����������
template <class K, class T>
void Tree<K, T>::Iterator::operator++() {
	cur = owner->BSTSuccessor(cur);
}
//�������� ���������
template <class K, class T>
bool Tree<K, T>::Iterator::is_off() {
	return  (cur == NULL);
}
//������ � ������ ��������
template <class K, class T>
T& Tree<K, T>::Iterator::operator *() {
	if (is_off())
		throw TreeException();
	return cur->data;
}
//�������� �� ��������� ������ ����������
template <class K, class T>
bool Tree<K, T>::Iterator::operator ==(Iterator& iterator) {
	return cur == iterator.cur;
}
//�������� �� ����������� ������ ����������
template <class K, class T>
bool Tree<K, T>::Iterator::operator !=(Iterator& iterator) {
	return cur != iterator.cur;
}
//�������� ��������
template <class K, class T>
Tree<K, T>::ReverseIterator::ReverseIterator(Tree<K, T>* treeOwner) {
	owner = treeOwner;
	cur = NULL;
}
//������ ��������� ���������
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
//������ "����������������" ��������� ���������
template <class K, class T>
typename Tree<K, T>::ReverseIterator Tree<K, T>::rend()
{
	ReverseIterator iter = ReverseIterator(this);
	Node* cur = root;
	if (cur != nullptr)
		while (cur->left != nullptr)
			cur = cur->left;
	iter.cur = cur->left;
	return iter;
}
//� �����������
template <class K, class T>
void Tree<K, T>::ReverseIterator::operator--() {
	cur = owner->BSTSuccessor(cur);
}
//� ����������
template <class K, class T>
void Tree<K, T>::ReverseIterator::operator++() {
	cur = owner->BSTPredecessor(cur);
}
//�������� ���������
template <class K, class T>
bool Tree<K, T>::ReverseIterator::is_rev_off() {
	return (cur == NULL);
}
//������ � ������ ��������
template <class K, class T>
T& Tree<K, T>::ReverseIterator::operator *() {
	if (is_rev_off())
		throw TreeException();
	return cur->data;
}
//�������� �� ��������� �������� ����������
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator ==(ReverseIterator& reviterator) {
	return cur == reviterator.cur;
}
//�������� �� ����������� �������� ����������
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator !=(ReverseIterator& reviterator) {
	return cur != reviterator.cur;
}