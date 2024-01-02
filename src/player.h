#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

class Player: public Entity {
    private:
        int stride = 5;

    public:
        float playerWidth, playerHeight, playerX, playerY;
        const char* axis = "origin";

        bool shouldAnimate = false;

        float totalFrames = 8.0f;
        float currentFrame = 1.0f;

        int animateBuffer = 1000;
        int elapsedFrames = 0;

        // default constructor
        Player() {}

        Player(char* texturePath, float width, float height, float x, float y) {
            playerWidth = width;
            playerHeight = height;
            playerX = x;
            playerY = y;

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

        void updatePosition(float newPlayerX, float newPlayerY) {
            playerX = newPlayerX;
            playerY = newPlayerY;
        }

        void updateSize(float newPlayerWidth, float newPlayerHeight) {
            playerWidth = newPlayerWidth;
            playerHeight = newPlayerHeight;
        }

        void setPosition(float newPlayerX, float newPlayerY) {
            model = glm::translate(model, glm::vec3(newPlayerX, newPlayerY, 0.0f));

            model = glm::translate(model, glm::vec3(-playerX, -playerY, 0.0f));

            updatePosition(newPlayerX, newPlayerY);
        }

        void scale(float scaleFactorX, float scaleFactorY) {
            float scaledWidth = playerWidth * scaleFactorX;
            float scaledHeight = playerHeight * scaleFactorY;

            if(axis == (char*)"center") {
                float dWidth = scaledWidth - playerWidth;
                float dHeight = scaledHeight - playerHeight;

                float newPlayerX = playerX - (dWidth / 2);
                float newPlayerY = playerY - (dHeight / 2);

                model = glm::translate(model, glm::vec3(playerX + (playerWidth / 2), playerY + (playerHeight / 2), 0.0f));

                model = glm::scale(model, glm::vec3(scaleFactorX, scaleFactorY, 1.0f));

                model = glm::translate(model, glm::vec3(-(playerX + (playerWidth / 2)), -(playerY + (playerHeight / 2)), 0.0f));

                updatePosition(newPlayerX, newPlayerY);
            }
            else {
                model = glm::translate(model, glm::vec3(playerX, playerY, 0.0f));

                model = glm::scale(model, glm::vec3(scaleFactorX, scaleFactorY, 1.0f));

                model = glm::translate(model, glm::vec3(-playerX, -playerY, 0.0f));

                // std::cout << playerX << "\t" << playerY << std::endl;
                // std::cout << scaleFactorX << "\t" << scaleFactorY << std::endl;
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