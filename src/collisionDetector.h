#pragma once

#include "collision.h"

#define COLLISIONDETECTOR_ARRAY_SIZE 100

struct {
    ColliderBox* c0;

    ColliderBox* colliders[COLLISIONDETECTOR_ARRAY_SIZE];
    unsigned int numColliders;
    
    ColliderBox* justCollided;
} typedef CollisionDetector;

void initCollisionDetector(CollisionDetector* collisionDetector);
int detectCollision(CollisionDetector* collisionDetector);
int addCollider(CollisionDetector* collisionDetector, ColliderBox* collider);