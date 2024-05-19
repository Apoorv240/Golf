#include "intro.h"
#include "collision.h"

int collidedId;

void initIntroScreen(Window* window, IntroScreen* introScreen) {
    introScreen->titleText.texture.renderer = window->renderer;
    setTextFont(&introScreen->titleText, "arial.ttf", 60);
    setTextColor(&introScreen->titleText, 255, 255, 255, 255);
    setText(&introScreen->titleText, "Golf!");
    introScreen->titleText.x = (int)((window->width - introScreen->titleText.w)/2);
    introScreen->titleText.y = 150;
    setText(&introScreen->titleText, "Golf!");

    introScreen->playText.texture.renderer = window->renderer;
    setTextFont(&introScreen->playText, "arial.ttf", 25);
    setTextColor(&introScreen->playText, 255, 255, 255, 255);
    setText(&introScreen->playText, "Play");
    introScreen->playText.x = (int)((window->width - introScreen->playText.w)/2);
    introScreen->playText.y = 300;
    setText(&introScreen->playText, "Play");
    updateColliderBox(&introScreen->playButtonCollider, introScreen->playText.x, introScreen->playText.y, introScreen->playText.w, introScreen->playText.h);
    introScreen->playButtonCollider.id = 0;

    introScreen->quitText.texture.renderer = window->renderer;
    setTextFont(&introScreen->quitText, "arial.ttf", 25);
    setTextColor(&introScreen->quitText, 255, 255, 255, 255);
    setText(&introScreen->quitText, "Quit");
    introScreen->quitText.x = (int)((window->width - introScreen->quitText.w)/2);
    introScreen->quitText.y = 350;
    setText(&introScreen->quitText, "Quit");
    updateColliderBox(&introScreen->quitButtonCollider, introScreen->quitText.x, introScreen->quitText.y, introScreen->quitText.w, introScreen->quitText.h);
    introScreen->quitButtonCollider.id = 1;

    updateColliderBox(&introScreen->mouseCollider, 0, 0, 5, 5);

    initCollisionDetector(&introScreen->collisionDetector);

    introScreen->collisionDetector.c0 = &introScreen->mouseCollider;
    addCollider(&introScreen->collisionDetector, &introScreen->playButtonCollider);
    addCollider(&introScreen->collisionDetector, &introScreen->quitButtonCollider);

    
    introScreen->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    SDL_SetCursor(introScreen->cursor);
}

void updateIntroScreen(Window* window, IntroScreen* introScreen) {
    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    updateColliderBox(&introScreen->mouseCollider, mouseX, mouseY, 5, 5);


    if (detectCollision(&introScreen->collisionDetector) != 0) {
        introScreen->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        SDL_SetCursor(introScreen->cursor);

        collidedId = introScreen->collisionDetector.justCollided->id;
        if (collidedId == 0) {
            setTextColor(&introScreen->playText, 0, 0, 0, 255);
            setText(&introScreen->playText, "Play");
        } else if (collidedId == 1) {
            setTextColor(&introScreen->quitText, 0, 0, 0, 255);
            setText(&introScreen->quitText, "Quit");
        }
    } else {
        setTextColor(&introScreen->playText, 255, 255, 255, 255);
        setText(&introScreen->playText, "Play");
        setTextColor(&introScreen->quitText, 255, 255, 255, 255);
        setText(&introScreen->quitText, "Quit");

        introScreen->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
        SDL_SetCursor(introScreen->cursor);

        collidedId = -1;
    }

    SDL_RenderClear(window->renderer);
    renderText(&introScreen->titleText);
    renderText(&introScreen->playText);
    renderText(&introScreen->quitText);
    SDL_RenderPresent(window->renderer);
}

void handleEventIntroScreen(SDL_Event e, IntroScreen* introScreen, Window* window) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (collidedId == 0) {
            window->goToGame = true;
        } if (collidedId == 1) {
            window->quit = true;
        }
    }
}