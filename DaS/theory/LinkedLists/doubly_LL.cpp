#include <iostream>
#include <iomanip>


using namespace std;




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
    doublyNode *head;

    doubly_LL(){
        head = nullptr;
    }

    void insert_end(int data){
        doublyNode *new_node = new doublyNode(data);
        if (head==nullptr)
        {
            head = new_node;
            new_node->prev = nullptr; // first node has no prev node to point to
            return;
        }

        doublyNode *temp = head;
        while (temp->next!=nullptr)
        {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->prev = temp; // new node will also point to prev node
        


        
    }

    void insert_start(int data){
        doublyNode *node = new doublyNode(data);

        // new node will point to where head is pointing
        node->next = head;
        // head will point to new node
        head = node;
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

        head = temp; // head is now at last node
        
        
    }
    void printNode(doublyNode* node){
        std::cout << "node: ";
        std::cout << std::setw(13) << node->prev << " | " << node->data << " | " << node->next << std::setw(13) << "    <--- " << node << std::endl;
    }

    void print(){
        doublyNode *temp = head; // a temporary pointer to traverse through the LL

        while (temp!=nullptr)
        {
            if (temp == head)
            {
                // std::cout << "head->" << head << std::endl;
                std::cout << std::setw(12) <<"head-> "  <<  temp->prev << " | " << temp->data << " | " << temp->next << std::setw(15) << "    <--- " << temp << std::endl;
            }else
            {
                std::cout << std::setw(13) << temp->prev << " | " << temp->data << " | " << temp->next << std::setw(13) << "    <--- " << temp << std::endl;
            }
            
            

            temp = temp->next;
        }
        
    }
    void printList() {
        if (!head) {
            std::cout << "List is empty." << std::endl;
            return;
        }

        // Define constants for column widths for easy adjustment
        const int ADDR_WIDTH = 18; // Width for printing pointer addresses
        const int DATA_WIDTH = 8;  // Width for printing the integer data

        // --- 1. Print a clear header for the columns ---
        std::cout << std::left // Align text to the left for headers
                << std::setw(8) << "Label"
                << std::setw(ADDR_WIDTH) << "Previous Node"
                << std::setw(DATA_WIDTH + 2) << "| Data" // +2 for separators
                << std::setw(ADDR_WIDTH + 2) << "| Next Node"
                << "| Own Address" << std::endl;
        
        std::cout << std::string(80, '-') << std::endl; // Print a separator line

        // --- 2. Iterate and print each node with proper alignment ---
        doublyNode* temp = head;
        while (temp != nullptr) {
            // Handle the label for the head node vs. other nodes
            if (temp == head) {
                std::cout << std::left << std::setw(8) << "head ->";
            } else {
                // Print empty space to keep the first column aligned
                std::cout << std::setw(8) << "";
            }

            // Use std::right for pointers and numbers to make them line up nicely
            std::cout << std::right;

            // --- 3. Apply setw() BEFORE EACH item to be printed in a column ---
            
            // Print Previous Address
            if (temp->prev == nullptr) {
                std::cout << std::setw(ADDR_WIDTH) << "nullptr";
            } else {
                std::cout << std::setw(ADDR_WIDTH) << temp->prev;
            }

            // Print Data
            std::cout << " | " << std::setw(DATA_WIDTH) << temp->data;

            // Print Next Address
            if (temp->next == nullptr) {
                std::cout << " | " << std::setw(ADDR_WIDTH) << "nullptr";
            } else {
                std::cout << " | " << std::setw(ADDR_WIDTH) << temp->next;
            }
        
            // Print the node's own address
            std::cout << " | " << temp << std::endl;

            temp = temp->next;
        }
    }

};



int main(){
    
    doubly_LL newLL;
    
    // printf("################\n");
    
    // newLL.print();
    newLL.insert_end(11);
    newLL.insert_end(10);
    newLL.insert_end(20);
    newLL.insert_end(30);
    newLL.insert_end(40);
    newLL.insert_end(50);

    newLL.print();
    // newLL.printList();
    std::cout << "------" << std::endl;
    
    newLL.reverse_LL();
    newLL.print();
    
    std::cout << "------" << std::endl;
    newLL.insert_start(60);
    
    newLL.print();

}