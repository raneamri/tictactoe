/*
Foreign includes
*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

/*
Local includes
*/
#ifndef GLOBAL_HPP
#include "globals.hpp"
#endif
#include "main.hpp"
#include "defs.hpp"
#include "types.hpp"

/*
Namespaces
*/
using namespace std;

/*
Global variables
*/

int main(int argc, char *argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO > 0) || !IMG_Init(IMG_INIT_PNG)) {
        std::cerr << "Fatal error: SDL fail." << endl;
    }    

    /*
    State machine for game state
    */
    state_t state = MENU, laststate;
    while (true) {
    switch (state) {
        case MENU:
            state = MenuState();
            cout << "state swapped" << endl;
            laststate = MENU;
            break;
        case OFFLINE:
            state = OfflineState();
            laststate = OFFLINE;
        case ONLINE:
            return -1;
        case SETTINGS:
            return -1;
        case QUIT:
            SDL_DestroyWindow(window);
            SDL_Quit();
            IMG_Quit();
            return 0;
    }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();

    return -1;
}

pair <int, int> gridChecks(int8_t grid[GLEN][GWID]) {
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != -1) {
            return {grid[i][0], (-1 * i) - 1};
        } else if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != -1) {
            return {grid[0][i], i + 1};
        }
    }

    if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != -1) {
        return {grid[0][0], 4};
    } else if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[1][1] != -1) {
        return {grid[0][2], 5};
    }

    return { -1, -1 }; // Return a pair of -1 values if no win condition is met
}


state_t MenuState() {
    SDL_Event event;

    Button startBtn(128, 64, 192 , 128 , (char *)"gfx/start.png", renderer);

    while (true) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return QUIT;
        }
        SDL_GetMouseState(&mouseX, &mouseY);
        /*
        Check if they're hovering button
        */
        if (startBtn.hitboxCheck(mouseX, mouseY)) {
            SDL_SetCursor(cursor.cursorHover);
            cout << mouseX << mouseY << endl;
            /*
            If they click while hovering, go to OFFLINE
            */
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                return OFFLINE;
            }
        } else {
            SDL_SetCursor(cursor.cursor);
        }

        SDL_RenderClear(renderer); 
        startBtn.renderButton(renderer);
        /*
        Display
        */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    }
    }
}


state_t OfflineState() {
    SDL_Event event;
    Entity board(512, 512, 0, 0, (char *)"gfx/board.png", renderer);
    Button boardBtns[GLEN][GWID];
    for (int i = 0; i < GLEN; i++) {
        for (int j = 0; j < GWID; j++) {
            boardBtns[i][j] = Button(j*BOARDBTN_SIZE, i*BOARDBTN_SIZE, BOARDBTN_SIZE, BOARDBTN_SIZE, nullptr, renderer);
        }
    }

    /*
    Smart texture tracker to minimise code
    */
    vector<char *> pfpaths = {(char *)"gfx/X.png", (char *)"gfx/O.png"};
    vector<char *> efpaths = {(char *)"gfx/player1win.png", (char *)"gfx/player2win.png", (char *)"gfx/tie.png"};
    pfpaths.shrink_to_fit(); efpaths.shrink_to_fit();

    /*
    Move matrix
    */
    int8_t int8board[GLEN][GWID] = {{-1, -1, -1},
                                    {-1, -1, -1},
                                    {-1, -1, -1}};

    /*
    Game flags
    */
    pair<int, int> winInfo = {-1, -1};
    int turn = 1, turnNum = 0;
    unsigned int lastWin = -1;


    while (true) {
    while (SDL_PollEvent(&event)) {
        if (turnNum * lastWin > -1 || turnNum >= 9) {
                /*
                Draw line using rotation
                */
                if (lastWin > -1) {
                    Entity line(512, 512, 0, 0, (char *)"gfx/line.png", renderer);

                    SDL_Rect dst = {0, 0, 512, 512};
                    int rot = 0;

                    if(winInfo.second == 5) {
                        rot = 45;
                    } else if(winInfo.second == 4) {
                        rot = 315;
                    } else if(winInfo.second > 0) {
                        dst.x = 170 * (winInfo.second - 2);
                    } else {
                        rot = 90;
                        dst.y = 170 * (winInfo.second * -1 - 2);
                    }

                    SDL_RenderCopyEx(renderer, line.texture, nullptr, &dst, rot, nullptr, SDL_FLIP_NONE);
                }

            Entity endScreen(512, 512, 0, 0, (lastWin == -1) ? efpaths[2] : (lastWin == 1) ? efpaths[0] : efpaths[1], renderer);
            
            return MENU;
        }

        SDL_GetMouseState(&mouseX, &mouseY);

        if (event.type == SDL_MOUSEBUTTONDOWN) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (boardBtns[i][j].hitboxCheck(mouseX, mouseY) && int8board[i][j] == -1) {
                    boardBtns[i][j].showButton(pfpaths[turn - 1], renderer);
                    int8board[i][j] += turn;
                    turnNum++;
                    /*
                    Swap turn
                    */
                    turn = (turn == 2) ? 1 : 2;

                    /*
                    Note: condense method as to obsolete winInfo var
                    or upgrade it to a tracker
                    */
                    winInfo = gridChecks(int8board);
                    if(winInfo.first != -1) {
                        lastWin = (winInfo.first == 0) ? 1 : 2;
                    }
                }
            }   
        }
        }

        /*
        Display
        */
        SDL_RenderClear(renderer);

        /*
        Selectively render buttons
        */
        for (int i = 0; i < GLEN; i++) {
            for (int j = 0; j < GWID; j++) {
                if (int8board[i][j] > -1)
                    boardBtns[j][i].renderButton(renderer);
            }
        }
        board.renderEntity(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
    }
    }

}