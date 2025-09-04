// #include <stdio.h>
#include <iostream>

using namespace std;

void swap(int &a, int &b){
    int *temp;

    *temp = a;
    a = b;
    b = *temp;
}

int main(){
    int a = 10, b = 2;
    swap(a,b);
    cout << a << "\n" << endl;
    cout << b << "\n" << endl;

}