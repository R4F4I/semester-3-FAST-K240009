/*

A university is managing the marks of students in multiple subjects. Each department has a
different number of students. Each student has marks for a fixed number of 5 subjects.
You need to store this data in a appropriate dynamic array where rows = number of departments
and columns = number of students in each department. Then, calculate the highest, lowest and
average marks of each department and display them.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

class dynamicList{
public:
    float *list ;
    int length; // size of array
    
    
    void allocateSpace(){
        float *newArr = new float[length+5];
        for (size_t i = 0; i < length; i++)
        {
            newArr[i] = list[i];
        }
        length+=5;
        delete[] list;
        list = newArr;

        // assign null values to the new arr
        for (size_t i = length; i < length+5; i++)
        {
            list[i]=-1;
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
        if (length - population<3){
            // allocate memory to the marks array
            allocateSpace();
        }
        
        list[population] = score;
        population++;

        getSum();
    }

    
    void getSum(){
        checkPop();
        sum = 0;
        for (size_t i = 0; i < population; i++)
        {
            sum+=list[i];
        }
        // std::cout << "sum: " <<sum<< std::endl;
    }

    void average(){
        std::cout << "average: " <<sum/population<< std::endl;

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


class Department {
public:
    dynamicList* studentsMarks;
    int numStudents;

    Department(int students) : numStudents(students) {
        studentsMarks = new dynamicList[numStudents];
    }

    ~Department() {
        delete[] studentsMarks;
    }

    void calculateStats() {
        float totalDepartmentMarks = 0;
        float highestMark = 0;
        float lowestMark = 1000000; // Assuming marks are less than this
        int totalSubjectsCount = 0;

        for (int i = 0; i < numStudents; ++i) {
            studentsMarks[i].getSum(); // Ensure sum is updated
            totalDepartmentMarks += studentsMarks[i].sum;
            totalSubjectsCount += studentsMarks[i].population;

            // Find highest and lowest marks within this student's subjects
            for (int j = 0; j < studentsMarks[i].population; ++j) {
                if (studentsMarks[i].list[j] > highestMark) {
                    highestMark = studentsMarks[i].list[j];
                }
                if (studentsMarks[i].list[j] < lowestMark) {
                    lowestMark = studentsMarks[i].list[j];
                }
            }
        }

        cout << "  Highest Mark: " << highestMark << endl;
        cout << "  Lowest Mark: " << lowestMark << endl;
        if (totalSubjectsCount > 0) {
            cout << "  Average Mark: " << totalDepartmentMarks / totalSubjectsCount << endl;
        } else {
            cout << "  No marks to calculate average." << endl;
        }
    }
};



int main(){

    // Create departments with varying numbers of students
    Department dept1(2); // Department 1 has 2 students
    Department dept2(3); // Department 2 has 3 students
    Department dept3(1); // Department 3 has 1 student

    // Populate marks for Departments
    for (size_t i = 0; i < 2; i++)
    {
        cout << "Populating marks for Department 1, Student "<<i<< ":" << endl;
        for (size_t j = 0; j < 5; j++)
        {
            dept1.studentsMarks[i].addVal(rand() % 100 + 1);
        }
        dept1.studentsMarks[i].print();
    }
    
    
    for (size_t i = 0; i < 3; i++)
    {
        cout << "Populating marks for Department 2, Student "<<i<< ":" << endl;
        for (size_t j = 0; j < 5; j++)
        {
            dept2.studentsMarks[i].addVal(rand() % 100 + 1);
        }
        dept2.studentsMarks[i].print();
    }
    
    for (size_t i = 0; i < 1; i++)
    {
        cout << "Populating marks for Department 2, Student "<<i<< ":" << endl;
        for (size_t j = 0; j < 5; j++)
        {
            dept3.studentsMarks[i].addVal(rand() % 100 + 1);
        }
        dept3.studentsMarks[i].print();
    }


    cout << "\n--- Department Statistics ---" << endl;

    cout << "Department 1:" << endl;
    dept1.calculateStats();

    cout << "\nDepartment 2:" << endl;
    dept2.calculateStats();

    cout << "\nDepartment 3:" << endl;
    dept3.calculateStats();


    return 0;
}