#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GUI/imgui.h>
#include <GUI/imgui_impl_glfw.h>
#include <GUI/imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION

#include "libs/shader.h"

#include "src/square.h"

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

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGuiIO &io = ImGui::GetIO(); (void)io;
    // ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init("#version 330");
    // ImGui::StyleColorsDark();

    int display_w, display_h;

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    Square square;

    shader.use();

    bool showDemo = false;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        // ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        // ImGui::NewFrame();

        square.render();

        // render your GUI
        // ImGui::Begin("Demo window");
        // ImGui::Button("Hello!");
        // static float color[4] = { 1.0f,1.0f,1.0f,1.0f };
        // // color picker
        // ImGui::ColorEdit3("color", color);
        // ImGui::End();

        // square.setUniformVec3f(&shader, (char*)"color", color[0], color[1], color[2]);

        // if(showDemo) ImGui::ShowDemoWindow(&showDemo);

        // Render dear imgui into screen
        // ImGui::Render();
        // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    return 1;
}