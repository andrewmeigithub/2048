#include <iostream>
#include <string>
#include <ctime> 
#include <windows.h>

using std::cout;

// rand spawning nums pos, grid numbers, score
int numX, numY, num, score;

// Grid 4 * 4
const int gridSize = 4;
int grid[gridSize][gridSize];
// Visualization of grid
/*
rows      columns
 0     {0, 1, 2, 3},
 1     {0, 1, 2, 3},
 2     {0, 1, 2, 3},
 3     {0, 1, 2, 3}
*/

//hoisting
void spawnNumber();
void draw();

// on start
void setup() {
    // init grid
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            grid[row][column] = 0;
        }
    }

    // start
    spawnNumber();
    draw();
}

// spawns a number on the grid
void spawnNumber() {
    // TO DO LIST:
    // change to make num change only when grid changes i.e. if the user presses up and there are no changes, no nums spawn
    // change to spawn 4s more frequently if score is higher

    srand((unsigned)time(0)); 
    
    int i = rand() % 5; // range 0-4
    if (i == 0) { // 1 in 5 chance
        num = 4;
    } else { // 4 in 5 chance
        num = 2;
    }

    numX = rand() % 4; // range 0-3
    numY = rand() % 4;

    // doesn't overwrite other numbers
    if (grid[numY][numX] == 0) {
        grid[numY][numX] = num;
    } else {
        return spawnNumber();
    }
}

// draws grid
void draw() {
    //goes down 50 lines
    for (int i = 1; i <= 50; i++) {
        cout << "\n";
    }

    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            cout << grid[row][column] << " ";
        }
        cout << "\n";
    }
}

bool gameOver() {
    int i = 0;
    for (int row = 1; row < gridSize - 1; row++) {
        for (int column = 1; column < gridSize-1; column++) {
            if (grid[column - 1][row - 1] == grid[column][row - 1] || grid[column + 1][row - 1] == grid[column][row - 1]) {
                break;
            } else if (row && column == 2) {
                i++;
            }
        }
    }
    for (int row = 1; row < gridSize - 1; row++) {
        for (int column = 1; column < gridSize; column++) {
            if (grid[column - 1][row] == grid[column - 1][row + 1] || row - 1 == row) {
                break;
            } else if (row == 2 && column == 3) {
                i++;
            }
        }
    }
    // resets variable
    if (i == 1) {
        i = 0;
    }

    if (i >= 2) {
        return 1;
    } else {
        return 0;
    }
}

// checks if there are any zeros left
bool isDone() {
    int i;
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            if (grid[row][column] != 0) {
                i++;
            }
        }
    }

    if (i == gridSize*gridSize) {
       return 1;
    }

    return 0;
}

// every move
void update(int dir) {
    switch(dir) {
        // up
        case 1:
            for (int i = 0; i < gridSize; i++) { 
                for (int row = 0; row < gridSize; row++) {
                    for (int column = 0; column < gridSize; column++) {
                        if (grid[row - 1][column] == grid[row][column]) {
                            // doubles the number
                            grid[row - 1][column] += grid[row][column];

                            grid[row][column] = 0;

                        }
                        // replaces 0s
                        if (grid[row - 1][column] == 0) {
                            grid[row - 1][column] = grid[row][column];

                            grid[row][column] = 0;
                        }
                    }
                }
            }

            break;
        // left
        case 2:
            for (int i = 0; i < gridSize; i++) {
                for (int row = 0; row < gridSize; row++) {
                    for (int column = 0; column < gridSize; column++) {
                        if (grid[row][column - 1] == grid[row][column]) {
                            // doubles the number
                            grid[row][column - 1] += grid[row][column];

                            grid[row][column] = 0;

                        }
                        // replaces 0s
                        if (grid[row][column - 1] == 0) {
                            grid[row][column - 1] = grid[row][column];
                            
                            grid[row][column] = 0;
                        }
                    }
                }
            }
            
            break;
        // down
        case 3:
            for (int i = 0; i < gridSize; i++) { 
                for (int row = 0; row < gridSize; row++) {
                    for (int column = 0; column < gridSize; column++) {
                        if (grid[row + 1][column] == grid[row][column]) {
                            // doubles the number
                            grid[row + 1][column] += grid[row][column];

                            grid[row][column] = 0;

                        }
                        // replaces 0s
                        if (grid[row + 1][column] == 0) {
                            grid[row + 1][column] = grid[row][column];
                            
                            grid[row][column] = 0;
                        }
                    }
                }
            }

            break;
        // right
        case 4:
            for (int i = 0; i < gridSize; i++) { 
                for (int row = 0; row < gridSize; row++) {
                    for (int column = 0; column < gridSize; column++) {
                        if (grid[row][column + 1] == grid[row][column]) {
                            // doubles the number
                            grid[row][column + 1] += grid[row][column];

                            grid[row][column] = 0;

                        }
                        // replaces 0s
                        if (grid[row][column + 1] == 0) {
                            grid[row][column + 1] = grid[row][column];

                            grid[row][column] = 0;
                        }
                    }
                }
            }

            break;
        default:
            cout << "\nError\n";
            gameOver();
    }
    spawnNumber();
    draw();

    if (isDone() == 1){
      gameOver();
    }
}

// events
void up() {
    update(1);
}

void left() {
    update(2);
}

void down() {
    update(3);
}

void right() {
    update(4);
}

// eventLoop
void eventLoop() {
    //keyboard inputs

    if(GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        up();
        Sleep(500);
    }
    if(GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        left();
        Sleep(500);
    }
    if(GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        down();
        Sleep(500);
    }
    if(GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        right();
        Sleep(500);
    }
}

int main() {
    setup();

    while (gameOver() == 0) {
        eventLoop();
        gameOver();
    }
    cout << "Game Over";

    return 0;
}
