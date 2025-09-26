#include <iostream>
#include <vector>
#include <chrono> // For sleeping
#include <thread> // For sleeping

using namespace std;

// Function to print the maze for visualization
void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    // Moves the cursor back up to the top of the maze to create an animation effect
    // Note: This might not work on all terminals (e.g., Windows cmd prompt).
    // A simpler alternative is system("cls") on Windows or system("clear") on Linux/macOS.
    cout << "\033[" << maze.size() << "A";
    cout << "\033[" << maze[0].size() * 2 << "D";
    this_thread::sleep_for(chrono::milliseconds(50)); // Pause to make it watchable
}

/**
 * Solves the maze using recursion and backtracking.
 * @param maze The maze grid. Passed by reference to persist changes.
 * @param targetX The target X-coordinate (column).
 * @param targetY The target Y-coordinate (row).
 * @param currentX The current X-coordinate of the crawler.
 * @param currentY The current Y-coordinate of the crawler.
 * @return true if a path to the target is found, false otherwise.
 */
bool solve_maze(vector<vector<char>>& maze, int targetX, int targetY, int currentX, int currentY) {
    
    // --- BASE CASES (Stopping Conditions) ---

    // 1. Check for out-of-bounds
    if (currentY < 0 || currentY >= maze.size() || currentX < 0 || currentX >= maze[0].size()) {
        return false; // Fell off the maze
    }

    // 2. Check for a wall ('#') or an already visited path ('.')
    if (maze[currentY][currentX] == '#' || maze[currentY][currentX] == '.') {
        return false; // Hit a wall or went in a circle
    }
    
    // Mark the current path as visited
    maze[currentY][currentX] = '.';

    // Print the maze to show the crawler's progress
    printMaze(maze);
    
    // 3. Check if we've reached the target (Success!)
    if (currentX == targetX && currentY == targetY) {
        maze[currentY][currentX] = 'E'; // Mark the end
        return true; 
    }

    // --- RECURSIVE STEP ---
    // Try to move in all 4 directions: Down, Right, Up, Left

    // Try moving DOWN (Y + 1)
    if (solve_maze(maze, targetX, targetY, currentX, currentY + 1)) {
        return true;
    }

    // Try moving RIGHT (X + 1)
    if (solve_maze(maze, targetX, targetY, currentX + 1, currentY)) {
        return true;
    }

    // Try moving UP (Y - 1)
    if (solve_maze(maze, targetX, targetY, currentX, currentY - 1)) {
        return true;
    }

    // Try moving LEFT (X - 1)
    if (solve_maze(maze, targetX, targetY, currentX - 1, currentY)) {
        return true;
    }

    // --- BACKTRACKING STEP ---
    // If none of the 4 directions led to a solution, this path is a dead end.
    // Un-mark the spot and return false to signal failure up the recursion chain.
    maze[currentY][currentX] = ' '; // Un-mark path
    printMaze(maze); // Show the backtracking step
    return false;
}

int main() {
    vector<vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'S', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', 'E', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };

    // Define start and target coordinates (Remember: X is column, Y is row)
    int startX = 1;
    int startY = 1;
    int targetX = 18;
    int targetY = 18;
    
    // I replaced the target character in the maze with 'E' for clarity
    // and the starting point with 'S'
    maze[startY][startX] = 'S';
    maze[targetY][targetX] = ' '; // Ensure target is a walkable space initially


    // Clear the screen before starting
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (solve_maze(maze, targetX, targetY, startX, startY)) {
        cout << "Solution Found!" << endl;
        // Final print of the solved maze without cursor manipulation
        for (const auto& row : maze) {
            for (char cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}