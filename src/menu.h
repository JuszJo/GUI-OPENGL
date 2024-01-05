#ifndef MENU_H
#define MENU_H

#include "../libs/shader.h"

// #include "entity.h"
#include "button.h"

class Menu {
    private:
        

    public:
        bool display = true;
        int* display_w;
        int* display_h;
        double cursor_position_x, cursor_position_y;
        bool mousePressed = false;

        Button buttons[4];
        int currentButtonIndex = 0;

        Menu(int* display_width, int* display_height) {
            display_w = display_width;
            display_h = display_height;
        }

        void addButton(char* texturePath, float width, float height, float x, float y, char* buttonName) {
            Button newButton(texturePath, width, height, x, y, buttonName);

            newButton.active = true;

            buttons[currentButtonIndex] = newButton;

            ++currentButtonIndex;
        }

        bool checkHover(Button currentButton) {
            if(
                cursor_position_x < currentButton.buttonX + currentButton.buttonWidth &&
                cursor_position_x > currentButton.buttonX &&
                abs(cursor_position_y - *display_h) < currentButton.buttonY + currentButton.buttonHeight &&
                abs(cursor_position_y - *display_h) > currentButton.buttonY
            ) {
                return true;
            }
            else {
                return false;
            }
        }

        void checkMousePress(GLFWwindow* window) {
            if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                mousePressed = true;
            }
            else {
                mousePressed = false;
            }
        }

        void startGame() {
            gameStart = true;
            display = false;
        }

        void pause() {
            gameStart = false;
            display = true;
        }

        void runAction(Button currentButton) {
            if(currentButton.name == (char*)"play") {
                startGame();
            }
        }

        void render(Shader* menuShader, glm::mat4 projection) {
            // std::cout << mousePressed << std::endl;
            // std::cout << cursor_position_x << "\t" << abs(cursor_position_y - (double)600.0) << std::endl;

            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
                Button currentButton = buttons[i];

                if(currentButton.active) {
                    if(checkHover(currentButton)) currentButton.scale(2.0f, 2.0f);
                    if(checkHover(currentButton) && mousePressed) {
                        runAction(currentButton);
                    }
                    currentButton.setProjection(menuShader, projection);
                    currentButton.setUniformMatrix4fv(menuShader, (char*)"model");
                    currentButton.render();
                }
            }
        }

};

#endif