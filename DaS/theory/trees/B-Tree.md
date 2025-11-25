# B-Tree
-suppose a 2,3 tree
- where a `node` contains **2** `keys` max, and can point to **3** other keys
- if a node reaches limit, it will be split into 3 nodes, with 1 node being the parent of the two, and left node containing all keys less than root, and vice verse ...

# INSERTION:
- keys are inserted, nodes are used for controls
- when inserted, they move to the bottom of the tree

## EDGE CASE OF INSERTION:

- *when the last node overflows:*
    - split it into 2 nodes, and move the middle key to above node, (all nodes will have their keys sorted)
    - *when parent overflows:*
        - then the middle key will be the new node, and the left will be left side of the prev node and for the right vice versa
        >[!NOTE] THIS IS THE ONLY CASE WHEN TREE GETS DEEPER
 

# DELETION
## what if the node crosses least keys threshold after deletion (<minimum) ?
- get key from sibling node
    - but doing directly can make the parent node wrong, 
    - all keys in parent act as "dividers"
    - instead, we will the key become the new divider in parent and the smaller key will sent to the smaller child, preserving the property of Btree
## what if all nodes are at minimum threshold?
- we will then merge the sibling nodes together

## what if the key is from the middle of the BTree
- the middle area serves as divider for 2 nodes
- the key must be greater than the left subtree, and smaller than the right sub tree
