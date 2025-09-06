/*

Q3. Create a C++ class Box that uses dynamic memory allocation for an integer. Implement the
Rule of Three by defining a destructor, copy constructor, and copy assignment operator.
Demonstrate the behavior of both shallow and deep copy using test cases.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-2A


*/

#include <iostream>

using namespace std;

class Box
{
private:
    int *data;

public:
    // Constructor
    Box(int val)
    {
        data = new int(val);
    }

    // Destructor
    ~Box()
    {
        delete data;
        data = nullptr;
    }

    // Copy Constructor (shallow copy)
    Box(const Box &other)
    {
        data = other.data;  // shallow copy the data
    }

    // Copy Assignment Operator (Deep Copy)
    Box &operator=(const Box &other)
    {
        if (this != &other)
        {
            delete data;             // Deallocate existing memory
            data = new int(*other.data); // Allocate new memory and copy data
        }
        return *this;
    }

    // Setter
    void setData(int val)
    {
        *data = val;
    }

    // Getter
    int getData() const
    {
        return *data;
    }

    void display() const
    {
        cout << "Data: " << *data << " (Address: " << data << ")" << endl;
    }
};



int main(){

    // Demonstrating Shallow Copy
    cout << "Demonstrating Shallow Copy:" << endl;
    Box box1(10);
    cout << "Box1 (original):" << endl;
    box1.display();

    Box box2(box1); // Shallow copy using copy constructor
    cout << "Box2 (shallow copy of Box1):" << endl;
    box2.display();

    box2.setData(20); // Modifying box2's data
    cout << "Box2 (after modification):" << endl;
    box2.display();
    cout << "Box1 (after Box2 modification - shows shallow copy issue):" << endl;
    box1.display();

    cout << "\n----------------------------------------\n";

    // Demonstrating Deep Copy using Copy Assignment Operator
    cout << "Demonstrating Deep Copy (using copy assignment operator):" << endl;
    Box box3(30);
    cout << "Box3 (original):" << endl;
    box3.display();

    Box box4(0); // Create a new box to assign to
    box4 = box3; // Deep copy using copy assignment operator
    cout << "Box4 (deep copy of Box3):" << endl;
    box4.display();

    box4.setData(40); // Modifying box4's data
    cout << "Box4 (after modification):" << endl;
    box4.display();
    cout << "Box3 (after Box4 modification - shows deep copy behavior):" << endl;
    box3.display();
    

    return 0;
}