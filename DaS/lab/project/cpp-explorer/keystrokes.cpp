#include <iostream>
#include <conio.h>
#include <windows.h>
 
int main() {
    char ch;
    int flag = 1;
 
    while (flag) {
        if(GetKeyState(VK_RSHIFT) & 0x8000) {
            std::cout << "Right Shift key pressed" << std::endl;
            flag = 0;
        }
        if(GetKeyState(VK_LEFT) & 0x8000) {
            std::cout << " <- ";
        }
        if(GetKeyState(VK_RIGHT) & 0x8000) {
            std::cout << " -> ";
        }
        if(GetKeyState(VK_DOWN) & 0x8000) {
            std::cout << "|";
            
        }
        if(GetKeyState(VK_UP) & 0x8000) {
            std::cout << "^";
            
        }

    }
 
    return 0;
}