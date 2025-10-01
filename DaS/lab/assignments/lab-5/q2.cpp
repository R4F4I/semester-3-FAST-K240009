/*

Assume you are developing a program to simulate a game where players take turns to guess
a number between 1 and 100. The program generates a random number between 1 and 100 at the start
of the game, and the player who guesses the correct number wins the game. If a player guesses
incorrectly, the program tells them whether their guess was too high or too low, and the turn passes
to the next player. Solve it using Direct Recursion?

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <algorithm> // For std::min

using namespace std;

// This function determines if the *current player* can win given 'stones_left'.
// 'true' means the current player can force a win.
// 'false' means the current player will lose if the opponent plays optimally.
bool canWin(int stones_left) {
    // 1. Base Case (Stopping Condition)
    // If there are 0 stones left, the previous player took the last stone and won.
    // The current player has no moves, so they lose.
    if (stones_left == 0) {
        return false;
    }

    // 2. Recursive Step (Try all valid moves)
    
    // The current player can take 1, 2, or 3 stones, 
    // but they cannot take more than are available.
    int max_take = min(3, stones_left);

    // The current player wins if ANY move leads to a state where 
    // the next player (opponent) LOSES.
    for (int k = 1; k <= max_take; ++k) {
        
        // Stones remaining after the current player takes k stones
        int remaining_stones = stones_left - k;

        // Check if the resulting state for the opponent is a LOSING state.
        // If canWin(remaining_stones) is FALSE, it means the opponent loses from that state.
        if (!canWin(remaining_stones)) {
            // Found a winning move! The current player should take 'k' stones.
            return true;
        }
    }

    // 3. Losing Condition
    // If the loop finishes, it means ALL possible moves lead to a state where 
    // the opponent canWin (the current player loses).
    return false;
}

int main() {
    int N;
    cout << "Enter the initial number of stones: ";
    
    // Read the number of stones from the user
    if (!(cin >> N) || N < 0) {
        cout << "Invalid input. Please enter a non-negative integer." << endl;
        return 1;
    }

    cout << "\nSimulating game with " << N << " stones..." << endl;

    if (canWin(N)) {
        cout << "Player 1 (starting player) will WIN." << endl;
        // Optional: Show the winning pattern (N % 4 != 0)
        if (N % 4 == 0) {
             cout << "ERROR in logic! The simple mathematical solution (N % 4 != 0) suggests losing." << endl;
             cout << "Note: This direct recursion is correct, but extremely slow for large N." << endl;
        }
    } else {
        cout << "Player 1 (starting player) will LOSE (Player 2 will win)." << endl;
        // Optional: Show the losing pattern (N % 4 == 0)
        if (N % 4 != 0) {
            cout << "ERROR in logic! The simple mathematical solution (N % 4 != 0) suggests winning." << endl;
        }
    }

    return 0;
}