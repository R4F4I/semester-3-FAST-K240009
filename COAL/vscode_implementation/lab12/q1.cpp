/* 1. Write a program in C++ which takes input from user and contains a
procedure in assembly named ThreeProd that displays the product of
three numeric parameters passed in a function argument.
 */


#include <iostream>

// Declare the external assembly function.
// It uses the standard C calling convention (_cdecl) 
// to ensure the C++ caller is responsible for stack cleanup, 
// which is common when linking C++ with external assembly.
// It takes three 32-bit integers and returns nothing (void),
// as the assembly procedure will handle the display itself.
extern "C" void ThreeProd(int, int, int);

int main() {
    int num1, num2, num3;

    std::cout << "--- Three Product Assembly Calculator ---\n";
    std::cout << "Note: The calculation and output are done entirely in assembly.\n";
    std::cout << "Enter the first integer: ";
    std::cin >> num1;

    std::cout << "Enter the second integer: ";
    std::cin >> num2;

    std::cout << "Enter the third integer: ";
    std::cin >> num3;

    std::cout << "\nCalling ThreeProd assembly procedure...\n";

    // Call the assembly procedure
    ThreeProd(num1, num2, num3);

    std::cout << "\nC++ program finished execution.\n";

    return 0;
}