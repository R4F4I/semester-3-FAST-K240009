#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST
{
public:
    Node* root;

    BST() : root(nullptr) {}

    Node *findMin(Node *current)
    {
        if (current == nullptr || current->left == nullptr)
        {
            return current;
        }
        return findMin(current->left);
    }

    Node* insert(Node* current, int val)
    {
        if (current == nullptr)
        {
            return new Node(val);
        }
        if (val < current->data)
        {
            current->left = insert(current->left, val);
        }
        else if (val > current->data)
        {
            current->right = insert(current->right, val);
        }
        return current;
    }

    bool search(Node *current, int key)
    {
        if (current == nullptr)
        {
            return false;
        }
        if (key == current->data)
        {
            return true;
        }
        if (key < current->data)
        {
            return search(current->left, key);
        }
        else
        {
            return search(current->right, key);
        }
    }

    Node* remove(Node *current, int key)
    {
        if (current == nullptr)
        {
            return current;
        }
        if (key < current->data)
        {
            current->left = remove(current->left, key);
        }
        else if (key > current->data)
        {
            current->right = remove(current->right, key);
        }
        else
        {
            if (current->left == nullptr)
            {
                Node *temp = current->right;
                delete current;
                return temp;
            }
            else if (current->right == nullptr)
            {
                Node *temp = current->left;
                delete current;
                return temp;
            }
            Node *temp = findMin(current->right);
            current->data = temp->data;
            current->right = remove(current->right, temp->data);
        }
        return current;
    }

    void inOrder(Node *current)
    {
        if (current != nullptr)
        {
            inOrder(current->left);
            cout << current->data << " ";
            inOrder(current->right);
        }
    }

    void preOrder(Node *current)
    {
        if (current != nullptr)
        {
            cout << current->data << " ";
            preOrder(current->left);
            preOrder(current->right);
        }
    }

    void postOrder(Node *current)
    {
        if (current != nullptr)
        {
            postOrder(current->left);
            postOrder(current->right);
            cout << current->data << " ";
        }
    }
};

int main()
{
    BST tree;

    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 70);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 40);

    tree.inOrder(tree.root);
    cout << endl;

    if (tree.search(tree.root, 40))
    {
        cout << "Found 40" << endl;
    }

    tree.root = tree.remove(tree.root, 50);

    tree.inOrder(tree.root);
    cout << endl;

    return 0;
}
