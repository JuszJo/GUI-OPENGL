#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

#include "src/square.h"

int main() {
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(600, 600, "ImGui Example", NULL, NULL);

    if (!window) {
        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    int display_w, display_h;

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Shader menuShader("shaders/menu/menuVertexShader.glsl", "shaders/menu/menuFragmentShader.glsl");
    Square square;

    bool showDemo = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        square.render();

        menuShader.use();

        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    return 1;
}