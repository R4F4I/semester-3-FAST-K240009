/*

Task 1: Implement and insert the values “BORROWROB” in the stack and identify if it’s a palindrome
or not. Use the push and pop functions to accomplish this (Note: Use Arrays to accomplish this)

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <string> // Required for using the string data type

using namespace std;

// Define the maximum size of the stack
#define MAX_SIZE 100

// Global declarations for the stack
char stack[MAX_SIZE];
int top = -1; // Initialize top of the stack to -1 (empty)

// Function to check if the stack is full
bool isFull() {
    return top == MAX_SIZE - 1;
}

// Function to check if the stack is empty
bool isEmpty() {
    return top == -1;
}

// Function to push an element onto the stack
void push(char value) {
    if (isFull()) {
        cout << "Stack Overflow! Cannot push value." << endl;
    } else {
        top++;
        stack[top] = value;
    }
}

// Function to pop an element from the stack
char pop() {
    if (isEmpty()) {
        cout << "Stack Underflow! Cannot pop value." << endl;
        return '\0'; // Return null character to indicate an error/empty stack
    } else {
        char value = stack[top];
        top--;
        return value;
    }
}

/**
 * @brief Checks if a given string is a palindrome using a stack.
 *
 * @param inputString The string to be checked.
 * @return true if the string is a palindrome, false otherwise.
 */
bool isPalindrome(string inputString) {
    // Reset the stack for the new operation
    top = -1;

    // Check if the input string can fit into our stack
    if (inputString.length() > MAX_SIZE) {
        cout << "Error: String length exceeds stack capacity." << endl;
        return false;
    }

    // 1. Push each character of the string onto the stack
    for (int i = 0; i < inputString.length(); i++) {
        push(inputString[i]);
    }

    string reversedString = "";
    // 2. Pop each character from the stack to build the reversed string
    while (!isEmpty()) {
        reversedString += pop();
    }

    // 3. Compare the original string with the reversed string and return the result
    return inputString == reversedString;
}


int main() {
    string testString1 = "BORROWROB";
    cout << "Checking string: " << testString1 << endl;

    if (isPalindrome(testString1)) {
        cout << "Result: The string is a palindrome." << endl;
    } else {
        cout << "Result: The string is not a palindrome." << endl;
    }


    string testString2 = "RAFAY";
    cout << "Checking string:" << testString2 << endl;

    if (isPalindrome(testString2)){
        cout << "Result: The string is a palindrome." << endl;
    } else {
        cout << "Result: The string is not a palindrome." << endl;
    }

    return 0;
}