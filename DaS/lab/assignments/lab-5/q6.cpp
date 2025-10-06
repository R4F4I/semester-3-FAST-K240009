/*

Write a C++ function int recursiveArraySum(int* arr[], int sizes[], int dim) that calculates the sum of
all elements in a multi-dimensional array represented by a jagged array. The function should work for
arrays containing nested arrays, and sizes is an array that contains the sizes of each dimension, and
dim is the current dimension being processed.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;




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

    void sumOfAllVal(){

        for (size_t i = 0; i < population; i++){
            sum+=list[i];
        }
        
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




// dim is the num of elements in outer arr
int recursiveArraySum(int* arr[], int sizes[], int dim){

    int sum  =0;

    if (dim<0)
    {
        return sum;
    }
    

    for (size_t i = 0; i < sizes[dim]; i++)
    {
        sum+=arr[dim][i];
    }
    return sum + recursiveArraySum(arr,sizes,dim-1);

}


int main(){

    int NUM_ROWS = 3;

    int** jaggedArray = new int*[NUM_ROWS];
    
    int sizes[] = {3,2,6};
    
    jaggedArray[0] = new int[sizes[0]];
    jaggedArray[1] = new int[sizes[1]];
    jaggedArray[2] = new int[sizes[2]];
    
    


     // 2. Populate the first inner array (Row 0)
    jaggedArray[0][0] = 10;
    jaggedArray[0][1] = 20;
    jaggedArray[0][2] = 30;

    // 3. Populate the second inner array (Row 1 - which is shorter)
    jaggedArray[1][0] =  5;
    jaggedArray[1][1] =  5;
    
    // 4. Populate the third inner array (Row 2 - which forces a resize)
    jaggedArray[2][0] = 1;
    jaggedArray[2][1] = 2;
    jaggedArray[2][2] = 3;
    jaggedArray[2][3] = 4;
    jaggedArray[2][4] = 5; // Fills initial capacity (5)
    jaggedArray[2][5] = 6; // Triggers allocateSpace (resizes to 6)


    std::cout << "/* message */" << std::endl;
    

    std::cout << recursiveArraySum(jaggedArray, sizes, 2) << std::endl;
    std::cout << "/* message */" << std::endl;



    return 0;
}