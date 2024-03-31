#pragma once

#include "golfball.h"
#include "hole.h"
#include "window.h"
#include "guide.h"
#include "collisionDetector.h"
#include "obstacle.h"
#include "text.h"

struct {
    Golfball golfball;
    Hole hole;
    Guide guide;
    Obstacle obstacle;
    Obstacle obstacle2;
    Text strokeText;

    CollisionDetector collisionDetector;
} typedef GameEntities;

void initGame(Window* window, GameEntities* entities);
void updateGame(Window* window, GameEntities* entities);
void renderGame(Window* window, GameEntities* entities);
void handleEventGame(SDL_Event e, GameEntities* entities);