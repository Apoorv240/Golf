#pragma once

#include <SDL.h>

struct {
    int x;
    int y;
    int w;
    int h;
} typedef ColliderBox;

void updateColliderBoxFromRect(ColliderBox* colliderBox, SDL_Rect rect);
void updateColliderBox(ColliderBox* colliderBox, int x, int y, int w, int h);
int checkCollision(ColliderBox* box1, ColliderBox* box2);