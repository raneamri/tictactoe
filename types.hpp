#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "globals.hpp"
#include "interface.hpp"

/*
States for state machine
*/
enum state_t {
    MENU,
    OFFLINE,
    ONLINE,
    SETTINGS,
    QUIT
};


/*
Square hitbox datatype where {
    x1, y1 = top left
    x2, y2 = bottom right
}
*/
typedef struct sq_hitbox_t { 
    int x1, x2, y1, y2;
} sq_hitbox_t;

class Entity {
public:
    float x, y;
    SDL_Rect currentFrame;
    SDL_Texture *texture;

    /*
    Constructor function to initialise the currentFrame variable
    size_w is the source width
    size_h is the source height
    p_x and p_y are the x and y coordiantes you want the texture to be diplayed at
    */
    Entity(int size_w, int size_h, float p_x, float p_y, char *tpath) {
        x = p_x;
        y = p_y;
        currentFrame.x = 0;
        currentFrame.y = 0;
        currentFrame.w = size_w;
        currentFrame.h = size_h;
        texture = IMG_LoadTexture(renderer, tpath);
    }

    ~Entity();
};


class RenderWindow {
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

class Button {
public:
    Button(int x1, int y1, int w, int h, char *tpath) {
        hitbox.x1 = x1;
        hitbox.y1 = y1;
        hitbox.x2 = x1 + w;
        hitbox.y2 = y1 + h;
        texture = IMG_LoadTexture(renderer, tpath);
    }

    /*
    Checks if point is in hitbox
    */
    bool hitboxCheck(int x, int y);
    /*
    Draws the button into the renderer
    */
    void renderButton();

    ~Button() {};
private:
    sq_hitbox_t hitbox;
    SDL_Texture *texture;
};

class Cursor {
public:
    SDL_Cursor *cursor, *cursorHover;
    SDL_Surface *surface, *hoverSurface, *convSurface, *convHoverSurface;

    Cursor() {
        surface = IMG_Load("gfx/cursor.png");
        hoverSurface = IMG_Load("gfx/cursorHover.png");
        convSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        convHoverSurface = SDL_ConvertSurfaceFormat(hoverSurface, SDL_PIXELFORMAT_RGBA32, 0);

        SDL_FreeSurface(surface);
        SDL_FreeSurface(hoverSurface);

        SDL_Cursor *cursor = SDL_CreateColorCursor(convSurface, 0, 0);
        SDL_Cursor *cursorHover = SDL_CreateColorCursor(convHoverSurface, 0, 0);
        SDL_FreeSurface(convSurface);
        SDL_FreeSurface(convHoverSurface);

        SDL_ShowCursor(true);

    }

    ~Cursor() {

    }
};