#include "window.h"
#include "texture.h"
#include "golfball.h"
#include "util.h"
#include "hole.h"

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
    SDL_SetRenderDrawColor(window->renderer, 124, 252, 0, 255);
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);

    Golfball golfball;
    golfball.texture.texture = NULL;
    golfball.texture.renderer = window->renderer;
    golfball.texture.imagePath = "image.png";
    golfball.accel = -10;
    golfball.startVelo.magnitude = 200;
    golfball.startVelo.theta = 0;
    golfball.velo = golfball.startVelo;
    golfball.startX = 300;//170;
    golfball.startY = 300;

    Hole hole;
    hole.texture.texture = NULL;
    hole.texture.renderer = window->renderer;
    hole.texture.imagePath = "hole.png";
    hole.x = 175;
    hole.y = 175;

    initGolfball(&golfball);
    initHole(&hole);

    int startTime = SDL_GetTicks();

    SDL_Event e; 
    bool quit = false; 
    bool scored = false;
    bool moving = false;
    while (quit == false) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) quit = true; 
        }
        
        if (moving = true) {
            // subtracting because y goes down but unit circle should stay the same
            golfball.y = golfball.startY - vectorCalcY(golfball.velo)*(SDL_GetTicks() - startTime)/1000;
            golfball.x = golfball.startX + vectorCalcX(golfball.velo)*(SDL_GetTicks() - startTime)/1000;
            golfball.velo.magnitude = golfball.startVelo.magnitude + golfball.accel*(SDL_GetTicks() - startTime)/1000;
            printf("%.2f : %.0f\n", golfball.velo.magnitude, golfball.accel*(SDL_GetTicks() - startTime)/1000); //vectorCalcY(golfball.velo)*(SDL_GetTicks() - startTime)/1000);//golfball.velo.theta * 180 / M_PI);

            // if () {
            //     moving = false;
            //     golfball.velo.magnitude = 0;
            //     golfball.startVelo.magnitude = 0;
            //     golfball.accel = 0;
            //     golfball.startX = golfball.x;
            //     golfball.startY = golfball.y;
            // }

            if ((golfball.y <= 0) || (golfball.y >= window->height-golfball.texture.textureRect.h)) {
                startTime = SDL_GetTicks();
                golfball.startVelo.theta = 360 - golfball.velo.theta;
                golfball.startVelo.magnitude = golfball.velo.magnitude;
                golfball.velo = golfball.startVelo;
                golfball.startY = bounds(1, window->height - golfball.texture.textureRect.h - 1, golfball.y);
                golfball.startX = golfball.x;
            }
            if ((golfball.x <= 0) || (golfball.x >= window->width-golfball.texture.textureRect.w)) {
                startTime = SDL_GetTicks();
                golfball.startVelo.theta = 180 - golfball.velo.theta;
                golfball.startVelo.magnitude = golfball.velo.magnitude;
                golfball.velo = golfball.startVelo;
                golfball.startY = golfball.y;
                golfball.startX = bounds(1, window->width - golfball.texture.textureRect.w - 1, golfball.x);
            }

            if (inBounds(hole.y-5, hole.y+5, golfball.y) && inBounds(hole.x-5, hole.x+5, golfball.x)) {
                golfball.velo.magnitude = 0;
                golfball.startVelo.magnitude = 0;
                golfball.accel = 0;
                golfball.startX = golfball.x;
                golfball.startY = golfball.y;
            }
            else if (inBounds(hole.y, hole.y + hole.texture.textureRect.h, golfball.y) && inBounds(hole.x, hole.x + hole.texture.textureRect.w, golfball.x) && !scored) {
                startTime = SDL_GetTicks();
                golfball.accel = 0;
                golfball.startVelo.theta = vectorCalcTheta(hole.x-golfball.x, golfball.y-hole.y);
                golfball.velo = golfball.startVelo;
                golfball.startX = golfball.x;
                golfball.startY = golfball.y;
                scored = true;
            }
        }
        

        SDL_RenderClear(window->renderer);
        reloadHole(&hole);
        reloadGolfBall(&golfball);
        SDL_RenderPresent(window->renderer);        
    }

    return 0;
}

int closeWindow(Window* window) {
    SDL_DestroyWindow(window->window);
    SDL_Quit();
    return 0;
}