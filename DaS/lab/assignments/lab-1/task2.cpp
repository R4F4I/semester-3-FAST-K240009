/*

Q2. Create a C++ class named "Exam" using DMA designed to manage student exam records,
complete with a shallow copy implementation? Define attributes such as student name, exam
date, and score within the class, and include methods to set these attributes and display exam
details. As part of this exercise, intentionally omit the implementation of the copy constructor 
and copy assignment operator. Afterward, create an instance of the "Exam" class, generate a
shallow copy, and observe any resulting issues?

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

class Exam
{
private:

    // string name, exam, date;
    // create the above attributes using DMA
    string *name, *exam, *date;
    int score;
public:
    Exam(string name, string exam, string date, int score){
        // set the attributes using DMA 
        this->name = new string(name);
        this->exam = new string(exam);
        this->date = new string(date);
        this->score = score;
    }

    // shallow copy constructor
    Exam(const Exam &other){
        // Perform a shallow copy
        this->name = other.name;
        this->exam = other.exam;
        this->date = other.date;
        this->score = other.score;
    }

    
    void set_name(string name) {
        this->name = &name;
    }
    void set_exam(string exam) {
        this->exam = &exam;
    }

    void set_date(string date) {
        this->date = &date;
    }

    void set_score(int score) {
        this->score = score;
    }

    void display(){
        cout << "Name: " << *name << endl;
        cout << "Exam: " << *exam << endl;
        cout << "Date: " << *date << endl;
        cout << "Score: " << score << endl;
    }
};




int main(){

    Exam exam1("Rafay", "DSA", "1/1/2024", 100);
    cout << "Exam 1 (Original):" << endl;
    exam1.display();

    Exam exam2(exam1); // Shallow copy
    cout << "\nExam 2 (Shallow Copy):" << endl;
    exam2.display();

    exam2.set_name("Jane Doe");
    exam2.set_score(85);
    cout << "\nExam 2 (Modified):" << endl;
    exam2.display();

    cout << "\nExam 1 (Original after Exam 2 modification):" << endl;
    exam1.display();
    

    return 0;
}