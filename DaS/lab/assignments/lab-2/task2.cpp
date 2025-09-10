/*

Task#2
A school has conducted exams for 5 students in 4 subjects.
You are required to:
- Use a appropriate dynamic array to store marks.
- Calculate and display:
- Total marks of each student.
- Average marks of each subject.
- The topper student (highest total marks).

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;
class dynamicList{
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
        std::cout << "sum: " <<sum<< std::endl;
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



class student{

public:
    dynamicList math, cs, phy, chem;


};


int main(){

    student s1;

    s1.math.addVal(2);
    s1.math.addVal(3);
    s1.math.addVal(4);
    s1.math.addVal(5);
    s1.math.addVal(5);
    s1.cs.addVal(2);
    s1.phy.addVal(2);
    s1.chem.addVal(2);

    // add for 4 more students
    student s2;
    s2.math.addVal(10);
    s2.math.addVal(12);
    s2.math.addVal(14);
    s2.cs.addVal(11);
    s2.phy.addVal(13);
    s2.chem.addVal(15);

    student s3;
    s3.math.addVal(20);
    s3.math.addVal(22);
    s3.math.addVal(24);
    s3.cs.addVal(21);
    s3.phy.addVal(23);
    s3.chem.addVal(25);

    student s4;
    s4.math.addVal(30);
    s4.math.addVal(32);
    s4.math.addVal(34);
    s4.cs.addVal(31);
    s4.phy.addVal(33);
    s4.chem.addVal(35);

    student s5;
    s5.math.addVal(40);
    s5.math.addVal(42);
    s5.math.addVal(44);
    s5.cs.addVal(41);
    s5.phy.addVal(43);
    s5.chem.addVal(45);

    student students[5] = {s1, s2, s3, s4, s5};

    // Calculate and display total marks of each student
    cout << "Total marks of each student:" << endl;
    float studentTotals[5];
    for (int i = 0; i < 5; ++i) {
        students[i].math.getSum();
        students[i].cs.getSum();
        students[i].phy.getSum();
        students[i].chem.getSum();
        studentTotals[i] = students[i].math.sum + students[i].cs.sum + students[i].phy.sum + students[i].chem.sum;
        cout << "Student " << i + 1 << ": "<< studentTotals[i] << endl;
    }

    // Calculate and display average marks of each subject
    cout << "\nAverage marks of each subject:" << endl;
    float totalMath = 0, totalCS = 0, totalPhy = 0, totalChem = 0;
    int countMath = 0, countCS = 0, countPhy = 0, countChem = 0;

    for (int i = 0; i < 5; ++i) {
        totalMath += students[i].math.sum;
        countMath += students[i].math.population;
        totalCS += students[i].cs.sum;
        countCS += students[i].cs.population;
        totalPhy += students[i].phy.sum;
        countPhy += students[i].phy.population;
        totalChem += students[i].chem.sum;
        countChem += students[i].chem.population;
    }

    cout << "Math: " << totalMath / countMath << endl;
    cout << "CS: " << totalCS / countCS << endl;
    cout << "Physics: " << totalPhy / countPhy << endl;
    cout << "Chemistry: " << totalChem / countChem << endl;

    // Find the topper student
    int topperIndex = 0;
    float maxMarks = studentTotals[0];
    for (int i = 1; i < 5; ++i) {
        if (studentTotals[i] > maxMarks) {
            maxMarks = studentTotals[i];
            topperIndex = i;
        }
    }
    cout << "\nTopper student: Student " << topperIndex + 1 << " with total marks: " << maxMarks << endl;
      ;

    return 0;
}