#pragma once
#include <iostream>
#include <utility>

#include "types.hpp"
#include "defs.hpp"

using namespace std;

/*
Function to check if a player has won.
Returns {-1, -1} if the game should continue.
Returns {0, x} if player 1 wins.
Returns {1, x} if player 2 wins.
The second index in the pair correlates to a code which helps figure out where the line should be drawn
*/
pair<int, int> gridChecks(int8_t grid[GLEN][GWID]);

/*
State machine branch functions
*/
state_t MenuState();
state_t OfflineState();