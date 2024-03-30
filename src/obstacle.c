#include "obstacle.h"

void initObstacle(Obstacle* obstacle) {
    createTexture(&obstacle->texture, 200, 200, obstacle->x, obstacle->y);
    updateColliderBoxFromRect(&obstacle->colliderBox, obstacle->texture.textureRect);
}

void renderObstacle(Obstacle* obstacle) {
    setTexturePosition(&obstacle->texture, 200, 200, obstacle->x, obstacle->y);
    updateColliderBoxFromRect(&obstacle->colliderBox, obstacle->texture.textureRect);
    displayTexture(&obstacle->texture);
}