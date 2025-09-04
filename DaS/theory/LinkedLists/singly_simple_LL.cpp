#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

// insert a data at the end of the node
void insert_end(struct node **head, int data){ // pass the head pptr's address to pass byref
    // allocate memory of size struct node, return type pointer of struct node, why? to prevent the local var from being destroyed when the function ends function 
    struct node *new_node = (struct node *) malloc(sizeof(struct node));
    
    new_node->data = data; // add data
    new_node->next = NULL; // add next
    
    // check if value of head ptr is NULL
    if (*head == NULL) // the value of head ptr
    {
        *head = new_node;
        return;
    }

    // move to the end of the linked list and get the last node to point to the new node
    
    struct node *temp = *head; // copy head pointer's value into temp
    while (temp->next!=NULL)
    {
        // temp->next is sam (*temp).next, meaning temp is being dereferenced and the next value of that node is being store in the temp pointer
        temp = temp->next;
    }
    // now that temp is null, get it to store the new_node's address
    temp->next = new_node;


}

void print_LL(struct node *head){
    struct node *temp = head;
    while (temp!=NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    
}

/* 

how the linked list will work

a head pointer will be null initially

at insert a new node will be created and the head pointer will point to it

the new node will have its next pointer pointing to null


*/

int main (){
    struct node *head=NULL; // head pointer
    // struct node LL; // first node
    // LL.data = 11;
    // LL.next = NULL;

    // head = &LL; // empty list

    print_LL(head);
    insert_end(&head, 11);
    print_LL(head);
    insert_end(&head, 10);
    print_LL(head);
    insert_end(&head, 20);
    print_LL(head);
    insert_end(&head, 30);
    print_LL(head);
    insert_end(&head, 40);
    print_LL(head);
    insert_end(&head, 50);

    print_LL(head);

    return 0;
}