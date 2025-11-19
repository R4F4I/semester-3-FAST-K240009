/* 
Task # 1
Suppose you are working on a program that needs to store a large number of strings, with the possibility of
duplicate strings. You decide to use chain hashing to efficiently store and retrieve the strings, but you want
to ensure that collisions are avoided as much as possible. Your hash function simply takes the sum of the
ASCII values of the characters in the string and returns the remainder after dividing by the number of
buckets. You decide to implement the hash table using a linked list for each bucket.
Input and output:
HashTable myhash;
[hine: key is A]
myhash.insert("A","aaaaa");
myhash.insert("B","bbbbb");
myhash.insert("C","ccccc");
myhash.insert("A","zzzzz");

 */

 #include <iostream>

 using namespace std;

 class node
 {
 public:
    string key, name;
    node* next;
    node(string k="", string n=""): key(k), name(n), next(nullptr) {}

    
 };

class hashTable
{
public:

    node **table;
    int size;

    hashTable(int size = 10){
        this->size = size;
        table = new node*[this->size]; // table is an array of nodes with each node being defaulted as head (it will not contain any value)
        // for (size_t i = 0; i < size; i++)
        // {
        //     table[i]->next = nullptr;
        // }
        
    }

    void resize(int newSize){

        node **newTable = new node*[newSize];
        // for (size_t i = 0; i < newSize; i++)
        // {
        //     newTable[i]->next = nullptr;
        // }
        for (size_t i = 0; i < this->size; i++) // using the old unupdated size
        {
            newTable[i] = this->table[i];
        }
        this->size = newSize; // update the size of the array
        delete[] table; // remove the old array from mem
        this->table = newTable; // get the attib to update
        delete[] newTable; // remove the temp arr pointer
    }

    void insert(string key, string name){
        // get sum of all ascii of string key
        int sum = 0;
        for (auto k: key)
        {
            sum+= static_cast<int>(k);
        }
        int index = sum;
        cout<<"success!1"<<endl;

        if (index>this->size){
            // create a new hastable of size index
            resize(index+10);
        }
        cout<<"success!2"<<endl;
        
        // TODO: HOW WILL WILL THE ARR OF POINTERS RESOLVE ADDING A NEW NODE?
        // what if the new node is manually defined
        node *newNode = new node(key,name);

        cout<<"success!3"<<endl;
        cout<<"this->table[index]->next: "<<this->table[index]->next<<endl;
        node* temp = this->table[index]->next;
        cout<<"success!4"<<endl;

        this->table[index]->next = newNode;
        cout<<"success!5"<<endl;
        newNode->next = temp; // new node added in front, keeps the insertion O(1) 
        
        cout<<"success!6"<<endl;
    }
 
};


int main(int argc, char const *argv[])
{
    hashTable table;
    table.insert("A","aaaaa");
    table.insert("B","bbbbb");
    table.insert("C","ccccc");
    table.insert("A","zzzzz");
    
    return 0;
}
