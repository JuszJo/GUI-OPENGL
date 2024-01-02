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
        float buttonWidth, buttonHeight, buttonX, buttonY;
        bool active = false;

        // default constructor
        Button() {}

        Button(char* texturePath, float width, float height, float x, float y) {
            buttonWidth = width;
            buttonHeight = height;
            buttonX = x;
            buttonY = y;

            float vertices[20] = {
                x, y, 0.0f, 0.0f, 1.0f,
                x + width, y, 0.0f, 1.0f, 1.0f,
                x, y + height, 0.0f, 0.0f, 0.0f,
                x + width, y + height, 0.0f, 1.0f, 0.0f
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

        void scale(float scaleFactor) {
            float scaledWidth = buttonWidth * scaleFactor;
            float scaledHeight = buttonHeight * scaleFactor;

            model = glm::translate(model, glm::vec3((300 - (scaledWidth / 2)) + (scaledWidth / 2), (300 - (scaledHeight / 2)) + (scaledHeight / 2), 0.0f));
            
            model = glm::scale(model, glm::vec3(scaleFactor, scaleFactor, 1.0f));
            
            model = glm::translate(model, glm::vec3(-(buttonX + (buttonWidth / 2)), -(buttonY + (buttonHeight / 2)), 0.0f));
        }

        void render() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};

#endif