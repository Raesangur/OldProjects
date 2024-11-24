// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and
// ends there.
//

#include <algorithm>
#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <variant>

int
main()
{
    using list_t = std::list<char>;

    std::list<std::variant<char, list_t>> lst{
      'W', 'o', 'r', 'l', 'd', list_t{'H', 'e', 'l', 'l', 'o'}};

    auto lambda = [&]() {
        for(const auto& x : lst)
        {
            if(std::holds_alternative<list_t>(x))
            {
                const auto& list = std::get<list_t>(x);
                return std::pair{list.cbegin(), list.cend()};
            }
        }
    };

    auto [beginIt, endIt] = lambda();
    std::cout << std::string{beginIt, endIt} << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add
//   existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln
//   file
