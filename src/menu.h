#ifndef MENU_H
#define MENU_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../libs/shader.h"

// #include "entity.h"
#include "button.h"

class Menu {
    private:
        

    public:
        double cursor_position_x, cursor_position_y;

        Button buttons[4];
        int currentButtonIndex = 0;

        Menu() {}

        void addButton(char* texturePath, float width, float height, float x, float y) {
            Button newButton(texturePath, width, height, x, y);

            newButton.active = true;

            buttons[currentButtonIndex] = newButton;

            ++currentButtonIndex;
        }

        bool checkHover(Button currentButton) {
            if(
                cursor_position_x > currentButton.buttonX &&
                cursor_position_x < currentButton.buttonX + currentButton.buttonWidth &&
                cursor_position_y > currentButton.buttonY &&
                cursor_position_y < currentButton.buttonY + currentButton.buttonHeight
            ) {
                return true;
            }
            else {
                return false;
            }
        }

        void render(Shader* menuShader, glm::mat4 projection) {
            // std::cout << cursor_position_x << "\t" << cursor_position_y << std::endl;

            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
                Button currentButton = buttons[i];

                if(currentButton.active) {
                    if(checkHover(currentButton)) currentButton.scale(0.9f);
                    currentButton.setProjection(menuShader, projection);
                    currentButton.setUniformMatrix4fv(menuShader, (char*)"model");
                    currentButton.render();
                }
            }
        }

};

#endif