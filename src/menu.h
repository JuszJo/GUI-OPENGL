#ifndef MENU_H
#define MENU_H

#include "../libs/shader.h"

#include "button.h"

class Menu {
    private:
        void startGame() {
            gameStart = true;
            setDisplay(false);
        }

    protected:
        void quit() {
            printf("QUIT\n");
        }

    public:
        bool display = false;
        int* display_w;
        int* display_h;
        double cursor_position_x, cursor_position_y;
        bool mousePressed = false;
        char* name = (char*)"Main Menu";

        Button buttons[4];
        int currentButtonIndex = 0;

        Menu(int* display_width, int* display_height) {
            display_w = display_width;
            display_h = display_height;
        }

        void setDisplay(bool value) {
            display = value;
        }

        void addButton(char* texturePath, float width, float height, float x, float y, char* buttonName) {
            Button newButton(texturePath, width, height, x, y, buttonName);

            newButton.active = true;

            buttons[currentButtonIndex] = newButton;

            ++currentButtonIndex;
        }

        void updateMenuCursor(GLFWwindow* window) {
            glfwGetCursorPos(window, &cursor_position_x, &cursor_position_y);
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

        virtual void runAction(Button currentButton) {
            if(currentButton.name == (char*)"play") {
                startGame();
            }
            if(currentButton.name == (char*)"quit") {
                quit();
            }
        }

        void render(GLFWwindow* window, Shader* menuShader, glm::mat4 projection) {
            // std::cout << name << std::endl;
            // std::cout << mousePressed << std::endl;
            // std::cout << cursor_position_x << "\t" << abs(cursor_position_y - (double)600.0) << std::endl;

            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
                checkMousePress(window);

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

        void stopGame() {
            gameStart = false;
            setDisplay(true);
        }

};

#endif