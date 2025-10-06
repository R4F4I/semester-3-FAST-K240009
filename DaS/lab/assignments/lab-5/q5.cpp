/*

Task #6 Imagine you are working on a scientific application that involves processing a multi-
dimensional array. You need to implement a function to calculate the sum of all elements in the array,

which may contain nested arrays (creating a multi-dimensional structure using a jagged array).

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


// multi-dimensional -> 2d array


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




int main(){

    const int NUM_ROWS= 3;


    dynamicList* jaggedArray = new dynamicList[NUM_ROWS];


     // 2. Populate the first inner array (Row 0)
    jaggedArray[0].addVal(10.5f);
    jaggedArray[0].addVal(20.0f);
    jaggedArray[0].addVal(30.1f);

    // 3. Populate the second inner array (Row 1 - which is shorter)
    jaggedArray[1].addVal(5.0f);
    jaggedArray[1].addVal(5.5f);
    
    // 4. Populate the third inner array (Row 2 - which forces a resize)
    jaggedArray[2].addVal(1.1f);
    jaggedArray[2].addVal(2.2f);
    jaggedArray[2].addVal(3.3f);
    jaggedArray[2].addVal(4.4f);
    jaggedArray[2].addVal(5.5f); // Fills initial capacity (5)
    jaggedArray[2].addVal(6.6f); // Triggers allocateSpace (resizes to 6)


    // 5. Print and process the Jagged Array
    std::cout << "\nJagged Array Contents:\n";
    for (int i = 0; i < NUM_ROWS; ++i) {
        // Access array elements using standard array notation (jaggedArray[i])
        std::cout << "Row " << i << " (Capacity: " << jaggedArray[i].population << "): ";
        jaggedArray[i].print();
        jaggedArray[i].sumOfAllVal();
        std::cout << " | Sum: " << jaggedArray[i].sum << std::endl;
    }

    std::cout << "\n--- Cleaning up memory ---\n";

    // 6. Clean up: Call delete[] to release the memory of the outer array.
    // This is vital. It also automatically calls the destructor for each dynamicList element.
    delete[] jaggedArray;

    std::cout << "--- Demonstration Complete ---\n";

    return 0;




    return 0;
}