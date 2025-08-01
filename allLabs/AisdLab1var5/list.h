#include <iostream>
#include <stdexcept>

using namespace std;

template<class T>
class List {
protected:
    class Node {
    public:
        T data;
        Node* next;
        Node* previous;
        Node();
        Node(T);
        Node(T, Node*, Node*);
    };

    int size;
    Node* head;
    Node* tail;

public:
    class Iterator {
    public:
        List* list;
        Node* node;

        Iterator();
        Iterator(List*, Node*);

        T& operator*() const;
        bool operator==(const Iterator& iter2) const;
        bool operator!=(const Iterator& iter2) const;
        void operator++();
        void operator--();
    };

    class ReverseIterator {
    public:
        List* list;
        Node* node;

        ReverseIterator();
        ReverseIterator(List*, Node*);

        T& operator*() const;
        bool operator==(const ReverseIterator& reviter2) const;
        bool operator!=(const ReverseIterator& reviter2) const;
        void operator++();
        void operator--();
    };

    List();
    List(const List<T>&);
    ~List();
    int get_size();
    void clear();
    bool is_empty();
    bool contains_value(T);
    T get_value(int);
    bool change_value(int, T);
    int get_index(T);
    void pushback(T);
    bool add_node(int, T);
    bool remove_by_value(T);
    bool remove_by_index(int);
    void print();

    Iterator begin();
    Iterator end();
    ReverseIterator rbegin();
    ReverseIterator rend();

    friend Iterator;
    friend ReverseIterator;
};

template<typename T>
List<T>::Node::Node() : next(nullptr), previous(nullptr) {};

template<typename T>
List<T>::Node::Node(T data) : data(data), next(nullptr), previous(nullptr) {};

template<typename T>
List<T>::Node::Node(T data, Node* newNext, Node* newPrevious) : data(data), next(newNext), previous(newPrevious) {};

template<typename T>
List<T>::List() : size(0), head(nullptr), tail(nullptr) {}

template<typename T>
List<T>::List(const List<T>& list2) {
    head = tail = nullptr;
    size = 0;

    if (list2.head != nullptr) {
        Node* list2Current = list2.head;
        do {
            pushBack(list2Current->data);
            list2Current = list2Current->next;
        } while (list2Current != nullptr);
    }
}

template<typename T>
List<T>::~List() { clear(); }

template<typename T>
int List<T>::get_size() { return size; }

template<typename T>
void List<T>::clear() {
    if (head == nullptr) return;

    Node* current = head;
    do {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    } while (current != nullptr);

    head = tail = nullptr;
    size = 0;
}

template<typename T>
bool List<T>::is_empty() { return size == 0; }

template<typename T>
bool List<T>::contains_value(T data)
{
    if (head == nullptr) return false;

    Node* current = head;
    do {
        if (current->data == data)
            return true;
        current = current->next;
    } while (current != nullptr);

    return false;
}

template<typename T>
T List<T>::get_value(int idx)
{
    if (idx < 0 || idx >= size)
        throw out_of_range("Исключение");

    Node* current = head;
    for (int i = 0; i < idx; ++i) {
        current = current->next;
    }

    return current->data;
}

template<typename T>
bool List<T>::change_value(int idx, T data)
{
    if (idx < 0 || idx >= size)
        return false;

    Node* current = head;
    for (int i = 0; i < idx; ++i) {
        current = current->next;
    }

    current->data = data;
    return true;
}

template<typename T>
int List<T>::get_index(T data)
{
    if (head == nullptr) return -1;

    int index = 0;
    Node* current = head;
    do {
        if (current->data == data)
            return index;
        current = current->next;
        index++;
    } while (current != nullptr);

    return -1;
}

template<typename T>
void List<T>::pushback(T data)
{
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        Node* prev = tail;
        tail->next = newNode;  
        tail = newNode;     
        tail->previous = prev;
    }

    size++;
}

template<typename T>
bool List<T>::add_node(int idx, T data)
{
    if (idx < 0 || idx > size)
        return false;

    if (idx == size) {
        pushback(data);
        return true;
    }

    if (idx == 0) {
        Node* node = new Node(data);
        node->next = head;
        head->previous = node;
        head = node;
        size++;
        return true;
    }

    Node* prev = head;
    for (int i = 0; i < idx - 1; ++i) {
        prev = prev->next;
    }

    Node* newNode = new Node(data, prev->next, prev);
    prev->next = newNode;
    newNode->next->previous = newNode;
    size++;

    return true;
}

template<typename T>
bool List<T>::remove_by_value(T data)
{
    if (head == nullptr) return false;

    Node* current = head;

    do {
        if (current->data == data) {
            if (current == head) {
                if (size == 1) {
                    delete head;
                    head = tail = nullptr;
                }
                else {
                    Node* toDelete = head;
                    head = head->next;
                    head->previous = nullptr;
                    delete toDelete;
                }
                size--;
                return true;
            }

            if (current == tail) {

                Node* toDelete = tail;
                tail = tail->previous;
                tail->next = nullptr;
                delete toDelete;

                size--;
                return true;
            }

            current->previous->next = current->next;
            current->next->previous = current->previous;

            delete current;
            size--;
            return true;
        }
        current = current->next;
    } while (current != nullptr);

    return false;
}

template<typename T>
bool List<T>::remove_by_index(int idx)
{
    if (idx < 0 || idx >= size)
        return false;

    if (idx == 0) {
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* toDelete = head;
            head = head->next;
            head->previous = nullptr;
            delete toDelete;
        }
        size--;
        return true;
    }

    Node* prev = head;
    for (int i = 0; i < idx - 1; ++i) {
        prev = prev->next;
    }

    Node* toDelete = prev->next;
    prev->next = toDelete->next;
    toDelete->next->previous = prev;

    if (toDelete == tail) {
        tail = prev;
    }

    delete toDelete;
    size--;
    return true;
}

template<typename T>
void List<T>::print()
{
    if (size == 0) {
        cout << "Список пуст" << endl; return;
    }
    Node* thisNode = head;
    int i = 0;
    do {
        cout << thisNode->data << "  ";
        i++;
        if (i == 10) { i = 0; cout << endl; }
        thisNode = thisNode->next;
    } while (thisNode != nullptr);
    cout << endl;
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
    return Iterator(this, this->head);
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
    Iterator it(this, nullptr);
    return it;
}

template<typename T>
List<T>::Iterator::Iterator() :list(nullptr), node(nullptr) {}

template<typename T>
List<T>::Iterator::Iterator(List* list, Node* node)
{
    this->list = list;
    this->node = node;
}

template<typename T>
T& List<T>::Iterator::operator*()const
{
    if (node == nullptr)
        throw invalid_argument("Прямой итератор не установлен");
    return node->data;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& iter2) const
{
    return node == iter2.node;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& iter2) const
{
    return node != iter2.node;
}

template<typename T>
void List<T>::Iterator::operator++()
{
    if (node == nullptr)
        throw invalid_argument("Прямой итератор не установлен");

    node = node->next;
}

template<typename T>
void List<T>::Iterator::operator--()
{
    if (node == nullptr || list == nullptr || list->size == 0)
        throw invalid_argument("Прямой итератор не установлен");

    node = node->previous;
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
    return ReverseIterator(this, this->tail);
}

template<typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
    ReverseIterator revit(this, nullptr);
    return revit;
}

template<typename T>
List<T>::ReverseIterator::ReverseIterator() :list(nullptr), node(nullptr) {}

template<typename T>
List<T>::ReverseIterator::ReverseIterator(List* list, Node* node)
{
    this->list = list;
    this->node = node;
}

template<typename T>
T& List<T>::ReverseIterator::operator*()const
{
    if (node == nullptr)
        throw invalid_argument("Обратный итератор не установлен");
    return node->data;
}

template<typename T>
bool List<T>::ReverseIterator::operator==(const ReverseIterator& reviter2) const
{
    return node == reviter2.node;
}

template<typename T>
bool List<T>::ReverseIterator::operator!=(const ReverseIterator& reviter2) const
{
    return node != reviter2.node;
}

template<typename T>
void List<T>::ReverseIterator::operator++()
{
    if (node == nullptr)
        throw invalid_argument("Обратный итератор не установлен");

    node = node->previous;
}

template<typename T>
void List<T>::ReverseIterator::operator--()
{
    if (node == nullptr || list == nullptr || list->size == 0)
        throw invalid_argument("Обратный итератор не установлен");

    node = node->next;
}