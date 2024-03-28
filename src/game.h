#pragma once

#include "golfball.h"
#include "hole.h"
#include "window.h"
#include "guide.h"

struct {
    Golfball golfball;
    Hole hole;
    Guide guide;
} typedef Entities;

void init(Window* window, Entities* entities);
void loop(Window* window, Entities* entities);
void render(Window* window, Entities* entities);
void handleEvent(SDL_Event e, Entities* entities);