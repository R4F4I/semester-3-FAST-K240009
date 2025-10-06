/*

Task # 8: Imagine a 4x4 grid where a person is on a mission to collect as many flags as possible.
Each cell of the grid represents a potential location for placing a flag. However, there are constraints:
Only one flag can be placed in each row or column.
Additionally, no two flags can ever be placed on the same diagonal (i.e., no two flags can threaten
each other diagonally).
Your goal is to design a backtracking algorithm in C++ to help this person maximize the number of
flags collected while adhering to these constraints. After implementing the algorithm, provide the
code and report the maximum number of flags that can be placed on the 4x4 grid.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

// nxn queens bktrking

bool isSafe(int** board, int size, int row, int col) {
    int i, j;

    // 1. Check this row on the left side
    for (i = 0; i < col; i++) {
        if (board[row][i] == 1) {
            return false;
        }
    }

    // 2. Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    // 3. Check lower diagonal on the left side
    for (i = row, j = col; i < size && j >= 0; i++, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}


bool solveNQueensUtil(int** board, int size, int col) {
    // Base Case: If all columns are filled, we've found a solution.
    if (col >= size) {
        return true;
    }

    // Try placing a queen in every row of the current column
    for (int row = 0; row < size; row++) {
        if (isSafe(board, size, row, col)) {
            // 1. Place the Queen (Choose)
            board[row][col] = 1;

            // 2. Recurse to the next column (Explore)
            if (solveNQueensUtil(board, size, col + 1)) {
                return true; // Solution found!
            }

            // 3. Backtrack (Unchoose): If the recursive call failed, remove the queen
            board[row][col] = 0;
        }
    }

    // If no row in this column works, return false to backtrack to the previous column.
    return false;
}

void printSolution(int** board, int size) {
    cout << "\nA Solution for N = " << size << " found:" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Print 'Q' for Queen, '.' for empty
            cout << (board[i][j] ? 'Q' : '.') << " ";
        }
        cout << endl;
    }
}


bool solve(int* arr[], int size){


    // int** board = reinterpret_cast<int**>(arr);

    if (size <= 0) {
        cout << "Error: Board size must be greater than 0." << endl;
        return false;
    }
    std::cout << "-";

    // Start the recursive process from the first column (col = 0)
    if (solveNQueensUtil(arr, size, 0) == false) {
        cout << "Solution does not exist for N = " << size << endl;
        return false;
    }

    // A solution was found and the arr is updated, so we print it.
    printSolution(arr, size);
    return true;


}

int main(){


    int N = 25;

    int **grid=new int*[N];
    for (size_t i = 0; i < N; i++)
    {
        grid[i] = new int[N];
    }
 
    
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            grid[i][j]=0;
        }
        
    }

    solve(grid, N); 


    return 0;
}