#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

class Shader {
public:
	unsigned int ID;

	// Constructor - loads, compiles, and links shaders
	Shader(const std::string& vertexPath, const std::string& fragmentPath);

	// Activate the shader program
	void use() const;

	// Utility function for setting uniform variables
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string&, int value) const;
	void setFloat(const std::string&, float value) const;
	void setFloat(const std::string&, float v1, float v2, float v3) const;
	void setMat4(const std::string& name, const glm::mat4& matrix) const;

	// Destructor
	~Shader();
private:
	// Helper function to load shader source code
	std::string loadShaderSource(const std::string& filePath);
	// Helper function to compile a shader
	unsigned int compileShader(unsigned int type, const std::string& source);
};
#endif