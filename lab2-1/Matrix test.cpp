#include "Matrix.h"

int main()
{

    Matrix m1(2, 2);
    Matrix m2(2, 2);

    std::cout << "Enter 4 numbers for first matrix(2x2): ";
    std::cin >> m1;

    std::cout << "Enter 4 numbers for second matrix(2x2): ";
    std::cin >> m2;

    std::cout << "\n Matrix 1 \n" << m1;
    std::cout << "\n Matrix 2 \n" << m2;
  
    std::cout << "\n Addition (m1 + m2) \n";
    std::cout << (m1 + m2);

    std::cout << "\n Multiplication (m1 * m2) \n";
    std::cout << (m1 * m2);

    m1 += m2;
    std::cout << "\n Result m1 += m2 \n";
    std::cout << m1;

}