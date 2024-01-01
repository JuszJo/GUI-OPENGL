#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

class Square: public Entity {
    private:
        int stride = 8;

    public:
        float vertices[32] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.5f, 0.7f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.2f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.3f, 0.1f, 0.3f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.0f, 0.7f, 0.8f, 0.5f, 1.0f, 0.0f
        };

        Square() {
            genVertexandBuffers(&VAO, &VBO);
            bindVAO(VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 3, stride, 3);
            handleVertexArrayObject(2, 2, stride, 6);

            cleanupBuffers();

            loadImage((char*)"src\\assets\\playbutton.png");
        }

        void render() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};

#endif