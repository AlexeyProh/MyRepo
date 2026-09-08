#pragma once 
#include <iostream>

class Matrix {

    int rows{0}, cols{0};
    int **matrix{nullptr};

public:

    Matrix() = default;

    Matrix(int r, int c) : rows(r), cols(c)
    {
        if(rows != 0 && cols != 0){
            matrix = new int*[rows];
            for (size_t i = 0; i < rows; i++)
            {
                matrix[i] = new int[cols];
            }
        }
        else
            matrix = nullptr;
    }

    Matrix(const Matrix& other) : Matrix(other.rows, other.cols) 
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }

    ~Matrix()
    {
        if (matrix) {
            for (size_t i = 0; i < rows; i++)
            {
                delete[] matrix[i];
            }
            delete[] matrix;
        }
    }


    Matrix& operator=(const Matrix& other) {
        if (this != &other) {

            if(matrix){
            for (size_t i = 0; i < rows; i++)
                {
                    delete[] matrix[i];
                }
            delete[] matrix;
            }

            rows = other.rows;
            cols = other.cols;

            if(rows != 0 && cols != 0){
            matrix = new int*[rows];
            for (size_t i = 0; i < rows; i++)
            {
                matrix[i] = new int[cols];
            }

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    matrix[i][j] = other.matrix[i][j];
                }
            }
            }
            else
                matrix = nullptr;
        }
        return *this;
    }

    Matrix operator+(const Matrix& other) const
    {
        if(rows != other.rows || cols != other.cols)
        {
            std::cout << "нельзя сложить матрицы\n";
            return Matrix(0, 0);
        }

        Matrix result(rows,cols);
        
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
              result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    } 


    Matrix& operator+=(const Matrix& other)
    {
        if(rows != other.rows || cols != other.cols)
        {
            std::cout << "нельзя сложить матрицы\n";
            return *this;
        }

        *this = *this + other;
        return *this;
    } 

    Matrix operator*(const Matrix& other) const
    {
        if (cols != other.rows) {
            std::cout << "нельзя умножить матрицы\n";
            return Matrix(0 , 0);
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < other.cols; j++)
            {
               result.matrix[i][j] = 0;
               for (size_t k = 0; k < cols; k++)
               {
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
               }

            }

        }
        
        return result;
    }

    Matrix& operator*=(const Matrix& other)
    {
        if (cols != other.rows) {
            std::cout << "нельзя умножить матрицы\n";
            return *this;
        }
        *this = *this * other;
        return *this;
    }

    void printMatrix()
    {
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
               std::cout << " " << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    void inputMatrix(){
        if (rows == 0 || cols == 0) {
        std::cout << "матрица пустая" << std::endl;
        return;
    }
    
    std::cout << "Введите элементы матрицы (" << rows << "x" << cols << "):" << std::endl;
    for (size_t i = 0; i < rows; i++) {
        std::cout << "Строка " << i + 1 << ": ";
        for (size_t j = 0; j < cols; j++) {
            std::cin >> matrix[i][j];
        }
    }
    }
};