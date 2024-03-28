#pragma once

#include "texture.h"
#include "util.h"

struct {
    double accel;
    Vector velo;
    
    double x;
    double y;

    bool moving;
    bool scored;

    Texture texture;
} typedef Golfball;

void initGolfball(Golfball* golfball);
void renderGolfBall(Golfball* golfball);
bool checkGolfBallCollisionY(Golfball* golfball, int topBound, int bottomBound);
bool checkGolfBallCollisionX(Golfball* golfball, int leftBound, int rightBound);
bool checkGolfBallCollisionHole(Golfball* golfball, int holeX, int holeY, int holeW, int holeH);
bool checkGolfBallScored(Golfball* golfball, int holeX, int holeY, int holeW, int holeH);
void moveGolfBall(Golfball* golfball, double deltaX, double deltaY, double deltaVeloMag);
void stopGolfBall(Golfball* golfball);