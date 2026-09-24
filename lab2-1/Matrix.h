#pragma once
#include <iostream>

class Matrix
{

    int rows{0}, cols{0};
    int *matrix{nullptr};

public:
    Matrix() : rows(0), cols(0), matrix(nullptr) { }

    Matrix(int r, int c) : rows(r), cols(c)
    {
        if (rows != 0 && cols != 0)
            matrix = new int[rows * cols]{};
        else
            matrix = nullptr;
    }

    Matrix(const Matrix &other) : Matrix(other.rows, other.cols)
    {
        int size = rows * cols;
        for (size_t i = 0; i < size; i++)
        {
            matrix[i] = other.matrix[i];
        }
    }

    ~Matrix()
    {
        delete[] matrix;
    }

    Matrix &operator=(const Matrix &other)
    {
        if (this != &other)
        {

            delete[] matrix;

            rows = other.rows;
            cols = other.cols;

            if (rows != 0 && cols != 0)
            {
                matrix = new int[rows * cols];

                int size = rows * cols;
                for (size_t i = 0; i < size; ++i)
                {
                    matrix[i] = other.matrix[i];
                }
            }
            else
                matrix = nullptr;
        }
        return *this;
    }

    Matrix operator+(const Matrix &other) const
    {
        if (rows != other.rows || cols != other.cols)
        {
            std::cout << "нельзя сложить матрицы\n";
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);

        int size = rows * cols;
        for (size_t i = 0; i < size; i++)
        {
            result.matrix[i] = matrix[i] + other.matrix[i];
        }
        return result;
    }

    Matrix &operator+=(const Matrix &other)
    {
        if (rows != other.rows || cols != other.cols)
        {
            std::cout << "нельзя сложить матрицы\n";
            return *this;
        }

        int size = rows * cols;
        for (int i = 0; i < size; ++i)
        {
            matrix[i] += other.matrix[i];
        }
        return *this;
    }

    Matrix operator*(const Matrix &other) const
    {
        if (cols != other.rows)
        {
            std::cout << "нельзя умножить матрицы\n";
            return Matrix(0, 0);
        }

        Matrix result(rows, other.cols);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < other.cols; j++)
            {
                result.matrix[i * other.cols + j] = 0;
                for (size_t k = 0; k < cols; k++)
                {
                    result.matrix[i * other.cols + j] += matrix[i * cols + k] * other.matrix[k * other.cols + j];
                }
            }
        }

        return result;
    }

    Matrix &operator*=(const Matrix &other)
    {
        if (cols != other.rows)
        {
            std::cout << "нельзя умножить матрицы\n";
            return *this;
        }
        *this = *this * other;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& mat)
    {
        if (mat.rows == 0 || mat.cols == 0)
        {
            os << "Пустая матрица";
            return os;
        }

        for (int i = 0; i < mat.rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                os << mat.matrix[i * mat.cols + j] << "\t"; 
            }
            os << "\n"; 
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Matrix& mat)
    {
        if (mat.rows == 0 || mat.cols == 0)
        {
            return is; 
        }

        int size = mat.rows * mat.cols;
        
        for (int i = 0; i < size; ) 
        {
            if (is >> mat.matrix[i]) 
            {
                i++; 
            }
            else 
            {
                std::cout << "Error. Enter a number ";
                
                is.clear(); 
                
                while (is.get() != '\n') {
                    if (is.eof()) break; 
                }
            }
        }
        return is;
    }
};