

#include "SinglyLinkedList.h"


template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), size(0) {}

template<typename T>
void SinglyLinkedList<T>::push_front(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    newNode->next = head;
    head = newNode;
    ++size;
}

template<typename T>
void SinglyLinkedList<T>::push_back(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    if (!head) {
        head = newNode;
    } else {
        auto current = head;
        while (current->next) current = current->next;
        current->next = newNode;
    }
    ++size;
}

template<typename T>
void SinglyLinkedList<T>::pop_front() {
    if (!head) throw std::out_of_range("List is empty");
    head = head->next;
    --size;
}

template<typename T>
void SinglyLinkedList<T>::pop_back() {
    if (!head) throw std::out_of_range("List is empty");
    if (!head->next) {
        head.reset();
    } else {
        auto current = head;
        while (current->next->next) current = current->next;
        current->next.reset();
    }
    --size;
}

template<typename T>
T& SinglyLinkedList<T>::at(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    auto current = head;
    for (size_t i = 0; i < index; ++i) current = current->next;
    return current->data;
}

template<typename T>
void SinglyLinkedList<T>::insert(size_t index, const T& value) {
    if (index > size) throw std::out_of_range("Index out of range");
    if (index == 0) return push_front(value);
    auto current = head;
    for (size_t i = 0; i < index - 1; ++i) current = current->next;
    auto newNode = std::make_shared<Node<T>>(value);
    newNode->next = current->next;
    current->next = newNode;
    ++size;
}

template<typename T>
void SinglyLinkedList<T>::erase(size_t index) {
    if (index >= size) throw std::out_of_range("Index out of range");
    if (index == 0) return pop_front();
    auto current = head;
    for (size_t i = 0; i < index - 1; ++i) current = current->next;
    current->next = current->next->next;
    --size;
}

template<typename T>
size_t SinglyLinkedList<T>::get_size() const {
    return size;
}

template<typename T>
bool SinglyLinkedList<T>::empty() const {
    return size == 0;
}

template<typename T>
bool SinglyLinkedList<T>::contains(const T& value) const {
    auto current = head;
    while (current) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}

template<typename T>
void SinglyLinkedList<T>::print(std::ostream& os) const {
    auto current = head;
    while (current) {
        os << current->data << " -> ";
        current = current->next;
    }
    os << "nullptr";
}

// Explicit template instantiation
template class SinglyLinkedList<int>;
template class SinglyLinkedList<std::string>;
