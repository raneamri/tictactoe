//g++ main.cpp -o main && main
#include <iostream>

#include "main.hpp"
#include "defs.hpp"

using namespace std;

int main(void) {
    
    cout << "Welcome to Tic Tac Toe. This project is currently in development but as of now, user input is taken in terminal" << endl;
    cout << "In this program, the top left square of the grid is considered (1, 1) and when required to input your move, it should be input as '1 1'." << endl;

    int grid[GLEN][GWID] = {{-1, -1, -1},
                            {-1, -1, -1},
                            {-1, -1, -1}};
    int player1, player2;

    bool end = false;
    int turn = 1, totalTurns = 0;

    int rowInput, colInput;
    string input;
    
    /*
    Game loop.
    */
    while (!end && totalTurns < 9) {

        system("cls"); //refreshes screen

        cout << "Player " << ((turn > 0) ? "1" : "2");
        cout << "'s turn: ";
        cout << endl;

        renderGrid(grid);

        cin >> rowInput;
        cin >> colInput; //reads input

        while(inputcheck(grid, rowInput, colInput) == 1) //validating input
        {
            cout << "Invalid input." << endl;
            cout << "Please type in a valid input" << endl;

            cin >> rowInput;
            cin >> colInput;
        }

        grid[rowInput - 1][colInput - 1] = ((turn > 0) ? 0 : 1); //changing the grid to match the input
        system("cls"); //refreshes screen
        renderGrid(grid);

        end = (gridChecks(grid) == -1) ? false : true;

        if(end)
        {
            cout << "Player " << gridChecks(grid) + 1 << " Wins!"<< endl;
            cout << "Thank you for playing our TicTacToe game!"<< endl;
        }

        totalTurns++; // count turn
        turn *= -1; // swaps turns
    }
    
}

void renderGrid(int grid[GLEN][GWID]) {

    for (int i = 0; i < GLEN; i++) {
        for (int j = 0; j < GWID; j++) {
            cout << " [" << ((grid[i][j] == -1) ? " " : ((grid[i][j] == 0) ? "X" : "O")) << "] ";
        }
        cout << endl;
    }
    cout << endl;
    return;
}

int gridChecks(int grid[GLEN][GWID]) {

    for(int i = 0; i < 3; i++) //checks horizontal wins
    {
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2])
        return grid[i][0];
    }
    for(int i = 0; i < 3; i++) //checks vertical wins
    {
        if(grid[0][i] == grid[0][i] && grid[0][i] == grid[2][i])
        return grid[0][i];
    }

    if(grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2])//checks diagnal wins
    return grid[0][0];
    if(grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0])
    return grid[0][2];


    return -1;
}

int inputcheck(int grid[GLEN][GWID], int rowInput, int colInput){

    if (grid[rowInput - 1][colInput - 1] != -1 || rowInput > 4 || colInput > 4 || rowInput < 1 || colInput < 1)
    return 1; // input is invalid
    else
    return 0; // input is valid

}