#version 330 core
out vec4 FragColor;

// Uniform for setting color dynamically
uniform vec3 uColor;

void main() {
	FragColor = vec4(uColor, 1.0);
}