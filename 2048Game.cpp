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
//Visualization of grid
/*
{
rows      columns
 0     {0, 1, 2, 3},
 1     {0, 1, 2, 3},
 2     {0, 1, 2, 3},
 3     {0, 1, 2, 3}
}
*/





void setup() {
    gameOver = 0;

    //prints grid
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            grid[row][column] = 0;
            cout << grid[row][column] << " ";
        }
        cout << "\n";
    }


}





//random generating nums 
void randNums() {
    //TO DO LIST:
    //=======================================================================================================================
    //change to make num change only when grid changes i.e. if the user presses up and there are no changes, no nums spawn//
    //change to not overwrite other numbers//
    //change to spawn more 4s if score is higher//
    //=======================================================================================================================

    srand((unsigned)time(0)); 
    
    int i = rand() % 5; //range 0-4
    if (i == 0) { //1 in 5 chance
        num = 4;
    } else { // 4 in 5 chance
        num = 2;
    }

    numX = rand() % 4; //range 0-3
    numY = rand() % 4;

    grid[numY][numX] = num;
}





//updates grid
void draw(){
    system("cls");
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            cout << grid[row][column] << " ";
        }
        cout << "\n";
    }
    
}





//changes grid when presses up, down, etc.
void update(int dir) {
    switch(dir) {
        //up
        case 1:
            for (int row = 0; row < gridSize; row++) {
                for (int column = 0; column < gridSize; column++) {
                    if (grid[row - 1][column] == grid[row][column]) {
                        //doubles the number
                        grid[row - 1][column] += grid[row][column];

                        grid[row][column] = 0;

                    }
                    //replaces 0s
                    if (grid[row - 1][column] == 0) {
                        grid[row - 1][column] = grid[row][column];

                        grid[row][column] = 0;
                    }
                }
            }
            break;
        //left
        case 2:
            for (int row = 0; row < gridSize; row++) {
                for (int column = 0; column < gridSize; column++) {
                    if (grid[row][column - 1] == grid[row][column]) {
                        //doubles the number
                        grid[row][column - 1] += grid[row][column];

                        grid[row][column] = 0;

                    }
                    //replaces 0s
                    if (grid[row][column - 1] == 0) {
                        grid[row][column - 1] = grid[row][column];
                        
                        grid[row][column] = 0;
                    }
                }
            }
            break;
        //down
        case 3:
            for (int row = 0; row < gridSize; row++) {
                for (int column = 0; column < gridSize; column++) {
                    if (grid[row + 1][column] == grid[row][column]) {
                        //doubles the number
                        grid[row + 1][column] += grid[row][column];

                        grid[row][column] = 0;

                    }
                    //replaces 0s
                    if (grid[row + 1][column] == 0) {
                        grid[row + 1][column] = grid[row][column];
                        
                        grid[row][column] = 0;
                    }
                }
            }
            break;
        //right
        case 4:
            for (int row = 0; row < gridSize; row++) {
                for (int column = 0; column < gridSize; column++) {
                    if (grid[row][column + 1] == grid[row][column]) {
                        //doubles the number
                        grid[row][column + 1] += grid[row][column];

                        grid[row][column] = 0;

                    }
                    //replaces 0s
                    if (grid[row][column + 1] == 0) {
                        grid[row][column + 1] = grid[row][column];

                        grid[row][column] = 0;
                    }
                }
            }
            break;
        default:
            cout << "\nError\n";
            //IT'S OVER 9000!
            gameOver = 9001;
    }


}





void up() {
    randNums();
    update(1);
    draw();
    cout << "Up";
}


void left() {
    randNums();
    update(2);
    draw();
    cout << "Left";
}


void down() {
    randNums();
    update(3);
    draw();
    cout << "Down";
}


void right() {
    randNums();
    update(4);
    draw();
    cout << "Right";
}




//detect gameOver, keyboard inputs
void logic() {

    //detect gameOver
    for (int row = 1; row < gridSize - 1; row++) {
        for (int column = 1; column < gridSize-1; column++) {
            if (grid[column - 1][row - 1] == grid[column][row - 1] || grid[column + 1][row - 1] == grid[column][row - 1]) {
                break;
            } else if (row && column == 2) {
                gameOver++;
            }
        }
    }
    for (int row = 1; row < gridSize - 1; row++) {
        for (int column = 1; column < gridSize; column++) {
            if (grid[column - 1][row] == grid[column - 1][row + 1] || row - 1 == row) {
                break;
            } else if (row == 2 && column == 3) {
                gameOver++;
            }
        }
    }
    //resets gameOver
    if (gameOver == 1 || 2) {
        gameOver = 0;
    }

    //keyboard inputs

    /////////////////////////////////////////////////////////////////
    //MAKE INSTANCE HAPPEN NO MORE THAN ONCE WHEN HOLDING THE KEY//
    ///////////////////////////////////////////////////////////////
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





//checks if there are any zeros left
bool isDone() {
    int i;
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            if (grid[row][column] != 0) {
                i++;
            }
        }
    }

    if (i == 16) {
       gameOver++;
       return 1;
    }
    return 0;
}





int main() {

    setup();
    draw();

    while (gameOver <= 3) {
        logic();
        isDone();
    }
    cout << "Game Over";

    return 0;

}
