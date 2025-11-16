/*

Task#1: Suppose you are building an application that stores student records in an AVL tree
based on their roll number. You want to insert a new student with roll number 15 into the AVL
tree, and you want to ensure that the tree is balanced using left rotation. Assuming the AVL
tree is already populated with the following student records:
Student 1 with roll number 10
Student 2 with roll number 20
Student 3 with roll number 30
Student 4 with roll number 40
Student 5 with roll number 50

 Walk me through the process of inserting the new student record with roll number 15
into the AVL tree.
* Insert 10: The tree is just the root node `10`. It is balanced.
* Insert 20: 20 is inserted as the right child of `10`. The tree is balanced.
* Insert 30: 30 is inserted as the right child of `20`. Node `10` is now unbalanced with a balance factor of -2.
* Rotation: This is a Right-Right (RR) case. A single Left Rotation is performed on `10`. `20` becomes the new root.
* Insert 40: 40 is inserted as the right child of `30`. The root `20` is now unbalanced (BF -2).
* Rotation: This is another RR case. A single Left Rotation is performed on `20`. `30` becomes the new root.
* Insert 50: 50 is inserted as the right child of `40`. The root `30` is now unbalanced (BF -2).
* Rotation: This is another RR case. A single Left Rotation is performed on `30`. `40` becomes the new root.
* Tree State: The tree is now `40` (root), `30` (left), `50` (right), `20` (left of `30`), `10` (left of `20`).
* Insert 15: 15 is inserted as the right child of `10`.
* Unwind & Rotation 1: The function unwinds. Node `30` is found to be unbalanced (BF +2). This is a Left-Left (LL) case, so a Right Rotation is performed on `30`.
* Unwind & Rotation 2: The function continues unwinding. The root `40` is now unbalanced (BF +2). This is also an LL case, so a Right Rotation is performed on `40`, making `20` the new and final root.

 After inserting the new student record, what will be the height of the AVL tree?

*       3
* 
* 
* 
*       30
*      /  \
*     15   40
*    /  \    \
*   10  20    50

 Using the left rotation operation, show the resulting AVL tree after inserting the new
student record.

* Before 15: The tree is a long, unbalanced chain: 40 -> 30 -> 20 -> 10.
* Insert 15: The 15 is inserted as the right child of 10.
* Find Imbalance: The code unwinds and finds the first unbalanced node, which is 20. It has a balance factor of +2 (Left-Heavy).
* Identify Case: The code looks at 20's left child, 10. Node 10 is Right-Heavy (balance factor -1 because of 15). This is a Left-Right (LR) Case.
* Use Left Rotation: To fix an LR case, the first step is the Left Rotation you asked about. A left rotation is performed on the child node (10).
*     15 moves up.
*     10 becomes the left child of 15.
* After the Left Rotation: This is immediately followed by a Right Rotation on the original unbalanced node (20). This causes a cascade of other rotations up the tree, resulting in the final, stable tree shown above.

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




    return 0;
}