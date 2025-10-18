#include <iostream>
#include "FOUR.h"

using namespace std;

int main() {
    try {
        cout << "Тест 1: Простое вычитание" << endl;
        Four a1 = {3, 2, 1};
        Four b1 = {1, 3};
        Four c1 = a1.minus(b1);
        
        cout << "321₄ - 13₄ = ";
        c1.print(cout);
        cout << "₄" << endl;
        cout << "Ожидаемый результат: 302₄ (50₁₀)" << endl << endl;

        cout << "Тест 2: Вычитание с заимствованием" << endl;
        Four a2 = {1, 0, 0}; 
        Four b2 = {1}; 
        Four c2 = a2.minus(b2);
        
        cout << "100₄ - 1₄ = ";
        c2.print(cout);
        cout << "₄" << endl;
        cout << "Ожидаемый результат: 33₄ (15₁₀)" << endl << endl;

        cout << "Тест 3: Вычитание равных чисел" << endl;
        Four a3 = {2, 1, 3};
        Four b3 = {2, 1, 3};
        Four c3 = a3.minus(b3);
        
        cout << "213₄ - 213₄ = ";
        c3.print(cout);
        cout << "₄" << endl;
        cout << "Ожидаемый результат: 0₄" << endl << endl;

        cout << "Тест 4: Вычитание из числа с удалением незначащих нулей" << endl;
        Four a4 = {0, 3, 0, 1};  
        Four b4 = {2, 3};
        Four c4 = a4.minus(b4);
        
        cout << "301₄ - 23₄ = ";
        c4.print(cout);
        cout << "₄" << endl;
        cout << "Ожидаемый результат: 212₄ (38₁₀)" << endl << endl;

        cout << "Тест 5: Попытка вычитания с отрицательным результатом" << endl;
        Four small = {1, 2};    
        Four large = {3, 2, 1};
        
        try {
            Four error = small.minus(large);
        } catch (const logic_error& e) {
            cout << "Поймано исключение: " << e.what() << endl;
            cout << "Это корректное поведение!" << endl << endl;
        }
    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    cout << endl << "Все тесты завершены успешно!" << endl;
    return 0;
}