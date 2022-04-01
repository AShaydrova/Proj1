#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>
#include "Exceptions.h"

// Создание структуры, описывающей узел стека
template <class T> struct Node
{
    T key;
    Node<T>* prev;
};

// Шаблонный класс стек для организации стека.
// Конструкторы класса:
//      конструктор по умолчанию Stack().
//      конструктор копирования Stack(const Stack&).
// Все методы реализованы в соответствии
//      с примененной структурой список.
// Метод Empty() очищает стек, т.е.
//      удаляет голову списка, назначая головой
//      следующий элемент в списке и так до тех пор,
//      пока элементов в списке не останется.
//      Метод не возвращает значение.
// Метод Push(T k) помещает элемент в стек, т.е. в голову списка.
//      В качестве входных аргументов передается
//      шаблонной объект по значению, который и помещается
//      в стек.
//      Метод не возвращает значение.
// Метод Pop() извлекает объект из стека, т.е. из головы списка.
//      Метод возвращает стек.
// Метод StackDim() требуется для получения размерности стека,
//      т.е. подсчитывает число элементов в списке, начиная с головы.
//      Метод возвращает целое число - размерность стека.
template <class T> class Stack
{
    Node<T>* head;
public:
    Stack() { head = nullptr; };
    Stack(const Stack<T>&);
    ~Stack() { Empty(); };
    Stack<T>& operator=(const Stack<T>&);
    void Empty();
    void Push(T k);
    T Pop();
    int StackDim();
};

template <typename T> Stack <T> ::Stack(const Stack<T>& S)
{
    if (S.head)
    {
        try
        {
            head = new Node<T>;
        }
        catch (std::bad_alloc e)
        {
            std::cout << e.what() << std::endl;
        }
        head->key = S.head->key;
        Node<T>* p0 = S.head->prev;
        Node<T>* p1 = head;
        while (p0 != nullptr)
        {
            try
            {
                p1->prev = new Node<T>;
            }
            catch (std::bad_alloc e)
            {
                std::cout << e.what() << std::endl;
            }
            p1 = p1->prev;
            p1->key = p0->key;
            p0 = p0->prev;
        }
        p1->prev = nullptr;
    }
    else
        head = nullptr;
}

template <typename T> Stack<T>& Stack <T> ::operator=(const Stack<T>& S)
{
    Empty();
    if (S.head)
    {
        try
        {
            head = new Node<T>;
        }
        catch (std::bad_alloc e)
        {
            std::cout << e.what() << std::endl;
        }
        head->key = S.head->key;
        Node<T>* p0 = S.head->prev;
        Node<T>* p1 = head;
        while (p0 != nullptr)
        {
            try
            {
                p1->prev = new Node<T>;
            }
            catch (std::bad_alloc e)
            {
                std::cout << e.what() << std::endl;
            }
            p1 = p1->prev;
            p1->key = p0->key;
            p0 = p0->prev;
        }
        p1->prev = nullptr;
    }
    else
        head = nullptr;
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
    Node<T>* p = nullptr;
    try
    {
        p = new Node<T>;
    }
    catch (std::bad_alloc e)
    {
        std::cout << e.what() << std::endl;
    }
    p->key = k;
    p->prev = head;
    head = p;
}

template <typename T> T Stack <T> ::Pop()
{
    if (head == nullptr)
    {
        throw exc::EStackEmpty("Stack is empty!");
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
