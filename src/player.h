#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity.h"
#include "animation.h"
#include "gravity.h"

class Player: public Entity {
    private:
        int stride = 5;

    public:
        unsigned int TBO2, TBO3, TBO4;

        float playerWidth, playerHeight, playerX, playerY;
        const char* axis = "origin";

        bool shouldAnimate = false;

        float currentFrame = 1.0f;

        // AnimatedState idle = {(char*)"idle", 11.0f, 4, 1, nullptr, false};

        // AnimatedState currentAnimatedState[1];

        // int elapsedFrames = 0;

        Animation animation;

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

        Gravity gravity;

        // float jumpForce = 10.0f;
        // bool shouldJump = false;
        // bool canJump = true;

        // float gForce = 1.0f;

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
            loadImage((char*)"src\\assets\\player2.png", &TBO3);
            loadImage((char*)"src\\assets\\playerup.png", &TBO4);

            // idle.TBO = &TBO2;

            // currentAnimatedState[0] = idle;

            Animation newAnimation((char*)"idle", 11.0f, 4, 1, nullptr, false);

            newAnimation.updateTextureBuffer(&TBO2);

            animation = newAnimation;
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
            else if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                // if(canJump) {
                //     gForce = 1.0f;
                //     shouldJump = true;
                //     canJump = false;
                // }
            }
            else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                if(currentState != LEFT) currentState = LEFT;
            }
            else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                if(currentState != RIGHT) currentState = RIGHT;
            }
            else {
                currentState = IDLE;
            }
        }

        // void resetAnimation(AnimatedState currentAnimation) {
        //     elapsedFrames = 0;
        //     currentFrame = currentAnimation.reversed ? currentAnimation.totalFrames : 1;
        // }

        // void pickAnimation(char* name, float numberFrames, int animationBuffer, int textureIndex, unsigned int* textureBuffer, bool reversed) {
            // if(currentAnimatedState[0].name != name) {
            //     AnimatedState animatedState;
            //     animatedState.name = name;
            //     animatedState.totalFrames = numberFrames;
            //     animatedState.animateBuffer = animationBuffer;
            //     animatedState.textureIndex = textureIndex;
            //     animatedState.TBO = textureBuffer;
            //     animatedState.reversed = reversed;

            //     currentAnimatedState[0] = animatedState;

            //     resetAnimation(currentAnimatedState[0]);
            // }
        // }

        void checkState() {
            switch (currentState) {
                case LEFT:
                    // pickAnimation((char*)"left", 8.0f, 4, 0, &TBO3, true);
                    animation.setCurrentAnimation((char*)"left", 8.0f, 4, 2, &TBO3, true);
                    speed = glm::vec3(-acceleration, speed.y, 0.0f);
                    animation.shouldAnimate = true;
                    
                    break;

                case RIGHT:
                    // pickAnimation((char*)"right", 8.0f, 4, 0, &TBO, false);
                    animation.setCurrentAnimation((char*)"right", 8.0f, 4, 0, &TBO, false);
                    speed = glm::vec3(acceleration, speed.y, 0.0f);
                    animation.shouldAnimate = true;
                    
                    break;

                case IDLE:
                    // pickAnimation((char*)"idle", 11.0f, 4, 1, &TBO2, false);
                    animation.setCurrentAnimation((char*)"idle", 11.0f, 4, 1, &TBO2, false);
                    speed = glm::vec3(0.0f, speed.y, 0.0f);
                    animation.shouldAnimate = true;
                    
                    break;
                
                default:
                    break;
            }
        }

        void move() {
            model = glm::translate(model, speed);
            playerX += speed.x;
            playerY += speed.y;
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

        // void animate(Shader* shader) {
        //     if(shouldAnimate) {
        //         if(elapsedFrames % currentAnimatedState[0].animateBuffer == 0) {
        //             if(!currentAnimatedState[0].reversed) animateForward(currentAnimatedState[0]);
        //             else animateReversed(currentAnimatedState[0]);

        //             elapsedFrames = 0;
        //         }

        //         ++elapsedFrames;
        //     }
        //     else {
        //         resetAnimation(currentAnimatedState[0]);
        //     }
        // }

        // void animateForward(AnimatedState currentAnimation) {
        //     if(currentFrame >= currentAnimation.totalFrames) currentFrame = 1;
        //     else ++currentFrame;
        // }

        // void animateReversed(AnimatedState currentAnimation) {
        //     if(currentFrame <= 1) currentFrame = currentAnimation.totalFrames;
        //     else --currentFrame;
        // }

        void render(Shader* shader) {
            // std::cout << currentAnimatedState[0].name << "\t" << currentAnimatedState[0].totalFrames << "\t" << currentFrame <<std::endl;
            // setUniform1f(shader, (char*)"totalFrames", currentAnimatedState[0].totalFrames);
            setUniform1f(shader, (char*)"totalFrames", animation.currentAnimatedState[0].totalFrames);
            setUniform1f(shader, (char*)"currentFrame", animation.currentFrame);
            glBindTexture(GL_TEXTURE_2D, *animation.currentAnimatedState[0].TBO);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        }

        void update(Shader* shader) {
            gravity.applyGravity(&speed);
            checkState();
            move();
            // applyGravity();
            animation.animate();
            // animate(shader);

            // std::cout << currentAnimatedState[0].name << std::endl;
        }
};

#endif