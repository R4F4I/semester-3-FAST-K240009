/*

consider the below maze , start from 0, 0 and target is to reach at (2, 0)(*). Write a back trakng code in
c++ to achieve this. Note that 1 is open and 0 is blocked.
Maze
1 1 1 1
0 0 0 1
* 1 0 1
1 1 1 1

* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A

! 0 = obstacle
! 1 = open path
! 2 = traveled path
! 3 = final dest



*/

#include <iostream>

using namespace std;

void printMaze(int **arr, int size){
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            cout << arr[i][j] <<" ";
        }
        std::cout << std::endl;
    }
    cout << "\033[4A";
    cout << "\033[4D";
}


bool solve
    (
        int **arr,
        int X, int Y ,      // size
        int spX,int spY,    // starting point
        int epX,int epY     // ending   point
    )
    {
        if 
        (
            spX==epX &&
            spY==epY
        )
        {
            arr[spY][spX] = 3;
            return true;
        }
        if 
        (
            spX<0 || spX>=X ||
            spY<0 || spY>=Y
        )
        {
            return false;
        }

        if 
        (
            arr[spY][spX]==0 || 
            arr[spY][spX]==2 // 2 for traveled, to prevent moving in a circle
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

        arr[spY][spX] = 1;
        return false;

}

int main(){


    int **maze=new int*[4];
    for (size_t i = 0; i < 4; i++)
    {
        maze[i] = new int[4];
    }
 
    /* 
    1 1 1 1
    0 0 0 1
    1 1 0 1
    1 1 1 1
    */
    
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            maze[i][j]=1;
        }
        
    }
    maze[1][0]=0;
    maze[1][1]=0;
    maze[1][2]=0;
    maze[2][2]=0;

    solve(maze,4,4,0,0,0,2);

    std::cout << "solved:" << std::endl;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cout << maze[i][j] <<" ";
        }
        cout<<endl;
    }

    return 0;
}