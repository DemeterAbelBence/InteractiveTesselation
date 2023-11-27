#pragma once

#include "util/Object.hpp"

class PatchSurface : public Object {

private:
	unsigned int rezolution;
	float scale;

	std::vector<glm::vec3> vertexData;

public:
	PatchSurface(unsigned int _rezolution);
	inline void setScale(float value) { scale = value; }
	inline void deleteVertexData() { vertexData.clear(); }

	glm::vec3 generateVertexData(float x, float y);

	void create() override;
	void draw() const override;
	void reCreate() override;

private:
	void setBufferData(const void* data, unsigned int size);
};