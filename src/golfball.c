#include "golfball.h"

void initGolfball(Golfball* golfball) {
    bool moving = false;
    bool scored = false;

    createTexture(&golfball->texture, 30, 30, (int)golfball->x, (int)golfball->y);
    updateColliderBoxFromRect(&golfball->colliderBox, golfball->texture.textureRect);
}

void renderGolfBall(Golfball* golfball) {
    setTexturePosition(&golfball->texture, 30, 30, (int)golfball->x, (int)golfball->y);
    updateColliderBoxFromRect(&golfball->colliderBox, golfball->texture.textureRect);
    displayTexture(&golfball->texture);
}

bool checkGolfBallCollisionY(Golfball* golfball, int topBound, int bottomBound) {
    return ((golfball->y <= topBound) || (golfball->y >= bottomBound - golfball->texture.textureRect.h));
}

bool checkGolfBallCollisionX(Golfball* golfball, int leftBound, int rightBound) {
    return ((golfball->x <= leftBound) || (golfball->x >= rightBound - golfball->texture.textureRect.h));
}

bool checkGolfBallCollisionHole(Golfball* golfball, int holeX, int holeY, int holeW, int holeH) {
    return (inBounds(holeY, holeY + holeH, golfball->y) && inBounds(holeX, holeX + holeW, golfball->x));
}

bool checkGolfBallScored(Golfball* golfball, int holeX, int holeY, int holeW, int holeH) {
    return (inBounds(holeY-2, holeY+2, golfball->y) && inBounds(holeX-2, holeX+2, golfball->x));
}

void moveGolfBall(Golfball* golfball, double deltaX, double deltaY, double deltaVeloMag) {
    golfball->x += deltaX;
    golfball->y -= deltaY;
    golfball->velo.magnitude += deltaVeloMag;
}

void stopGolfBall(Golfball* golfball) {
    golfball->velo.magnitude = 0;
    golfball->accel = 0;
    golfball->moving = false;
}