#ifndef GRAVITY_H
#define GRAVITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Gravity {
    public:
        float gForce = 0.5f;

        Gravity() {}

        void applyGravity(glm::vec3* speed) {
            speed -> y -= gForce;
        }
};

#endif