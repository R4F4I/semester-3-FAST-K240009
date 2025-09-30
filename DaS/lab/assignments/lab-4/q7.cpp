/*

From array mentioned below find the following names and their index using binary
search as well as linear search and count the number of steps on each finding element by using
both techniques and analyze which technique is getting more time:
- Aftab
- Rizwan
- Tariq

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

int binSearch(string arr[],string target, int start,int end,int counter){
    int mid = (start+end)/2;

    if (arr[mid]==target)
        return counter; // instead of returning index return the total num of steps

    if (end<start)
    {
        return -1;
    }
    

    if (arr[mid]>target)
        return binSearch(arr,target,start,mid,counter+1);
    if (arr[mid]<target)
        return binSearch(arr,target,mid,end,counter+1);
    
    return -1;
}

int linSearch(string arr[], string target, int end, int count){
    if (arr[count]==target)
        return count;
    if (count==end)
        return -1;
    return linSearch(arr,target,end,count+1);

}




int main(){

    string arr[]={
        "Ahmed",    // 0
        "Ali",      // 1
        "Basit",    // 2
        "Karim",    // 3
        "Rizwan",   // 4
        "Sarwar",   // 5
        "Tariq",    // 6
        "Taufiq",   // 7
        "Yasin",    // 8
        "Zulfiqar"  // 9
    };

    // std::cout << "for Aftab: " <<binSearch(arr,"Aftab",0,9,1)<< std::endl;
    std::cout << "for Rizwan: " <<binSearch(arr,"Rizwan",0,9,1)<< std::endl;
    std::cout << "for Tariq: " <<binSearch(arr,"Tariq",0,9,1)<< std::endl;
    
    std::cout << "for Rizwan: " <<linSearch(arr,"Rizwan",9,0)<< std::endl;
    std::cout << "for Tariq: " <<linSearch(arr,"Tariq",9,0)<< std::endl;



    return 0;
}