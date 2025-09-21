/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// in a grid of 3x3, we will check all the possible paths to move, if a path reaches the end successfully it cant be counted as a "path", we se visualize it as a sum
// we can only move down(i+1) and right(j+1)
int count(int i , int j, int m, int n){

    if (i == m && j==n)
    {
        return 1;
    }
    // we will have add a clause of invalid paths

    if (i>n ||j>m)
    {
        return 0;
    }
    
    
    return count(i+1,j,m,n)+count(i,j+1,m,n);

}


int main(){

    // for a 3x3 we will use 0-indexing
    std::cout << "paths: " << count(0,0,2,2)<< std::endl;


    return 0;
}