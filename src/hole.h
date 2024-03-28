#pragma once

#include "texture.h"

struct {
    int x;
    int y;
    Texture texture;
} typedef Hole;

void initHole(Hole* hole);
void renderHole(Hole* hole);