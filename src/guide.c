#include "guide.h"


void initGuide(Guide* guide) {
    int dist = guide->vector.magnitude / NUM_GUIDE_CIRCLES;

    for (int i = 0; i < NUM_GUIDE_CIRCLES; i++) {
        Vector v;
        v.magnitude = i * dist;
        v.theta = guide->vector.theta;
        createTexture(&guide->textures[i], 10, 10, guide->startX + vectorCalcX(v), guide->startY + vectorCalcY(v));
    }
}

void renderGuide(Guide* guide) {
    if (!guide->enabled) return;
    int dist = guide->vector.magnitude / NUM_GUIDE_CIRCLES;
    for (int i = 0; i < NUM_GUIDE_CIRCLES; i++) {
        Vector v;
        v.magnitude = i * dist;
        v.theta = guide->vector.theta;
        setTexturePosition(&guide->textures[i], 10, 10, guide->startX + vectorCalcX(v), guide->startY + vectorCalcY(v));
        displayTexture(&guide->textures[i]);
    }
}