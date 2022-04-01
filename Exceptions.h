#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string.h>

namespace exc {

    // Класс исключительных ситуаций EStackException
    //      для обработки ошибок, которые могут возникать
    //      при работе со стеком.
    // Конструктоны класса:
    //      конструктор с аргументом строкового типа EStackException(const char* arg_message)
    //      конструктор копирования EStackException(const EStackException& arg)
    // Метод what() возвращает сообщение об ошибке,
    //      тип возвращаемого значения - строка.
    class EStackException
    {
    private:
        char* message;
    public:
        EStackException(const char* arg_message)
        {
            message = new char[strlen(arg_message) + 1];
            strcpy(message, arg_message);
        }
        EStackException(const EStackException& arg)
        {
            message = new char[strlen(arg.message) + 1];
            strcpy(message, arg.message);
        }
        ~EStackException()
        {
            delete message;
        }
        const char* what() const { return message; }
    };

    // Класс EStackEmpty является наследником класса EStackException
    // и обрабатывает ошибку, возникающую при попытке извлечения элемента из стека,
    // когда стек пуст.
    class EStackEmpty : public EStackException
    {
    public:
        EStackEmpty(const char* arg) : EStackException(arg) {}
        EStackEmpty(const EStackEmpty& arg) : EStackException(arg) {}
    };

} // of namespace exc

#endif // EXCEPTIONS_H
