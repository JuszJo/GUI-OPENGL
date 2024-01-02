#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

#include "src/square.h"
#include "src/button.h"
#include "src/menu.h"

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
    // Button button((char*)"src\\assets\\playbutton.png", 50.0f, 30.0f, 0.0f, 0.0f);
    Menu menu(&display_w, &display_h);

    menu.addButton((char*)"src\\assets\\playbutton.png", 100.0f, 50.0f, 50.0f, 25.0f);

    glm::mat4 projection = glm::mat4(1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwGetCursorPos(window, &menu.cursor_position_x, &menu.cursor_position_y);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -1.0f, 1.0f);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // shader.use();
        // square.setProjection(&shader, projection);
        // square.render();

        menuShader.use();
        menu.render(&menuShader, projection);
        // button.setProjection(&menuShader, projection);
        // button.render();
        
        glfwSwapBuffers(window);
    }

    return 1;
}