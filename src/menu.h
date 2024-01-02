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
        int* display_w;
        int* display_h;
        double cursor_position_x, cursor_position_y;

        Button buttons[4];
        int currentButtonIndex = 0;

        Menu(int* display_width, int* display_height) {
            display_w = display_width;
            display_h = display_height;
        }

        void addButton(char* texturePath, float width, float height, float x, float y) {
            Button newButton(texturePath, width, height, x, y);

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

        void render(Shader* menuShader, glm::mat4 projection) {
            // std::cout << cursor_position_x << "\t" << abs(cursor_position_y - (double)600.0) << std::endl;

            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
                Button currentButton = buttons[i];

                if(currentButton.active) {
                    if(checkHover(currentButton)) currentButton.scale(2.0f);
                    currentButton.setProjection(menuShader, projection);
                    currentButton.setUniformMatrix4fv(menuShader, (char*)"model");
                    currentButton.render();
                }
            }
        }

};

#endif