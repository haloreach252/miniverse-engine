#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include "Mesh.h"
#include "tiny_obj_loader.h"

class Model {
public:
	Model(const std::string& filepath, bool fromMemory = false);
	void Draw() const;

private:
	std::vector<Mesh> meshes;
};

#endif