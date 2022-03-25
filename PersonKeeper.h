#ifndef PERSONKEEPER_H
#define PERSONKEEPER_H

#include <fstream>
#include "Person.h"
#include "TStack.h"

// Класс PersonKeeper для записи из файла в стек элементов
//      класса Person и записи в поток из стека с
//      элементами класса Person.
// Конструкторы класса (закрыты):
//      конструктор по умолчанию PersonKeeper().
//      конструктор копирования PersonKeeper(PersonKeeper const&).
// PersonKeeper& Instance() -
//      статический создающий метод, который будет использоваться
//      для получения единственного объекта класса PersonKeeper.
//      Возвращает ссылку на объект класса PersonKeeper
// Метод readPersons(std::istream& stream)
//      Метод считывает информацию о людях из входного
//      файла (файл передается аргументом), создает на основе этой
//      информации объекты класса Person, и помещает их в стек.
//      Метод возвращает стек.
// Метод writePersons(std::ostream& stream, Stack<Person> ret)
//      Метод записывает в файл из
//      стека (файл и стек передаются аргументами) информацию о людях
//      При этом передаваемый методу writePersons стек не изменяется
//      (передача по значению).
//      Метод не возвращает значение.
class PersonKeeper
{
public:
    static PersonKeeper& Instance()
    {
        static PersonKeeper k;
        return k;
    }
    Stack<Person> readPersons(std::istream& stream)
    {
        Stack<Person> ret; //создание стека типа Person
        Person pers; //создание объекта класса Person
        for (std::string last_name, name, patronymic; stream >> last_name >> name >> patronymic;)
        {
            pers.setLastName(last_name); // фамилия записывается в объект Person
            pers.setFirstName(name + " " + patronymic); //запись имени и отчества в объект Person
            ret.Push(pers); // объект Person помещается в стек
        }
        return ret;
    }
    void writePersons(std::ostream& stream, Stack<Person> ret)
    {
        Person pers;
        std::string word;
        while (1) {
            try
            {
                pers = ret.Pop(); // объект Person извлекается из стека
                word = pers.getLastName(); // считыванается фамилия из объекта Person
                stream << word << " "; // фамилия записывается в файл
                word = pers.getFirstName(); // считываются имя и отчество из объекта Person
                stream << word << std::endl; // имя и отчество записываются в файл
            }
            catch (const exc::EStackException& e) { // обрабатывается исключение
                break;
            }
        }
    }
private:
    PersonKeeper() {}
    ~PersonKeeper() {}
    PersonKeeper(PersonKeeper const&);
    PersonKeeper& operator=(PersonKeeper const&);
};

#endif // PERSONKEEPER_H
