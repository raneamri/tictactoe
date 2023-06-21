#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    Default constructor for matrix of buttons
    */
    Entity() {}

    /*
    Constructor function to initialise the currentFrame variable
    size_w is the source width
    size_h is the source height
    p_x and p_y are the x and y coordiantes you want the texture to be diplayed at
    */
    void loadEnt(int size_w, int size_h, float p_x, float p_y, char *tpath, SDL_Renderer *renderer);

    void renderEnt(SDL_Renderer *renderer);

    void renderRotEnt(SDL_Renderer *renderer, SDL_Rect dst, double rotAngle);

    ~Entity() {
        
    };

};

class Button {
public:
    /*
    Blank constructor
    */
    Button() {}

    /*
    Duplicate constructor
    */
    Button(const Button &other) {
        hitbox.x1 = other.hitbox.x1;
        hitbox.y1 = other.hitbox.y1;
        hitbox.x2 = other.hitbox.x2 - other.hitbox.x1;
        hitbox.y2 = other.hitbox.y2 - other.hitbox.y1;
        texture = other.texture;
    }

    Button(int x1, int y1, int w, int h, char *tpath, SDL_Renderer *renderer) {
    hitbox.x1 = x1;
    hitbox.y1 = y1;
    hitbox.x2 = x1 + w;
    hitbox.y2 = y1 + h;
    texture = (tpath != nullptr) ? IMG_LoadTexture(renderer, tpath) : nullptr;
}


    /*
    Checks if point is in hitbox
    */
    bool hitboxCheck(int x, int y);
    /*
    Draws the button into the renderer
    */
    void renderButton(SDL_Renderer *renderer);
    /*
    Removes buttons texture
    */
    void hideButton();
    /*
    Shows buttons texture given tpath (only works if texture is null)
    */
    void showButton(char *fpath, SDL_Renderer *renderer);

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

        cursor = SDL_CreateColorCursor(convSurface, 0, 0);
        cursorHover = SDL_CreateColorCursor(convHoverSurface, 0, 0);
        SDL_FreeSurface(convSurface);
        SDL_FreeSurface(convHoverSurface);

        SDL_ShowCursor(true);
    }

    ~Cursor() {

    }
};
