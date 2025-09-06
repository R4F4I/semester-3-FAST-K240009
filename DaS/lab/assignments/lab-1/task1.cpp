/* 

Q1. Suppose you are developing a bank account management system, and you have defined the
BankAccount class with the required constructors. You need to demonstrate the use of these
constructors in various scenarios.
1. Default Constructor Usage: Create a default-initialized BankAccount object named
account1. Print out the balance of account1.
2. Parameterized Constructor Usage: Create a BankAccount object named account2 with
an initial balance of $1000. Print out the balance of account2.
3. Copy Constructor Usage: Using the account2 you created earlier, create a new
BankAccount object named account3 using the copy constructor. Deduct $200 from
account3 and print out its balance. Also, print out the balance of account2 to ensure it
hasn't been affected by the transaction involving account3.

Name:   Rafay Siddiqui
Class:  BAI-3A
Roll:   24K-0009


*/


#include <iostream>

using namespace std;

class BankAccount{

    float balance;


public:


    BankAccount(){
        balance = 100;
    }

    BankAccount(float balance){
        this->balance = balance;
    }

    BankAccount(BankAccount &other){
        this->balance = other.balance;
    }

    void add(float val){
        this->balance += val;
    }
    
    void sub(float val){
        this->balance -= val;

    }

    void printBal(){
        cout << this->balance << endl;
    }
};

int main(){
 
    BankAccount account1;
    cout << "Account 1 Balance: ";
    account1.printBal();

    BankAccount account2(1000);
    cout << "Account 2 Balance: ";
    account2.printBal();

    BankAccount account3(account2);
    account3.sub(200);
    cout << "Account 3 Balance after deduction: ";
    account3.printBal();
    cout << "Account 2 Balance (should be unaffected): ";
    account2.printBal();
    

}