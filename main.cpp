#include "Exceptions.h"
#include "TStack.h"
#include "PersonKeeper.h"

void error (const char* p) //обрабатывает ошибки при работе с файлами
{
std::cerr << p;
std::exit (1);
}

int main()
{
    Stack<int> S0; //Создание стека S0
    for (int i = 1; i < 5; i++) {
        S0.Push(i); //помещение объекта в стек S0
    }
    Stack<int> S1(S0); //используется конструктор копирования
    for (int i = 5; i < 8; i++) {
        S1.Push(i); //помещение объекта в стек S1
    }
    S0 = S1; //используется оператор копирования
    std::cout << "Stack dimension: " << S0.StackDim() << std::endl; //вывод размера стека

    while(1){
        try // Критический участок. Возможны исключительные ситуации
        {
            std::cout << S0.Pop() << std::endl; //извлечение объекта из стека
        }
        catch (const exc::EStackException& e) { // обрабатываем исключение
            std::cout << "Exception: " << e.what() << std::endl;
            break;
        }
    }
    S1.Empty(); //очищение стека S1

    std::fstream instream("infile.txt", std::ios_base::out); //открытие файла на запись
    if (instream) { //если файл открыт, записываем фио в файл
        std::string fio;
        fio = "Иванов Петр Иванович";
        instream << fio << std::endl;
        fio = "Сидоров Александр Михайлович";
        instream << fio << std::endl;
        fio = "Петров Алексей Федорович";
        instream << fio << std::endl;
    }
    else {
        error("The output file does not open");
    }
    instream.close(); //закрытие файла
    instream.open("infile.txt", std::ios_base::in); //открытие файла на чтение
    Stack<Person> ret; //создание стека типа Person
    if (instream) { //если файл открыт, заполняем стек информацией о людях из файла
        ret = PersonKeeper::Instance().readPersons(instream);
        instream.close();
    }
    else {
        error("The input file does not open");
    }
    std::ofstream outstream("outfile.txt"); //открытие файла на запись
    if (outstream) { //если файл открыт, записываем в поток из стека
        PersonKeeper::Instance().writePersons(outstream, ret);
        outstream.close();
    }
    else {
        error("The output file does not open");
    }

    return 0;
}
