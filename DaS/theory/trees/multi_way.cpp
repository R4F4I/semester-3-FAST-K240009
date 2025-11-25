/* 
#B-tree
*/


#include <iostream>

/* 

suppose a 2,3 tree
where a node contains 2 keys max, and can point to 3 other keys

*/


#define KEYS 2
#define CHILDREN 3

using namespace std;



void swap(int& a, int& b){
    int temp = a;
    a=b;
    b=temp;
}



class node{
public:
    int data[KEYS+1]; // flexible space
    int pop;
    bool leaf;
    node *children[CHILDREN];

    node(bool isLeaf){
        for (size_t i = 0; i < KEYS; i++){
            data[i]=0;
        }
        for (size_t i = 0; i < CHILDREN; i++){
            children[i]=nullptr;
        }
        pop = 0;
        leaf = isLeaf;
    }

    void sort(){
        for (size_t i = 0; i < 3; i++){
            for (size_t j = 0; j < 3; j++){
                if (data[j]>data[j+1])
                    swap(data[j],data[j]);
            }
        }
    }
    
    void insertIntoNode(int val, node* childPtr) {
        int i = pop - 1;
        
        // Shift values to make room
        // val will be inserted in a sorted order
        while (i >= 0 && data[i] > val) {
            data[i + 1] = data[i];
            children[i + 2] = children[i + 1]; // Shift children to match keys
            i--;
        }
        
        data[i + 1] = val;
        children[i + 2] = childPtr; // Place the new child to the right of the key
        pop++;
    }
    
    // Debug print
    void traverse() {
        int i;
        for (i = 0; i < pop; i++) {
            if (!leaf) children[i]->traverse();
            cout << " " << data[i];
        }
        if (!leaf) children[i]->traverse();
    }
};



/* 

if a node reaches limit, it will be split into 3 nodes, with 1 node being the parent of the two, and left node containing all keys less than root, and vice verse ...

*/
/*  

! INSERTION:
* keys are inserted, nodes are used for controls
* when inserted, they move to the bottom of the tree

EDGE CASE OF INSERTION:

? when the last node overflows
    - split it into 2 nodes, and move the middle key to above node, (all nodes will have their keys sorted)
    ? when parent overflows
        - then the middle key will be the new node, and the left will be left side of the prev node and for the right vice versa
        ! THIS IS THE ONLY CASE WHEN TREE GETS DEEPER
 */

 
bool insertInternal(node* cursor, int val, int &promotedKey, node* &newSibling) {
    if (cursor->leaf) {
        // Simple insert into leaf
        cursor->insertIntoNode(val, nullptr);
    } else {
        // Find which child to go down to
        int i = 0;
        while (i < cursor->pop && val > cursor->data[i]) {
            i++;
        }
        
        // Recursive call
        int childPromotedKey;
        node* childNewSibling = nullptr;
        bool childDidSplit = insertInternal(cursor->children[i], val, childPromotedKey, childNewSibling);
        
        if (childDidSplit) {
            // If the child split, we must insert the promoted key into THIS node
            cursor->insertIntoNode(childPromotedKey, childNewSibling);
        } else {
            return false; // No split happened below, we are done
        }
    }

    // CHECK OVERFLOW
    if (cursor->pop > KEYS) {
        // If this node is now full, split it and tell the parent
        split(cursor, promotedKey, newSibling);
        return true;
    }
    
    return false;
}


/* 

! DELETION
? what if the node crosses least keys threshold after deletion (<minimum)
- get key from sibling node
    - but doing directly can make the parent node wrong, 
    - all keys in parent act as "dividers"
    - instead, we will the key become the new divider in parent and the smaller key will sent to the smaller child, preserving the property of Btree
? what if all nodes are at minimum threshold
- we will then merge the sibling nodes together

? what if the key is from the middle of the BTree
- the middle area serves as divider for 2 nodes
- the key must be greater than the left subtree, and smaller than the right sub tree


*/



// use functions for generalized processes like split node

// the parent will have mult children, and a child cannot refer up back to parent, hence both are args
void split(node* cursor, int &promotedKey, node* &newSibling) {
    // 1. Create a new node for the right half
    newSibling = new node(cursor->leaf);
    
    // 2. Determine the middle index (For a 2-3 tree with 3 keys temporarily, mid is index 1)
    int midIndex = KEYS / 2; 
    promotedKey = cursor->data[midIndex]; // The key that goes up

    // 3. Move keys > mid to the new sibling
    // (In 2-3 tree: keys[0] stays, keys[1] goes up, keys[2] goes to new sibling)
    int siblingIdx = 0;
    for (int i = midIndex + 1; i < cursor->pop; i++) {
        newSibling->data[siblingIdx] = cursor->data[i];
        // Move corresponding children if not leaf
        if (!cursor->leaf) {
            newSibling->children[siblingIdx] = cursor->children[i];
        }
        siblingIdx++;
    }
    
    // Handle the last child pointer (often missed!)
    if (!cursor->leaf) {
        newSibling->children[siblingIdx] = cursor->children[cursor->pop];
    }

    newSibling->pop = siblingIdx;
    
    // 4. Resize the old node (cursor)
    cursor->pop = midIndex;
}



int main(){




    return 0;
}
