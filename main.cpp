#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

// #include "src/square.h"
// #include "src/button.h"
// #include "src/menu.h"

struct Camera {
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 cameraFaceDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float cameraSpeed = 2.0f;
};

#include "src/background.h"
#include "src/player.h"

Camera camera;

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // const float cameraSpeed = 1.0f; // adjust accordingly
    // forward
    // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos += cameraSpeed * cameraFaceDirection;
    // // backward
    // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) cameraPos -= cameraSpeed * cameraFaceDirection;
    // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.cameraPos -= glm::normalize(glm::cross(camera.cameraFaceDirection, camera.cameraUp)) * cameraSpeed;
    // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.cameraPos += glm::normalize(glm::cross(camera.cameraFaceDirection, camera.cameraUp)) * cameraSpeed;

    // std::cout << cameraPos.x << "\t" << cameraPos.y << std::endl;
}

int main() {
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "ImGui Example", NULL, NULL);

    if (!window) {
        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    int display_w, display_h;

    // Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    // Shader menuShader("shaders/menu/menuVertexShader.glsl", "shaders/menu/menuFragmentShader.glsl");
    // Button button((char*)"src\\assets\\playbutton.png", 50.0f, 30.0f, 0.0f, 0.0f);
    // Background bg((char*)"src\\assets\\bg.jpg", 600.0f, 600.0f, 0.0f, 0.0f);
    // Menu menu(&display_w, &display_h);

    // menu.addButton((char*)"src\\assets\\playbutton.png", 100.0f, 50.0f, 50.0f, 25.0f);
    // menu.addButton((char*)"src\\assets\\quitbutton.png", 100.0f, 50.0f, 50.0f, 300.0f);

    // Square square((char*)"src\\assets\\playbutton.png", 50.0f, 50.0f, 100.0f, 100.0f);

    // square.scale(2.0f, 2.0f);

    // Player player((char*)"src\\assets\\player.png", 78.0f, 58.0f, 0.0f, 500.0f);

    // player.model = glm::translate(player.model, glm::vec3(200.0f, 0.0f, 0.0f));

    // model = glm::translate(model, glm::vec3(-playerX, -playerY, 0.0f));

    // player.setPosition(500.0f, 500.0f);

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Shader bgShader("shaders/background/bgVertexShader.glsl", "shaders/background/bgFragmentShader.glsl");
    Shader cShader("shaders/collision/collisionVertexShader.glsl", "shaders/collision/collisionFragmentShader.glsl");
    BackgroundBeta bgBeta((char*)"src\\assets\\bg.jpg", 0.0f, 0.0f, 600.0f, 600.0f);
    Player player((char*)"src\\assets\\player.png", 0.0f, 500.0f, 78.0f, 58.0f);
    player.camera = &camera;

    // bgBeta.experimentalScale(10.0f, 1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFaceDirection, camera.cameraUp);

    glfwSwapInterval(1);

    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window)) {
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // glfwGetCursorPos(window, &menu.cursor_position_x, &menu.cursor_position_y);

        projection = glm::ortho(0.0f, (float)display_w, 0.0f, (float)display_h, -10.0f, 10.0f);
        view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFaceDirection, camera.cameraUp);

        player.processInput(window);
        // processInput(window);

        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        bgShader.use();
        bgBeta.experimentalScale((float)(display_w / bgBeta.bgWidth), (float)(display_h / bgBeta.bgHeight));
        glUniformMatrix4fv(glGetUniformLocation(bgShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(bgShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(bgShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(bgBeta.model));
        bgBeta.render(&bgShader, projection);
        
        shader.use();
        player.update(&shader);
        glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(player.model));
        player.render(&shader);

        cShader.use();
        player.hitbox.render(&cShader, projection, view);
        player.collision.render(&cShader, projection, view);

        // shader.use();
        // glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(player.model));
        // square.setUniformMatrix4fv(&shader, (char*)"model");
        // square.setProjection(&shader, projection);
        // square.animate(&shader);
        // square.render();
        // bg.scale((display_w / bg.backgroundWidth), (display_h / bg.backgroundHeight));
        // bg.setUniformMatrix4fv(&shader, (char*)"model");
        // bg.setProjection(&shader, projection);
        // bg.render(&shader);

        // player.update(&shader);
        // player.setUniformMatrix4fv(&shader, (char*)"model");
        // player.setProjection(&shader, projection);
        // player.render(&shader);

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