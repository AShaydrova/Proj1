#ifndef TSTACK_H
#define TSTACK_H

#include "Exceptions.h"
#include <iostream>

template <typename T> struct Node //создаем структуру, описывающую узел стека
{
    T key;
    Node<T>* prev;
};

template <typename T> class Stack
{
    Node<T>* head; //указатель на вершину стека
public:
    Stack() { head = nullptr; }; //конструктор по умолчанию
    Stack(const Stack&); //конструктор копирования
    ~Stack() { Empty(); }; //деструктор
    Stack<T>& operator=(const Stack<T>&); //оператор копирования
    void Empty(); // очищает стек
    void Push(T k); //помещение объекта в стек
    T Pop(); //извлечение объекта из стека
    int StackDim(); //получение размерности стека
};

template <typename T> Stack <T> ::Stack(const Stack<T>& S)
{
    head = new Node<T>;
    head->key = S.head->key;
    Node<T>* p0 = S.head->prev;
    Node<T>* p1 = head;
    while (p0 != nullptr)
    {
        p1->prev = new Node<T>;
        p1 = p1->prev;
        p1->key = p0->key;
        p0 = p0->prev;
    }
    p1->prev = nullptr;
}

template <typename T> Stack<T>& Stack <T> ::operator=(const Stack<T>& S)
{
    Empty();
    head = new Node<T>;
    head->key = S.head->key;
    Node<T>* p0 = S.head->prev;
    Node<T>* p1 = head;
    while (p0 != nullptr)
    {
        p1->prev = new Node<T>;
        p1 = p1->prev;
        p1->key = p0->key;
        p0 = p0->prev;
    }
    p1->prev = nullptr;
    return *this;
}

template <typename T> void Stack <T> ::Empty()
{
    Node<T>* p = head;
    while (p != nullptr) {
        head = head->prev;
        delete p;
        p = head;
    };
}

template <typename T> void Stack <T> ::Push(T k)
{
    Node<T>* p;
    p = new Node<T>;
    p->key = k;
    p->prev = head;
    head = p;
}

template <typename T> T Stack <T> ::Pop()
{
    if (head == nullptr)
    {
        throw exc::EStackEmpty("Stack is empty!"); //генерируем исключение
    }
    Node<T>* p;
    T key;
    key = head->key;
    p = head;
    head = head->prev;
    delete p;
    return key;
}

template <typename T> int Stack <T> ::StackDim()
{
    Node<T>* p = head;
    int count = 0;
    while (p != nullptr) {
        count++;
        p = p->prev;
    };
    return count;
}

#endif // TSTACK_H
