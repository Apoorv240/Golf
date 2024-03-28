#include "game.h"
#include <math.h>

int elapsedTime;
int lastFrameTimeElapsed;
double deltaTime;

void init(Window* window, Entities* entities) {
    entities->golfball.texture.texture = NULL;
    entities->golfball.texture.renderer = window->renderer;
    entities->golfball.texture.imagePath = "image.png";

    entities->golfball.accel = -2;
    entities->golfball.velo.magnitude = 0;//50;
    entities->golfball.velo.theta = 30;

    entities->golfball.x = 400;
    entities->golfball.y = 400;

    entities->golfball.moving = false;
    entities->golfball.scored = false;

    entities->hole.texture.texture = NULL;
    entities->hole.texture.renderer = window->renderer;
    entities->hole.texture.imagePath = "hole.png";
    entities->hole.x = 175;
    entities->hole.y = 175;

    for (int i = 0; i < NUM_GUIDE_CIRCLES; i++) {
        entities->guide.textures[i].texture = NULL;
        entities->guide.textures[i].renderer = window->renderer;
        entities->guide.textures[i].imagePath = "image.png";
    }

    entities->guide.enabled = false;
    entities->guide.startX = 300;
    entities->guide.startY = 300;
    entities->guide.vector.magnitude = 50;
    entities->guide.vector.theta = 30;

    initGolfball(&entities->golfball);
    initHole(&entities->hole);
    initGuide(&entities->guide);
}

bool mouseDown = false;
int mouseXi;
int mouseYi;
int mouseXf;
int mouseYf;
void handleEvent(SDL_Event e, Entities* entities) {
    if (e.type == SDL_MOUSEBUTTONDOWN && !entities->golfball.moving && !entities->golfball.scored) {
        printf("mousebuttondown");
        mouseDown = true;
        SDL_GetMouseState(&mouseXi, &mouseYi);
    }
    if (e.type == SDL_MOUSEBUTTONUP && mouseDown) {
        printf("mousebuttonup");
        mouseDown = false;
        SDL_GetMouseState(&mouseXf, &mouseYf);
        entities->golfball.velo.magnitude = bounds(0, 120, sqrt(pow(mouseXf - mouseXi, 2) + pow(mouseYf - mouseYi, 2))) * 2 / 3;
        entities->golfball.velo.theta = vectorCalcTheta(-(mouseXf - mouseXi), mouseYf - mouseYi);
        entities->golfball.moving = true;
        entities->golfball.accel = -2;
    }
}

void loop(Window* window, Entities* entities) {
    elapsedTime = SDL_GetTicks();

    moveGolfBall(&entities->golfball, 
                    vectorCalcX(entities->golfball.velo) * deltaTime, 
                    vectorCalcY(entities->golfball.velo) * deltaTime,
                    entities->golfball.accel * deltaTime);

    if (entities->golfball.velo.magnitude <= 0) stopGolfBall(&entities->golfball);

    if (checkGolfBallCollisionY(&entities->golfball, 0, window->height)) {
        entities->golfball.velo.theta = 360 - entities->golfball.velo.theta;
        entities->golfball.y = bounds(1, window->height - entities->golfball.texture.textureRect.h - 1, entities->golfball.y);
    }
    if (checkGolfBallCollisionX(&entities->golfball, 0, window->width)) {
        entities->golfball.velo.theta = 180 - entities->golfball.velo.theta;
        entities->golfball.x = bounds(1, window->width - entities->golfball.texture.textureRect.h - 1, entities->golfball.x);
    }

    if (!entities->golfball.scored && checkGolfBallCollisionHole(&entities->golfball, entities->hole.texture.textureRect.x, entities->hole.texture.textureRect.y, entities->hole.texture.textureRect.w, entities->hole.texture.textureRect.h)) {
        entities->golfball.scored = true;
        entities->golfball.velo.theta = vectorCalcTheta(entities->hole.x-entities->golfball.x, entities->golfball.y-entities->hole.y);
    }
    if (entities->golfball.scored && checkGolfBallScored(&entities->golfball, entities->hole.texture.textureRect.x, entities->hole.texture.textureRect.y, entities->hole.texture.textureRect.w, entities->hole.texture.textureRect.h)) {
        stopGolfBall(&entities->golfball);
    }


    if (mouseDown) {
        SDL_GetMouseState(&mouseXf, &mouseYf);
        entities->guide.enabled = true;
        entities->guide.startX = entities->golfball.x + entities->golfball.texture.textureRect.w/2 - 5;
        entities->guide.startY = entities->golfball.y + entities->golfball.texture.textureRect.h/2 - 5;
        entities->guide.vector.magnitude = bounds(0, 120, sqrt(pow(mouseXf - mouseXi, 2) + pow(mouseYf - mouseYi, 2)));
        entities->guide.vector.theta = -vectorCalcTheta(-(mouseXf - mouseXi), mouseYf - mouseYi);
    } else {
        entities->guide.enabled = false;
    }
    
    render(window, entities);
    deltaTime = (elapsedTime - lastFrameTimeElapsed) * 0.01;
    lastFrameTimeElapsed = elapsedTime;
}

void render(Window* window, Entities* entities) {
    SDL_RenderClear(window->renderer);

    renderHole(&entities->hole);
    renderGolfBall(&entities->golfball);
    renderGuide(&entities->guide);

    SDL_RenderPresent(window->renderer);
}