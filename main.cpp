//g++ -Isrc\include -Lsrc\lib -o main main.cpp RenderWindow.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "main.hpp"
#include "defs.hpp"
#include "RenderWindow.hpp"

using namespace std;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;


int main(int argc, char **argv)
{
    if(SDL_Init(SDL_INIT_VIDEO > 0))
    cout << "SDL_Init HAS FAILED, SDL_ERROR: "<< SDL_GetError() << endl;
    

    if(!IMG_Init(IMG_INIT_PNG))
    cout << "IMG_Init has failed. Error" << SDL_GetError()<< endl;

    RenderWindow window("GAME v1.0", WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_Texture* OTexture = window.loadTexture("gfx/O.png");

    bool gameRunning = true;
    SDL_Event event;

    while(gameRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }   
        }
        window.clear();
        window.render(OTexture);
        window.display();
    }


    window.cleanUp();
    SDL_Quit();

    return 0;
}