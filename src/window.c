#include "window.h"
#include "texture.h"
#include "golfball.h"
#include "util.h"
#include "hole.h"
#include "game.h"

int initWindow(Window* window) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window->window = SDL_CreateWindow("Golf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width, window->height, SDL_WINDOW_SHOWN);
    if (window->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (window->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    return 0;
}

int runWindow(Window* window) {
    SDL_RenderSetLogicalSize(window->renderer, window->width, window->height);
    SDL_SetRenderDrawColor(window->renderer, 56, 128, 4, 255);//124, 252, 0, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);

    Entities entities;

    init(window, &entities);

    SDL_Event e; 
    bool quit = false; 
    while (quit == false) {
        while(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            handleEvent(e, &entities);
        }

        loop(window, &entities);        
    }

    return 0;
}

int closeWindow(Window* window) {
    SDL_DestroyWindow(window->window);
    SDL_Quit();
    return 0;
}