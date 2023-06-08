//g++ -IC:/Users/new/OneDrive/Desktop/projects/libs/SDLinclude -LC:/Users/new/OneDrive/Desktop/projects/libs/SDLlibs -o main main.cpp RenderWindow.cpp Entity.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

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
    SDL_Texture* startButtonTex = window.loadTexture("gfx/start.png"); //loading the textures

    Entity boardEnt(512, 512, 0, 0, boardTex);
    Entity startButtonEnt(128, 64, 100 ,100 , startButtonTex);
    Entity platform0(32, 32, 100, 100, OTex);//setting the textures as entities

    Button TLBtn(0, 0, 170, 170);
    Button MLBtn(0, 170, 170, 170);
    Button BLBtn(0, 340, 170, 170);
    
    Button TMBtn(170, 0, 170, 170);
    Button MMBtn(170, 170, 170, 170);
    Button BMBtn(170, 340, 170, 170);

    Button TRBtn(340, 0, 170, 170);
    Button MRBtn(340, 170, 170, 170);
    Button BRBtn(340, 340, 170, 170);
    Button startButtonBtn(100, 100, 128, 64); //initalising all the buttons

    int board[GLEN][GWID] = {{-1, -1, -1},
                             {-1, -1, -1},
                             {-1, -1, -1}};

    bool gameRunning = true;
    SDL_Event event;
    int state = 0;
    int match = 0;
    
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
                    if (TLBtn.hitboxCheck(window.getMouseX(),window.getMouseY()))
                    {
                        Entity Xent(32, 32, 0, 0, XTex);
                        match = 1;
                    }
                }

            }
        }

        switch (state)
        {
            case 0: //main menu
                window.clear();
                window.render(startButtonEnt);
                window.display();
                break;

            case 1: //game
                window.clear();
                window.render(boardEnt);
                if(match){
                Entity Xent(32, 32, 0, 0, XTex);
                window.render(Xent);
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

int gridChecks(int grid[GLEN][GWID]) {

    for(int i = 0; i < 3; i++) //checks horizontal wins
    {
        if(grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2])
        return grid[i][0];
    }
    for(int i = 0; i < 3; i++) //checks vertical wins
    {
        if(grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i])
        return grid[0][i];
    }

    if(grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2])//checks diagnal wins
    return grid[0][0];
    if(grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0])
    return grid[0][2];


    return -1;
}