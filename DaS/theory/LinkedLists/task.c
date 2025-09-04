/* 

suppose a task scheduler in an OS managing background tasks

the scheduler maintains multiples ques of tasks to be executed

Q1 contains high priority task that must be done immediately
Q2 contains normal task that can wait

when Q1 becomes empty, you must attach Q2 to Q1
*/


#include <stdio.h>

struct node
{
    int done; // 1 if done
    struct node *next;
};

int check_que(struct node *head){

}

void merge(struct node *head1,struct node *head2 ){
    if (head1!=NULL && head2!=NULL){
        struct node *temp = head1;
        while (temp!=NULL){
            temp = temp->next;
        }
        temp->next = head2;
    }
}


int main(){

    // check whether if all the tasks in Q1 are completed
    // then simply get the tail pointer of Q2 to point to Q1

    struct node *Q1_head, *Q2_head; // 

    int check = check_que(Q1_head);



}