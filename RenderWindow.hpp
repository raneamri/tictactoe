#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

class RenderWindow
{
    public:
        RenderWindow(const char* p_title, int p_w, int p_h);
        SDL_Texture* loadTexture(const char* p_filePath);
        void cleanUp(); 
        void clear();
        void render(Entity& p_entity);
        void renderRotate(Entity p_entity, SDL_Rect &destRect, float rotAngle);
        void display();
        void updateMouseCords();
        int getMouseX();
        int getMouseY();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        int mouseX;
        int mouseY;
};