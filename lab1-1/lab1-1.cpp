#include "lab1-1.h"
#include <windows.h>

int input()
{
    int temp;
    while (true)
    {
        std::cin >> temp;

        if (std::cin.fail() || temp < 0)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Введите целое положительное число: ";
            continue;
        }
        break;
    }
    return temp;
}

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int rows, cols;

    std::cout << "Введите размер первой матрицы (строки x столбцы): ";
    rows = input();
    cols = input();
    Matrix M1(rows, cols);
    M1.inputMatrix();

    std::cout << "Введите размер второй матрицы (строки x столбцы): ";
    rows = input();
    cols = input();
    Matrix M2(rows, cols);
    M2.inputMatrix();

    std::cout << "Матрица M1:\n";
    M1.printMatrix();
    std::cout << "Матрица M2:\n";
    M2.printMatrix();

    std::cout << "\nСложение (M3 = M1 + M2)\n";
    Matrix M3 = M1 + M2;
    M3.printMatrix();

    std::cout << "\nУмножение (M4 = M1 * M2)\n";
    Matrix M4 = M1 * M2;
    M4.printMatrix();

    std::cout << "\nКопирование (M5 = M1)\n";
    Matrix M5 = M1;
    M5.printMatrix();

    std::cout << "\nПроверка += (M5 += M2)\n";
    M5 += M2;
    M5.printMatrix();

    std::cout << "\nПроверка *= (M5 *= M2)\n";
    M5 *= M2;
    M5.printMatrix();

    std::cout << "\nПроверка присваивания (M5 = M2)\n";
    M5 = M2;
    M5.printMatrix();
}