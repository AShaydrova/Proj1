#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string.h>
namespace exc {


    class EStackException //создание класса исключений для класса стек
    {
    private:
        char* message;
    public:
        EStackException(const char* arg_message)
        {   //формирование сообщения об ошибке
            message = new char[strlen(arg_message) + 1];
            strcpy(message, arg_message);
        }
        EStackException(const EStackException& arg)
        {   //формирование сообщения об ошибке
            message = new char[strlen(arg.message) + 1];
            strcpy(message, arg.message);
        }
        ~EStackException()
        {
            delete message;
        }
        const char* what() const { return message; } //возвращает диагностическое сообщение

    };

    class EStackEmpty : public EStackException //наследник класса EStackException
    {
    public:
        EStackEmpty(const char* arg) : EStackException(arg) {}
        EStackEmpty(const EStackEmpty& arg) : EStackException(arg) {}
    };

} // of namespace exc

#endif // EXCEPTIONS_H
