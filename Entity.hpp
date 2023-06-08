#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

typedef struct hitbox // data type that stores coordinates of hitboxes
{ 
    int x1, x2, y1, y2;
}hitbox;

class Entity
{
public:
    Entity(int size_w, int size_h,float p_x, float p_y, SDL_Texture* p_tex);
    /*
    initialising function to initialise the currentFrame variable
    size_w is the source width
    size_h is the source height
    p_x and p_y are the x and y coordiantes you want the texture to be diplayed at
    */
    float getX();
    float getY();
    SDL_Texture* getTex();
    SDL_Rect getCurrentFrame();
    ~Entity();

private:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture* tex;
};

class Button
{
public:
    Button(int p_x1, int p_y1, int p_width, int p_height);
    /*
    Initislaises the hitbox of the button
    takes the top left coordinate and calculates the bottom right coordinate
    */
    hitbox getHitbox();
    /*
    returns the hitbox struct
    */
    bool hitboxCheck(int x, int y);
    /*
    function that checks if the mouse is in the hitbox
    */
    ~Button();    
private:
    hitbox buttonHitbox;
};