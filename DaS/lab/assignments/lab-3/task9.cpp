/*

Task#9:
Given a linked list, you have to perform the following task:
1. Extract the alternative nodes starting from second node.
2. Reverse the extracted list.
3. Append the extracted list at the end of the original list.
Note: Try to solve the problem without using any extra memory.
Example 1:
Input:
LinkedList = 10->4->9->1->3->5->9->4
Output:
10 9 3 9 4 5 1 4
Explanation:
Alternative nodes in the given linked list are 4,1,5,4. Reversing the alternative nodes from the given list, and then
appending them to the end of the list results in a list 10->9->3->9->4->5->1->4.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <iomanip>

using namespace std;

// extract the nodes in alternating fashion, place these extracted nodes into a new LL, reverse that LL, then merge it
// for efficiency this ll has tail pointer
// specific type of LL not specified


class doublyNode
{
public:
    int data;
    doublyNode *prev, *next;

    // constructor
    doublyNode(int data){
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }
};


class doubly_LL
{
public:
    doublyNode *head, *tail;
    int length;

    doubly_LL(){
        head = nullptr;
        tail = nullptr;
    }

    void checkLength(){ // of LL
        doublyNode *temp=head;
        int i =0;
        while(temp!=tail){
            temp = temp->next;
            i++;
        }
        this->length = i;
    }

    void insert_end(int data){
        doublyNode *new_node = new doublyNode(data);
        if (head==nullptr)
        {
            head = new_node;
            new_node->prev = nullptr; // first node has no prev node to point to
            tail = new_node;
            return;
        }

        // tail points to last node

        tail->next = new_node; // last node point to new node
        new_node->prev = tail; // new node points to prev node
        tail = new_node; // tail points to new node

    }

    void reverse_LL(){
        // simply switch the prev pointer, and next pointer values
        // point head to the last node
        // a single temp pointer will traverse through the LL, and swap the pointers, the last node will be head

        doublyNode *temp = head, *swap;
        while (temp->next!=nullptr)
        {
        
            // swap
            swap = temp->next;
            temp->next = temp->prev;
            temp->prev = swap;
            
            temp = temp->prev;
        }
        
        // after reaching last node, perform last swap
        swap = temp->next;
        temp->next = temp->prev;
        temp->prev = swap;
        
        std::cout << "completed swap" << std::endl;
        
        doublyNode *newTemp;
        
        // head and tail will switch places
        newTemp = head;
        head = tail;
        tail = newTemp;
        
        std::cout << head->next->data << std::endl;
        
    }
    

    // merge this ll into the object
    void merge(doubly_LL ll){

        // for this get the one calling is L, and the arg is M
        // get tail of L to point to the M head node, and the head node to point to L's tail
        tail->next = ll.head;
        ll.head->prev = tail;
        // the M tail will be new tail
        tail = ll.tail;
    }

    // insert node at end
    void insert_node(doublyNode* node){

        // cout<<"insert"<<endl;
        if (head == nullptr) 
        {
            head = node;
            tail = node;
            node->prev = nullptr; // the first node has no prev node
            return;
        }
        

        tail->next = node;
        node->prev = tail; // new node will point to previous last node
        tail = node;
    }

    doublyNode* extract_pos(int pos){
        checkLength();
        // if it is the last node to be extracted
        if (pos == this->length)
        {
            /* // the position is the last node, for this simply get the 2nd last node to point to null 
            doublyNode *curr = nullptr, *next = head;
            while (next->next != nullptr)
            {
                curr = next;
                next = next->next;
            }
            tail = curr;
            tail->next = nullptr;

            return next; */

            doublyNode *temp = tail;
            // retract tail
            tail = tail->prev;
            // new last node will stop pointing to this node
            tail->next = nullptr;
            // isolate node
            temp->prev = nullptr;
            return temp;
        }
        

        if (head!=nullptr)
        {
            doublyNode *curr = head;

            while (pos-- != 0)
            {
                
                curr = curr->next;
            }
            // we have reached the node to be extract, get the prev node to point to the next node and get the next node to point to prev node

            // V` prev node    V` next node
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;

            // curr node point to nothing now
            curr->next = nullptr;
            curr->prev = nullptr;


            return curr;
        }
        return nullptr;
    }

    void print(){
        doublyNode *temp = head; // a temporary pointer to traverse through the LL

        while (temp!=nullptr)
        {
            // if (temp == head)
            // {
            //     // std::cout << "head->" << head << std::endl;
            //     std::cout << std::setw(12) <<"head-> "  <<  temp->prev << " | " << temp->data << " | " << temp->next << std::setw(15) << "    <--- " << temp << std::endl;
            // }else
            // {
            //     std::cout << std::setw(13) << temp->prev << " | " << temp->data << " | " << temp->next << std::setw(13) << "    <--- " << temp << std::endl;
            // }
            

            std::cout << temp->data << " -> ";
            
            temp = temp->next;
        }
        std::cout << "NULL" << endl;
    }
};


int main(){

    doubly_LL ll;

    ll.insert_end(10);
    ll.insert_end(4);
    ll.insert_end(9);
    ll.insert_end(1);
    ll.insert_end(3);
    ll.insert_end(5);
    ll.insert_end(9);
    ll.insert_end(4);

    ll.print();

    // extract alternative nodes and place them into a new ll

    doubly_LL newLL;
    doublyNode *tempNode=ll.head, *temP=ll.head;

    
    ll.checkLength();

    for (size_t i = 1; i < (ll.length/2)+1; i++)
    {
        
        if (tempNode != nullptr)
        {
            
            std::cout << "i: " << i<< std::endl;
            tempNode = ll.extract_pos(i);
            newLL.insert_node(tempNode);
            
            ll.print();
            std::cout << "length:" << ll.length<< std::endl;
            
            std::cout << "i2: " << i<< std::endl;
            newLL.print();
        }else{
            std::cout << "break " << std::endl;
            break;
        }
        
    }
    newLL.print();
    // // reverse the new ll
    newLL.reverse_LL();
    newLL.print();

    // now merge this reversed ll
    ll.merge(newLL);
    ll.print();




    return 0;
}