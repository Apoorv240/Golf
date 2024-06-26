#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "collision.h"

struct {
    const int width;
    const int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool quit;
    bool goToGame;
} typedef Window;

int initWindow(Window* window);
int runWindow(Window* window);
int closeWindow(Window* window);