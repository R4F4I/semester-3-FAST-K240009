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
#include <iostream>
#include <cstdlib>  // for randomness
#include <ctime>    // for seeding

using namespace std;

// Function Prototypes
void playGameRecursive(int targetNumber, int currentPlayer);
int getValidGuess(int currentPlayer);

void playGameRecursive(int targetNumber, int currentPlayer) {
    int guess = getValidGuess(currentPlayer);

    if (guess == targetNumber) {
        cout << "Player " << currentPlayer << " Wins! The number was " << targetNumber << "!" << endl;
    } else {
        if (guess < targetNumber) {
            cout << "LOW! The target number is higher than " << guess << "." << endl;
        } else {
            cout << "HIGH! The target number is lower than " << guess << "." << endl;
        }

        int nextPlayer = (currentPlayer+1) % 2;
        cout << "Turn passes to Player " << nextPlayer << ".\n" << endl;

        playGameRecursive(targetNumber, nextPlayer);
    }
}

int getValidGuess(int currentPlayer) {
    int guess;

    while (true) {
        cout << "Player " << currentPlayer << ", enter your guess (1-100): ";

        if (cin >> guess) {
            if (guess >= 1 && guess <= 100) {
                return guess;
            } else {
                cout << "Invalid range! Please enter a number between 1 and 100." << endl;
            }
        } else {
            cout << "Invalid input! Please enter an integer." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int main() {
    srand(time(0));

    const int TARGET_NUMBER = (rand() % 100) + 1;

    cout << "Number Guessing Game!" << endl;
    cout << "Two players will guess a number between 1 and 100." << endl;

    playGameRecursive(TARGET_NUMBER, 1);

    cout << "\nGame Over. Thanks for playing!" << endl;

    return 0;
}