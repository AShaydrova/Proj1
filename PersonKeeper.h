#ifndef PERSONKEEPER_H
#define PERSONKEEPER_H

#include <fstream>
#include "Person.h"
#include <TStack.h>

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
        std::ios_base::iostate s = stream.exceptions(); //Сохранили состояние исключений потока

        //Установили состояние таким образом, что при достижении
        //конца файла будет сгенерировано исключение
        stream.exceptions(std::ios_base::eofbit);

        Stack<Person> ret; //создание стека типа Person
        Person pers; //создание объекта класса Person
        std::string word, word2; //переменные для хранения строк
        while (1) {
            try {
                stream >> word;  //считывание фамилии из входного потока
                pers.setLastName(word); //запись фамилии в объект Person
                stream >> word; //считывание имени из входного потока
                stream >> word2; //считывание отчества из входного потока
                word = word + " " + word2; //объединение считанных имени и отчества в одну строку
                pers.setFirstName(word); //запись имени и отчества в объект Person
                ret.Push(pers); //помещение объекта Person в стек
            }
            catch (const std::ios_base::failure&) { // обрабатываем исключение
                break;
            }
        }
        stream.exceptions(s);
        return ret;
    }
    void writePersons(std::ostream& stream, Stack<Person> ret)
    {
        Person pers;
        std::string word;
        while (1) {
            try
            {
                pers = ret.Pop(); //извлечение объекта Person из стека
                word = pers.getLastName(); //считывание фамилии из объекта Person
                stream << word << " "; //запись в файл фамилии
                word = pers.getFirstName(); //считывание имени и отчества из объекта Person
                stream << word << std::endl; //запись в файл имени и отчества
            }
            catch (const exc::EStackException& e) { // обрабатываем исключение
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
