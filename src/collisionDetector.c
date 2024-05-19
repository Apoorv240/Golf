#include "collisionDetector.h"
#include <stdio.h>

void initCollisionDetector(CollisionDetector* collisionDetector) {
    collisionDetector->numColliders = 0;
}

int detectCollision(CollisionDetector* collisionDetector) {
    for (int i = 0; i < collisionDetector->numColliders; i++) {

        int collision = checkCollision(collisionDetector->c0, collisionDetector->colliders[i]);
        if (collision != 0) {
            collisionDetector->justCollided = collisionDetector->colliders[i];
            return collision;
        }
    }
    return 0;
}

int addCollider(CollisionDetector* collisionDetector, ColliderBox* collider) {
    collisionDetector->numColliders += 1;
    collisionDetector->colliders[collisionDetector->numColliders-1] = collider;
    return collisionDetector->numColliders - 1;
}