#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

// insert a data at the end of the node
void insert_end(struct node *head, int data){
    struct node new_node;
    
    new_node.data = data;
    new_node.next = NULL;
    
    if (head == NULL)
    {
        head = &new_node;
    }
    // move to the end of the linked list and get the last node to point to the new node
    else{

    }

}

void print_LL(struct node *head){
    struct node *temp = head;
    while (temp!=NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    
}

/* 

how the linked list will work

a head pointer will be null initially

at insert a new node will be created and the head pointer will point to it

the new node will have its next pointer pointing to null


*/

int main (){
    struct node *head; // head pointer
    struct node LL; // first node
    LL.data = 0;
    LL.next = NULL;

    head = &LL; // empty list

    insert_end(head, 10);
    insert_end(head, 20);
    insert_end(head, 30);
    insert_end(head, 40);
    insert_end(head, 50);

    print_LL(head);

    return 0;
}