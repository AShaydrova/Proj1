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
        std::ios_base::iostate s = stream.exceptions();

        stream.exceptions(std::ios_base::eofbit);

        Stack<Person> ret; //создание стека типа Person
        Person pers;
        std::string word, word2;
        while (1) {
            try {
                stream >> word;
                pers.setLastName(word);
                stream >> word;
                stream >> word2;
                word = word + " " + word2;
                pers.setFirstName(word);
                ret.Push(pers);
            }
            catch (const std::ios_base::failure&) {
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
                pers = ret.Pop();
                word = pers.getLastName();
                stream << word << " ";
                word = pers.getFirstName();
                stream << word << std::endl;
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
