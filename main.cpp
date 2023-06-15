//g++ -IC:/Users/new/OneDrive/Desktop/projects/libs/SDLinclude -LC:/Users/new/OneDrive/Desktop/projects/libs/SDLlibs -o main main.cpp RenderWindow.cpp Entity.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
//g++ -IC:/projects/libs/SDLinclude -LC:/projects/libs/SDLlibs -o main main.cpp RenderWindow.cpp Entity.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "main.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;
const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 512; 


int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO > 0))
    cout << "SDL_Init HAS FAILED, SDL_ERROR: "<< SDL_GetError() << endl;
    

    if(!IMG_Init(IMG_INIT_PNG))
    cout << "IMG_Init has failed. Error" << SDL_GetError()<< endl;

    RenderWindow window("GAME v1.0", WINDOW_WIDTH, WINDOW_HEIGHT); //initialising the game window

    SDL_Texture* boardTex = window.loadTexture("gfx/board.png");
    SDL_Texture* OTex = window.loadTexture("gfx/O.png");
    SDL_Texture* XTex = window.loadTexture("gfx/X.png");
    SDL_Texture* startButtonTex = window.loadTexture("gfx/start.png");
    SDL_Texture* lineTex = window.loadTexture("gfx/line.png"); //loading the textures

    Entity boardEnt, startBtnEnt, lineEnt;

    Entity XOents[GLEN][GWID]; //initalising 2d array of entities which will help with rendering later on
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            XOents[i][j].createEnt(170, 170, (170 * j), (170 * i), nullptr);
        }
    }

    boardEnt.createEnt(512, 512, 0, 0, boardTex);
    startBtnEnt.createEnt(128, 64, 100 ,256 , startButtonTex); //setting the textures as entities

    
    Button startButtonBtn;
    startButtonBtn.createBtn(100, 256, 128, 64); 

    Button gameBoardBtns[GLEN][GWID];
    // Create and initialize the game board buttons using a loop
    for (int i = 0; i < GLEN; i++) {
        for (int j = 0; j < GWID; j++) {
            int x1 = j * 170;
            int y1 = i * 170;
            gameBoardBtns[i][j].createBtn(x1, y1, 170, 170);
        }
    }

    bool gameRunning = true;
    SDL_Event event;
    /*
    state is for the switch statement
    turn is to track the player turn
    numOfTurns is to track the number of turns
    playerWon is used to store the player who won either 1 or 2
    */
    int state = 0,turn = 1, numOfTurns = 0, playerWon = -1;

    /*
    tracks win info
    */
    pair<int, int> winInfo = {-1, -1};

    /*
    2d array to track the moves of the two players
    */
    int gameBoard[GLEN][GWID] = {{-1, -1, -1},
                                {-1, -1, -1},
                                {-1, -1, -1}};
    
    while(gameRunning)
    {
        window.updateMouseCords();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) 
            {
                if (state == 0 && startButtonBtn.hitboxCheck(window.getMouseX(), window.getMouseY()))
                {
                    state = 1; 
                }
                else if (state == 1)
                {

                    if(numOfTurns == 9 || playerWon != -1)
                    {   

                        state = 0;//going back to main menu
                        numOfTurns = 0;
                        turn = 1;
                        playerWon = -1;

                        for (int i = 0; i < 3; i++)
                        {
                            for (int j = 0; j < 3; j++) 
                            {
                                XOents[i][j].createEnt(170, 170, (170 * j), (170 * i), nullptr);//reseting entities
                                gameBoard[i][j] = -1; // reseting gameboard
                            }
                        }

                        break;
                    }


                    for(int i = 0; i < 3; i++)
                    {
                        for(int j = 0; j < 3; j++)
                        {
                            if (turn == 1 && gameBoardBtns[i][j].hitboxCheck(window.getMouseX(), window.getMouseY()) && gameBoard[i][j] == -1)// if it's player 1's turn and the mouse is in the hitbox
                            {
                                XOents[i][j].createEnt(170, 170, (170 * j), (170 * i), XTex);
                                gameBoard[i][j] = 0;
                                numOfTurns++;
                                turn = 2; // Switch turn to player 2

                                winInfo = gridChecks(gameBoard);

                                if(winInfo.first != -1)
                                playerWon = (winInfo.first == 0) ? 1 : 2;
                
                            }

                            else if (turn == 2 && gameBoardBtns[i][j].hitboxCheck(window.getMouseX(), window.getMouseY())&& gameBoard[i][j] == -1)// if it's player 2's turn and the mouse is in the hitbox
                            {
                                XOents[i][j].createEnt(170, 170, (170 * j), (170 * i), OTex);
                                gameBoard[i][j] = 1;
                                numOfTurns++;
                                turn = 1; // Switch turn to player 1

                                winInfo = gridChecks(gameBoard);

                                if(winInfo.first != -1)
                                playerWon = (winInfo.first == 0) ? 1 : 2;
                                            
                            }
                        }   
                    }
                }

            }
        }

        switch (state)
        {
            case 0: //main menu
                window.clear();
                window.render(startBtnEnt);
                window.display();
                break;

            case 1: //game
                window.clear();
                window.render(boardEnt);
                
                if(playerWon != -1)
                {
                    SDL_Rect dst= {0, 0, 512, 512};
                    int rotAngle = 0;

                    if(winInfo.second == 5)
                    {
                        rotAngle = 45;
                    }
                    else if(winInfo.second == 4)
                    {
                        rotAngle = 315;
                    }
                    else if(winInfo.second > 0)
                    {
                        dst.x = 170 * (winInfo.second - 2);
                    }
                    else
                    {
                        rotAngle = 90;
                        dst.y = 170 * (winInfo.second * -1 - 2);
                    }
                    
                    
                    lineEnt.createEnt(512, 512, 0, 0, lineTex);
                    window.renderRotate(lineEnt, dst, rotAngle);
                }

                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        window.render(XOents[i][j]);
                    }
                }

                window.display();
                break;

            default:
                state = 0;
                break;
        }
    }

    window.cleanUp();
    SDL_Quit();
    IMG_Quit();

    return 0;
}

pair <int, int> gridChecks(int grid[GLEN][GWID])
{
    for (int i = 0; i < 3; i++) //checks horizontal wins
    {
        if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] != -1)
            return { grid[i][0], (-1 * i) - 1 };
    }

    for (int i = 0; i < 3; i++) //checks vertical wins
    {
        if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] != -1)
            return { grid[0][i], i + 1 };
    }

    if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2] && grid[0][0] != -1) //checks diagonal wins
        return { grid[0][0], 4 };
    if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0] && grid[1][1] != -1)
        return { grid[0][2], 5 };

    return { -1, -1 }; // Return a pair of -1 values if no win condition is met
}