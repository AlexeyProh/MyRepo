#pragma once

class MyString
{
    char* data{nullptr};
    size_t size{0};

    public:
    MyString() : data(nullptr), size(0) { }
    MyString(size_t n) : size(n +1) {
        if(!n) {
            data = new char[size];
            data[size] = '\0';
        }
        data = nullptr;
    } 


    MyString(MyString& other) : MyString(other.size - 1) {
        for (size_t i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        data[size] = '\0';
        
    }

    MyString& operator=(const MyString& other){
        if(this != &other){
        size = other.size;
        delete[] data;
        data = new char[size];
        for (size_t i = 0; i < size; i++)
        {
             data[i] = other.data[i];
        }
    }
        return *this;
    }

    bool operator>(const MyString& other){
        
        for (size_t i = 0; i < (size > other.size ? other.size : size) ; i++)
        {
            if (data[i] > other.data[i])
                return true;    
        }

        return false;
    }
    
    bool operator<(const MyString& other){
        
        for (size_t i = 0; i < (size > other.size ?  other.size : size) ; i++)
        {
            if (data[i] < other.data[i])
                return true;    
        }

        return false;
    }

    bool operator>=(const MyString& other){
        
        for (size_t i = 0; i < (size > other.size ? other.size : size) ; i++)
        {
            if (data[i] >= other.data[i])
                return true;    
        }

        return false;
    }

    bool operator<=(const MyString& other){
        
        for (size_t i = 0; i < (size > other.size ? other.size : size) ; i++)
        {
            if (data[i] <= other.data[i])
                return true;    
        }

        return false;
    }

    bool operator!=(const MyString& other){
        
        for (size_t i = 0; i < (size > other.size ? other.size : size) ; i++)
        {
            if (data[i] = other.data[i])
                return false;    
        }

        return true;
    }
};