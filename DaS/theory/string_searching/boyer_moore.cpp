/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


/* 
find string1 in string2

text:bananas
pattern:nana
  starts searching from the 'end' of the pattern

  bananas  //no match, no b in pattern the pattern will be skip the b
  a

  bananas //no match, will be shifted
   nana


  bananas  //shifted forward pattern is now full match
    nana

*/

class node
{
public:

    char data;
    node *next;

    node(char data){
        this->data = data;
        next = nullptr;
    }

};



class queueLL
{
public:
    
    int qSize;
    node *head, *tail;
    queueLL(int size){
        qSize = size;
    }

    void enqueue(char n){
        node *temp = head;
        node *newNode = new node(n);
        while (temp!=nullptr)
        {
            temp=temp->next;
        }
        temp->next = newNode;

    }
    char dequeue(){
        node *temp = head;
        
        head = head->next;
        char r = temp->data;
        delete temp;
        return r;

    }

    string cast_to_string(){
        string res;
        node *temp = head;

        while (temp!=nullptr)
        {
            res += temp->data;
            temp = temp->next;
        }
        return res;
    }
    
};




int find_string(string targ, string src){
    int srcLen = src.length();
    int targLen = targ.length();

    // can be solved using sliding window
    // create of window of size targLen
    queueLL q(targLen);

    // now the src will slide through this window
    // a pattern in src can be mismatched with targ, for this we will find the occurrence of mismatched src char, 
    // we will then 'skip' to that char
 

}

int badCharCheck(char N, string targ){
    // find where N is in target
    for (size_t i = 0; i < targ.length(); i++)
    {
        if(N == targ[i])
            return i;
    }
    return -1;
}

int main(){




    return 0;
}