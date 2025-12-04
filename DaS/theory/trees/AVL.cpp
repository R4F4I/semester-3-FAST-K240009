/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;


class node{

public:

    int data, height;
    node *left, *right;


    node(int data){
        this->data = data;
        height = 0;
        left = nullptr;
        right = nullptr;
    }

};

class BST{

public:

    node *root;

    BST(int data){
        root->data = data;
        root->height = 0;
        root->left = nullptr;
        root->right = nullptr;
    }

    // void addLeft(int data, node* root){
    //     node *newNode = new node(data);

    //     root->left = newNode;
    // }

    // void addRight(int data, node* root){
    //     node *newNode = new node(data);

    //     root->right = newNode;
    // }

    // void addVal(int data, node *root){

    //     if(root->right==nullptr && data>root->data){
    //         addRight(data,root);
    //         // cout<< "added right" << endl;
    //         return;
    //     }
    //     else if(root->left==nullptr && data<root->data){
    //         addLeft(data,root);
    //         // cout<< "added left" << endl;
    //         return;
    //     }

        
    //     if (root!=nullptr && data<root->data)
    //     {
    //         addVal(data,root->left);
    //     }

    //     if (root!=nullptr && data>root->data)
    //     {
    //         addVal(data,root->right);
    //     }

    // }

    // // for printing, left, parent , right -> flatten the tree into an array
    
};
void print(node *root){

    if(root==nullptr){
        return;
    }
    print(root->left);
    cout<< root->data << endl;
    print(root->right);
    
}


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




/* 

        A
       / \
      X   B
         / \
        y   Z

        to

        
        B
       / \
      A   Z
     / \
    x   y

*/

node* leftRotate(node *A){
    node *B = A->right;
    node *y = B->left;

    B->left = A;
    A->right = y;

    A->height = heightBST(A);

    B->height = heightBST(B);

    return B;
}

node* rightRotate(node *B){
    node *A = B->left;
    node *y = A->right;

    A->right = B;
    B->left = y;

    A->height = heightBST(A);

    B->height = heightBST(B);

    return A;
}


int bf(node *root){
    return heightBST(root->left) - heightBST(root->right);
}

// void addLeft(int data, node* root){
    //     node *newNode = new node(data);

    //     root->left = newNode;
    // }


void insertAVL(int val, node *root){

    node *newNode = new node(val);

    root->left=newNode;

    if (bf(root)>1 &&  val < root->left->data)
    {
        rightRotate(root);
    }

    if (bf(root)>1 &&  val > root->left->data)
    {
        root->left = leftRotate(root->left);
        rightRotate(root);
    }

    if (bf(root)<-1 && val > root->right->data)
    {
        leftRotate(root);
    }
    if (bf(root)<-1 && val < root->right->data)
    {
        root->right = rightRotate(root->right);
        leftRotate(root);
    }
    
    


}




int main(){

    // BST bt(10);


    // bt.addVal(2,bt.root);
    // bt.addVal(60,bt.root);
    // bt.addVal(51,bt.root);
    // bt.addVal(9,bt.root);
    // bt.addVal(11,bt.root);
    // bt.addVal(50,bt.root);
    // bt.addVal(20,bt.root);
    
    
    // std::cout << search(bt.root, 51) << std::endl;
    // std::cout << search(bt.root, 52) << std::endl;
    
    // printTrail(bt.root,20);
    
    // std::cout << heightBST(bt.root) << std::endl;
    
    BST bt(10);
    insertAVL(2,bt.root);
    insertAVL(60,bt.root);
    insertAVL(51,bt.root);
    insertAVL(9,bt.root);
    insertAVL(11,bt.root);
    insertAVL(50,bt.root);
    insertAVL(20,bt.root);
    printTrail(bt.root,51);
    
    return 0;
}