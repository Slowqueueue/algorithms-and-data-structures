#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<class K, class T>
class RNDTree : public Tree<K, T>
{
public:
	bool Insert(K key, T val); //Включение данных по ключу
	bool Delete(K key); //Удаление данных по ключу
    void Show(); //Вертикальная печать дерева
private:
    void FindSubroot(typename Tree <K, T>::Node*& temp, typename Tree <K, T>::Node*& subroot, bool& goDown, bool& insertInRoot, typename Tree <K, T>::Node* t);
    void _Insert(typename Tree <K, T>::Node*& temp, typename Tree <K, T>::Node* t);
    void UpdateNInsert(typename Tree <K, T>::Node* temp);
    void RotateNodes(typename Tree <K, T>::Node* t, typename Tree <K, T>::Node* subroot, bool& loop);
    bool _Delete(typename Tree<K, T>::Node* h, K key);
    void UpdateNDelete(typename Tree<K, T>::Node* h);
    void CalcN(typename Tree <K, T>::Node* h);
    typename Tree<K, T>::Node* RNDJoin(typename Tree <K, T>::Node* a, typename Tree <K, T>::Node* b);
    void _Show(typename Tree<K, T>::Node* r, int level);
};

//Вставка
template <typename K, typename T>
bool RNDTree<K, T>::Insert(K key, T val) {
    typename Tree <K, T>::Node* t = new typename Tree <K, T>::Node(key, val);
    if (this->root == NULL) {
        this->root = t;
        this->size++;
        this->cnt++;
        return true;
    }
    typename Tree <K, T>::Node* subroot = NULL;
    bool goDown = true, insertInRoot = true;
    typename Tree <K, T>::Node* temp = this->root;
    FindSubroot(temp, subroot, goDown, insertInRoot, t);
    if (t->key == temp->key) return false;
    _Insert(temp, t);
    if (t->key == temp->key) return false;
    temp = t;
    UpdateNInsert(temp);
    if (!insertInRoot) {
        bool loop = true;
        RotateNodes(t, subroot, loop);
    }
    return true;
}
template <typename K, typename T>
void RNDTree<K, T>::FindSubroot(typename Tree <K, T>::Node*& temp, typename Tree <K, T>::Node*& subroot, bool& goDown, bool& insertInRoot, typename Tree <K, T>::Node* t) {
    if (!(goDown && insertInRoot)) return;
    this->cnt++;
    if (rand() < RAND_MAX / temp->n + 1) {
        subroot = temp;
        insertInRoot = false;
        return;
    }
    else {
        if (t->key == temp->key) return;
        if (t->key < temp->key) {
            if (temp->left == NULL) goDown = false;
            else {
                temp = temp->left;
            }
        }
        else {
            if (temp->right == NULL) goDown = false;
            else {
                temp = temp->right;
            }
        }
        FindSubroot(temp, subroot, goDown, insertInRoot, t);
    }
}
template <typename K, typename T>
void RNDTree<K, T>::_Insert(typename Tree <K, T>::Node*& temp, typename Tree <K, T>::Node* t) {
    if (t->key == temp->key) return;
    this->cnt++;
    if (t->key > temp->key) {
        if (temp->right == NULL) {
            temp->right = t;
            t->parent = temp;
            this->size++;
            return;
        }
        else temp = temp->right;
    }
    else {
        if (temp->left == NULL) {
            temp->left = t;
            t->parent = temp;
            this->size++;
            return;
        }
        else temp = temp->left;
    }
    _Insert(temp, t);
}
template <typename K, typename T>
void RNDTree<K, T>::UpdateNInsert(typename Tree <K, T>::Node* temp) {
    if (temp == this->root) return;
    temp = temp->parent;
    temp->n++;
    UpdateNInsert(temp);
}
template <typename K, typename T>
void RNDTree<K, T>::RotateNodes(typename Tree <K, T>::Node* t, typename Tree <K, T>::Node* subroot, bool& loop) {
    if (!loop) return;
    typename Tree <K, T>::Node* temp = t->parent;
    if (t->parent == subroot) loop = false;
    if (t->key > temp->key) {
        temp->right = t->left;
        if (t->left != NULL) t->left->parent = temp;
        t->left = temp;
    }
    else {
        temp->left = t->right;
        if (t->right != NULL) t->right->parent = temp;
        t->right = temp;
    }
    if (temp->parent != NULL) {
        if (t->key > temp->parent->key) temp->parent->right = t;
        else temp->parent->left = t;
    }
    t->parent = temp->parent;
    temp->parent = t;
    if (temp == this->root) this->root = t;
    temp->n = 1;
    if (temp->right != NULL) temp->n = temp->n + temp->right->n;
    if (temp->left != NULL) temp->n = temp->n + temp->left->n;
    t->n = 1;
    if (t->right != NULL) t->n = t->n + t->right->n;
    if (t->left != NULL) t->n = t->n + t->left->n;
    RotateNodes(t, subroot, loop);
}
//Удаление
template <class K, class T>
bool RNDTree<K, T>::Delete(K key) {
    return _Delete(this->root, key);
}
template <class K, class T>
bool RNDTree<K, T>::_Delete(typename Tree<K, T>::Node* h, K key) {
    this->cnt++;
    if (h == NULL) return false;

    K w = h->key;
    if (key < w) return _Delete(h->left, key);
    if (key > w) return _Delete(h->right, key);

    // key == w
    typename Tree<K, T>::Node* t = h;
    typename Tree<K, T>::Node* prev = h->parent;

    if (h == this->root) {
        this->root = h = RNDJoin(h->left, h->right);
        if (this->root) this->root->parent = NULL;
    }
    else {
        if (prev->left == h) prev->left = h = RNDJoin(h->left, h->right);
        else prev->right = h = RNDJoin(h->left, h->right);
        if (h) h->parent = prev;
        if (!h) h = prev;
    }
    delete t;
    this->size--;

    UpdateNDelete(h);
    return true;
}
template <class K, class T>
void RNDTree<K, T>::UpdateNDelete(typename Tree<K, T>::Node* h) {
    if (h) {
        CalcN(h);
        UpdateNDelete(h->parent);
    }
}
template <class K, class T>
void RNDTree<K, T>::CalcN(typename Tree <K, T>::Node* h) {
    if (h == NULL) return;
    if (h->left == NULL && h->right == NULL) { h->n = 1; return; }
    else {
        if (h->left == NULL) { h->n = h->right->n + 1; return; }
        if (h->right == NULL) { h->n = h->left->n + 1; return; }
    }
    h->n = h->left->n + h->right->n + 1;
}
template <class K, class T>
typename Tree<K, T>::Node* RNDTree<K, T>::RNDJoin(typename Tree<K, T>::Node* a, typename Tree<K, T>::Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (rand() / (RAND_MAX / (a->n + b->n) + 1) < a->n) {
        a->right = RNDJoin(a->right, b);
        a->right->parent = a;
        CalcN(a);
        return a;
    }
    else {
        b->left = RNDJoin(a, b->left);
        b->left->parent = b;
        CalcN(b);
        return b;
    }
}
//Вертикальная печать
template <class K, class T>
void RNDTree<K, T>::Show() {
    if (this->root == NULL) {
        cout << "Дерево пусто" << endl;
        return;
    }
    _Show(this->root, 0);
}
template <class K, class T>
void RNDTree<K, T>::_Show(typename Tree<K, T>::Node* r, int level) {
    if (r == NULL) return;
    _Show(r->right, level + 1);
    for (int i = 0; i < 3 * level; i++) cout << " ";
    cout << r->key << "(" << r->n << ")" << endl;
    _Show(r->left, level + 1);
    return;
}