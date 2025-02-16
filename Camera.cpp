#include "Camera.h"
#include "KeyInput.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 position, float speed, float sensitivity) : position(position), yaw(0.0f), speed(speed) {}

// Process movement inputs (WASD + QE)
void Camera::ProcessKeyboard(int key) {
	glm::vec3 forward = glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));
	glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

    if (KeyInput::GetKey(GLFW_KEY_W)) position += speed * forward;  // Move forward
    if (KeyInput::GetKey(GLFW_KEY_S)) position -= speed * forward;  // Move backward
    if (KeyInput::GetKey(GLFW_KEY_A)) position -= speed * right;    // Move left
    if (KeyInput::GetKey(GLFW_KEY_D)) position += speed * right;    // Move right
    if (KeyInput::GetKey(GLFW_KEY_Q)) yaw -= 1.5f;                  // Turn left
    if (KeyInput::GetKey(GLFW_KEY_E)) yaw += 1.5f;                  // Turn right

    // Vertical movement
    if (KeyInput::GetKey(GLFW_KEY_SPACE)) position.y += speed;       // Move up
    if (KeyInput::GetKey(GLFW_KEY_LEFT_CONTROL)) position.y -= speed; // Move down

    if (KeyInput::GetKeyDown(GLFW_KEY_Z)) IncreaseSpeed();          // Increase speed
    if (KeyInput::GetKeyDown(GLFW_KEY_X)) DecreaseSpeed();          // Decrease speed
}

// Generates the view matrix for opengl
glm::mat4 Camera::GetViewMatrix() const {
    glm::vec3 forward = glm::vec3(cos(glm::radians(yaw)), 0.0f, sin(glm::radians(yaw)));
    return glm::lookAt(position, position + forward, glm::vec3(0.0f, 1.0f, 0.0f));
}

// Adjust camera speed
void Camera::IncreaseSpeed() {
    speed = std::min(speed + 0.5f, 10.0f);
}

void Camera::DecreaseSpeed() {
    speed = std::max(speed - 0.5f, 0.5f);
}