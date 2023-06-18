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
    src.x = hitbox.x1;
    src.y = hitbox.y1;
    src.w = hitbox.x2 - hitbox.x1;
    src.h = hitbox.y2 - hitbox.y1;

    SDL_Rect dst;
    dst.x = hitbox.x1;
    dst.y = hitbox.y1;
    dst.w = hitbox.x2 - hitbox.x1;
    dst.h = hitbox.y2 - hitbox.y1;
    int err = SDL_RenderCopy(renderer, texture, &src, &dst);
    if (err < 0) {
        cout << "render copy error";
        exit(-1);
    }
}

void Button::hideButton() {
    texture = NULL;
}

void Button::showButton(char *tpath, SDL_Renderer *renderer) {
    texture = (texture == NULL) ? IMG_LoadTexture(renderer, tpath) : texture;
}

void Entity::renderEntity(SDL_Renderer *renderer) {
    SDL_Rect src;
    src.x = currentFrame.x;
    src.x = currentFrame.y;
    src.w = currentFrame.w;
    src.h = currentFrame.h;

    SDL_Rect dst;
    dst.x = currentFrame.x;
    dst.x = currentFrame.y;
    dst.w = currentFrame.w;
    dst.h = currentFrame.h;
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

Entity::Entity(int size_w, int size_h, float p_x, float p_y, char *tpath, SDL_Renderer *renderer) {
    x = p_x;
    y = p_y;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = size_w;
    currentFrame.h = size_h;
    texture = IMG_LoadTexture(renderer, tpath);
}