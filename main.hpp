#include <iostream>
#include <utility>

#include "Entity.hpp"
#include "defs.hpp"

using namespace std;

/*
Prints the grid to stdin.
Currently only works for 3x3.
*/
void renderGrid(int grid[GLEN][GWID]);

/*
Function to check if a player has won.
Returns {-1, -1} if the game should continue.
Returns {0, x} if player 1 wins.
Returns {1, x} if player 2 wins.
The second index in the pair correlates to a code which helps figure out where the line should be drawn
*/
pair <int, int> gridChecks(int grid[GLEN][GWID]);

/*
Function to check the validity of an input
Returns 1 if the input is invalid
Returns 0 if the input is valid
*/
int inputcheck(int grid[GLEN][GWID], int rowInput, int colInput);
/*
function that checks if the cursor is hovering over buttons
Returns 1 if there is a button
Returns 0 if there is not a button.
*/
int checkButtonHover(Button buttons[GLEN][GWID], int cursorX, int cursorY);