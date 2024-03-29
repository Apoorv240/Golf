#include "collisionDetector.h"
#include <stdio.h>

int detectCollision(CollisionDetector* collisionDetector) {
    int collision1;
    int collision2;
    int collision3;
    int collision4;

    collision1 = checkCollision(&collisionDetector->c0, &collisionDetector->c1);
    collision2 = checkCollision(&collisionDetector->c0, &collisionDetector->c2);
    collision3 = checkCollision(&collisionDetector->c0, &collisionDetector->c3);
    collision4 = checkCollision(&collisionDetector->c0, &collisionDetector->c4);

    printf("%i, %i, %i, %i\n", collision1, collision2, collision3, collision4);

    if (collision1 != 0) return collision1;
    if (collision2 != 0) return collision2;
    if (collision3 != 0) return collision3;
    if (collision4 != 0) return collision4;
}