#include <iostream>

// Declare the external assembly function GCD.
// It uses the standard C calling convention (_cdecl).
// It accepts two 32-bit integers and will return nothing (void),
// as the assembly procedure will handle the output.
extern "C" void GCD(int, int);

int main() {
    int num1, num2;

    std::cout << "--- Greatest Common Divisor (GCD) Assembly Calculator ---\n";
    std::cout << "Note: The GCD calculation and final output are done in assembly.\n";
    
    std::cout << "Enter the first positive integer: ";
    if (!(std::cin >> num1)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    std::cout << "Enter the second positive integer: ";
    if (!(std::cin >> num2)) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    // Basic input validation to ensure positive numbers for the algorithm
    if (num1 <= 0 || num2 <= 0) {
        std::cerr << "Please enter positive integers.\n";
        return 1;
    }

    std::cout << "\nCalling GCD assembly procedure...\n";

    // Call the assembly procedure
    GCD(num1, num2);

    std::cout << "\nC++ program finished execution.\n";

    return 0;
}