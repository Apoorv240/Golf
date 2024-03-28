#pragma once

#include "texture.h"
#include "util.h"

#define NUM_GUIDE_CIRCLES 5

struct {
    Vector vector;
    int startX;
    int startY;

    bool enabled;

    Texture textures[NUM_GUIDE_CIRCLES];
} typedef Guide;

void initGuide(Guide* guide);
void renderGuide(Guide* guide);