#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Controller {
    public:
        struct Keys {
            bool w = false;
            bool a = false;
            bool s = false;
            bool d = false;
            bool f = false;
            bool space = false;
        };

        Keys key;

        Controller() {}

        void processInput(GLFWwindow* window) {
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) key.w = true;
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) key.w = false;

            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) key.s = true;
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) key.s = false;

            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) key.a = true;
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) key.a = false;

            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) key.d = true;
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) key.d = false;

            if(glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) key.f = true;
            if(glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE) key.f = false;

            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) key.space = true;
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) key.space = false;   
        }

};

#endif