#pragma once

#include "src/util/gl/GpuProgram.hpp"
#include "src/util/gl/TesselationProgram.hpp"
#include "src/util/gl/VertexArray.hpp"
#include "src/util/Object.hpp"
#include "src/util/input.hpp"
#include "src/util/datatypes/Material.hpp"

#include "src/Grid.hpp"
#include "src/Function.hpp"
#include "src/Camera.hpp"
#include "src/Sun.hpp"
#include "src/PatchSurface.hpp"

class Scene {

private:
	std::vector<Object*> objects;
	Sun* sun;

	glm::vec3 center;

	Camera* camera;

	GpuProgram* gridShader;
	GpuProgram* functionShader;
	GpuProgram* sunShader;
	TesselationProgram* patchShader;

	unsigned int objectIndex = 0;
	unsigned int shaderIndex = 0;

	unsigned int minimal_tesselation;
	unsigned int maximal_tesselation;
	float minimal_distance;
	float maximal_distance;

private:
	void createShaders();

public:
	Scene();

	inline void setObjectIndex(unsigned int value) { objectIndex = value; }
	inline void setShaderIndex(unsigned int value) { shaderIndex = value; }
	inline void setFunctionMaterial(const Material _material) { /*function->setMaterial(_material);*/ }

	void setPrimitiveType(unsigned int type);
	void setTesselationParameters(unsigned int min_tess, unsigned int max_tess, float min_dist, float max_dist);
	void reevaluateFunction(const char* positionString, const char* normalString);
	void invertFunctionNormal();

	void create();
	void draw() const;
	void update(GLFWwindow* window);

	~Scene();	
};