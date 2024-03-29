#pragma once

#include "collision.h"

struct {
    ColliderBox c0;
    ColliderBox c1;
    ColliderBox c2;
    ColliderBox c3;
    ColliderBox c4;
} typedef CollisionDetector;

int detectCollision(CollisionDetector* collisionDetector);