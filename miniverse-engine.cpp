#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "KeyInput.h"
#include "Mesh.h"

// Callback to adjust viewport when window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Global color values
float red = 1.0f, green = 1.0f, blue = 1.0f;

// Process input
void processInput(GLFWwindow* window, float& red, float& green, float& blue) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    KeyInput::Update(window);

    // Adjust Red
    if (KeyInput::GetKeyDown(GLFW_KEY_R)) red = std::clamp(red + 0.05f, 0.0f, 1.0f);
    if (KeyInput::GetKeyDown(GLFW_KEY_T)) red = std::clamp(red - 0.05f, 0.0f, 1.0f);

    // Adjust Green
    if (KeyInput::GetKeyDown(GLFW_KEY_G)) green = std::clamp(green + 0.05f, 0.0f, 1.0f);
    if (KeyInput::GetKeyDown(GLFW_KEY_H)) green = std::clamp(green - 0.05f, 0.0f, 1.0f);

    // Adjust Blue
    if (KeyInput::GetKeyDown(GLFW_KEY_B)) blue = std::clamp(blue + 0.05f, 0.0f, 1.0f);
    if (KeyInput::GetKeyDown(GLFW_KEY_N)) blue = std::clamp(blue - 0.05f, 0.0f, 1.0f);
}

int main() {
    // Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

    // OpenGL version 3.3 core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Miniverse Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OPenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Load shaders using the shader class
    Shader shader("../shaders/vertex_shader.glsl", "../shaders/fragment_shader.glsl");
    Shader outlineShader("../shaders/outline_vertex_shader.glsl", "../shaders/outline_fragment_shader.glsl");

    // Define a cube (8 vertices, indexed)
    std::vector<float> vertices = {
        // Positions
        -0.5f, -0.5f, -0.5f,  // 0 - Back bottom-left
         0.5f, -0.5f, -0.5f,  // 1 - Back bottom-right
         0.5f,  0.5f, -0.5f,  // 2 - Back top-right
        -0.5f,  0.5f, -0.5f,  // 3 - Back top-left
        -0.5f, -0.5f,  0.5f,  // 4 - Front bottom-left
         0.5f, -0.5f,  0.5f,  // 5 - Front bottom-right
         0.5f,  0.5f,  0.5f,  // 6 - Front top-right
        -0.5f,  0.5f,  0.5f   // 7 - Front top-left
    };

    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0,  // Back face
        4, 5, 6, 6, 7, 4,  // Front face
        0, 4, 7, 7, 3, 0,  // Left face
        1, 5, 6, 6, 2, 1,  // Right face
        3, 2, 6, 6, 7, 3,  // Top face
        0, 1, 5, 5, 4, 0   // Bottom face
    };

    Mesh cube(vertices, indices);

    // Enable depth testing for 3D rendering
    glEnable(GL_DEPTH_TEST);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window, red, green, blue);

        // Clear the screen
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 mvp = projection * view * model;

        // Pass 1: Render outline (scale up slightly)
        outlineShader.use();
        outlineShader.setMat4("modelViewProjection", mvp);
        outlineShader.setFloat("outlineScale", 1.05f);

        glEnable(GL_POLYGON_OFFSET_FILL); // Depth offset to avoid z-fighting
        glPolygonOffset(-1.0f, -1.0f); // Push outline further in depth
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        cube.Draw();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_POLYGON_OFFSET_FILL);

        // Pass 2: Render normal cube
        shader.use();
        shader.setMat4("modelViewProjection", mvp);
        shader.setFloat("uColor", red, green, blue);
        cube.Draw();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}