#include <iostream>

using namespace std;


int main(){

    // \033[42m
    for (size_t i = 0; i < 100; i++)
    {
        std::cout <<i <<": ";
        std::cout << "\033[" <<i<<"m";
        std::cout << "hello everyone";
        std::cout << "\033[0m"<<endl;
    }
    // std::cout << "\033[" <<7<<"m";
    // std::cout << "hello everyone" << std::endl;
    // std::cout << "\033[0m"<<endl;



    return 0;
}