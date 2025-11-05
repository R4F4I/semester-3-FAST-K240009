/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


class node{

public:

    int data;
    node *left, *right;

    node(int data){
        this->data = data;
        left = nullptr;
        right = nullptr;
    }

};

class BST{

public:

    node *root;

    BST(int data){
        root->data = data;
        root->left = nullptr;
        root->right = nullptr;
    }

    void addLeft(int data, node* root){
        node *newNode = new node(data);

        root->left = newNode;
    }

    void addRight(int data, node* root){
        node *newNode = new node(data);

        root->right = newNode;
    }

    void addVal(int data, node *root){

        if(root->right==nullptr && data>root->data){
            addRight(data,root);
            // cout<< "added right" << endl;
            return;
        }
        else if(root->left==nullptr && data<root->data){
            addLeft(data,root);
            // cout<< "added left" << endl;
            return;
        }

        
        if (root!=nullptr && data<root->data)
        {
            addVal(data,root->left);
        }

        if (root!=nullptr && data>root->data)
        {
            addVal(data,root->right);
        }

    }

    // for printing, left, parent , right -> flatten the tree into an array
    void print(node *root){

        if(root==nullptr){
            return;
        }
        print(root->left);
        cout<< root->data << endl;
        print(root->right);
        
    }

};


bool search(node *root, int val){

    if(root==nullptr){
        return false;
    }
    if (root->data==val)
    {
        return true;
    }

    return search(root->left,val) || search(root->right,val);
}
// better search
bool searchBST(node *root, int val){

    if(root==nullptr){
        return false;
    }
    if (root->data==val)
    {
        return true;
    }
    if (val<root->data)
    {
        return searchBST(root->left,val);
    } else {
        return searchBST(root->right,val);
    }
}

bool printTrail(node *root,int val){
    
    if(root==nullptr){
        return false;
    }

    std::cout << root->data << std::endl;
    
    if (root->data==val)
    {
        return true;
    }


    if (val<root->data)
    {
        return printTrail(root->left,val);
    } else {
        return printTrail(root->right,val);
    }

}

int max(int m,int n){
    return m > n ? m : n;
}

// height of root = max(height of left, height of right)

int heightBST(node *root){
    if (root==nullptr)
        return 0;
    return max(heightBST(root->left),heightBST(root->right))+1;
}



int main(){

    BST bt(10);
    bt.addVal(2,bt.root);
    bt.addVal(60,bt.root);
    bt.addVal(51,bt.root);
    bt.addVal(9,bt.root);
    bt.addVal(11,bt.root);
    bt.addVal(50,bt.root);
    bt.addVal(20,bt.root);

    // bt.print(bt.root);

    // std::cout << search(bt.root, 51) << std::endl;
    // std::cout << search(bt.root, 52) << std::endl;

    printTrail(bt.root,20);

    std::cout << heightBST(bt.root) << std::endl;

    return 0;
}