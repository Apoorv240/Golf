#include "texture.h"


void createTexture(Texture* texture, int width, int height, int x, int y) {
    texture->texture = IMG_LoadTexture(texture->renderer, texture->imagePath);
    setTexturePosition(texture, width, height, x, y);
}

void setTexturePosition(Texture* texture, int width, int height, int x, int y) {
    texture->textureRect.x = x;
    texture->textureRect.y = y;
    texture->textureRect.w = width;
    texture->textureRect.h = height;
}

void displayTexture(Texture* texture) {
    SDL_RenderCopy(texture->renderer, texture->texture, NULL, &texture->textureRect);
}