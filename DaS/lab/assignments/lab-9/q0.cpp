/*

Task#0: Why AVL? Explain in just two lines.

!ans: a balanced tree does not have uneven heights, keeping it away from worst case scenarios for BST

Given the BST (A and B) below, write a function to convert these BST into an AVL tree. The
function should take the root of the BST as input and perform the conversion. Write only the
conversion function, with no insertion logic needed. You may hard-code the given BST for this
task.

    10 | 10
   /   |   \
  6    |   16
 / \   |  /  \
4   8  | 12  18

After converting the above BST to an AVL tree, explain each step of the code: how nodes are
linked to form the AVL, the types of temporary pointers used in rotation functions, and how
specific nodes (e.g., x, y, t2) correspond to the original tree nodes. Additionally, specify the type
of rotation performed (right, left, or double rotation), and explain in 3-4 lines which node is
returned at the end of the function and why.


? 1. The convertToAVLRecursive function works after the recursive calls return. This means it balances the tree from the leaves up to the root.
? 
?     Node 4: The function is called on 4. It checks its left and right children (both nullptr). It's balanced. It returns.
?     Node 8: The function is called on 8. It's also balanced. It returns.
?     Node 6: The function is called on 6. It now sees its (balanced) children, 4 and 8. It calculates its own height and balance factor. Since height(4) is 1 and height(8) is 1, the balance factor is 1 - 1 = 0. Node 6 is perfectly balanced.
?     Node 10: The function is called on 10. It sees its (balanced) left child 6 and its right child (nullptr).
? 
?         It calculates the height of its left child (6) as 2.
?         It calculates the height of its right child (nullptr) as 0.
?         It finds its balance factor: height(left) - height(right) = 2 - 0 = 2.
? 
? 2. The Imbalance and Rotation
? 
? A balance factor of 2 (or -2) means the node is unbalanced. Because the balance is +2, we know the tree is Left-Heavy.
? The code then checks the balance of its left child (6) to decide the rotation type. Since 6 has a balance factor of 0 (it's balanced), the code identifies this as a Left-Left (LL) Case.
? This imbalance is fixed with a single Right Rotation centered at the unbalanced node (10).
? 
? 3. How the Rotation Works (Node Linking)
? 
? This is where the temporary pointers (x, y, t2) are used to relink the nodes.
? 
?     y (The Unbalanced Node): This pointer refers to node 10.
?     x (The Left Child): This pointer refers to node 6.
?     t2 (The "Middle" Subtree): This pointer refers to x's right child, which is node 8.
? 
? Here is the re-linking:
? 
?     y's left child becomes t2: The left pointer of node 10 is changed to point to node 8.
?     x's right child becomes y: The right pointer of node 6 is changed to point to node 10.
? 
? After these two pointer changes, node 6 is now the root of this subtree.


* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

class node
{

    public:

    int data, height;
    node *left, *right;

    node(int data=0): data(data), left(nullptr), right(nullptr){}
 

};

int max(int n, int m){
    return m>n?m:n;
}


class BST
{

public:

    node *root;

    BST(): root(nullptr){}

    void insert(int data){

        root = insertRecursive(root,data);

    }

    node* insertRecursive(node* curr, int data){
        if (curr == nullptr)
            return new node(data);

        if (data<curr->data)
            curr->left  = insertRecursive(curr->left ,data);
        else
            curr->right = insertRecursive(curr->right,data);
    
        // if the code data is neither greater or lesser, then curr stays (root stays root), meaning root = insert... does not change root val
        return curr;
    }

    int height(node *root){
        if (root == nullptr)
            return 0;
        
        return max(height(root->left),height(root->right)) +1;
    }

    
    node* leftRotate(node *A){
        node *B = A->right;
        node *y = B->left;

        B->left = A;
        A->right = y;

        A->height = 1+ max(height(A->left),height(A->right));
        B->height = 1+ max(height(B->left),height(B->right));

        return B;
    }

    node* rightRotate(node *B){
        node *A = B->left;
        node *y = A->right;

        A->right = B;
        B->left = y;

        A->height = 1+ max(height(A->left),height(A->right));
        B->height = 1+ max(height(B->left),height(B->right));

        return A;
    }


    int balance(node *root){
        return height(root->left) - height(root->right);
    }
    
    node* convertToAVLRecursive(node* current) {
        // --- 1. Base Case ---
        if (current == nullptr) {
            return nullptr;
        }

        // --- 2. Recurse on children (Post-order) ---
        // Balance the left and right subtrees first
        current->left = convertToAVLRecursive(current->left);
        current->right = convertToAVLRecursive(current->right);

        // --- 3. Update Height ---
        // (Must be done *after* children are balanced)
        current->height = 1 + std::max(height(current->left), height(current->right));

        // --- 4. Get Balance ---
        int bal = balance(current);

        // --- 5. Rebalance (This is the corrected logic) ---
        
        // Case 1: Left-Left (LL)
        // 'current' is left-heavy (bal > 1) and its left child
        // is balanced or also left-heavy.
        if (bal > 1 && balance(current->left) >= 0) {
            return rightRotate(current);
        }

        // Case 2: Left-Right (LR)
        // 'current' is left-heavy (bal > 1) but its left child
        // is right-heavy.
        if (bal > 1 && balance(current->left) < 0) {
            current->left = leftRotate(current->left);
            return rightRotate(current);
        }

        // Case 3: Right-Right (RR)
        // 'current' is right-heavy (bal < -1) and its right child
        // is balanced or also right-heavy.
        if (bal < -1 && balance(current->right) <= 0) {
            return leftRotate(current);
        }

        // Case 4: Right-Left (RL)
        // 'current' is right-heavy (bal < -1) but its right child
        // is left-heavy.
        if (bal < -1 && balance(current->right) > 0) {
            current->right = rightRotate(current->right);
            return leftRotate(current);
        }

        // --- 6. Return (possibly new) node pointer ---
        // (If no rotations, this is just the original 'current')
        return current;
    }


    // --- Public "wrapper" function to start the print ---
    void printTreeStyle() {
        // Call the private helper, starting at the root,
        // with an initial level of 0.
        printTreeRecursive(root, 0);
    }


    void printTreeRecursive(node* current, int level) {
        // 1. Base Case: If the node is null, just return.
        if (current == nullptr) {
            return;
        }

        // 2. Increase indentation level
        // (We add 5 spaces per level for clarity)
        int indent = 5;

        // 3. Recursive Step 1: Print the RIGHT child first
        //    (This will be at the "top" of the visual print)
        printTreeRecursive(current->right, level + 1);

        // 4. Process Root: Print the current node's data
        //    - Print indentation (level * indent spaces)
        for (int i = 0; i < level * indent; i++) {
            std::cout << " ";
        }
        //    - Print the node's data
        std::cout << current->data << "\n";

        // 5. Recursive Step 2: Print the LEFT child
        //    (This will be at the "bottom" of the visual print)
        printTreeRecursive(current->left, level + 1);
    }

};





int main(){

    BST bst;
    bst.insert(10);
    bst.insert(6);
    bst.insert(4);
    bst.insert(8);
    
    // assume the tree is rotated anti-clockwise 90`
    bst.printTreeStyle();
    
    bst.root = bst.convertToAVLRecursive(bst.root);
    std::cout << std::endl<< std::endl<< std::endl;
    bst.printTreeStyle();
    
    BST bst2;
    bst2.insert(10);
    bst2.insert(16);
    bst2.insert(12);
    bst2.insert(18);
    
    // assume the tree is rotated anti-clockwise 90`
    bst2.printTreeStyle();
    
    bst2.root = bst2.convertToAVLRecursive(bst2.root);
    std::cout << std::endl<< std::endl<< std::endl;
    bst2.printTreeStyle();
    

    return 0;
}