#include "MyString.h"

int main()
{

    MyString s1;                 
    MyString s2 = "Apple";     
    MyString s3 = s2;            
    MyString s4(10);             
    
    s1 = "Banana";             

    std::cout << "s1: " << s1 << '\n';
    std::cout << "s2: " << s2 << '\n';
    std::cout << "s3: " << s3 << '\n';

    std::cout << "\n Compare (" << s2 << " & " << s1 << ") \n";
    std::cout << "!= : " << (s2 != s1) << '\n';
    std::cout << "<  : " << (s2 < s1)  << '\n';
    std::cout << ">  : " << (s2 > s1)  << '\n';
    std::cout << "<= : " << (s2 <= s3) << " (with " << s3 << ")\n";
    std::cout << ">= : " << (s2 >= s3) << " (with " << s3 << ")\n";

    MyString inputStr;
    std::cout << "\nEnter word: ";
    std::cin >> inputStr;
    std::cout << "You are enter: " << inputStr << '\n';

}