/*

Task 3: You are developing a calculator application in C++ that needs to handle arithmetic expressions
entered by the user. The expressions can include the basic arithmetic operators (+, -, *, /) as well as
parentheses to group operations. How would you convert the infix expression a+b*(c^d-e)^(f+g*h)-i
to postfix notation.
Use the class of stack created in Task 01 ( Lab Tasks).

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

class Node{

public:
    char data;
    Node* next = nullptr;

    Node(char data){
        this->data = data;
        next = nullptr;
    }

 };

class Stack{

public:
    Node *head;
    Stack(){
        head =nullptr;
    }
    
    bool isEmpty(){
        return (head==nullptr);
    }

    
    // will add data from head, head points to top val now
    void push(char data){
        Node* newNode = new Node(data);
        if (head==nullptr)
        {
            head = newNode;
            return;
        }
        newNode->next=head;
        head = newNode;
        


    }

    char top(){
        if (head!=nullptr)
        {
            /* code */
            return head->data;
        }
        return '-'; // assume a least precedent if the stack is empty
        
    }

    char pop(){
        
        if (head == nullptr)
        {
            return 0;
        }
        
        
        char val = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    void print(){
        Node* temp = head;
        while (temp!=nullptr)
        {
            std::cout << temp->data <<" ";
            temp = temp->next;
        }
        cout << endl << endl;

    }

};

bool isOp(char c){
    if (
        c=='('||
        c==')'||
        c=='^'||
        c=='/'||
        c=='*'||
        c=='-'||
        c=='+'
    )
    {
        return true;
    }
    return false;
}

int prec(char c){
    if(c=='^'){
        return 3;
    }
    if(c=='/'|| c=='*'){
        return 2;
    }
    if(c=='-'||c=='+'){
        return 1;
    }
    return -1;
}


// https://www.calcont.in/Conversion/infix_to_postfix

// first cycle through the entire string using for loop
// this will create a new string with all the var, and a stack with all the opcodes
// then use a while loop to pop all the val in stack into the postfix string
string convert_infix_to_postfix(string expr){

    string resString;
    Stack opStack;

    // 1. cycle through the expression
    for (size_t i = 0; i < expr.length(); i++)
    {
        // if (  is found, then perform the push it in stack, any operator before ) is pushed, if any operator that is of lower precedence is to be pushed, then perform the standard dump UNTIL ( IS REACHED DO NOT EMPTY IT ANY FURTHER

        // 1.1 push () into the stack as they are operators
        if (expr[i] == '(') {
            opStack.push(expr[i]);
        }
        
        // 1.2 if ) is found the dump all operators before (
        else if (expr[i] == ')') {
            
            
            while (!opStack.isEmpty() && opStack.top() != '(') {
                resString += opStack.pop();
            }
            // Pop and discard the opening parenthesis '('
            if (!opStack.isEmpty()) {
                opStack.pop(); 
            }
        }
        

        // 1.3 if not an operator simply pass it through ... into the resultant expression
        else if (!isOp(expr[i]))
        {
            resString += expr[i];
        } 
        else
        {
            // 1.4 while being pushed, if the new operator has a lower precedence, then dump the stack into the reString, then push the new operator

            // the new op has a higher prec, stack it, if it has lesser prec, pop (dump) the entire stack, into postfix, 
            if (!opStack.isEmpty() && (prec(expr[i]) <= prec(opStack.top())) )
            {
                // 1.5 the stack will only be emptied until the top val is (, ( will only be cleared by a )
                while (!opStack.isEmpty() 
                && opStack.top()!='('
            )
                {
                    // std::cout << "top: ";
                    // opStack.print();
                    resString += opStack.pop();
                }
            }
            // the lower precedent operator being pushed into stack after the stack is emptied
            opStack.push(expr[i]);
            
        }
    }
    
    

    
    // after that is done, pop all val from stack
    char temp;
    while (!opStack.isEmpty())
    {
        opStack.print();

        
        temp = opStack.pop();
        
        
        
        // if temp is ) leave it
        if (temp!=')')
        {
            resString += temp;
            std::cout << "expr " << resString<<endl;
        }
        

    }

    return resString;

}


int main(){

    // convert this:
    // a+b*(c^d-e)^(f+g*h)-i
    // to
    //      a+b*(cd^e-)^(fgh*+)-i
    //      a+b*cd^e-fgh*+^-i
    //      a+bcd^e-fgh*+^*-i
    //      abcd^e-fgh*+^*+-i
    // abcd^e-fgh*+^*+i-
    
    

   

    string expr = "a+b*(c^d-e)^(f+g*h)-i";
    cout <<expr<<endl;

    string newExpr = convert_infix_to_postfix(expr);
    
    cout << newExpr << endl;


    return 0;
}