#include "text.h"
#include <stdio.h>

void setTextColor(Text* text, unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    text->color.a = a;
    text->color.r = r;
    text->color.g = g;
    text->color.b = b;
}

void setText(Text* text, const char* t) {
    text->surface = TTF_RenderText_Solid(text->font, t, text->color);
    text->texture.texture = SDL_CreateTextureFromSurface(text->texture.renderer, text->surface);
    SDL_QueryTexture(text->texture.texture, NULL, NULL, &text->w, &text->h);
    setTexturePosition(&text->texture, text->w, text->h, text->x, text->y);
}

void setTextFont(Text* text, const char* font, int fontSize) {
    text->font = TTF_OpenFont(font, fontSize);
}

void renderText(Text* text) {
    displayTexture(&text->texture);
}