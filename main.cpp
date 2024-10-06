#include <iostream>
#include "include/Four.hpp"

int main()
{
    std::string first, second;
    std::cin >> first;
    std::cin >> second;
    Four num1(first);
    Four num2(second);
    num1 = std::move(num2);
    num1.print(std::cout);
    return 0;
}