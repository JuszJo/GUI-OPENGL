#ifndef BUTTON_H
#define BUTTON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

class Button: public Entity {
    private:
        int stride = 5;

    public:
        float width = 50.0f;
        float height = 30.0f;

        float vertices[20] = {
            0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            width, 0.0f, 0.0f, 1.0f, 1.0f,
            0.0f, height, 0.0f, 0.0f, 0.0f,
            width, height, 0.0f, 1.0f, 0.0f
        };

        Button() {
            genVertexandBuffers(&VAO, &VBO);
            bindVAO(VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 2, stride, 3);

            cleanupBuffers();

            loadImage((char*)"src\\assets\\playbutton.png");
        }

        void render() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};

#endif