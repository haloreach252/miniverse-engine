#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera(glm::vec3 position, float speed = 2.5f, float sensitivity = 0.1f);

	void ProcessKeyboard(int key);
	glm::mat4 GetViewMatrix() const;

	void IncreaseSpeed();
	void DecreaseSpeed();

private:
	glm::vec3 position;
	float yaw;
	float speed;
};

#endif