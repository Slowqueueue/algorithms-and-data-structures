#pragma once
#include <iostream>
#include <stack>
using namespace std;

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
	class Node
	{
	public:
		K key;
		T data;
		T criteria;
		Node* left, * right;
		Node(K k, T d)
		{
			key = k;
			data = d;
			left = right = NULL;
		}
	};
	Node* root;
	int size;
	int cnt;
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
	void PostorderTraversal(); //����� �� LRT
	void FindCritStab(); //����������� �������� ������������������
	void Show(); //������������ ������ ������
	int getCountNodesView(); //����� �����, ������������� ����. ���������
private:
	void CopyTree(Node* r);	//��������������� ������� ��� ����������� ������
	void _Postorder(Node* r); //��������������� ������� ��� ������ ������
	void _Show(Node* r, int level); //��������������� ������� ��� ������������ ������ 	
	int _Crit(Node* r); //��������������� ������� ��� ����������� �������� ������������������
	Node* _GetData(K key, Node* root); //��������������� ������� ��� ������ ������ �� �����
	Node* _Insert(K key, T val, Node* root, bool* inserted); //��������������� ������� ��� ������ ������ �� �����
	Node* _Del(Node* targetReplaceWith, Node* current); //��������������� ������� ��� �������� ������ �� �����
	Node* _Delete(Node* current, Node* targetParent, K key, bool* deleted); //��������������� ������� ��� �������� ������ �� �����
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
//�����������
template <class K, class T>
Tree<K, T>::Tree() {
	root = NULL;
	size = 0;
	cnt = 0;
}
//����������� �����������
template <class K, class T>
Tree<K, T>::Tree(Tree<K, T> &t)
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
template<class K, class T>
T Tree<K, T>::GetData(K key) {
	Node* targetNode = _GetData(key, root);
	if (targetNode == NULL) throw TreeException();
	return targetNode->data;
}
//������ ������ �� �����
template<class K, class T>
bool Tree<K, T>::Replace(K key, T val) {
	Node* targetNode = _GetData(key, root);
	if (targetNode == NULL) return false;
	targetNode->data = val;
	return true;
}
//�������
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
//��������
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
//����������� �������� ������������
template <class K, class T>
void Tree<K, T>::FindCritStab()
{
	if (root != NULL) _Crit(root);
	else cout << "������ �����";
	cout << endl;
}
template <class K, class T>
int Tree<K, T>::_Crit(typename Tree<K, T>::Node* r) {
	if (r == NULL) return 0;
	int left = _Crit(r->left);
	int right = _Crit(r->right);
	int h = ((left > right) ? left : right) + 1;
	r->criteria = right - left;
	return h;
}
//LRT
template <class K, class T>
void Tree<K, T>::PostorderTraversal()
{
	if (root != NULL) _Postorder(root);
	else cout << "������ �����";
	cout << endl;
}
//��������������� ������� ��� ������������ ������
template <class K, class T>
void Tree<K, T>::_Postorder(typename Tree<K, T>::Node* r)
{
	if (r == NULL) return;
	_Postorder(r->left);
	_Postorder(r->right);
	cout << r->key << " ";
}
template <class K, class T>
void  Tree<K, T>::_Show(typename Tree<K, T>::Node* r, int level) {
	if (r == NULL) return;
	_Show(r->right, level + 1);
	for (int i = 0; i < 3 * level; i++) cout << " ";
	cout << r->key << "(" << r->criteria << ")" << endl;
	_Show(r->left, level + 1);
	return;
}
//������������ ������
template <class K, class T>
void Tree<K, T>::Show() {
	if (root == NULL) {
		cout << "������ �����" << endl;
		return;
	}
	_Show(root, 0);
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
	if (cur != nullptr) {
		while (cur->right != nullptr)
			cur = cur->right;
		iter.cur = cur->right;
	}
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
//������ � ������ ��������
template <class K, class T>
T& Tree<K, T>::Iterator::operator *() {
	if (cur == NULL)
		throw TreeException();
	return cur->data;
}
//�������� �� ��������� ������ ����������
template <class K, class T>
bool Tree<K, T>::Iterator::operator ==(const Iterator& iterator) const  {
	return cur == iterator.cur;
}
//�������� �� ����������� ������ ����������
template <class K, class T>
bool Tree<K, T>::Iterator::operator !=(const Iterator& iterator) const {
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
	if (cur != nullptr) {
		while (cur->left != nullptr)
			cur = cur->left;
		iter.cur = cur->left;
	}
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
//������ � ������ ��������
template <class K, class T>
T& Tree<K, T>::ReverseIterator::operator *() {
	if (cur == NULL)
		throw TreeException();
	return cur->data;
}
//�������� �� ��������� �������� ����������
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator ==(const ReverseIterator& reviterator) const {
	return cur == reviterator.cur;
}
//�������� �� ����������� �������� ����������
template <class K, class T>
bool Tree<K, T>::ReverseIterator::operator !=(const ReverseIterator& reviterator) const {
	return cur != reviterator.cur;
}
