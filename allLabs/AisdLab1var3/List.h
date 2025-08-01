#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class List {
private:
    struct Node {
        T data;
        int next;
        bool isUsed;
    };

    Node* nodes;
    int capacity;
    int size;
    int head;
    int freeList;

    void ensureCapacity() {
        if (size == capacity) {
            throw std::runtime_error("Maximum capacity reached");
        }
    }

    int getFreeNode() {
        if (freeList == -1) {
            ensureCapacity();
        }
        int index = freeList;
        freeList = nodes[freeList].next;
        nodes[index].isUsed = true;
        return index;
    }

    void freeNode(int index) {
        nodes[index].next = freeList;
        nodes[index].isUsed = false;
        freeList = index;
    }

public:
    List(int initialCapacity) : capacity(initialCapacity), size(0), head(-1), freeList(0) {
        if (initialCapacity <= 0) {
            throw std::invalid_argument("Initial capacity must be positive");
        }

        nodes = new Node[capacity];
        for (int i = 0; i < capacity; ++i) {
            nodes[i].next = i + 1;
            nodes[i].isUsed = false;
        }
        nodes[capacity - 1].next = -1;
    }

    ~List() {
        delete[] nodes;
    }

    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    bool contains(const T& value) const {
        int current = head;
        while (current != -1) {
            if (nodes[current].data == value) return true;
            current = nodes[current].next;
        }
        return false;
    }

    T get(size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");

        int current = head;
        for (size_t i = 0; i < index; ++i) {
            current = nodes[current].next;
        }
        return nodes[current].data;
    }

    bool get(size_t index, T& value) const {
        if (index >= size) return false;

        int current = head;
        for (size_t i = 0; i < index; ++i) {
            current = nodes[current].next;
        }
        value = nodes[current].data;
        return true;
    }

    bool set(size_t index, const T& value) {
        if (index >= size) return false;

        int current = head;
        for (size_t i = 0; i < index; ++i) {
            current = nodes[current].next;
        }
        nodes[current].data = value;
        return true;
    }

    bool indexOf(const T& value, size_t& foundIndex) const {
        int current = head;
        size_t index = 0;
        while (current != -1) {
            if (nodes[current].data == value) {
                foundIndex = index;
                return true;
            }
            current = nodes[current].next;
            ++index;
        }
        return false;
    }

    bool add(const T& value) {
        try {
            int newNode = getFreeNode();
            nodes[newNode].data = value;
            nodes[newNode].next = head;
            head = newNode;
            ++size;
            return true;
        }
        catch (...) {
            return false;
        }
    }

    bool addAt(size_t index, const T& value) {
        if (index > size) return false;

        try {
            if (index == 0) return add(value);

            int newNode = getFreeNode();
            nodes[newNode].data = value;

            int prev = head;
            for (size_t i = 0; i < index - 1; ++i) {
                prev = nodes[prev].next;
            }

            nodes[newNode].next = nodes[prev].next;
            nodes[prev].next = newNode;
            ++size;
            return true;
        }
        catch (...) {
            return false;
        }
    }

    bool remove(const T& value) {
        if (head == -1) return false;

        if (nodes[head].data == value) {
            int toRemove = head;
            head = nodes[head].next;
            freeNode(toRemove);
            --size;
            return true;
        }

        int prev = head;
        while (nodes[prev].next != -1 && nodes[nodes[prev].next].data != value) {
            prev = nodes[prev].next;
        }

        if (nodes[prev].next != -1) {
            int toRemove = nodes[prev].next;
            nodes[prev].next = nodes[toRemove].next;
            freeNode(toRemove);
            --size;
            return true;
        }
        return false;
    }

    bool removeAt(size_t index) {
        if (index >= size) return false;

        if (index == 0) {
            int toRemove = head;
            head = nodes[head].next;
            freeNode(toRemove);
        }
        else {
            int prev = head;
            for (size_t i = 0; i < index - 1; ++i) {
                prev = nodes[prev].next;
            }

            int toRemove = nodes[prev].next;
            nodes[prev].next = nodes[toRemove].next;
            freeNode(toRemove);
        }
        --size;
        return true;
    }

    void clear() {
        int current = head;
        while (current != -1) {
            int next = nodes[current].next;
            freeNode(current);
            current = next;
        }
        head = -1;
        size = 0;
    }

    void display() const {
        int current = head;
        while (current != -1) {
            std::cout << nodes[current].data << " ";
            current = nodes[current].next;
        }
        std::cout << std::endl;
    }

    class Iterator {
    private:
        const List<T>* list;
        int currentIndex;

    public:
        Iterator(const List<T>* l, int index) : list(l), currentIndex(index) {}

        T& operator*() {
            if (currentIndex == -1) throw std::out_of_range("Exception");
            return const_cast<T&>(list->nodes[currentIndex].data);
        }

        const T& operator*() const {
            if (currentIndex == -1) throw std::out_of_range("Exception");
            return list->nodes[currentIndex].data;
        }

        Iterator& operator++() {
            if (currentIndex != -1) {
                currentIndex = list->nodes[currentIndex].next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const Iterator& other) const {
            return currentIndex == other.currentIndex;
        }

        bool operator!=(const Iterator& other) const {
            return currentIndex != other.currentIndex;
        }
    };

    Iterator begin() const { return Iterator(this, head); }
    Iterator end() const { return Iterator(this, -1); }
};

#endif