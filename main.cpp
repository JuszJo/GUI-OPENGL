#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GUI/imgui.h>
#include <GUI/imgui_impl_glfw.h>
#include <GUI/imgui_impl_opengl3.h>

#include "libs/shader.h"

int main() {
    // Initialize GLFW
    if (!glfwInit()) return 1;

    GLFWwindow* window = glfwCreateWindow(600, 600, "ImGui Example", NULL, NULL);

    if (!window) {
        glfwTerminate();

        return 1;
    }

    glfwMakeContextCurrent(window);

    glewInit();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.3f, 0.5f, 0.7f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.5f, 0.2f,
        0.0f,  0.5f, 0.0f,  0.3f, 0.1f, 0.3f,
    };

    unsigned int VBO, VAO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    shader.use();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // render your GUI
        ImGui::Begin("Demo window");
        ImGui::Button("Hello!");
        static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        // color picker
        ImGui::ColorEdit3("color", color);
        ImGui::End();

        int colorLocation = glGetUniformLocation(shader.shaderProgram, "color");
        glUniform3f(colorLocation, color[0], color[1], color[2]);

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    return 1;
}