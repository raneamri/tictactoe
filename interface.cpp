#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "globals.hpp"
#include "types.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h) : window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

    if (window == NULL) {
        std::cout << "Window failed to open" << SDL_GetError()<< std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture *RenderWindow::loadTexture(const char* p_filePath) {
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);

    if(texture == NULL)
    std::cout << "Error texture has not loaded. Error:"<< SDL_GetError()<< std::endl;
    
    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);   
}

void RenderWindow::updateMouseCords()  {
    SDL_GetMouseState(&mouseX, &mouseY);
}

/*
Following two functions obsoloted*
*/
int RenderWindow::getMouseX() {
    return mouseX;
}

int RenderWindow::getMouseY() {
    return mouseY;
}

void RenderWindow::renderRotate(Entity p_entity, SDL_Rect &destRect, float rotAngle) {
    SDL_Rect src;
    src.x=p_entity.getCurrentFrame().x;
    src.y=p_entity.getCurrentFrame().y;
    src.w=p_entity.getCurrentFrame().w;
    src.h=p_entity.getCurrentFrame().h;

    SDL_RenderCopyEx(renderer, p_entity.getTex(), nullptr, &destRect, rotAngle, nullptr, SDL_FLIP_NONE);
}

void RenderWindow::display() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderPresent(renderer);
}

float Entity::getX()
{
    return x;
}
float Entity::getY()
{
    return y;
}
SDL_Texture* Entity::getTex()
{
    return tex;
}
SDL_Rect Entity::getCurrentFrame() 
{
    return currentFrame;
}
Entity::~Entity()
{

}

bool Button::hitboxCheck(int x, int y) {
    if (hitbox.x1 <= x <= hitbox.x2 && hitbox.y1 <= y <= hitbox.y2) {
        return true;
    } else {
        return false;
    }
}

void Button::renderButton() {
    SDL_Rect src;
    src.x = hitbox.x1;
    src.y = hitbox.y1;
    src.w = hitbox.x2 - hitbox.x1;
    src.h = hitbox.y2 - hitbox.y1;

    SDL_Rect dst;
    src.x = hitbox.x1;
    src.y = hitbox.y1;
    src.w = hitbox.x2 - hitbox.x1;
    src.h = hitbox.y2 - hitbox.y1;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}