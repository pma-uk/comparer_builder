/*
* Filename:		main.cpp
* Project:		ComparerBuilder
* By:			Paul Ma
* Date:			August 13, 2024
* Description:  This source file contains an example usage of the `comparer_builder` utility class to sort a vector of `MyStruct` objects
*               based on various member variables and functions.
*/

#include <iostream>
#include <vector>
#include "comparer_builder.hpp"


// Example structure
struct MyStruct 
{
private:
    int x2;
    std::string x3;   

public:
    int x1;
    MyStruct(int x1, int x2, const std::string& x3) : x1(x1), x2(x2), x3(x3) {} // Constructor to initialize (private) members 

    // Getters
    int get_x2() const { return x2; }
    const std::string& get_x3() const { return x3; }
};


// For printing MyStruct
void printMyStruct(const MyStruct& myStruct)
{
    std::cout << "x1: " << myStruct.x1 << " x2: " << myStruct.get_x2() << " x3: " << myStruct.get_x3() << "\n";
}


int main() 
{
    std::vector<MyStruct> v = 
    {
        {1, 3, "b"},
        {3, 2, "c"},
        {2, 2, "a"},
        {1, 1, "c"}
    };

    std::cout << "Original ordering:" << std::endl;
    for (const MyStruct& item : v) 
    {
        printMyStruct(item);
    }


    std::sort(v.begin(), v.end(), comparer_builder<MyStruct>().by(&MyStruct::x1).by(&MyStruct::get_x2).build());

    std::cout << "\nSorting by x1, then by x2" << std::endl;
    for (const MyStruct& item : v) 
    {
        printMyStruct(item);
    }

    std::sort(v.begin(), v.end(), comparer_builder<MyStruct>().by(&MyStruct::get_x3).by(&MyStruct::get_x2).build());

    std::cout << "\nSorting by x3, then by x2" << std::endl;
    for (const MyStruct& item : v) 
    {
        printMyStruct(item);
    }

    std::sort(v.begin(), v.end(), comparer_builder<MyStruct>().by(&MyStruct::get_x3, true).by(&MyStruct::get_x2).build());

    std::cout << "\nSorting by x3 in descending order, then by x2 in ascending order" << std::endl;
    for (const MyStruct& item : v) 
    {
        printMyStruct(item);
    }

    std::sort(v.begin(), v.end(), comparer_builder<MyStruct>().by(&MyStruct::get_x2, true).by(&MyStruct::x1, true).build());

    std::cout << "\nSorting by x2, then by x1, both in descending order" << std::endl;
    for (const MyStruct& item : v) 
    {
        printMyStruct(item);
    }

    return 0;
}