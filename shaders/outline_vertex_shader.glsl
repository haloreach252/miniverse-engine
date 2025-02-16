#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 modelViewProjection;
uniform float outlineScale;

void main() {
	vec4 scaledPos = vec4(aPos * outlineScale, 1.0);
	gl_Position = modelViewProjection * scaledPos;
}