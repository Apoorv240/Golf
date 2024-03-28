#pragma once

#include <SDL.h>

struct {
    int x;
    int y;
    int w;
    int h;
} typedef ColliderBox;

void initColliderBoxFromRect(ColliderBox* colliderBox, SDL_Rect rect);
void initColliderBox(ColliderBox* colliderBox, int x, int y, int w, int h);
int checkCollision(ColliderBox* box1, ColliderBox* box2);