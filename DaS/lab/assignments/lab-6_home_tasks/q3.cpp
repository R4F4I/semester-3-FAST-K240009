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
#include <stack>

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

// // only the operators will be pushed int
// string convert_infix_to_postfix(string expr){

//     // for a+b*c, we will only get
//     //     abc*+, due to precedence, (), ^, /, *,+,-

//     // use 2 stacks, one to output and one for operators
//     Stack oPStack;
//     string outStr;

//     char Char;
//     for (size_t i = 0; i < expr.length(); i++)
//     {
//         std::cout << "e" << std::endl;
//         Char = expr[i];

//         std::cout << "prec " <<outStr<< std::endl;
        

//         if (!isOp(Char))
//         {
//             outStr +=Char;
//         }
//         else if (Char=='(')
//         {
//             oPStack.push(Char);
//         }
//         else if (Char==')')
//         {
//             while (!oPStack.isEmpty() && oPStack.top() != '(')
//             {
//                 outStr += oPStack.pop();
//             }
//             if (oPStack.isEmpty())
//             {
//                 return "Error";
//             }
            
            
//             oPStack.pop();
            
//         }

        

//         else{
//             while (!oPStack.isEmpty() && oPStack.top() != '(')
//             {
//                 char topOp = oPStack.top();
//                 int currPrec = prec(Char);


//                 if (
//                     prec(oPStack.top() > prec(Char)) ||
//                     prec(oPStack.top() == prec(Char))

//                 )
//                 {
//                     outStr += oPStack.pop();
//                 } else {
//                     break;
//                 }
                
//             }
//             oPStack.push(Char);
            
//         }

//         // after pushing check the precedences in oPstack, if the top val has precedence than one below, pop it, and concatenate, in the new str

//     }

//     while (!oPStack.isEmpty())
//     {
//         if (oPStack.top() == '(')
//         {
//             return "Error";
//         }
//         outStr += oPStack.pop();
//     }
    


//     oPStack.print();    
    
    
//     return outStr;


// }


// first cycle through the entire string using for loop
// this will create a new string with all the var, and a stack with all the opcodes
// then use a while loop to pop all the val in stack into the postfix string
string convert_infix_to_postfix(string expr){

    string resString;
    Stack opStack;


    for (size_t i = 0; i < expr.length(); i++)
    {
        // if ( ) are found, extract the text b/w them and perform a recursive function on that string

        // if (expr[i]=='(')
        // {
        //     i++;
        //     string encapExpr="";
        //     while (expr[i]!=')')
        //     {
        //         encapExpr += expr[i];
        //         i++;
        //         cout<< "encapExpr:" <<encapExpr<<endl;
        //     }
        //     encapExpr = convert_infix_to_postfix(encapExpr);
        //     resString +=encapExpr;
        // }
        


        if (!isOp(expr[i]))
        {
            resString += expr[i];
        } else
        {
            // now we will check if the op to be push has a higher precedence the then the top val in stack, if not then directly concat it in res
            // cout<<prec(opStack.top())<< "-> prec";


            
            
            
            // the new op has a higher prec, stack it, if it has lesser prec, pop the entire stack, into postfix
            if (!opStack.isEmpty() && (prec(expr[i]) <= prec(opStack.top())) )
            {
                while (!opStack.isEmpty())
                {
                    resString += opStack.pop();
                    cout<< "resString: "<<resString<<endl;
                }
                
            }
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
    
    // string check = "a+b*c^d-e^f+g*h-i";
    // a+b*c^d-e^f+g*h-i
    // a+b*cd^-ef^+gh*-i
    // a+bcd^*-ef^+gh*-i
    // abcd^*+ef

   

    // string expr = "a+b*(c^d-e)^(f+g*h)-i";

    // string newExpr = convert_infix_to_postfix(expr);

    // std::cout << newExpr << std::endl;

    string check = "a+b*c^d-e^f+g*h-i";
    cout <<"showing check1 "<<endl;
    check = convert_infix_to_postfix(check);
    cout <<"showing check2 "<<endl;
    std::cout << check << std::endl;


    return 0;
}