#ifndef PERSON_H
#define PERSON_H

#include <iostream>

class Person
{
private:
    long key;
    std::string last_name;
    std::string first_name;
public:
    Person();
    Person(const Person&);
    const std::string& getLastName() const { return last_name; }
    const std::string& getFirstName() const { return first_name; }
    void setLastName(const std::string&);
    void setFirstName(const std::string&);
};
Person::Person()
{
    key = 0;
    last_name = "";
    first_name = "";
}
Person::Person(const Person& P)
{
    key = P.key;
    last_name = P.last_name;
    first_name = P.first_name;
}
void Person::setLastName(const std::string& s)
{
    last_name = s;
}
void Person::setFirstName(const std::string& s)
{
    first_name = s;
}

#endif // PERSON_H
