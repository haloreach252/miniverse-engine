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
set(CMAKE_TOOLCHAIN_FILE "C:/Users/halor/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "VCPKG toolchain file")

# Manually set package directories
set(CMAKE_PREFIX_PATH "C:/Users/halor/Desktop/vcpkg/installed/x64-windows")

# Find libraries
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Add executable
add_executable(miniverse-engine miniverse-engine.cpp "Shader.h" "Shader.cpp" "KeyInput.h" "KeyInput.cpp" "Mesh.h" "Mesh.cpp")

# Link libraries
target_link_libraries(miniverse-engine PRIVATE glfw glad::glad glm::glm)