/*

Task 2: You are required to design a simple Store Transaction Manager for a small shop using a stack
implemented with a linked list in C++. The shopkeeper wants to keep track of all sales and refunds as
transactions, where each transaction is stored as an object containing a unique transaction ID, amount,
description, and a flag value to indicate whether it is a sale or a refund. A sale means the shop sold an
item (money received), so the amount is positive, while a refund means the shop returned money to a
customer, so the amount is negative. The flag is used to represent this: if the amount ≥ 0, set flag = 1
(Sale), and if the amount < 0, set flag = 0 (Refund).
When a new transaction is added (pushed) to the stack, it is given a unique ID starting from 1, and its
description is checked — if it is longer than 20 characters, it should be cut short and “...” added at the
end. Before storing a sale transaction, apply a discount on the amount based on the following rules:
• If the sale amount ≥ 500 PKR → give a 5% discount
• If the sale amount ≥ 1000 PKR → give a 15% discount
• If the sale amount ≥ 1500 PKR → give a 30% discount
This means that the final stored amount must be after the discount has been applied. Refund
transactions are stored as negative amounts and are not discounted.
You are given a predefined list of 7 transactions (an array of objects), where some are sales and some
are refunds. From this list, your program should randomly select transactions and store them in the
stack (implemented with a linked list). When a transaction is removed (popped) from the stack, it
means the shopkeeper has cancelled or reversed it. In that case, the amount should be multiplied by -
1 to change its sign, the description should have " [REVERSED]" added at the end, and the flag should
be updated to indicate it has been reversed.
For example, in the main() function, you can create a stack of transactions and randomly push a few
entries such as:
• Sale of Rs. 1200 → "Sale: Blue Jacket" (after 15% discount = Rs. 1020)
• Sale of Rs. 450 → "Sale: Cotton Socks" (no discount)
• Refund of Rs. -300 → "Refund: Defective Shirt"
• Sale of Rs. 1700 → "Sale: Leather Jacket" (after 30% discount = Rs. 1190)
After adding them, display all transactions in the stack. Then perform infix to postfix conversion and
evaluation for a mathematical expression like (100 + 20) * 0.9 - 5, which should convert to postfix
form 100 20 + 0.9 * 5 - and evaluate to 103.0.

Next, remove (pop) one transaction from the stack — for example, remove the refund transaction.
After popping, this transaction should be shown as reversed, with its amount sign changed and
description updated. Finally, display the remaining transactions still in the stack.
This problem helps you practice how a stack using a linked list works with object manipulation during
push and pop operations, how to apply conditional discounts, and how to convert and evaluate
mathematical expressions using stacks (infix-to-postfix conversion and evaluation).
You can use the rand() function in C++ from the library <cstdlib> (and <ctime> to seed random
numbers).
Example:
#include <cstdlib>
#include <ctime>

// Initialize random seed once in main()
srand(time(0));
// Generate a random value from 0 to 10
int randomIndex = rand() % 10;

Sample Input and outputs
Pushed Transactions:
1. Sale: Blue Jacket (1200) → Discount 15% → Final: 1020.00
2. Sale: Cotton Socks (450) → No discount
3. Sale: Leather Jacket (1700) → Discount 30% → Final: 1190.00
4. Refund: Defective Shirt (-300)

Intermediate Expression Calculation:
Infix: (100 + 20) * 0.9 - 5
Postfix: 100 20 + 0.9 * 5 -
Evaluated Result: 103.00

Pop (remove) one transaction:
Popped Transaction: Refund: Defective Shirt [REVERSED]
Amount changed from -300 to +300
Flag updated to 2
Final Stack Output:
Top → [id=3, amt=1190.00, desc="Sale: Leather Jacket", flag=1]
[id=2, amt=450.00, desc="Sale: Cotton Socks", flag=1]
Bottom → [id=1, amt=1020.00, desc="Sale: Blue Jacket", flag=1]

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// HELPER FUNCTIONS (to replace cctype)

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}


// 1. DATA STRUCTURES & STACK IMPLEMENTATIONS


// --- Transaction Stack ---
struct Transaction {
    int transactionID;
    double amount;
    string description;
    int flag; // 0: Refund, 1: Sale, 2: Reversed
};

struct TNode { // Transaction Node
    Transaction data;
    TNode* next;
};

class TransactionStack {
private:
    TNode* top;
    int nextTransactionID;

public:
    TransactionStack() : top(nullptr), nextTransactionID(1) {}
    ~TransactionStack() {
        while (!isEmpty()) { pop(); }
    }
    bool isEmpty() { return top == nullptr; }

    void push(double initialAmount, string description) {
        Transaction newTrans;
        newTrans.transactionID = nextTransactionID++;

        if (description.length() > 20) {
            newTrans.description = description.substr(0, 17) + "...";
        } else {
            newTrans.description = description;
        }

        double finalAmount = initialAmount;
        if (initialAmount >= 1500) finalAmount *= 0.70; // 30% discount
        else if (initialAmount >= 1000) finalAmount *= 0.85; // 15% discount
        else if (initialAmount >= 500) finalAmount *= 0.95; // 5% discount
        newTrans.amount = finalAmount;

        newTrans.flag = (newTrans.amount >= 0) ? 1 : 0;

        TNode* newNode = new TNode{newTrans, top};
        top = newNode;

        cout << "Pushed: " << newTrans.description << " (ID: " << newTrans.transactionID << "), Amount: " << newTrans.amount << endl;
    }

    Transaction pop() {
        if (isEmpty()) return Transaction{-1, 0.0, "Error", -1};
        TNode* temp = top;
        Transaction poppedTransaction = temp->data;
        top = top->next;
        delete temp;

        poppedTransaction.amount *= -1;
        poppedTransaction.description += " [REVERSED]";
        poppedTransaction.flag = 2;
        return poppedTransaction;
    }

    void display() {
        if (isEmpty()) { cout << "Stack is empty." << endl; return; }
        cout << "Current Transactions in Stack:" << endl;
        TNode* current = top;
        while (current != nullptr) {
            cout << "  -> [ID=" << current->data.transactionID
                 << ", Amount=" << current->data.amount
                 << ", Desc=\"" << current->data.description << "\""
                 << ", Flag=" << current->data.flag << "]" << endl;
            current = current->next;
        }
    }
};

// --- Character Stack (for expression evaluation) ---
struct CNode { // Character Node
    char data;
    CNode* next;
};

class CharStack {
private:
    CNode* top;
public:
    CharStack() : top(nullptr) {}
    ~CharStack() { while(!isEmpty()) { pop(); } }
    bool isEmpty() { return top == nullptr; }
    void push(char val) { CNode* newNode = new CNode{val, top}; top = newNode; }
    char pop() {
        if (isEmpty()) return '\0';
        char val = top->data;
        CNode* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
    char peek() { return isEmpty() ? '\0' : top->data; }
};

// --- Double Stack (for expression evaluation) ---
struct DNode { // Double Node
    double data;
    DNode* next;
};

class DoubleStack {
private:
    DNode* top;
public:
    DoubleStack() : top(nullptr) {}
    ~DoubleStack() { while(!isEmpty()) { pop(); } }
    bool isEmpty() { return top == nullptr; }
    void push(double val) { DNode* newNode = new DNode{val, top}; top = newNode; }
    double pop() {
        if (isEmpty()) return 0.0;
        double val = top->data;
        DNode* temp = top;
        top = top->next;
        delete temp;
        return val;
    }
};


// 2. EXPRESSION EVALUATION FUNCTIONS

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(string s) {
    CharStack st;
    string result = "";
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c == ' ') continue;

        if (isDigit(c) || c == '.') {
            string number_str;
            while (i < s.length() && (isDigit(s[i]) || s[i] == '.')) {
                number_str += s[i];
                i++;
            }
            result += number_str + " ";
            i--;
        } else if (c == '(') {
            st.push('(');
        } else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                result += st.pop();
                result += " ";
            }
            st.pop();
        } else if (isOperator(c)) {
            while (!st.isEmpty() && precedence(c) <= precedence(st.peek())) {
                result += st.pop();
                result += " ";
            }
            st.push(c);
        }
    }
    while (!st.isEmpty()) {
        result += st.pop();
        result += " ";
    }
    return result;
}

double evaluatePostfix(string s) {
    DoubleStack st;
    string current_token = "";

    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c == ' ') {
            if (!current_token.empty()) {
                if (isDigit(current_token[0])) {
                    st.push(stod(current_token));
                } else if (isOperator(current_token[0])) {
                    double val2 = st.pop();
                    double val1 = st.pop();
                    switch (current_token[0]) {
                        case '+': st.push(val1 + val2); break;
                        case '-': st.push(val1 - val2); break;
                        case '*': st.push(val1 * val2); break;
                        case '/': st.push(val1 / val2); break;
                    }
                }
                current_token = "";
            }
        } else {
            current_token += c;
        }
    }
    return st.pop();
}


// 3. MAIN SIMULATION LOGIC

void runStoreSimulation() {
    // Predefined list of transactions
    vector<pair<double, string>> predefinedTransactions = {
        {1200.0, "Sale: Blue Jacket"},
        {450.0, "Sale: Cotton Socks"},
        {1700.0, "Sale: Leather Jacket with a very long description"},
        {-300.0, "Refund: Defective Shirt"},
        {600.0, "Sale: Designer Scarf"},
        {-150.0, "Refund: Wrong Size T-shirt"},
        {2200.0, "Sale: Premium Watch"}
    };

    TransactionStack storeStack;

    cout << "--- Pushing 4 Transactions (Fixed Selection) ---" << endl;
    // Push the first 4 transactions instead of random ones
    for (int i = 0; i < 4; ++i) {
        storeStack.push(predefinedTransactions[i].first, predefinedTransactions[i].second);
    }
    cout << "------------------------------------------------" << endl << endl;

    cout << "--- Current Stack Status ---" << endl;
    storeStack.display();
    cout << "----------------------------" << endl << endl;

    cout << "--- Intermediate Expression Calculation ---" << endl;
    string infix_expression = "(100 + 20) * 0.9 - 5";
    string postfix_expression = infixToPostfix(infix_expression);
    double result = evaluatePostfix(postfix_expression);
    
    cout << "Infix: " << infix_expression << endl;
    cout << "Postfix: " << postfix_expression << endl;
    cout << "Evaluated Result: " << result << endl;
    cout << "------------------------------------------" << endl << endl;

    cout << "--- Popping One Transaction ---" << endl;
    Transaction reversedTrans = storeStack.pop();
    if (reversedTrans.transactionID != -1) {
         cout << "Popped and Reversed Transaction Details:" << endl;
         cout << "  -> [ID=" << reversedTrans.transactionID
                 << ", New Amount=" << reversedTrans.amount
                 << ", Desc=\"" << reversedTrans.description << "\""
                 << ", New Flag=" << reversedTrans.flag << "]" << endl;
    }
    cout << "-------------------------------" << endl << endl;

    cout << "--- Final Stack Status ---" << endl;
    storeStack.display();
    cout << "--------------------------" << endl;
}


int main() {
    runStoreSimulation();
    return 0;
}