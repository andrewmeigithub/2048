#include <iostream>
#include <string>
#include <ctime> 
#include <windows.h>

using std::cout;

int gameOver = 0;

//rand spawning nums pos, grid numbers, score
int numX, numY, num, score;

//Grid
const int gridSize = 4;
int grid[gridSize][gridSize];

void setup() {
    gameOver = 0;

    srand((unsigned)time(0)); 


    numX = rand() % 4; //range of 0-3
    numY = rand() % 4;

    //prints grid
    for (int column = 0; column < gridSize; column++) {
        for (int row = 0; row < gridSize; row++) {
            grid[column][row] = 0;
            cout << grid[column][row] << " ";
        }
        cout << "\n";
    }


}

void draw(){
    //random generating nums (///////////////////////////////////////////////
                //change to make num change only when grid changes//
    ////////////////////////////////////////////////////////////////////////)
    int i = rand() % 3;
    if (i == 0) {
        num = 2;
    } else {
        num = 4;
    }

    //changes grid
    grid[numY][numX] = num;
    system("cls");
    for (int column = 0; column < gridSize; column++) {
        for (int row = 0; row < gridSize; row++) {
            cout << grid[column][row] << " ";
        }
        cout << "\n";
    }

}

void up() {
    draw();
    cout << "Up";
}

void left() {
    draw();
    cout << "Left";
}

void down() {
    draw();
    cout << "Down";
}

void right() {
    draw();
    cout << "Right";
}

void logic() {

    //detect gameOver
    for (int column = 1; column < gridSize - 1; column++) {
        for (int row = 1; row < gridSize-1; row++) {
            if (grid[row - 1][column - 1] == grid[row][column - 1] || grid[row + 1][column - 1] == grid[row][column - 1]) {
                break;
            } else if (column && row == 2) {
                gameOver++;
            }
        }
    }
    for (int column = 1; column < gridSize - 1; column++) {
        for (int row = 1; row < gridSize; row++) {
            if (grid[row - 1][column] == grid[row - 1][column + 1] || column - 1 == column) {
                break;
            } else if (column == 2 && row == 3) {
                gameOver++;
            }
        }
    }
    int i;
    for (int column = 0; column < gridSize; column++) {
        for (int row = 0; row < gridSize; row++) {
            if (grid[column][row] != 0) {
                i++;
                if (i == 16) {
                    gameOver++;
                }
            }
        }
    }
    if (gameOver > 3) {
        gameOver = 0;
    }

    //keyboard inputs
    if(GetKeyState('W') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
        up();
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

    while (gameOver < 4) {
        logic();
    }
    cout << "Game Over";

    return 0;

}
