#include "Model.h"
#include <iostream>
#include <sstream>
#include "EmbeddedModels.h"

Model::Model(const std::string& filepath, bool fromMemory) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	std::string objData;

	if (fromMemory) {
		if (filepath == "Statue.obj") {
			objData = statueModelData;
		}
		else {
			throw std::runtime_error("Model not found in embedded assets: " + filepath);
		}
	}

	std::istringstream objStream(objData);

	bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, &objStream);

	if (!warn.empty()) std::cout << "OBJ Loader Warning: " << warn << std::endl;
	if (!err.empty()) std::cerr << "OBJ Loader Error: " << err << std::endl;
	if (!success) throw std::runtime_error("Failed to load OBJ file: " + filepath);

	for (const auto& shape : shapes) {
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		for (const auto& index : shape.mesh.indices) {
			int vertexIndex = index.vertex_index * 3;
			vertices.push_back(attrib.vertices[vertexIndex]);
			vertices.push_back(attrib.vertices[vertexIndex + 1]);
			vertices.push_back(attrib.vertices[vertexIndex + 2]);
			indices.push_back(indices.size());
		}

		meshes.emplace_back(vertices, indices);
	}

	std::cout << "Successfully loaded model: " << filepath << " with " << meshes.size() << " meshes.\n";
}

void Model::Draw() const {
	for (const auto& mesh : meshes) {
		mesh.Draw();
	}
}