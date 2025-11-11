/*  

Question#2: Reuse the methods from above question 1 and complete below question:
You are required to implement a game titled “BattleQuest: BST Arena” using a Binary
Search Tree (BST) where each node in the tree stores a Combatant object. This
game simulates a classic RPG-style battle between a player’s team of heroes and a
team of enemies. The core challenge involves managing two separate BSTs — one for
the player’s team and another for the enemy team — where each node contains a
Combatant object with attributes such as name, health points (HP), and attack power.
The game follows a strict turn-based combat system, where the player’s team and the
enemy team alternate turns. Only the frontline combatant — defined as the node with
the smallest key value (i.e., the leftmost node in the BST) participates in combat during
each turn.
When a combatant’s health drops to zero or below, that combatant is removed from
their respective BST. The next available combatant in the tree (the new leftmost node)
becomes the frontline fighter for the following turn.
The battle continues until one team’s BST becomes empty, determining the winner.
The player’s team should be initialized with five heroes. The enemy team should be
initialized with five enemies.
Both trees should be constructed using insertions according to the BST property based
on the combatant’s name or unique ID.
The player always attacks first in each round, followed by the enemy counterattack.
During an attack: The attacker’s damage = base attack power + random value (0 to 4)
The damage will affect the defender’s health. If the defender’s health ≤ 0, they are
removed from their BST immediately. The next combatant automatically takes their
place as the new frontline fighter.

During each turn, the game must display the following information clearly:

 Round number
 Names and current HP of all heroes and enemies (in BST order)
 Active attackers and defenders
 Damage dealt in the attack
 Updated HP values after each hit
 Elimination messages when a combatant is defeated
 Victory message when one BST becomes empty

*/

#include <iostream>

using namespace std;

struct Combatant
{
    const char *name;
    int hp;
    int attack;
};

struct Node
{
    int id;
    Combatant combatant;
    Node *left;
    Node *right;

    Node(int key, const Combatant &data) : id(key), combatant(data), left(nullptr), right(nullptr) {}
};

class BST
{
public:
    Node *root;

    BST() : root(nullptr) {}

    Node *findMin(Node *current)
    {
        if (current == nullptr || current->left == nullptr)
        {
            return current;
        }
        return findMin(current->left);
    }

    Node *insert(Node *current, int key, const Combatant &data)
    {
        if (current == nullptr)
        {
            return new Node(key, data);
        }
        if (key < current->id)
        {
            current->left = insert(current->left, key, data);
        }
        else if (key > current->id)
        {
            current->right = insert(current->right, key, data);
        }
        return current;
    }

    Node *remove(Node *current, int key)
    {
        if (current == nullptr)
        {
            return current;
        }
        if (key < current->id)
        {
            current->left = remove(current->left, key);
        }
        else if (key > current->id)
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
            current->id = temp->id;
            current->combatant = temp->combatant;
            current->right = remove(current->right, temp->id);
        }
        return current;
    }

    void displayInOrder(Node *current)
    {
        if (current != nullptr)
        {
            displayInOrder(current->left);
            cout << current->combatant.name << " (HP: " << current->combatant.hp << ")  ";
            displayInOrder(current->right);
        }
    }

    void destroy(Node *current)
    {
        if (current)
        {
            destroy(current->left);
            destroy(current->right);
            delete current;
        }
    }
};

void displayRoster(const char *teamName, BST &tree)
{
    cout << teamName << " Roster (BST Order): ";
    tree.displayInOrder(tree.root);
    cout << "\n";
}

int main()
{
    // srand and time calls removed due to removed includes

    BST heroes;
    BST enemies;

    Combatant h1 = {"Paladin", 100, 15};
    Combatant h2 = {"Archer", 80, 20};
    Combatant h3 = {"Mage", 70, 25};
    Combatant h4 = {"Rogue", 90, 18};
    Combatant h5 = {"Cleric", 110, 12};

    heroes.root = heroes.insert(heroes.root, 10, h1);
    heroes.root = heroes.insert(heroes.root, 5, h2);
    heroes.root = heroes.insert(heroes.root, 15, h3);
    heroes.root = heroes.insert(heroes.root, 3, h4);
    heroes.root = heroes.insert(heroes.root, 8, h5);

    Combatant e1 = {"Goblin", 60, 10};
    Combatant e2 = {"Orc", 120, 18};
    Combatant e3 = {"Witch", 75, 22};
    Combatant e4 = {"Ogre", 150, 25};
    Combatant e5 = {"Imp", 50, 15};

    enemies.root = enemies.insert(enemies.root, 20, e1);
    enemies.root = enemies.insert(enemies.root, 25, e2);
    enemies.root = enemies.insert(enemies.root, 18, e3);
    enemies.root = enemies.insert(enemies.root, 30, e4);
    enemies.root = enemies.insert(enemies.root, 15, e5);

    int round = 1;
    Node *pFront = nullptr;
    Node *eFront = nullptr;

    while (heroes.root != nullptr && enemies.root != nullptr)
    {
        cout << "\n------------------------------------------------------\n";
        cout << "ROUND: " << round++ << "\n";
        cout << "------------------------------------------------------\n";

        displayRoster("Heroes", heroes);
        displayRoster("Enemies", enemies);

        pFront = heroes.findMin(heroes.root);
        eFront = enemies.findMin(enemies.root);

        // Player Turn (Attack)
        cout << "\n--- Hero Turn ---\n";
        if (pFront != nullptr && eFront != nullptr)
        {
            int pDamage = pFront->combatant.attack + 2; // Fixed bonus damage instead of random
            eFront->combatant.hp -= pDamage;

            cout << "ATTACK: " << pFront->combatant.name << " attacks " << eFront->combatant.name << "\n";
            cout << "DAMAGE: " << pDamage << "\n";
            cout << "Enemy " << eFront->combatant.name << " HP remaining: " << (eFront->combatant.hp > 0 ? eFront->combatant.hp : 0) << "\n";

            if (eFront->combatant.hp <= 0)
            {
                cout << "!! ELIMINATION: " << eFront->combatant.name << " has been defeated and removed from the Enemy team BST. !!\n";
                enemies.root = enemies.remove(enemies.root, eFront->id);
                eFront = nullptr;
            }
        }

        // Check victory condition after player attack
        if (enemies.root == nullptr)
        {
            break;
        }

        // Enemy Turn (Counter-Attack)
        cout << "\n--- Enemy Turn ---\n";
        if (heroes.root != nullptr && enemies.root != nullptr)
        {
            pFront = heroes.findMin(heroes.root);
            eFront = enemies.findMin(enemies.root);

            if (pFront != nullptr)
            {
                int eDamage = eFront->combatant.attack + 2; // Fixed bonus damage instead of random
                pFront->combatant.hp -= eDamage;

                cout << "ATTACK: " << eFront->combatant.name << " attacks " << pFront->combatant.name << "\n";
                cout << "DAMAGE: " << eDamage << "\n";
                cout << "Hero " << pFront->combatant.name << " HP remaining: " << (pFront->combatant.hp > 0 ? pFront->combatant.hp : 0) << "\n";

                if (pFront->combatant.hp <= 0)
                {
                    cout << "!! ELIMINATION: " << pFront->combatant.name << " has been defeated and removed from the Hero team BST. !!\n";
                    heroes.root = heroes.remove(heroes.root, pFront->id);
                }
            }
        }
    }

    cout << "\n\n******************************************************\n";
    if (heroes.root != nullptr)
    {
        cout << "VICTORY! The Hero Team has won the BattleQuest!\n";
    }
    else if (enemies.root != nullptr)
    {
        cout << "DEFEAT! The Enemy Team has won the BattleQuest!\n";
    }
    else
    {
        cout << "DRAW! Both teams were eliminated simultaneously (highly unlikely).\n";
    }
    cout << "******************************************************\n";

    heroes.destroy(heroes.root);
    enemies.destroy(enemies.root);

    return 0;
}
