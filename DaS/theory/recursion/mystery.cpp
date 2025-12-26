#include <iostream>

using namespace std;


int mystery(int n) {
    if (n < 10) {
        return n;
    } else {
        int a = n/10;
        int b = n % 10;
        return mystery(a + b);
    }
}


int main(){

    
    for (size_t i = 1000; i < 1020; i++)
    {
        cout <<i<<": "<< mystery(i)<< endl;
    }
    



    return 0;
}