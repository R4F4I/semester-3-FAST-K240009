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

  bananas  //no match
  a

  bananas //match on a, fail on n=b. Shift forward to next a
  na

  bananas  //match on ana, but still n != b. No further ana in pattern, so it checks for a smaller matching suffix - there is another na in the pattern, so shift forward to that
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
    queue q(targLen);

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