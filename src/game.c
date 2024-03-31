#include "game.h"
#include <math.h>
#include "collision.h"

int elapsedTime;
int lastFrameTimeElapsed;
double deltaTime;

int strokes;
char strokeString[20];

void initGame(Window* window, GameEntities* entities) {
    entities->golfball.texture.renderer = window->renderer;
    entities->golfball.texture.imagePath = "image.png";

    entities->golfball.accel = -2;
    entities->golfball.velo.magnitude = 0;//50;
    entities->golfball.velo.theta = 30;

    entities->golfball.x = 500;
    entities->golfball.y = 300;

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

    entities->obstacle.texture.imagePath = "square.png";
    entities->obstacle.texture.renderer = window->renderer;
    entities->obstacle.x = 400;
    entities->obstacle.y = 100;

    entities->obstacle2.texture.imagePath = "square.png";
    entities->obstacle2.texture.renderer = window->renderer;
    entities->obstacle2.x = 100;
    entities->obstacle2.y = 300;

    strokes = 0;
    entities->strokeText.texture.renderer = window->renderer;
    setTextFont(&entities->strokeText, "arial.ttf");
    setTextColor(&entities->strokeText, 255, 255, 255, 255);
    entities->strokeText.x = 10;
    entities->strokeText.y = 10;
    
    sprintf(strokeString, "Strokes: %i", strokes);
    setText(&entities->strokeText, strokeString);

    initGolfball(&entities->golfball);
    initHole(&entities->hole);
    initGuide(&entities->guide);
    initObstacle(&entities->obstacle);
    initObstacle(&entities->obstacle2);
    
    initCollisionDetector(&entities->collisionDetector);
    entities->collisionDetector.c0 = entities->golfball.colliderBox;
    addCollider(&entities->collisionDetector, &entities->obstacle.colliderBox);
    addCollider(&entities->collisionDetector, &entities->obstacle2.colliderBox);
    //entities->collisionDetector.c1 = entities->obstacle.colliderBox;
}

bool mouseDown = false;
int mouseXi;
int mouseYi;
int mouseXf;
int mouseYf;
void handleEventGame(SDL_Event e, GameEntities* entities) {
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

        strokes++;
        sprintf(strokeString, "Strokes: %i", strokes);
        setText(&entities->strokeText, strokeString);
    }
}

void updateGame(Window* window, GameEntities* entities) {
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

    if (detectCollision(&entities->collisionDetector) == 2) {
        entities->golfball.velo.theta = 360 - entities->golfball.velo.theta;
        entities->golfball.y = outsideBounds(
            entities->collisionDetector.justCollided->y - entities->golfball.colliderBox.h - 2, 
            entities->collisionDetector.justCollided->y + entities->collisionDetector.justCollided->h + 2,
            entities->golfball.y
        );
    } else if (detectCollision(&entities->collisionDetector) == 1) {
        entities->golfball.velo.theta = 180 - entities->golfball.velo.theta;
        entities->golfball.x = outsideBounds(
            entities->collisionDetector.justCollided->x - entities->golfball.colliderBox.w - 2, 
            entities->collisionDetector.justCollided->x + entities->collisionDetector.justCollided->w + 2,
            entities->golfball.x
        );
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
    
    renderGame(window, entities);
    deltaTime = (elapsedTime - lastFrameTimeElapsed) * 0.01;
    lastFrameTimeElapsed = elapsedTime;

    entities->collisionDetector.c0 = entities->golfball.colliderBox;
}

void renderGame(Window* window, GameEntities* entities) {
    SDL_RenderClear(window->renderer);

    renderObstacle(&entities->obstacle);
    renderObstacle(&entities->obstacle2);

    renderText(&entities->strokeText);

    renderHole(&entities->hole);
    renderGolfBall(&entities->golfball);
    renderGuide(&entities->guide);
    

    SDL_RenderPresent(window->renderer);
}