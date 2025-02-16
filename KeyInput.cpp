#include "KeyInput.h"

// Initialize static member variables
std::unordered_map<int, bool> KeyInput::keyState;
std::unordered_map<int, bool> KeyInput::lastKeyState;

// Call this at the start of each frame
void KeyInput::Update(GLFWwindow* window) {
	for (auto& [key, state] : keyState) {
		lastKeyState[key] = state; // Store previous frame state
		keyState[key] = glfwGetKey(window, key) == GLFW_PRESS; // Update current state
	}
}

// Returns true if the key was pressed *this frame only*
bool KeyInput::GetKeyDown(int key) {
	return keyState[key] && !lastKeyState[key];
}

// Returns true if the key is currently being help
bool KeyInput::GetKey(int key) {
	return keyState[key];
}

// Returns true if the key was released *this frame only*
bool KeyInput::GetKeyUp(int key) {
	return keyState[key] && lastKeyState[key];
}