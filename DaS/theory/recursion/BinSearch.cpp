/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


int BinSearch(int arr[], int low, int high, int target){
    
    int middle = (low+high)/2;

    if (arr[middle]==target)
        return middle;

    else if (arr[middle]>target)
    {
        // find in the lower half
        return BinSearch(arr,low,middle, target);
    }
    // else find in upper half
    return BinSearch(arr,middle,high, target);

}


int main(){

    int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    std::cout << BinSearch(arr,0,20,7) << std::endl;


    return 0;
}