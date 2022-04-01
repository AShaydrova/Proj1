#include "Exceptions.h"
#include "TStack.h"
#include "PersonKeeper.h"

// Функция обрабатывает ошибки при работе с файлами
void error(const char* p)
{
    std::cerr << p;
    std::exit(1);
}

// В функции открывается на чтение входной файл
// выполнятеся метод readPersons, который возвращает
// стек с фамилиями из файла, затем метод writePersons
// который записывает данные из стека в выходной файл
int main()
{
    using namespace std;
    string input_path, output_path;
    string exit_the_loop = "n";
    cout << "Path to the input file or input n:" << endl;
    cin >> input_path;

    if (input_path != "n")
    {
        ifstream instream(input_path); // открытие входного файла на чтение

        Stack<Person> fio; // создание стека типа Person
        if (instream) { // если файл открыт, заполняем стек информацией о людях из файла
            fio = PersonKeeper::Instance().readPersons(instream);
            instream.close();

            cout << endl;
            cout << "Path to the output file:" << endl;
            cin >> output_path;

            ofstream outstream(output_path); // открытие файла на запись
            if (outstream) { // если файл открыт, записываем в поток из стека
                PersonKeeper::Instance().writePersons(outstream, fio);
                outstream.close();
            }
            else {
                error("The output file does not open");
            }
        }
        else {
            error("The input file does not open");
        }

        cout << endl;

    }
    return 0;
}
