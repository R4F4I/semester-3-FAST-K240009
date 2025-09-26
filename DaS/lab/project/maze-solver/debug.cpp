#include <iostream>

// Platform-specific includes and setup
#ifdef _WIN32
#include <windows.h>
#endif

// Your original array, now declared as an array of pointers to string literals
// This is often a cleaner way to handle this.
const char* corner[16] = {
    " ", "╶", "╴", "─",
    "╷", "┌", "┐", "┬",
    "╵", "└", "┘", "┴",
    "│", "├", "┤", "┼"
};

int main() {
    // --- Step 1: Configure the console environment ---
    #ifdef _WIN32
    // Set the console code page to UTF-8 on Windows
    SetConsoleOutputCP(CP_UTF8);
    // Optional: Set input code page as well if you need to read UTF-8
    // SetConsoleCP(CP_UTF8);
    #endif

    // --- Step 2: Print the characters ---
    std::cout << "--- Testing Box Drawing Characters ---" << std::endl;

    for (int i = 0; i < 16; ++i) {
        std::cout << "Index " << i << ": " << corner[i] << std::endl;
    }
    
    std::cout << "\n--- Assembled Box ---" << std::endl;
    std::cout << corner[5] << corner[3] << corner[3] << corner[7] << corner[3] << corner[3] << corner[6] << std::endl;
    std::cout << corner[12] << " A" << corner[12] << " B" << corner[12] << std::endl;
    std::cout << corner[13] << corner[3] << corner[3] << corner[15] << corner[3] << corner[3] << corner[14] << std::endl;
    std::cout << corner[12] << " C" << corner[12] << " D" << corner[12] << std::endl;
    std::cout << corner[9] << corner[3] << corner[3] << corner[11] << corner[3] << corner[3] << corner[10] << std::endl;

    return 0;
}