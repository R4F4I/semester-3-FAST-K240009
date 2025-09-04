#include <stdio.h>

struct node
{
    int data;
    struct node *next;
};

void print_LL(struct node *head){
    struct node *temp = head;
    while (temp!=NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    
}

 // idea
    // use 3 pointers, prev curr and next 
    // only the curr node will be made to point to the previous node
void reverse_LL(struct node *head){
    struct node *prev = NULL, *curr=NULL, *next=head;

    // next = head;
    //  make first node have a NULL, to prevent a circ LL
    next->next = NULL; 
    int i =0;
    while (next !=NULL)
    {
        printf("\n%d",i++);
        // traverse ahead
        prev = curr;
        curr = next;
        next = next->next;
        
        // switch the node at which next is point to be prev
        
        // wait for the prev node to enter into the LL
        if (prev !=NULL){
            curr->next = prev;
        }
        printf("\n%d",i++,next->data);
        // printf("\n%d");

    }
    // make head point to the last node
    head = next->next;

}

int main(){

    // init a LL
    struct node *head = NULL;
    struct node first;
    first.data = 2;
    first.next = NULL;
    head = &first;

    struct node second;
    second.data = 3;
    second.next = NULL;
    first.next = &second;

    struct node third;
    third.data = 4;
    third.next = NULL;
    second.next = &third;

    struct node fourth;
    fourth.data = 5;
    fourth.next = NULL;
    third.next = &fourth;

    print_LL(head);
    
    reverse_LL(head);

    printf("\ntest2:\n");

    print_LL(head);




}

