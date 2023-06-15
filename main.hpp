#include <iostream>
#include <utility>

#include "defs.hpp"

using namespace std;

/*
Prints the grid to stdin.
Currently only works for 3x3.
*/
void renderGrid(int grid[GLEN][GWID]);

/*
Function to check if a player has won.
Returns -1 if the game should continue.
Returns 0 if player 1 wins.
Returns 1 if player 2 wins.
*/
pair <int, int> gridChecks(int grid[GLEN][GWID]);

/*
Function to check the validity of an input
Returns 1 if the input is invalid
Returns 0 if the input is valid
*/
int inputcheck(int grid[GLEN][GWID], int rowInput, int colInput);