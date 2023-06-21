#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "main.hpp"
#include "types.hpp"

bool Button::hitboxCheck(int x, int y) {
    if ((hitbox.x1 <= x && x <= hitbox.x2) && (hitbox.y1 <= y && y <= hitbox.y2)) {
        return true;
    } else {
        return false;
    }
}

void Button::renderButton(SDL_Renderer *renderer) {
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = hitbox.x2 - hitbox.x1;
    src.h = hitbox.y2 - hitbox.y1;

    SDL_Rect dst;
    dst.x = hitbox.x1;
    dst.y = hitbox.y1;
    dst.w = hitbox.x2 - hitbox.x1;
    dst.h = hitbox.y2 - hitbox.y1;
    

    int err = SDL_RenderCopy(renderer, texture, &src, &dst);
    if (err < 0) {
        cout << "render copy error" << endl;
    }
}

void Button::hideButton() {
    texture = NULL;
}

void Button::showButton(char *tpath, SDL_Renderer *renderer) {
    texture = IMG_LoadTexture(renderer, tpath);
}

void Entity::renderEnt(SDL_Renderer *renderer) {
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = currentFrame.w;
    dst.h = currentFrame.h;
    SDL_RenderCopy(renderer, texture, &currentFrame, &dst);
}

void Entity::loadEnt(int size_w, int size_h, float p_x, float p_y, char *tpath, SDL_Renderer *renderer) {
    x = p_x;
    y = p_y;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = size_w;
    currentFrame.h = size_h;
    texture = IMG_LoadTexture(renderer, tpath);
}

void Entity::renderRotEnt(SDL_Renderer *renderer, SDL_Rect dst, double rotAngle) {
    
    SDL_RenderCopyEx(renderer, texture, nullptr, &dst, rotAngle, nullptr, SDL_FLIP_NONE);
}
