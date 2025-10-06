/*

Task # 7 : Imagine you are given a grid representing a maze, where '0's represent obstacles(red
highlighted) or walls, and '1's represent open paths or empty cells. You have two arrays at your
disposal: an empty Solution array and a maze represented by the following grid:

0 1 0 1 0
0 0 0 0 0
1 0 1 0 0
0 1 1 0 0
0 0 0 1 0


Your task is to guide a lion through this maze from the starting point at (0, 0) to reach a piece of meat
located at the destination point (4, 4). The lion is also not allowed to move diagonally. The lion can
only move through open paths ('1's) while avoiding obstacles ('0's).
Please provide a C++ code that uses a backtracking algorithm to navigate the maze and move the lion
to the meat. Additionally, display the contents of the Solution array after the lion has reached the
meat.

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>

using namespace std;

bool solve
    (
        int **arr,
        int X, int Y ,          // size
        int spX,int spY,        // starting point
        int epX,int epY         // ending   point
    )
    {
        if 
        (
            spX==epX &&
            spY==epY
        )
        {
            arr[spY][spX] = 3;  // mark the reached place
            return true;
        }
        if 
        (
            spX<0 || spX>=X ||  // out bounds checking
            spY<0 || spY>=Y
        )
        {
            return false;
        }

        if 
        (
            arr[spY][spX]==1 || // 1 for obstacle
            arr[spY][spX]==2    // 2 for traveled, to prevent moving in a circle
        )
        {
            return false;
        }
        
        arr[spY][spX] = 2; // mark that point as traveled
        std::cout << spX <<" "<<spY<< std::endl;
        // printMaze(arr,X);
        // RECURSIVE PART
        if (solve(arr,X,Y, spX, spY + 1,epX, epY)) {
            return true;
        }

        // Try moving RIGHT (X + 1)
        if (solve(arr,X,Y, spX + 1, spY,epX, epY)) {
            return true;
        }

        // Try moving UP (Y - 1)
        if (solve(arr,X,Y, spX, spY - 1,epX, epY)) {
            return true;
        }

        // Try moving LEFT (X - 1)
        if (solve(arr,X,Y, spX - 1, spY,epX, epY)) {
            return true;
        }

        arr[spY][spX] = 0;  // backtracking
        return false;

}

int main(){


    int **maze=new int*[5];
    for (size_t i = 0; i < 5; i++)
    {
        maze[i] = new int[5];
    }
 
    /* 
    
    0 1 0 1 0
    0 0 0 0 0
    1 0 1 0 0
    0 1 1 0 0
    0 0 0 1 0

    */
    
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            maze[i][j]=0;
        }
        
    }
    maze[0][1]=1;
    maze[0][3]=1;
    maze[2][0]=1;
    maze[2][2]=1;
    maze[3][1]=1;
    maze[3][2]=1;
    maze[4][3]=1;



    
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            cout << maze[i][j] <<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    std::cout << "steps:" << std::endl;
    solve(maze,5,5,0,0,4,4);
    
    cout<<endl;
    std::cout << "solved:" << std::endl;

    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            cout << maze[i][j] <<" ";
        }
        cout<<endl;
    }

    return 0;
}