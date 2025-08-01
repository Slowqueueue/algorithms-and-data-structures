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
	bool Insert(K key, T val);//Включение данных по ключу
	bool Delete(K key); //Удаление данных по ключу
	void Show(); //Вертикальная печать дерева
	T& GetData(K key); //Чтение данных по ключу
private:
	void _Show(typename Tree<K,T>::Node* r, int level); //Вспомогательная функция для вертикальной печати 	
	bool _Insert(typename Tree <K, T>::Node*& t, K key, T val, typename Tree <K, T>::Side side); //Вспомогательная функция для включения данных
	void fixRBTree(typename Tree <K, T>::Node* x);	//Cохранение свойств красно-черного дерева
	bool isRed(typename Tree <K, T>::Node* node); //Проверка на цвет узла
	void setColor(typename Tree <K, T>::Node* node, bool color); //Установка цвета узла
	typename Tree<K, T>::Node* rotate(typename Tree <K, T>::Node* p, typename Tree <K, T>::Side side); //Поворот
	typename Tree<K, T>::Node* _GetData(K key, typename Tree<K, T>::Node* root); //Вспомогательная функция для чтения данных по ключу
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
	if (side == this->LEFT) // в случае поворота налево
	{
		typename Tree <K, T>::Node* r = p->right; // Node* r - стержень дерева
		p->right = r->left;
		if (r->left) r->left->parent = p;
		r->parent = p->parent; // при этом возможно что r станет корнем дерева,
		if (!p->parent) //								если нет предка у узла p
		{
			this->root = r;
		}
		else if (p->parent->left == p) // если левый потомок предка p ссылается сам на себя,
		{
			p->parent->left = r;						// то присваиваем ему значение стержня
		}
		else
		{
			p->parent->right = r;
		}
		r->left = p;		// делаем p левым потомком стержня r
		p->parent = r;		//
		return r;
	}
	else // в случае поворота направо аналогично
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
bool RbTree<K, T>::_Insert(typename Tree <K, T>::Node*& t, K key, T val, typename Tree <K, T>::Side side) {
	if (!t)									// при отсутствии заданного узла
	{
		t = new typename Tree <K, T>::Node(key, val); // создаем его
		return true;
	}
	if (isRed(t->left) && isRed(t->right)) // когда узел существует, а его левый и правый потомки красные
	{
		t->color = RED;			// цвет узла будет красным
		t->left->color = BLACK;	// а цвета потомков черным (свойство RB-дерева) 
		t->right->color = BLACK;
	}
	bool success; // успешно ли прошла вставка
	if (t->key == key) // если такой ключ уже есть в данном узле возврат false
	{
		return false;
	}
	else if (key < t->key) // иначе если заданный ключ меньше ключа в узле
	{
		success = _Insert(t->left, key, val, this->LEFT); // вставляем влево
		t->left->parent = t;
		if (isRed(t) && isRed(t->left) && (side == this->RIGHT)) // если узел и его левый потомок красные,
		{
			t = rotate(t, this->RIGHT);								// то поворачиваем вправо
		}
		if (isRed(t->left) && isRed(t->left->left))  // если левый потомок и левый потомок левого потомка красные
		{
			t = rotate(t, this->RIGHT);	// поворачиваем вправо
			t->color = BLACK;	// красим узел в черный
			t->right->color = RED; // а его правого потомка в красный
		}
	}
	else
	{
		success = _Insert(t->right, key, val, this->RIGHT); // иначе вставляем вправо
		t->right->parent = t;
		if (isRed(t) && isRed(t->right) && (side == this->LEFT)) // если узел и его правый потомок красные, а сторона левая,
		{
			t = rotate(t, this->LEFT);							// то поворачиваем влево
		}
		if (isRed(t->right) && isRed(t->right->right))	// если правый потомок и правый потомок правого потомка красные
		{
			t = rotate(t, this->LEFT);	// поворачиваем влево
			t->color = BLACK;	// красим узел в черный
			t->left->color = RED;	// а левого потомка в красный
		}
	}
	this->cnt++;
	return success;
}

template <class K, class T>
bool RbTree<K, T>::Insert(K key, T val)
{
	this->cnt = 0;
	bool success = _Insert(this->root, key, val, this->LEFT); // вставка по умолчанию влево
	if (!success) return false;
	this->root->color = BLACK; // красим корень в черный
	this->size++;	// инкремент счетчика размера дерева
	return true;
}

//Cохранение свойств красно-черного дерева
template <class K, class T>
void RbTree<K, T>::fixRBTree(typename Tree <K, T>::Node* x)
{
	while (x != this->root && isRed(x) == BLACK) // пока заданный узел x - не корень и он черный
	{
		if (x == getLeft(getParent(x))) // если x - левый потомок предка самого себя
		{
			typename Tree <K, T>::Node* sibling = getRight(getParent(x)); // то братом x делаем правого потомка предка x

			if (isRed(sibling) == RED) {		// если брат x красный
				setColor(sibling, BLACK);		// делаем брата черным
				setColor(getParent(x), RED);	// делаем предка x красным
				rotate(getParent(x), this->LEFT); // и поворачиваем влево по предку x
				sibling = getRight(getParent(x)); // братом становится правый потомок предка x
			}

			if (!isRed(getLeft(sibling)) && !isRed(getRight(sibling))) { // если оба потомка брата черные
				setColor(sibling, RED); // делаем брата красным
				x = getParent(x); // а x становится предком
			}
			else {
				if (isRed(getRight(sibling)) == BLACK) { // если правый потомок брата черный
					setColor(getLeft(sibling), BLACK); // красим левого потомка брата тоже в черный
					setColor(sibling, RED); // а брата делаем красным
					rotate(sibling, this->RIGHT); // поворачиваем вправо по брату
					sibling = getRight(getParent(x)); // брат становится правым потомком предка x
				}
				setColor(sibling, isRed(getParent(x))); // цвет брата становится цветом отца x
				setColor(getParent(x), BLACK); // красим предка x в черный
				setColor(getRight(sibling), BLACK); // и правого потока брата в черный
				rotate(getParent(x), this->LEFT); // поворачиваем влево по брату
				x = this->root; // x становится корнем
			}
		}
		else { // симметрично
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
	typename Tree <K, T>::Node* t = this->root, * x = NULL; // x - вспомогательная переменная
	while (t != NULL && t->key != key) // пока не дошли до листа с NULL-значением и ключ корня не равен заданному
	{
		if (key < t->key) t = t->left; // если заданный ключ меньше текущего то идем влево
		else t = t->right;	// иначе вправо
		this->cnt++;
	}
	if (t == NULL)	return false; // если дошли до листа
	this->cnt++;
	if (t->left && t->right) // если есть правый и левый потомки
	{
		x = this->successor(t); // в x записываем следующий по ключу узел
		t->key = x->key; // ключом t становится ключ x
		t->data = t->data; // аналогично данные
		t = x;	// и сам узел
	}
	typename Tree <K, T>::Node* replacement = (t->left ? t->left : t->right); // если есть левый потомок - записываем его, иначе - правого

	if (replacement)
	{
		t->key = replacement->key;  // запись в t ключей replacement
		t->data = replacement->data; // данных
		t->left = t->right = NULL; // обнуление потомков t
		t = replacement;
	}
	else if (!t->parent) // если у t нет предка
	{
		this->root = NULL; // обнуляем корень
	}
	else
	{
		if (t->color == BLACK) // если t - черный, восстанавливаем RB-дерево согласно свойствам
			fixRBTree(t);

		if (t->parent) // если у t есть предок
		{
			if (t == t->parent->left)	// если t - левый потомок предка t,
				t->parent->left = NULL; // то обнуляем левого потомка предка t
			else if (t == t->parent->right) // если правый
				t->parent->right = NULL;	// аналогично
			t->parent = NULL; // обнуляем предка t
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
//Получение данных по ключу
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