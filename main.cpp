#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

#include "src/square.h"
#include "src/button.h"
#include "src/menu.h"
#include "src/background.h"
#include "src/player.h"

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
    // Button button((char*)"src\\assets\\playbutton.png", 50.0f, 30.0f, 0.0f, 0.0f);
    Background bg((char*)"src\\assets\\bg2.jpg", 600.0f, 600.0f, 0.0f, 0.0f);
    Menu menu(&display_w, &display_h);

    menu.addButton((char*)"src\\assets\\playbutton.png", 100.0f, 50.0f, 50.0f, 25.0f);
    menu.addButton((char*)"src\\assets\\quitbutton.png", 100.0f, 50.0f, 50.0f, 300.0f);

    Player player((char*)"src\\assets\\player.png", 78.0f, 58.0f, 100.0f, 200.0f);

    player.scale(1.5f, 1.5f);

    glm::mat4 projection = glm::mat4(1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwGetCursorPos(window, &menu.cursor_position_x, &menu.cursor_position_y);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -1.0f, 1.0f);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        player.setUniformMatrix4fv(&shader, (char*)"model");
        player.setProjection(&shader, projection);
        player.shouldAnimate = true;
        player.animate(&shader);
        player.render();

        // menuShader.use();
        // menu.render(&menuShader, projection);
        // button.setProjection(&menuShader, projection);
        // button.render();
        // bg.scale((display_w / bg.backgroundWidth), (display_h / bg.backgroundHeight));
        // bg.setUniformMatrix4fv(&menuShader, (char*)"model");
        // bg.setProjection(&menuShader, projection);
        // bg.animate(&menuShader);
        // bg.render();
        
        glfwSwapBuffers(window);
    }

    return 1;
}