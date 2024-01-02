#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"

struct AnimatedState {
    char* name;
    float totalFrames;
    int animateBuffer;
    int textureIndex;
    unsigned int* TBO;
};

class Player: public Entity {
    private:
        int stride = 5;

    public:
        unsigned int TBO2;

        float playerWidth, playerHeight, playerX, playerY;
        const char* axis = "origin";

        bool shouldAnimate = false;

        float currentFrame = 1.0f;

        AnimatedState idle = {(char*)"idle", 11.0f, 4, 1, nullptr};

        AnimatedState currentAnimatedState[1];

        int animateBuffer = 4;
        int elapsedFrames = 0;

        glm::vec3 speed = glm::vec3(0.0f, 0.0f, 0.0f);

        float acceleration = 1.0f;

        enum STATE {
            UP,
            DOWN,
            LEFT,
            RIGHT,
            IDLE
        };

        STATE currentState = IDLE;

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

            loadImage(texturePath, &TBO);
            loadImage((char*)"src\\assets\\playeridle.png", &TBO2);

            idle.TBO = &TBO2;

            currentAnimatedState[0] = idle;
        }

        void loadImage(char* path, unsigned int* TBO) {
            int width, height, nChannels;

            stbi_uc* imageData = stbi_load(path, &width, &height, &nChannels, 0);

            if(!imageData) {
                const char* reason = stbi_failure_reason();

                std::cout << reason << std::endl;
            }

            glGenTextures(1, TBO);
            glBindTexture(GL_TEXTURE_2D, *TBO);

            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            if(nChannels > 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
            }

            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(imageData);
        }

        void processInput(GLFWwindow* window) {
            // if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
            //     glfwSetWindowShouldClose(window, true);
            // }
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                
            }
            else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                
            }
            else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                
            }
            else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                if(currentState != RIGHT) currentState = RIGHT;
            }
            else {
                currentState = IDLE;
            }
        }

        void pickAnimation(char* name, float numberFrames, int animationBuffer, int textureIndex, unsigned int* textureBuffer) {
            if(currentAnimatedState[0].name != name) {
                AnimatedState animatedState;
                animatedState.name = name;
                animatedState.totalFrames = numberFrames;
                animatedState.animateBuffer = animateBuffer;
                animatedState.textureIndex = textureIndex;
                animatedState.TBO = textureBuffer;

                currentAnimatedState[0] = animatedState;

                elapsedFrames = 0;
                currentFrame = 0;
            }
        }

        void checkState() {
            switch (currentState) {
                case RIGHT:
                    pickAnimation((char*)"right", 8.0f, 4, 0, &TBO);
                    speed = glm::vec3(acceleration, 0.0f, 0.0f);
                    shouldAnimate = true;
                    
                    break;

                case IDLE:
                    pickAnimation((char*)"idle", 11.0f, 4, 1, &TBO2);
                    speed = glm::vec3(0.0f, 0.0f, 0.0f);
                    shouldAnimate = true;
                    
                    break;
                
                default:
                    break;
            }
        }

        void move() {
            model = glm::translate(model, speed);;
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
            }
            updateSize(scaledWidth, scaledHeight);
        }

        void animate(Shader* shader) {
            if(shouldAnimate) {
                if(elapsedFrames % currentAnimatedState[0].animateBuffer == 0) {
                    if(currentFrame >= currentAnimatedState[0].totalFrames) currentFrame = 1;
                    else {
                        ++currentFrame;
                    }

                    elapsedFrames = 0;
                }

                ++elapsedFrames;
            }
            else {
                currentFrame = 1;
                elapsedFrames = 0;
            }
        }

        void render(Shader* shader) {
            // std::cout << currentAnimatedState[0].name << "\t" << currentAnimatedState[0].totalFrames << "\t" << currentFrame <<std::endl;
            setUniform1f(shader, (char*)"totalFrames", currentAnimatedState[0].totalFrames);
            setUniform1f(shader, (char*)"currentFrame", currentFrame);
            glBindTexture(GL_TEXTURE_2D, *currentAnimatedState[0].TBO);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        void update(Shader* shader) {
            checkState();
            move();
            animate(shader);

            // std::cout << currentAnimatedState[0].name << std::endl;
        }
};

#endif