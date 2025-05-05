//
// Created by Oksana Mikhalyncuk on 21.04.2025.
//

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#pragma once
#include "Node.h"
#include <memory>
#include <iostream>
#include <stdexcept>

template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    size_t size;

public:
    SinglyLinkedList();
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    T& at(size_t index);
    void insert(size_t index, const T& value);
    void erase(size_t index);
    size_t get_size() const;
    bool empty() const;
    bool contains(const T& value) const;
    void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
        list.print(os);
        return os;
    }
};



#endif //SINGLYLINKEDLIST_H
