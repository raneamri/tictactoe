#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL)
    {
        std::cout << "Window failed to open" << SDL_GetError()<< std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
    std::cout << "Error texture has not loaded. Error:"<< SDL_GetError()<< std::endl;
    
    return texture;
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);   
}

void RenderWindow::render(SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.x=0;
    src.y=0;
    src.w=2000;
    src.h=2000;

    SDL_Rect dst;
    dst.x=300-32;
    dst.y=300-32;
    dst.w=32;
    dst.h=32;
    SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void RenderWindow::display()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}