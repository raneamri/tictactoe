#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"

Entity::Entity(int size_w, int size_h, float p_x, float p_y, SDL_Texture* tex) 
:x(p_x), y(p_y), tex(tex) //sets the values of x y and tex to the ones being passed into the function
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = size_w;
    currentFrame.h = size_h;
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

Button::Button(int p_x1, int p_y1, int p_width, int p_height)
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

Button::~Button()
{

}

