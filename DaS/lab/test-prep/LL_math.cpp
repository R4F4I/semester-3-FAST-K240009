/* 
---

/ DSA Lab Mid Fall'24 Shift I PaperB.pdf

**Question # 02 (LLO # 1)**
**[16 Points, 8 Weightage]**

At this point you have studied **linked lists** very effectively so let's turn this concept into an **expression solver**. In Mathematics you are given an expression $12+13-5 = 20$ and $12/2*3 = 18$ and you add the resultant it yields $38$ so take a **linked list with two nodes**. In each node there is another **linked list** (size can vary so assume the expression to be **3 variables**) and compute its output. The layout would be something like this mentioned below:

`Node1->Node2->NULL`

`Node1->12-> + -> 13 -> - -> 15 -> Node1`
`Node2->12-> / -> 2 -> * -> 3 -> Node2`

**Output**
$38$

**Note:** Both the **outer** and **inner nodes** must be a **doubly linked lists** and order of operations must be **PEDMAS** (**P**arenthesis, **E**xponents, **D**ivision, **M**ultiplication, **A**ddition, **S**ubtraction).

---

Let me know if you need any help understanding the problem or want to discuss how to approach the solution!


*/

#include <iostream>
#include <string>

using namespace std;

// used for the data within the outer nodes
class innerNode
{
public:
    string data; // will convert the string to numbers later on
    innerNode  *next, *prev;

    innerNode(string d){
        data = d;
        next = nullptr;
        prev = nullptr;
    }
    innerNode(){
        next = nullptr;
        prev = nullptr;
    }

};



// used for the outer nodes
class outerNode
{
public:
    innerNode* data; // will convert the char num to numbers later on
    outerNode  *next, *prev;

    outerNode(){
        next = nullptr;
        prev = nullptr;
    }
    
    outerNode(innerNode* data){
        this->data = data;
        next = nullptr;
        prev = nullptr;
    }

};



class outerLL{

public:
    outerNode* head;

    outerLL(){
        head=nullptr;
    }



    // will take outerNodes as 
    void insertNode(outerNode* node){

        if (head==nullptr){
            head = node;
            return;
        }
        
        outerNode *temp = head;
        while (temp->next!=nullptr){
           temp = temp->next; 
        }
        temp->next = node;

        node->prev = temp;
        // outer LL is not circ
    }

    void printLL(){
        outerNode* temp = head;

        while (temp!=nullptr){
            std::cout 
            << temp->data->data << "->"
            << temp->data->next->data << "->"
            << temp->data->next->next->data << ":"
            ;
            temp = temp->next;
        }
        
        cout<<endl;

    }

};


class innerLL{

public:
    innerNode* head;

    innerLL(){
        head=nullptr;
    }

    void insertData(string data){

        innerNode* node = new innerNode(data);


        if (head == nullptr)
        {
            head = node;
            // circ LL
            node->prev = head;
            head->prev = node; 
            return;
        }
        
        // temp is innerNode ptr due to all the data being within inner Nodes, 
        // also the last node will point to head
        
        innerNode* temp = head->prev;


        
        temp->next = node; // last node points to new node
        node->prev = temp; // new node will point to prev
        node->next = head; // circ LL
        head->prev = node; //         head's prev is the new node

    }

    void printLL(){
        innerNode* temp = head;
        
        std::cout << temp->data << " -> ";
        temp = temp->next;
        while (temp!=head)
        {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout<<endl;
        

    }

};

float calc(float oper1, string op, float oper2 ){
    if (op=="*") return oper1*oper2;
    if (op=="/") return oper1/oper2;
    if (op=="+") return oper1+oper2;
    if (op=="-") return oper1-oper2;

    return 0;
}

// this func will look at a simple ll with no (), for PEMDAS, * , / before +,-
// the ll will not have a op in the beginning
// the inner ll is circ
float solveLL(innerNode* head){

    if (head==nullptr)
    {
        return 0;
    }
    
    innerNode* curr = head; // curr the op * / - +


    // curr points to node in the ll
    while (curr->prev != curr->next) // will stop if both sides are pointing to same node (that being head (the inner ll is circ))
    {

        if (
            curr->data=="*" ||
            curr->data=="/" 
        )
        {
            float oper1 = std::stof(curr->prev->data);
            string op = curr->data;
            float oper2 = std::stof(curr->next->data);
            float result = calc(oper1,op,oper2);

            // std::cout << "calced result: " <<result<< std::endl;

            innerNode *res = new innerNode(to_string(result));

            // after calc result remove the the 3 nodes from the ll, and replace them with value in result
            // P C N -> R
            // *1 <-> P <-> C <-> N <-> *2 , get the two *s to point to R
            // *1 <-> R <-> *2 , get the two *s to point to R

            // *1 points to R
            if (curr->prev->prev->next){
                curr->prev->prev->next = res;
                // res points to *1
                res->prev = curr->prev->prev;
            } else {
                // if C is 2nd node, then no n-2 node exists
                
                // h<->10 <-> C <-> 20 <-> *
                // h<->R <-> *
                head = res; // if 2nd node, the head now points to new res
                res->prev = head; // being the 1st 

                
                res->next = curr->next->next;
                curr->next->next->prev = res;
            }
            

            // std::cout << "patching ll" << std::endl;
            // R points to *2
            if (curr->next->next)
            {
                // what if C is 2nd last op
                // *1 - P - C - N - , get the two *s to point to R
                res->next = curr->next->next;
                // *2 points to R
                curr->next->next->prev = res;
            } else{
                res->next = nullptr;
            }
            


            // get all the uneeded nodes to stop pointing 
            curr->prev->prev=nullptr;
            curr->prev->next=nullptr;

            curr->next->next=nullptr;
            curr->next->prev=nullptr;
            
            curr->prev=nullptr;
            curr->next=nullptr;

            head = res;
            

            // delete P C N

            delete curr->prev;
            delete curr->next;
            delete curr;

        
            curr=res; // curr will now point to the new res node
        } else
        {
            curr=curr->next;
        }

        ////////////////////////////////////
        /// + and - kept separated
        if (
            curr->data=="+" ||
            curr->data=="-" 
        )
        {
            float oper1 = std::stof(curr->prev->data);
            string op = curr->data;
            float oper2 = std::stof(curr->next->data);
            float result = calc(oper1,op,oper2);

            // std::cout << "calced result: " <<result<< std::endl;

            innerNode *res = new innerNode(to_string(result));

            // after calc result remove the the 3 nodes from the ll, and replace them with value in result
            // P C N -> R
            // *1 <-> P <-> C <-> N <-> *2 , get the two *s to point to R
            // *1 <-> R <-> *2 , get the two *s to point to R

            // *1 points to R
            if (curr->prev->prev->next){
                curr->prev->prev->next = res;
                // res points to *1
                res->prev = curr->prev->prev;
            } else {
                // if C is 2nd node, then no n-2 node exists
                
                // h<->10 <-> C <-> 20 <-> *
                // resolving: h<->R 
                head = res; // if 2nd node, the head now points to new res
                res->prev = head; // being the 1st 
                
                // resolving: R <-> *
                res->next = curr->next->next;
                curr->next->next->prev = res;
            }
            

            // std::cout << "patching ll" << std::endl;
            // R points to *2
            if (curr->next->next)
            {
                // what if C is 2nd last op
                // *1 - P - C - N - , get the two *s to point to R
                res->next = curr->next->next;
                // *2 points to R
                curr->next->next->prev = res;
            } else{
                res->next = nullptr;
            }
            


            // get all the uneeded nodes to stop pointing 
            curr->prev->prev=nullptr;
            curr->prev->next=nullptr;

            curr->next->next=nullptr;
            curr->next->prev=nullptr;
            
            curr->prev=nullptr;
            curr->next=nullptr;

            head = res;
            

            // delete P C N

            delete curr->prev;
            delete curr->next;
            delete curr;

        
            curr=res; // curr will now point to the new res node
        } else
        {
            curr=curr->next;
        }
        
        
        // if curr is some oper1 traverse
        // std::cout << "curr: " <<curr->data << std::endl;
        
    }
    head = curr;
    return stof(curr->data);

}

int solveQuestion(outerLL ll){

    float sum=0;
    outerNode* temp = ll.head;
    // go to first node
    while (temp!=nullptr)
    {
        sum+= solveLL(temp->data);
        cout 
        // << temp->data->data
        // << temp->data->next->data
        // << temp->data->next->next->data
        // << temp->data->next->next->next->data
        // << temp->data->next->next->next->next->data
        <<endl;
        temp = temp->next;
        
    }
    return sum;

}

void printNode(innerNode* head){
    innerNode* temp = head;
    // std::cout << "/* message */" << std::endl;
    std::cout << temp->data << "->";
    temp = temp->next;
    while (temp!=head)
    {
        std::cout << temp->data << "->";
        temp = temp->next;
    }
    cout<<endl;

}

int main(){

    // define the inner nodes
    innerLL iLL1;
    
    iLL1.insertData("12");
    iLL1.insertData("+");
    // iLL1.printLL();
    iLL1.insertData("13");
    iLL1.insertData("-");
    iLL1.insertData("5");
    iLL1.insertData("+");
    iLL1.insertData("2");
    
    iLL1.printLL();
    
    innerLL iLL2;

    iLL2.insertData("12");
    iLL2.insertData("/");
    iLL2.insertData("2");
    iLL2.insertData("*");
    iLL2.insertData("3");


    iLL2.printLL();

    // node1 is pointing to node2 and also pointing to head to innerLL's head
    

    outerLL oLL;
    outerNode node1(iLL1.head);
    oLL.insertNode(&node1);


    outerNode node2(iLL2.head);
    oLL.insertNode(&node2);
    
    
    oLL.printLL();
    // oLL.printLL();
    
    // iLL1.printLL();
    // iLL2.printLL();
    
    printNode(iLL1.head);
    printNode(iLL2.head);
    std::cout << "output:\n" <<solveQuestion(oLL)<< std::endl;
    printNode(iLL1.head);
    printNode(iLL2.head);

    // std::cout << node1.data->data << std::endl;
    // std::cout << node2.data->data << std::endl;



    return 0;
}