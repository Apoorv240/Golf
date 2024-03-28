#include "hole.h"


void initHole(Hole* hole) {
    createTexture(&hole->texture, 30, 30, hole->x, hole->y);
}

void renderHole(Hole* hole) {
    setTexturePosition(&hole->texture, 30, 30, hole->x, hole->y);
    displayTexture(&hole->texture);
}