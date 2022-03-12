#include "Exceptions.h"
#include "TStack.h"


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
    S1.Empty();

    return 0;
}
