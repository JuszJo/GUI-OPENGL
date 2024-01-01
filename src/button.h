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
        float buttonWidth;
        float buttonHeight;

        Button(char* texturePath, float width, float height) {
            buttonWidth = width;
            buttonHeight = height;

            float vertices[20] = {
                0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                width, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, height, 0.0f, 0.0f, 0.0f,
                width, height, 0.0f, 1.0f, 0.0f
            };
            genVertexandBuffers(&VAO, &VBO);
            bindVAO(VAO);

            int verticeSize = sizeof(vertices);
            handleVertexBufferObject(VBO, vertices, verticeSize);

            handleVertexArrayObject(0, 3, stride, 0);
            handleVertexArrayObject(1, 2, stride, 3);

            cleanupBuffers();

            loadImage(texturePath);
        }

        void render() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};

#endif