#include "collision.h"
#include <stdio.h>
#include <stdbool.h>

void initColliderBoxFromRect(ColliderBox* colliderBox, SDL_Rect rect) {
    colliderBox->x = rect.x;
    colliderBox->y = rect.y;
    colliderBox->h = rect.h;
    colliderBox->w = rect.w;
    //printf("%.2f, %.2f\n", (double)rect.x, (double)rect.w);
}

void initColliderBox(ColliderBox* colliderBox, int x, int y, int w, int h) {
    colliderBox->x = x;
    colliderBox->y = y;
    colliderBox->h = h;
    colliderBox->w = w;
}

/*
0 - no collision
1 - collision on x axis ([][])
2 - collision on y axis ([]
                         [])
*/
int checkCollision(ColliderBox* box1, ColliderBox* box2) {
    int box1l = box1->x;
    int box1r = box1->x + box1->w;
    int box1t = box1->y;
    int box1b = box1->y + box1->w;

    int box2l = box2->x;
    int box2r = box2->x + box2->w;
    int box2t = box2->y;
    int box2b = box2->y + box2->h;

    //printf("%.2f : %.2f", (float)box1l, (double)box1r);
    //printf("|||||%.2f : %.2f \n", (float)box2l, (double)box2r);

    bool collisionX = false;
    bool collisionY = false;

    // if left side of box1 is in between left and right of box2
    if (box1l >= box2l && box1l <= box2r) {
        collisionX = true;
    } 
    // if right side of box1 is in between left and right of box2
    else if (box1r >= box2l && box1r <= box2r) {
        collisionX = true;
    }

    if (box1b >= box2t && box1b <= box2b) {
        collisionY = true;
    }
    else if (box1t >= box2t && box1t <= box2b) {
        collisionY = true;
    }

    if (!collisionY || !collisionX) return 0;
    
    int ldiff = abs(box1r - box2l); // [x][]
    int rdiff = abs(box1l - box2r); // [][x]
    int tdiff = abs(box1b - box2t); /* [x]
                                       [] */
    int bdiff = abs(box1t - box2b); /* []
                                       [x] */

    int maxNum = ldiff; int max = 0;
    if (rdiff > maxNum) { maxNum = rdiff; max = 1; }
    if (tdiff > maxNum) { maxNum = tdiff; max = 2; }
    if (bdiff > maxNum) { maxNum = bdiff; max = 3; }

    if (max == 0 || max == 1) return 1;
    return 2;
}