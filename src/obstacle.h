#pragma once

#include "texture.h"
#include "collision.h"

struct {
    int x;
    int y;
    Texture texture;
    ColliderBox colliderBox;
} typedef Obstacle;

void initObstacle(Obstacle* obstacle);
void renderObstacle(Obstacle* obstacle);