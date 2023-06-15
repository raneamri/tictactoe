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
    void createEnt(int size_w, int size_h,float p_x, float p_y, SDL_Texture* p_tex);
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
    /*
    Initislaises the hitbox of the button
    takes the top left coordinate and calculates the bottom right coordinate
    */
    void createBtn(int p_x1, int p_y1, int p_width, int p_height);
    /*
    returns the hitbox struct
    */
    hitbox getHitbox();
    /*
    function that checks if the mouse is in the hitbox
    */
    bool hitboxCheck(int x, int y);
    /*
    nullifies the button, essentially deleting
    */
    void btnDel();

    ~Button();    
private:
    hitbox buttonHitbox;
};
