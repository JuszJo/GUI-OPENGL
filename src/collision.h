#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>

struct CollidableBlock {
    float position_x;
    float position_y;
    float width;
    float height;
};

struct CollisionInfo {
    int collidableBlockIndex;
};

class Collision {
    public:
        CollidableBlock block1 = {0.0f, 0.0f, 50.0f, 50.0f};
        CollidableBlock block2 = {50.0f, 0.0f, 50.0f, 50.0f};

        CollidableBlock blocks[2] = {
            block1,
            block2
        };

        Collision() {}

        void getCollideAxisX() {

        }

        char* getCollideAxisY(float bottom, float top) {
            return bottom > top ? (char*)"bottom" : (char*)"top";
        }

        bool didCollide(float position_x, float position_y, float width, float height, CollidableBlock currentBlock) {
            if(
                position_x < currentBlock.position_x + currentBlock.width &&
                position_x + width > currentBlock.position_x &&
                position_y < currentBlock.position_y + currentBlock.height &&
                position_y + height > currentBlock.position_y
            ) {
                return true;
            }
            else return false;
        }

        CollisionInfo checkCollision(float position_x, float position_y, float width, float height) {
            bool collisionOccured = false;

            for(int i = 0; i < sizeof(blocks) / sizeof(blocks[0]); ++i) {
                CollidableBlock currentBlock = blocks[i];

                if(didCollide(position_x, position_y, width, height, currentBlock)) {
                    collisionOccured = true;

                    CollisionInfo info = {i};

                    return info;
                }
            }

            CollisionInfo info = {-1};

            return info;
        }
};

#endif