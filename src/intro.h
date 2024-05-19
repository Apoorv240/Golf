#pragma once

#include "text.h"
#include "window.h"
#include "collisionDetector.h"

struct {
    Text titleText;
    Text playText;
    Text quitText;

    ColliderBox playButtonCollider;
    ColliderBox quitButtonCollider;
    ColliderBox mouseCollider;

    CollisionDetector collisionDetector;

    SDL_Cursor *cursor;
} typedef IntroScreen;

void initIntroScreen(Window* window, IntroScreen* introScreen);
void updateIntroScreen(Window* window, IntroScreen* introScreen);
void renderIntroScreen(Window* window, IntroScreen* introScreen);
void handleEventIntroScreen(SDL_Event e, IntroScreen* introScreen, Window* window);