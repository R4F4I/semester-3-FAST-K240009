/*

You're developing a program to manage a seating chart for a conference held in a hall with
multiple rows of seats. Each row has a different seat capacity. To efficiently handle the seating
arrangements, you decide to use a dynamic array. Implement a C++ code that allocates memory
for the seating chart and allows attendees' names to be inputted for each seat. Choose and
implement the appropriate type of dynamic array for this scenario.

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

    int rows;
    cout << "Enter the number of rows in the hall: ";
    cin >> rows;

    // Create a dynamic array of dynamicList objects (jagged array for seats)
    dynamicList* seatingChart = new dynamicList[rows];

    for (int i = 0; i < rows; ++i) {
        int seats;
        cout << "Enter the number of seats for row " << i + 1 << ": ";
        cin >> seats;

        cout << "Enter names for seats in row " << i + 1 << ":" << endl;
        for (int j = 0; j < seats; ++j) {
            float name;
            cout << "Seat(float) " << j + 1 << ": ";
            cin >> name;
            // Assuming names are  float
            seatingChart[i].addVal(name); 
        }
    }

    cout << "\n--- Seating Chart ---" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "Row " << i + 1 << ": ";
        seatingChart[i].print(); // This will print dummy float values
    }

    // Deallocate memory
    delete[] seatingChart;


    return 0;
}