#include <iostream>

#include "main.hpp"
#include "defs.hpp"

using namespace std;

int main(void) {
    
    cout << "Welcome to Tic Tac Toe. This project is currently in development but as of now, user input is taken in terminal" << endl;
    cout << "In this program, the top left square of the grid is considered (1, 1) and when required to input your move, it should be input as '1 1'." << endl;

    int grid[GLEN][GWID] = {-1};
    int player1, player2;

    bool end = false;
    int turn = 1, totalTurns = 0;


    /*
    Game loop.
    */
    while (!end) {

        renderGrid(grid);

        cout << "Player " << (turn > 0) ? "1" : "2";
        cout << "'s turn: ";
        cout << endl;

        end = (gridChecks(grid) == -1) ? false : true;

        totalTurns++; // count turn
        turn *= -1; // swaps turns
    }
    
}

void renderGrid(int grid[GLEN][GWID]) {
    for (int i = 0; i < GWID; i++) {
        for (int j = 0; j < GLEN; j++) {
            cout << " [" << ((grid[GLEN][GWID] == -1) ? " " : ((grid[GLEN][GWID] == 0) ? "X" : "O")) << "] ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

int gridChecks(int grid[GLEN][GWID]) {

    return -1;
}