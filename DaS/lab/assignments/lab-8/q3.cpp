/*  

Question#3
Create the BST which stores the students object in BST and student object has the
property like name, roll and score. Create tree based on name of student AND Perform
following operations in BST:
 Insert the student record,
 Search the students based on name
 Delete the students whose score is less than 10
 And get the students whose score is max in tree.
In main function create the object array of students with 10 students from those store 7
seven students randomly and perform all above objects.

*/
#include <iostream>

using namespace std;

// Student structure (Data payload)
struct Student
{
    const char *name;
    int roll;
    int score;
};

// Node structure (stores data and pointers)
struct Node
{
    Student student;
    Node *left;
    Node *right;

    Node(const Student &data) : student(data), left(nullptr), right(nullptr) {}
};

// Manual C-style string comparison (since <cstring> is forbidden)
int compareNames(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

class BST
{
public:
    Node *root;

    BST() : root(nullptr) {}

    // 1. Find Minimum Node (for Deletion) - Recursive
    Node *findMin(Node *current)
    {
        if (current == nullptr || current->left == nullptr)
        {
            return current;
        }
        return findMin(current->left);
    }

    // 2. Insert Student Record - Recursive
    Node *insert(Node *current, const Student &data)
    {
        if (current == nullptr)
        {
            return new Node(data);
        }

        int comparison = compareNames(data.name, current->student.name);

        if (comparison < 0)
        {
            current->left = insert(current->left, data);
        }
        else if (comparison > 0)
        {
            current->right = insert(current->right, data);
        }
        return current;
    }

    // 3. Search Student by Name - Recursive
    bool search(Node *current, const char *keyName)
    {
        if (current == nullptr)
        {
            return false;
        }

        int comparison = compareNames(keyName, current->student.name);

        if (comparison == 0)
        {
            cout << "Found: " << current->student.name << ", Roll: " << current->student.roll << ", Score: " << current->student.score << "\n";
            return true;
        }
        if (comparison < 0)
        {
            return search(current->left, keyName);
        }
        else
        {
            return search(current->right, keyName);
        }
    }

    // 4. Delete Student by Name (Helper for deleteLowScore) - Recursive
    Node *remove(Node *current, const char *keyName)
    {
        if (current == nullptr)
        {
            return current;
        }

        int comparison = compareNames(keyName, current->student.name);

        if (comparison < 0)
        {
            current->left = remove(current->left, keyName);
        }
        else if (comparison > 0)
        {
            current->right = remove(current->right, keyName);
        }
        else
        {
            if (current->left == nullptr)
            {
                Node *temp = current->right;
                delete current;
                return temp;
            }
            else if (current->right == nullptr)
            {
                Node *temp = current->left;
                delete current;
                return temp;
            }
            Node *temp = findMin(current->right);
            current->student = temp->student;
            current->right = remove(current->right, temp->student.name);
        }
        return current;
    }

    // 5. Delete Students Whose Score is Less Than 10 - Recursive Traversal
    Node *deleteLowScore(Node *current)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        // Recursively clean up children first (Post-order-like processing)
        current->left = deleteLowScore(current->left);
        current->right = deleteLowScore(current->right);

        // Check the current node
        if (current->student.score < 10)
        {
            cout << "DELETED: " << current->student.name << " (Score: " << current->student.score << " < 10)\n";

            // Perform the standard BST removal logic on the current node
            if (current->left == nullptr)
            {
                Node *temp = current->right;
                delete current;
                return temp;
            }
            else if (current->right == nullptr)
            {
                Node *temp = current->left;
                delete current;
                return temp;
            }
            // Node with two children: swap with successor and recursively remove successor
            Node *temp = findMin(current->right);
            current->student = temp->student;
            current->right = remove(current->right, temp->student.name);
        }
        return current;
    }

    // 6. Get Max Score Student - Recursive Traversal
    Node *findMaxScoreNode(Node *current)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        Node *maxNode = current;

        Node *leftMax = findMaxScoreNode(current->left);
        if (leftMax != nullptr && leftMax->student.score > maxNode->student.score)
        {
            maxNode = leftMax;
        }

        Node *rightMax = findMaxScoreNode(current->right);
        if (rightMax != nullptr && rightMax->student.score > maxNode->student.score)
        {
            maxNode = rightMax;
        }

        return maxNode;
    }

    const Student *getMaxScore(Node *current)
    {
        Node *result = findMaxScoreNode(current);
        return (result != nullptr) ? &(result->student) : nullptr;
    }

    // Traversal for Display
    void inOrder(Node *current)
    {
        if (current != nullptr)
        {
            inOrder(current->left);
            cout << current->student.name << " (R" << current->student.roll << ", S" << current->student.score << ")  ";
            inOrder(current->right);
        }
    }
};

void displayRoster(BST &tree)
{
    cout << "\n--- Current Roster (Alphabetical Order) ---\n";
    tree.inOrder(tree.root);
    cout << "\n";
}

int main()
{
    BST studentTree;

    // Array of 10 students
    Student students[10] = {
        {"Alice", 101, 85},
        {"Bob", 102, 92},
        {"Charlie", 103, 5}, // Low score
        {"David", 104, 78},
        {"Eve", 105, 99},
        {"Fiona", 106, 3}, // Low score
        {"George", 107, 65},
        {"Hannah", 108, 99},
        {"Igor", 109, 10},
        {"Jack", 110, 88}};

    // Inserting 7 students (manually selected for simplicity due to no randomization)
    cout << "Inserting 7 Student Records...\n";
    studentTree.root = studentTree.insert(studentTree.root, students[0]); // Alice
    studentTree.root = studentTree.insert(studentTree.root, students[1]); // Bob
    studentTree.root = studentTree.insert(studentTree.root, students[2]); // Charlie (low)
    studentTree.root = studentTree.insert(studentTree.root, students[4]); // Eve (max)
    studentTree.root = studentTree.insert(studentTree.root, students[5]); // Fiona (low)
    studentTree.root = studentTree.insert(studentTree.root, students[8]); // Igor (boundary)
    studentTree.root = studentTree.insert(studentTree.root, students[9]); // Jack

    displayRoster(studentTree);

    // Operation 1: Search the students based on name
    cout << "\n--- SEARCH Operation ---\n";
    studentTree.search(studentTree.root, "Eve");
    studentTree.search(studentTree.root, "Zoe"); // Should not be found

    // Operation 2: Delete the students whose score is less than 10
    cout << "\n--- DELETE LOW SCORE Operation (Score < 10) ---\n";
    studentTree.root = studentTree.deleteLowScore(studentTree.root);
    displayRoster(studentTree);

    // Operation 3: Get the students whose score is max in tree
    cout << "\n--- GET MAX SCORE Operation ---\n";
    const Student *maxStudent = studentTree.getMaxScore(studentTree.root);
    if (maxStudent != nullptr)
    {
        cout << "Max Score Student: " << maxStudent->name << ", Score: " << maxStudent->score << "\n";
    }

    return 0;
}
