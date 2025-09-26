#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stack>
#include <random>
#include <thread>

#define BG_GREY   "\033[40m"
#define BG_GREEN "\033[42m"
#define RESET    "\033[0m"

using namespace std;


class crawl{


public:

    int X,Y, dir;

    crawl(int x, int y, int dir){
        X=x;
        Y=y;
        this->dir = dir;
    }

    void move(){
        
        if (dir == 5)
        {
            dir=1; // to prevent overflow
            
        }

        switch (dir)
        {
        case 1:
            Y--; // up
            break;
        
        case 2:
            Y++; // down
            break;
        
        case 3:
            X--; // left
            break;
        
        case 4:
            X++; //right
            break;
        
        default:
            break;
        }
    }

    void backtrack(){
        
        if (dir == 5)
        {
            dir=1; // to prevent overflow
        }

        switch (dir)
        {
        case 1:
            Y++; // up
            break;
        
        case 2:
            Y--; // down
            break;
        
        case 3:
            X++; // left
            break;
        
        case 4:
            X--; //right
            break;
        
        default:
            break;
        }
        
    }

};

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            if (cell=='.')
            {
                cout << BG_GREEN << "  "<<RESET;
            } else if (cell=='#')
            {
                cout << BG_GREY << "  "<<RESET;
            
            }
            else{
                cout << cell << " ";

            }
            
        }
        cout << endl;
    }
    // Moves the cursor back up to the top of the maze to create an animation effect
    // Note: This might not work on all terminals (e.g., Windows cmd prompt).
    // A simpler alternative is system("cls") on Windows or system("clear") on Linux/macOS.
    cout << "\033[" << maze.size() << "A";
    cout << "\033[" << maze[0].size() * 2 << "D";
    // this_thread::sleep_for(chrono::milliseconds(50)); // Pause to make it watchable
}

bool solve_maze(vector<vector<char>>& maze,int currX,int currY,int tarX, int tarY){

    // base cases
    
    if (
        currY < 0 || currY >= maze.size() || 
        currX < 0 || currX >= maze[0].size()
    ) 
    {
        return false; // Fell off the maze
    }

    // check if path is already visited or wall
    if (
        maze[currY][currX]=='#' ||
        maze[currY][currX]=='.' 
    )
    {
        return false;
    }
    
    
    maze[currY][currX] = '.';
    
    printMaze(maze);
    
    if (
        currX == tarX &&
        currY == tarY 
    )
    {
        maze[currY][currX] = 'E';
        return true;
    }
    
    // --- RECURSIVE STEP ---
    // Try to move in all 4 directions: Down, Right, Up, Left

    // Try moving DOWN (Y + 1)
    if (solve_maze(maze,  currX, currY + 1,tarX, tarY)) {
        return true;
    }

    // Try moving RIGHT (X + 1)
    if (solve_maze(maze,  currX + 1, currY,tarX, tarY)) {
        return true;
    }

    // Try moving UP (Y - 1)
    if (solve_maze(maze,  currX, currY - 1,tarX, tarY)) {
        return true;
    }

    // Try moving LEFT (X - 1)
    if (solve_maze(maze,  currX - 1, currY,tarX, tarY)) {
        return true;
    }
    
    // back tracking
    maze[currY][currX] = ' ';
    printMaze(maze);
    return false;
}


void generateMaze(vector<vector<char>>& maze, int width, int height) {
    // Initialize the grid with walls
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            maze[y][x] = '#';
        }
    }

    // Modern C++ random number setup
    random_device rd;
    mt19937 g(rd());

    // Stack for backtracking
    std::stack<pair<int, int>> cell_stack;

    // 1. Choose a random starting cell (must be at an odd coordinate)
    int startX = 1;
    int startY = 1;
    maze[startY][startX] = ' '; // Mark as path
    cell_stack.push({startX, startY});

    // Array to hold neighbor directions [dx, dy]
    int dirs[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}};

    while (!cell_stack.empty()) {
        pair<int, int> current = cell_stack.top();
        
        vector<int> neighbors;

        // Check for unvisited neighbors (2 cells away)
        for (int i = 0; i < 4; ++i) {
            int nx = current.first + dirs[i][0];
            int ny = current.second + dirs[i][1];

            if (nx > 0 && nx < width - 1 && ny > 0 && ny < height - 1 && maze[ny][nx] == '#') {
                neighbors.push_back(i);
            }
        }

        if (!neighbors.empty()) {
            // There are unvisited neighbors
            std::shuffle(neighbors.begin(), neighbors.end(), g); // Randomize neighbor choice
            int chosen_dir_index = neighbors[0];
            
            int nx = current.first + dirs[chosen_dir_index][0];
            int ny = current.second + dirs[chosen_dir_index][1];

            // Knock down the wall between current and neighbor
            int wallX = current.first + dirs[chosen_dir_index][0] / 2;
            int wallY = current.second + dirs[chosen_dir_index][1] / 2;
            maze[wallY][wallX] = ' ';
            
            // Mark the neighbor as visited
            maze[ny][nx] = ' ';
            
            // Push neighbor to stack
            cell_stack.push({nx, ny});
        } else {
            // No unvisited neighbors, backtrack
            cell_stack.pop();
        }
    }

    // Create an entrance and an exit
    maze[1][0] = 'S'; // Start
    maze[height - 1][width - 2] = ' '; // End
    maze[height - 1][width - 1] = ' '; // End
    maze[height - 2][width - 2] = ' '; // End
    maze[height - 2][width - 1] = 'E'; // End
}


int main() {
    std::cout << "\033[?25l" << std::endl;// hide cursor
    // Assuming the image represents a 20x20 maze
    // We'll manually create the 2D array based on the provided image 
    // '#' represents a wall/boundary, ' ' represents a path 

    std::vector<std::vector<char>> maze = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#',' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#',' ', '#', ' ', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#','#', ' ', '#', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#',' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#','#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#','#', ' ', '#', ' ', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#','#', ' ', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', '#','#', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#','#', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' ', '#','#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#',' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#',' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#',' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#',' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#',' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#',' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#',' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#'}
    };

    // std::vector<std::vector<char>> maze;
    generateMaze(maze,25,25);


    // std::vector<std::vector<char>> renderedMaze = maze;


    // Print the maze to verify
    // for (int i = 0; i < 20; ++i) {
    //     for (int j = 0; j < 20; ++j) {
    //         std::cout << maze[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    
    // crawl target(18,18,0);
    // crawl crawler(1,1,4);

    for (size_t i = 0; i < 25; i++)
    {
        for (size_t j = 25*i; j < 25+ i*25; j++)
        {
            std::cout <<"0 ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;

    int startX=1;
    int startY=1;
    int targetX=24;
    int targetY=24;

    // solve_maze(maze,startX,startY,targetX,targetY);

    return 0;
}