#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <stdexcept>


template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    Node(const T& val) : data(val), next(nullptr) {}
};


template<typename T>
struct DNode {
    T data;
    std::shared_ptr<DNode<T>> prev;
    std::shared_ptr<DNode<T>> next;
    DNode(const T& val) : data(val), prev(nullptr), next(nullptr) {}
};


template<typename T>
class SinglyLinkedList {
private:
    std::shared_ptr<Node<T>> head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void addFront(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = head;
        head = newNode;
    }

    void addBack(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        if (!head) {
            head = newNode;
            return;
        }
        auto curr = head;
        while (curr->next) curr = curr->next;
        curr->next = newNode;
    }

    void removeFront() {
        if (!head) throw std::underflow_error("Empty list");
        head = head->next;
    }

    void removeBack() {
        if (!head) throw std::underflow_error("Empty list");
        if (!head->next) {
            head = nullptr;
            return;
        }
        auto curr = head;
        while (curr->next->next) curr = curr->next;
        curr->next = nullptr;
    }

    T& peekFront() {
        if (!head) throw std::underflow_error("Empty list");
        return head->data;
    }

    T& peekBack() {
        if (!head) throw std::underflow_error("Empty list");
        auto curr = head;
        while (curr->next) curr = curr->next;
        return curr->data;
    }

    bool isEmpty() const {
        return !head;
    }

    void print() const {
        auto curr = head;
        while (curr) {
            std::cout << curr->data << " -> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }
};


template<typename T>
class DoublyLinkedList {
private:
    std::shared_ptr<DNode<T>> head, tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void addFront(const T& value) {
        auto newNode = std::make_shared<DNode<T>>(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void addBack(const T& value) {
        auto newNode = std::make_shared<DNode<T>>(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void removeFront() {
        if (!head) throw std::underflow_error("Empty list");
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
    }

    void removeBack() {
        if (!tail) throw std::underflow_error("Empty list");
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
    }

    T& peekFront() {
        if (!head) throw std::underflow_error("Empty list");
        return head->data;
    }

    T& peekBack() {
        if (!tail) throw std::underflow_error("Empty list");
        return tail->data;
    }

    bool isEmpty() const {
        return !head;
    }

    void print() const {
        auto curr = head;
        while (curr) {
            std::cout << curr->data << " <-> ";
            curr = curr->next;
        }
        std::cout << "nullptr\n";
    }
};


template<typename T>
class ArrayQueue {
private:
    T* data;
    size_t capacity;
    int front, rear, count;

public:
    ArrayQueue(size_t cap = 100) : capacity(cap), front(0), rear(-1), count(0) {
        data = new T[capacity];
    }

    ~ArrayQueue() {
        delete[] data;
    }

    void enqueue(const T& value) {
        if (isFull()) throw std::overflow_error("Queue full");
        rear = (rear + 1) % capacity;
        data[rear] = value;
        count++;
    }

    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue empty");
        front = (front + 1) % capacity;
        count--;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Queue empty");
        return data[front];
    }

    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
};


template<typename T>
class LinkedListQueue {
private:
    std::shared_ptr<Node<T>> front, rear;

public:
    void enqueue(const T& value) {
        auto node = std::make_shared<Node<T>>(value);
        if (rear) rear->next = node;
        rear = node;
        if (!front) front = rear;
    }

    void dequeue() {
        if (!front) throw std::underflow_error("Queue empty");
        front = front->next;
        if (!front) rear = nullptr;
    }

    T& peek() {
        if (!front) throw std::underflow_error("Queue empty");
        return front->data;
    }

    bool isEmpty() const { return front == nullptr; }
    bool isFull() const { return false; }
};


template<typename T>
class PriorityQueue {
private:
    std::vector<T> data;

public:
    void enqueue(const T& value) {
        data.push_back(value);
        std::sort(data.begin(), data.end(), std::greater<T>());
    }

    void dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue empty");
        data.erase(data.begin());
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Queue empty");
        return data.front();
    }

    bool isEmpty() const { return data.empty(); }
    bool isFull() const { return false; }
};


template<typename T>
class ArrayStack {
private:
    T* data;
    int top;
    size_t capacity;

public:
    ArrayStack(size_t cap = 100) : top(-1), capacity(cap) {
        data = new T[capacity];
    }

    ~ArrayStack() {
        delete[] data;
    }

    void push(const T& value) {
        if (isFull()) throw std::overflow_error("Stack full");
        data[++top] = value;
    }

    void pop() {
        if (isEmpty()) throw std::underflow_error("Stack empty");
        --top;
    }

    T& peek() {
        if (isEmpty()) throw std::underflow_error("Stack empty");
        return data[top];
    }

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top + 1 == capacity; }
};


template<typename T>
class LinkedListStack {
private:
    std::shared_ptr<Node<T>> top;

public:
    void push(const T& value) {
        auto newNode = std::make_shared<Node<T>>(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (!top) throw std::underflow_error("Stack empty");
        top = top->next;
    }

    T& peek() {
        if (!top) throw std::underflow_error("Stack empty");
        return top->data;
    }

    bool isEmpty() const { return top == nullptr; }
    bool isFull() const { return false; }
};


int main() {
    SinglyLinkedList<int> sll;
    sll.addFront(10);
    sll.addBack(20);
    sll.print();

    DoublyLinkedList<int> dll;
    dll.addFront(100);
    dll.addBack(200);
    dll.print();

    ArrayQueue<int> aq;
    aq.enqueue(1); aq.enqueue(2);
    std::cout << "ArrayQueue peek: " << aq.peek() << "\n";

    LinkedListQueue<std::string> lq;
    lq.enqueue("Hello"); lq.enqueue("World");
    std::cout << "LinkedListQueue peek: " << lq.peek() << "\n";

    PriorityQueue<int> pq;
    pq.enqueue(5); pq.enqueue(2); pq.enqueue(9);
    std::cout << "PriorityQueue peek: " << pq.peek() << "\n";

    ArrayStack<int> as;
    as.push(50); as.push(60);
    std::cout << "ArrayStack peek: " << as.peek() << "\n";

    LinkedListStack<std::string> ls;
    ls.push("Stack"); ls.push("Top");
    std::cout << "LinkedListStack peek: " << ls.peek() << "\n";

    return 0;
}

