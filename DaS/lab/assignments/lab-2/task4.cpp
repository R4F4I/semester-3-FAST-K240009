/*

Write a program that creates a 2D array of 5x5 values of type Boolean. Suppose
indices represent people and the value at row i, column j of a 2D array is true just in
case i and j are friends and false otherwise. You can use initializer list to instantiate
and initialize your array to represent the following configuration: (* means “friends”)
i/j |0 1 2 3 4
0   |  *   * *
1   |*   *   *
2   |  *
3   |*       *
4   |* *   *
Write a method to check whether two people have a common friend. For example, in the
example above, 0 and 4 are both friends with 3 (so they have a common friend), whereas 1 and 2
have no common friends.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/


/* 

solution: a method that takes 2 "friends" as arg and returns a bool

there will be a fixed for loop that will run 5 times

for loop will check if both have a star in the same col / row and then returns bool

e.g: 

input 1,4 -> true (both have a star with 0)
input 2,3 -> false (both dont have a star at the same index)



*/


#include <iostream>

using namespace std;


bool checkMutuals(bool arr[][5], int f1,int f2){

    for (int i = 0; i < 5; i++)
    {
        if (arr[f1][i] == true && arr[f2][i] == true)
        {
            return true;
        }
    }
    return false;
    

}



int main(){

    bool array[5][5] = {
        {false, true , false, true , true},
        {true , false, true , false, true},
        {false, true , false, false, false},
        {true , false, true , false, true},
        {true , true , false, true , false},

    };

    std::cout << checkMutuals(array, 1,4) << std::endl;
    std::cout << checkMutuals(array, 2,3) << std::endl;


    return 0;
}