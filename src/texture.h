#pragma once

#include <SDL.h>
#include <SDL_image.h>

struct {
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect textureRect;

    const char* imagePath;
} typedef Texture;

void createTexture(Texture* texture, int width, int height, int x, int y);
void setTexturePosition(Texture* texture, int width, int height, int x, int y);
void displayTexture(Texture* texture);
