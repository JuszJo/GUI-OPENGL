#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

class Background: public Entity {
    private:
        int stride = 5;

    public:
        float backgroundWidth, backgroundHeight, backgroundX, backgroundY;
        const char* axis = "origin";
        // float totalFrames = 2.0f;

        bool shouldAnimate = false;

        float totalFrames = 1.0f;
        float currentFrame = 1.0f;

        int animateBuffer = 1000;
        int elapsedFrames = 0;

        // default constructor
        Background() {}

        Background(char* texturePath, float width, float height, float x, float y) {
            backgroundWidth = width;
            backgroundHeight = height;
            backgroundX = x;
            backgroundY = y;

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

        void updatePosition(float newbackgroundX, float newbackgroundY) {
            backgroundX = newbackgroundX;
            backgroundY = newbackgroundY;
        }

        void updateSize(float newbackgroundWidth, float newbackgroundHeight) {
            backgroundWidth = newbackgroundWidth;
            backgroundHeight = newbackgroundHeight;
        }

        void setPosition(float newbackgroundX, float newbackgroundY) {
            model = glm::translate(model, glm::vec3(newbackgroundX, newbackgroundY, 0.0f));

            model = glm::translate(model, glm::vec3(-backgroundX, -backgroundY, 0.0f));

            updatePosition(newbackgroundX, newbackgroundY);
        }

        void scale(float scaleFactorX, float scaleFactorY) {
            float scaledWidth = backgroundWidth * scaleFactorX;
            float scaledHeight = backgroundHeight * scaleFactorY;

            if(axis == (char*)"center") {
                float dWidth = scaledWidth - backgroundWidth;
                float dHeight = scaledHeight - backgroundHeight;

                float newbackgroundX = backgroundX - (dWidth / 2);
                float newbackgroundY = backgroundY - (dHeight / 2);

                model = glm::translate(model, glm::vec3(backgroundX + (backgroundWidth / 2), backgroundY + (backgroundHeight / 2), 0.0f));

                model = glm::scale(model, glm::vec3(scaleFactorX, scaleFactorY, 1.0f));

                model = glm::translate(model, glm::vec3(-(backgroundX + (backgroundWidth / 2)), -(backgroundY + (backgroundHeight / 2)), 0.0f));

                updatePosition(newbackgroundX, newbackgroundY);
            }
            else {
                model = glm::translate(model, glm::vec3(backgroundX, backgroundY, 0.0f));

                model = glm::scale(model, glm::vec3(scaleFactorX, scaleFactorY, 1.0f));

                model = glm::translate(model, glm::vec3(-backgroundX, -backgroundY, 0.0f));
            }
            updateSize(scaledWidth, scaledHeight);
        }

        void animate(Shader* shader) {
            if(shouldAnimate) {
                if(elapsedFrames % animateBuffer == 0) {
                    if(currentFrame > totalFrames) currentFrame = 1;

                    setUniform1f(shader, (char*)"totalFrames", totalFrames);
                    setUniform1f(shader, (char*)"currentFrame", currentFrame);

                    ++currentFrame;

                    elapsedFrames = 0;
                }

                ++elapsedFrames;
            }
            else {
                currentFrame = 1;
                elapsedFrames = 0;

                setUniform1f(shader, (char*)"totalFrames", totalFrames);
                setUniform1f(shader, (char*)"currentFrame", currentFrame);
            }
        }

        void render() {
            glBindTexture(GL_TEXTURE_2D, TBO);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }
};

#endif