/*

You are tasked with developing a program to manage and display the Grade Point Average
(GPA) for the core courses offered in the first semester of four departments: Software
Engineering (SE), Artificial Intelligence (AI), Computer Science (CS), and Data Science (DS).
Each department offers a distinct number of core courses for this semester: SE has 3 core
courses, AI has 4 core courses, CS has 2 core courses, and DS has 1 core course. To efficiently
store and present this data, which type of array structure would you employ? implement a
solution using the chosen array structure to display the GPAs of the core courses for each
department.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

/* 

SE: 3
AI: 4
CS: 2
DS: 1

jagged array could be used above

*/


class dynamicList{
    float *list ;
    int length; // size of array
    
    // will only allocate 1 extra space to keep it space efficient
    void allocateSpace(){
        float *newArr = new float[length+1];
        for (size_t i = 0; i < length; i++)
        {
            newArr[i] = list[i];
        }
        length+=1;
        delete[] list;
        list = newArr;

        // assign null values to the new arr
        for (size_t i = length; i < length+1; i++)
        {
            list[i]=0;
        }
        
    }

    void checkPop(){
        population = 0;
        for (size_t i = 0; i < length; i++)
        {
            if (list[i]!=0)
                population++;
        }
        
    }

public:
    float sum;
    int population; // num of members / non empty blocks
    dynamicList(){
        list = new float[5];

        for (size_t i = 0; i < 5; i++){
            list[i] = 0;
        }
        length = 5;
        population = 0;
        
    }

    dynamicList(float val){
        dynamicList();
        list[0] = val;
    }

    void addVal(float score){
        checkPop();
        if (length - population<1){
            // allocate memory to the marks array
            allocateSpace();
        }
        
        list[population] = score;
        population++;
    }



    void print(){
        checkPop();
        for (size_t i = 0; i < population; i++)
        {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }

};



int main(){

    // for the individual dynamic arrays, we will use the prev defined class

    dynamicList arr[4]; 

    arr[0].addVal(1);
    arr[0].addVal(2);
    arr[0].addVal(3);
    
    arr[1].addVal(4);
    arr[1].addVal(5);
    arr[1].addVal(6);
    arr[1].addVal(7);
    
    arr[2].addVal(8);
    arr[2].addVal(9);
    
    arr[3].addVal(10);
    
    

    for (int i = 0; i < 4; i++)
    {
        arr[i].print();
    }
    





    
    
    





    return 0;
}