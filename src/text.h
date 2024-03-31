#pragma once

#include <SDL_ttf.h>
#include "texture.h"

struct {
    TTF_Font* font;
    SDL_Surface* surface;
    SDL_Color color;
    Texture texture;

    int x;
    int y;
} typedef Text;

void setTextColor(Text* text, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void setText(Text* text, const char* t);
void setTextFont(Text* text, const char* font);
void renderText(Text* text);