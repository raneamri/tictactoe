#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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



void RenderWindow::render(Entity &p_entity) {
    SDL_Rect src;
    src.x=p_entity.getCurrentFrame().x;
    src.y=p_entity.getCurrentFrame().y;
    src.w=p_entity.getCurrentFrame().w;
    src.h=p_entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x=p_entity.getX();
    dst.y=p_entity.getY();
    dst.w=p_entity.getCurrentFrame().w;
    dst.h=p_entity.getCurrentFrame().h;
    SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
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

void Entity::createEnt(int size_w, int size_h, float p_x, float p_y, SDL_Texture* p_tex) 
{
    x = p_x;
    y = p_y;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = size_w;
    currentFrame.h = size_h;
    tex = p_tex;
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

void Button::createBtn(int p_x1, int p_y1, int p_width, int p_height)
{
    buttonHitbox.x1 = p_x1;
    buttonHitbox.y1 = p_y1;
    buttonHitbox.x2 = p_x1 + p_width;
    buttonHitbox.y2 = p_y1 + p_height;
}

hitbox Button::getHitbox()
{
    return buttonHitbox;
}

bool Button::hitboxCheck(int mousePosX, int mousePosY)
{
    if (mousePosX > buttonHitbox.x1 && mousePosX < buttonHitbox.x2 && mousePosY > buttonHitbox.y1 && mousePosY < buttonHitbox.y2)
    {
        return true;
    }
    
    return false;
}

void Button::btnDel()
{
    buttonHitbox.x1 = -1;
    buttonHitbox.y1 = -1;
    buttonHitbox.x2 = -1;
    buttonHitbox.y2 = -1;
}

Button::~Button()
{

}