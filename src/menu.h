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
        Button buttons[4];
        int currentButtonIndex = 0;

        Menu() {}

        void addButton(char* texturePath, float width, float height, float x, float y) {
            Button newButton(texturePath, width, height, x, y);

            newButton.active = true;

            buttons[currentButtonIndex] = newButton;

            ++currentButtonIndex;
        }

        void render(Shader* menuShader, glm::mat4 projection) {
            for(int i = 0; i < sizeof(buttons) / sizeof(buttons[0]); ++i) {
                Button currentButton = buttons[i];

                if(currentButton.active) {
                    currentButton.setProjection(menuShader, projection);
                    currentButton.render();
                }
            }
        }

};

#endif