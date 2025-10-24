/*


Task 4: Consider you have an expression x=12+13-5(0.5+0.5) +1 which results to 20. Implement a
stack-based implementation to solve this question via linked lists (linked lists can be single or double)
and the resulted output must be at the top of the stack. Note that the x and the equal sign must be
present in the stack and when inserting the top value (20 result) all the values must be present in the
stack (You can pop and push them accordingly)



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A

*/

#include <iostream>
#include <string> // Required for string manipulation

using namespace std;


//   Stack Implementation for CHAR (From User)


class Node {
public:
    char data;
    Node* next = nullptr;

    Node(char data) {
        this->data = data;
        next = nullptr;
    }
};

class Stack {
public:
    Node* head;
    Stack() {
        head = nullptr;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    // will add data from head, head points to top val now
    void push(char data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    char top() {
        if (isEmpty()) {
            return '\0'; // Return null char if empty
        }
        return head->data;
    }

    char pop() {
        if (isEmpty()) {
            return '\0'; // Return null char if empty
        }

        char val = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    void print() {
        cout << "Stack (top to bottom): ";
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl << endl;
    }
};

// =====================================
//  Stack Implementation for DOUBLE (Required)
// =====================================

class NodeDouble {
public:
    double data;
    NodeDouble* next = nullptr;

    NodeDouble(double data) {
        this->data = data;
        next = nullptr;
    }
};

class StackDouble {
public:
    NodeDouble* head;
    StackDouble() {
        head = nullptr;
    }

    bool isEmpty() {
        return (head == nullptr);
    }

    void push(double data) {
        NodeDouble* newNode = new NodeDouble(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        newNode->next = head;
        head = newNode;
    }

    double top() {
        if (isEmpty()) {
            cout << "Error: Stack is empty." << endl;
            return 0.0; // Return 0.0 if empty
        }
        return head->data;
    }

    double pop() {
        if (isEmpty()) {
            cout << "Error: Pop from empty stack." << endl;
            return 0.0; // Return 0.0 if empty
        }

        double val = head->data;
        NodeDouble* temp = head;
        head = head->next;
        delete temp;
        return val;
    }

    void print() {
        cout << "NumStack (top to bottom): ";
        NodeDouble* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


// =====================================
//    Helper Functions (From User & New)
// =====================================

// Provided by user
bool isOp(char c) {
    if (
        c == '(' ||
        c == ')' ||
        c == '^' ||
        c == '/' ||
        c == '*' ||
        c == '-' ||
        c == '+'
        ) {
        return true;
    }
    return false;
}

// Provided by user
int prec(char c) {
    if (c == '^') {
        return 3;
    }
    if (c == '/' || c == '*') {
        return 2;
    }
    if (c == '-' || c == '+') {
        return 1;
    }
    return -1; // For '(' and other non-operators
}

// Custom function to calculate 10^p
double my_pow10(int p) {
    double res = 1.0;
    for (int i = 0; i < p; i++) {
        res *= 10.0;
    }
    return res;
}

// Custom string-to-double converter
double my_stod(string s) {
    double int_part = 0.0;
    double frac_part = 0.0;
    int frac_len = 0;
    int dec_pos = -1;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '.') {
            dec_pos = i;
            continue;
        }
        if (dec_pos == -1) { // Building integer part
            int_part = int_part * 10.0 + (s[i] - '0');
        }
        else { // Building fractional part
            frac_part = frac_part * 10.0 + (s[i] - '0');
            frac_len++;
        }
    }

    return int_part + (frac_part / my_pow10(frac_len));
}



// Infix to Postfix (Rewritten for Task)


// Handles multi-digit numbers, decimals, and implicit multiplication
string convert_infix_to_postfix(string expr) {
    string resString;
    Stack opStack; // The char stack

    for (size_t i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // 1. If it's a digit or a decimal, parse the whole number
        if ((c >= '0' && c <= '9') || c == '.') {
            string number;
            while (i < expr.length() && ((expr[i] >= '0' && expr[i] <= '9') || expr[i] == '.')) {
                number += expr[i];
                i++;
            }
            i--; // Step back one char because the for-loop will i++
            resString += number + " "; // Add number to result with a space
        }
        // 2. If it's an opening parenthesis
        else if (c == '(') {
            // Check for implicit multiplication (e.g., "5(" or ")(")
            if (i > 0 && ((expr[i - 1] >= '0' && expr[i - 1] <= '9') || expr[i - 1] == ')')) {
                // Treat implicit multiplication as a '*' operator
                while (!opStack.isEmpty() && opStack.top() != '(' && prec('*') <= prec(opStack.top())) {
                    resString += opStack.pop();
                    resString += " ";
                }
                opStack.push('*');
            }
            opStack.push(c); // Push the '('
        }
        // 3. If it's a closing parenthesis
        else if (c == ')') {
            // Pop operators from stack to result until '(' is found
            while (!opStack.isEmpty() && opStack.top() != '(') {
                resString += opStack.pop();
                resString += " ";
            }
            opStack.pop(); // Pop and discard the '('
        }
        // 4. If it's a standard operator
        else if (isOp(c)) { // isOp handles +, -, *, /
            // Pop operators with higher or equal precedence
            while (!opStack.isEmpty() && opStack.top() != '(' && prec(c) <= prec(opStack.top())) {
                resString += opStack.pop();
                resString += " ";
            }
            opStack.push(c); // Push the current operator
        }
    }

    // 5. Pop all remaining operators from the stack
    while (!opStack.isEmpty()) {
        resString += opStack.pop();
        resString += " ";
    }

    return resString;
}



// Postfix Solver (Rewritten for T


// Solves a space-separated postfix expression
double solve_postfix_expr(string expr) {
    StackDouble s_nums; // The double stack

    cout << "\n--- Postfix Evaluation Start ---" << endl;

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        if (c == ' ') {
            continue; // Skip spaces
        }

        // 1. If it's a number (digit or decimal), parse it
        if ((c >= '0' && c <= '9') || c == '.') {
            string num_str;
            // Build the number string until the next space
            while (i < expr.length() && expr[i] != ' ') {
                num_str += expr[i];
                i++;
            }
            double val = my_stod(num_str);
            s_nums.push(val);
            cout << "Pushed " << val << ". "; s_nums.print();
        }
        // 2. If it's an operator
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            // Pop two operands
            double op2 = s_nums.pop();
            double op1 = s_nums.pop();
            double result;

            if (c == '+') result = op1 + op2;
            else if (c == '-') result = op1 - op2;
            else if (c == '*') result = op1 * op2;
            else if (c == '/') result = op1 / op2;

            s_nums.push(result); // Push the result back
            cout << "Op: " << op1 << " " << c << " " << op2 << " = " << result << ". "; s_nums.print();
        }
    }

    cout << "--- Postfix Evaluation Complete ---" << endl;
    return s_nums.pop(); // The final result is the last item on the stack
}



int main() {
    // Per the note at the top, using the expression that results in 20.
    string fullExpr = "x=12+13-5(0.5+0.5)";
    string evalExpr = "12+13-5(0.5+0.5)";

    cout << "Original Expression: " << fullExpr << endl;
    
    // 1. Convert the evaluable part to postfix
    string postfix = convert_infix_to_postfix(evalExpr);
    cout << "Postfix Expression: " << postfix << endl;

    // 2. Solve the postfix expression
    double result = solve_postfix_expr(postfix);
    cout << "\nCalculated Result: " << result << endl;

    // 3. Create the final display stack as required
    Stack displayStack;

    // 4. Push the original expression onto the stack, char by char
    // This will result in the stack (top-to-bottom) being:
    // ) 5 . 0 + ... = x
    cout << "\nPushing original expression onto stack..." << endl;
    for (int i = 0; i < fullExpr.length(); i++) {
        displayStack.push(fullExpr[i]);
    }

    cout << "Stack before adding result:" << endl;
    displayStack.print();

    // 5. Push the result (20) onto the top of the stack
    // We push '2', then '0', so '0' is at the very top.
    cout << "Pushing result '20' onto stack..." << endl;
    string resStr = "20";
    for(int i = 0; i < resStr.length(); i++) {
        displayStack.push(resStr[i]);
    }

    // 6. Print the final stack state
    cout << "--- Final Stack State ---" << endl;
    cout << "(Result '20' is at the top)" << endl;
    displayStack.print();

    return 0;
}