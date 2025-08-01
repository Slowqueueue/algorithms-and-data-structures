#pragma once
#include <iostream>
#include <stack>
using namespace std;

class RNDTreeException
{
	string code;
public:
	RNDTreeException() { code = "Исключение"; }
	string What() { return code; }
};

template<class K, class T>
class RNDTree : public Tree<K, T>
{
public:
    T GetData(K key); //Чтение данных по ключу
	bool Insert(K key, T val); //Включение данных по ключу
	bool Delete(K key); //Удаление данных по ключу
    void Show(); //Вертикальная печать дерева
private:
    void CalcN(typename Tree <K, T>::Node* h);
    typename Tree<K, T>::Node* RNDJoin(typename Tree <K, T>::Node* a, typename Tree <K, T>::Node* b);
    void _Show(typename Tree<K, T>::Node* r, int level);
};

//Получение данных по ключу
template<class K, class T>
T RNDTree<K, T>::GetData(K key) {
    typename Tree<K, T>::Node* current = this->root;
    while (current != nullptr) {
        this->cnt++;
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
    throw RNDTreeException();
}
//Вставка
template <typename K, typename T>
bool RNDTree<K, T>::Insert(K key, T val) {
    typename Tree <K, T>::Node* t = new typename Tree <K, T>::Node(key, val), * temp = this->root, * subroot = NULL;
    if (this->root == NULL) {
        this->root = t;
        this->size++;
        this->cnt++;
    }
    else {
        bool goDown = true, insertInRoot = true, loop = true;
        while ((goDown) && (insertInRoot)) {
            this->cnt++;
            if (rand() < RAND_MAX / temp->n + 1) {
                subroot = temp;
                insertInRoot = false;
            }
            else {
                if (t->key == temp->key) return false;
                if (t->key < temp->key) {
                    if (temp->left == NULL) goDown = false;
                    else temp = temp->left;
                }
                if (t->key > temp->key) {
                    if (temp->right == NULL) goDown = false;
                    else temp = temp->right;
                }
            }
        }
        while (true) {
            this->cnt++;
            if (t->key == temp->key) return false;
            if (t->key > temp->key)
                if (temp->right == NULL) {
                    temp->right = t;
                    t->parent = temp;
                    this->size++;
                    break;
                }
                else temp = temp->right;
            else {
                if (temp->left == NULL) {
                    temp->left = t;
                    t->parent = temp;
                    this->size++;
                    break;
                }
                else temp = temp->left;
            }
        }
        temp = t;
        while (temp != this->root) {
            temp = temp->parent;
            temp->n++;
        }
        if (insertInRoot == NULL) {
            loop = true;
            while (loop) {
                this->cnt++;
                temp = t->parent;
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
                    if (temp->key > temp->parent->key) temp->parent->right = t;
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
            }
        }
    }
    return true;
}
//Удаление
template <class K, class T>
bool RNDTree<K, T>::Delete(K key) {
    typename Tree<K, T>::Node* prev, * h = this->root;
    while (true) {
        this->cnt++;
        if (h == NULL) return false;
        K w = h->key;
        if (key < w) h = h->left;
        if (key > w) h = h->right;
        if (key == w) {
            typename Tree<K, T>::Node* t = h;
            if (h == this->root) {
                this->root = h = RNDJoin(h->left, h->right);
                if (this->root) this->root->parent = NULL;
            }
            else {
                prev = h->parent;
                if (prev->left == h) prev->left = h = RNDJoin(h->left, h->right);
                else prev->right = h = RNDJoin(h->left, h->right);
                if (h) h->parent = prev;
                if (!h) h = prev;
            }
            delete t;
            this->size--;
            break;
        }
    }
    while (h) {
        CalcN(h);
        h = h->parent;
    }
    return true;
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