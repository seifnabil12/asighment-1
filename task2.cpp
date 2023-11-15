#include <iostream>
#include <string>
#include <algorithm>
#include "BigReal.h"

int main() {
    std::string num1Str, num2Str;
    std::cout << "Enter the first number: ";
    std::cin >> num1Str;

    std::cout << "Enter the second number: ";
    std::cin >> num2Str;

    BigReal num1(num1Str);
    BigReal num2(num2Str);

    int choice;
    std::cout << "Choose an operation:\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Subtraction\n";
    std::cout << "3. Greater than\n";
    std::cout << "4. Less than\n";
    std::cout << "5. Equal to\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
        {
            BigReal result = num1 + num2;
            std::cout << "Sum: " << result << std::endl;
            break;
        }
        case 2:
        {
            BigReal result = num1 - num2;
            std::cout << "Difference: " << result << std::endl;
            break;
        }
        case 3:
        {
            bool result = num1 > num2;
            std::cout << "Greater than: " << std::boolalpha << result << std::endl;
            break;
        }
        case 4:
        {
            bool result = num1 < num2;
            std::cout << "Less than: " << std::boolalpha << result << std::endl;
            break;
        }
        case 5:
        {
            bool result = num1 == num2;
            std::cout << "Equal to: " << std::boolalpha << result << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice\n";
            break;
    }

    return 0;
}
