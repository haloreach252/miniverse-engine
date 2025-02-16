#ifndef KEYINPUT_H
#define KEYINPUT_H

#include <GLFW/glfw3.h>
#include <unordered_map>

class KeyInput {
public:
	// Call at the start of each frame to update key states
	static void Update(GLFWwindow* window);

	// Unity-Style input functions
	static bool GetKeyDown(int key);
	static bool GetKey(int key);
	static bool GetKeyUp(int key);
private:
	static std::unordered_map<int, bool> keyState; // Is key currently held?
	static std::unordered_map<int, bool> lastKeyState; // Was key held last frame?
};
#endif