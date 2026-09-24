#pragma once
#include <iostream>

class MyString
{
    char *data{nullptr};
    size_t size{0};

public:
    MyString() : size(0)
    {
        data = new char[1];
        data[size] = '\0';
    }
    MyString(size_t n) : size(n)
    {
        data = new char[size + 1];
        data[0] = '\0';
        data[size] = '\0';
    }

    MyString(const MyString &other) : MyString(other.size)
    {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        data[size] = '\0';
    }

    MyString(const char *str) : size(0)
    {
        while (str[size] != '\0')
        {
            size++;
        }

        data = new char[size + 1];
        for (size_t i = 0; i < size; i++)
        {
            data[i] = str[i];
        }
        data[size] = '\0';
    }

    ~MyString()
    {
        delete[] data;
    }

    MyString &operator=(const MyString &other)
    {
        if (this != &other)
        {
            size = other.size;
            delete[] data;
            data = new char[size + 1];
            for (size_t i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
            data[size] = '\0';
        }

        return *this;
    }

    bool operator<(const MyString &other) const
    {
        size_t min_size = (size < other.size) ? size : other.size;

        for (size_t i = 0; i < min_size; i++)
        {
            if (data[i] < other.data[i])
                return true;
            if (data[i] > other.data[i])
                return false;
        }
        return size < other.size;
    }

    bool operator>(const MyString &other) const
    {
        return other < *this;
    }

    bool operator<=(const MyString &other) const
    {
        return !(*this > other);
    }

    bool operator>=(const MyString &other) const
    {
        return !(*this < other);
    }

    bool operator!=(const MyString &other) const
    {
        if (size != other.size)
            return true;

        for (size_t i = 0; i < size; i++)
        {
            if (data[i] != other.data[i])
                return true;
        }

        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const MyString &str)
    {
        if (str.data != nullptr)
        {
            os << str.data;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, MyString &str)
    {
        char c;

        while (is.get(c) && (c == ' ' || c == '\n' || c == '\t' || c == '\r'))
            ;

        if (!is)
            return is;

        size_t capacity = 32;
        size_t length = 0;
        char *temp = new char[capacity];

        do
        {
            if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
            {
                is.unget();
                break;
            }

            if (length >= capacity - 1)
            {
                capacity *= 2;
                char *new_temp = new char[capacity];

                for (size_t i = 0; i < length; i++)
                {
                    new_temp[i] = temp[i];
                }

                delete[] temp;
                temp = new_temp;
            }

            temp[length++] = c;
        } while (is.get(c));

        temp[length] = '\0';

        delete[] str.data;
        str.size = length;
        str.data = temp;

        return is;
    }
};