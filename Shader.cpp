#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Constructor - loads, compiles, and links shaders
Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
	// Load shader source code
	std::string vertexCode = loadShaderSource(vertexPath);
	std::string fragmentCode = loadShaderSource(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "ERROR: Shader source is empty!" << std::endl;
        return;
    }

    // Compile shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    // Create and link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

// Use the shader program
void Shader::use() const {
    glUseProgram(ID);
}

// Set uniform variables
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float v1, float v2, float  v3) const {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

// Destructor
Shader::~Shader() {
    glDeleteProgram(ID);
}

// Load shader source from a file
std::string Shader::loadShaderSource(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Compile a shader
unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int shader = glCreateShader(type);
    const char* sourceCStr = source.c_str();
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}