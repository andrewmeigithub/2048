#include <iostream>
#include <string>
#include <ctime> 
#include <windows.h>

using std::cout;

int gameOver;
bool keyPressed = false;

//head pos, rand spawning nums pos, score
int x, y, numX, numY, score;

// enum eDir {LEFT = 0, RIGHT, UP, DOWN};

//Grid
const int gridSize = 4;
int grid[gridSize][gridSize];

void setup() {
    gameOver = 0;
    x, y = gridSize / 2;

    srand((unsigned)time(0)); 

    numX = rand() % 4 + 1; //range of 1-4
    numY = rand() % 4 + 1;

    for (int column = 0; column < gridSize; column++) {
        for (int row = 0; row < gridSize; row++) {
            grid[column][row] = 0;
            cout << grid[column][row] << " ";
        }
        cout << "\n";
    }

}

void draw(){

    

}

void up() {
    cout << "W pressed \n";
    keyPressed = false;
}

void left() {
    cout << "A pressed \n";
}

void down() {
    cout << "S pressed \n";
}

void right() {
    cout << "D pressed \n";
}

void logic() {

    //detect gameOver
    for (int column = 1; column < gridSize - 1; column++) {
        for (int row = 1; row < gridSize-1; row++) {
            if (grid[row - 1][column - 1] == grid[row][column - 1] || grid[row + 1][column - 1] == grid[row][column - 1]) {
                break;
            } else {
                gameOver++;
            }
        }
    }
    for (int column = 1; column < gridSize - 1; column++) {
        for (int row = 1; row < gridSize; row++) {
            if (grid[row - 1][column] == grid[row - 1][column + 1] || column - 1 == column) {
                break;
            }/* else if (column == 0) {
                if (column - 1 == column) {
                    break;
                }
            } else if (column == gridSize-1) {
                if (column + 1 == column) {
                    break;
                }
            }*/ else {
                gameOver++;
            }
        }
    }

    //keyboard inputs
    if(GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        if (!keyPressed) {
            up();
        } else {
            keyPressed = false;
        }
    }

    if(GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        left();
    }

    if(GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        down();
    }

    if(GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        right();
    }


}

int main() {

    setup();
    draw();

    while (gameOver < 1) {
        logic();
    }
    cout << "Game Over";

    return 0;

}
