#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <vector>

class Mesh {
public:
	// Constructor: Accepts vertices and indices to create buffers
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

	// Renders the mesh
	void Draw() const;

	// Destructor: Cleans up buffers
	~Mesh();

private:
	unsigned int VAO, VBO, EBO;
	unsigned int indexCount;
};

#endif