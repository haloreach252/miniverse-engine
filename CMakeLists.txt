cmake_minimum_required(VERSION 3.16)
project(miniverse-engine)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable LLVM/Clang Compiler if detected
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	message(STATUS "Using clang/llvm compiler")
endif()

# Add vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "VCPKG toolchain file")

# Manually set package directories
set(CMAKE_PREFIX_PATH "C:/vcpkg/installed/x64-windows")

# Find libraries
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(tinyobjloader CONFIG REQUIRED)

# Add executable
add_executable(miniverse-engine "miniverse-engine.cpp" "Shader.h" "Shader.cpp" "KeyInput.h" "KeyInput.cpp" "Mesh.h" "Mesh.cpp" "Model.h" "Model.cpp" "Camera.h" "Camera.cpp")

# Link libraries
target_link_libraries(miniverse-engine PRIVATE glfw glad::glad glm::glm tinyobjloader::tinyobjloader)

# Convert shaders to a header file at build time
file(WRITE ${CMAKE_BINARY_DIR}/GeneratedShaders.h "// Auto-generated shader files\n")

function(embed_shader SHADER_FILE SHADER_NAME)
	file(READ ${SHADER_FILE} SHADER_SOURCE)
	string(REPLACE "\"" "\\\"" SHADER_SOURCE "${SHADER_SOURCE}")
	string(REPLACE "\n" "\\n\"\n\"" SHADER_SOURCE "${SHADER_SOURCE}")
    file(APPEND ${CMAKE_BINARY_DIR}/GeneratedShaders.h "const char* ${SHADER_NAME} = \"${SHADER_SOURCE}\";\n")
endfunction()

# Convert each GLSL file into a C++ string
embed_shader(${CMAKE_SOURCE_DIR}/shaders/vertex_shader.glsl vertexShaderSource)
embed_shader(${CMAKE_SOURCE_DIR}/shaders/fragment_shader.glsl fragmentShaderSource)
embed_shader(${CMAKE_SOURCE_DIR}/shaders/outline_vertex_shader.glsl outlineVertexShaderSource)
embed_shader(${CMAKE_SOURCE_DIR}/shaders/outline_fragment_shader.glsl outlineFragmentShaderSource)

# Ensure the generated header is available
include_directories(${CMAKE_BINARY_DIR})

# Auto-generate a header file with OBJ data
file(WRITE ${CMAKE_BINARY_DIR}/EmbeddedModels.h "// Auto-generated OBJ file\n")

function(embed_model MODEL_FILE MODEL_NAME)
    file(READ ${MODEL_FILE} MODEL_DATA)
    string(REPLACE "\"" "\\\"" MODEL_DATA "${MODEL_DATA}")
    string(REPLACE "\n" "\\n\"\n\"" MODEL_DATA "${MODEL_DATA}")
    file(APPEND ${CMAKE_BINARY_DIR}/EmbeddedModels.h "const char* ${MODEL_NAME} = \"${MODEL_DATA}\";\n")
endfunction()

# Convert models to C++ strings
embed_model(${CMAKE_SOURCE_DIR}/models/Statue.obj statueModelData)
embed_model(${CMAKE_SOURCE_DIR}/models/Sack.obj sackModelData)
embed_model(${CMAKE_SOURCE_DIR}/models/Pillar.obj pillarObjectData)

# Ensure the generated header is available
include_directories(${CMAKE_BINARY_DIR})