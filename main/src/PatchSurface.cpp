#include "PatchSurface.hpp"

PatchSurface::PatchSurface(unsigned int _rezolution) {
    rezolution = _rezolution;
	scale = 1.0f;
}

glm::vec3 PatchSurface::generateVertexData(float x, float y) {
	float z = 0;
    glm::vec3 position = glm::vec3(x, z, y);
	position = center + position;

    return position;
}

void PatchSurface::create() {
	unsigned int r = rezolution;
	float s = scale;

	for (unsigned int i = 0; i < r; i++) {
		for (unsigned int j = 0; j < r; j++) {
			vertexData.push_back(generateVertexData(s * (float)i / r, s * (float)j / r));
			vertexData.push_back(generateVertexData(s * (float)(i + 1) / r, s * (float)j / r));
			vertexData.push_back(generateVertexData(s * (float)i / r, s * (float)(j + 1) / r));
			vertexData.push_back(generateVertexData(s * (float)(i + 1) / r, s * (float)(j + 1) / r));
		}
	}
	setBufferData((const void*)&vertexData[0], vertexData.size() * sizeof(glm::vec3));
}

void PatchSurface::draw() const {
    vertexArray.bind();

	shader->bind();
	setAllUniforms();

	glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays(GL_PATCHES, 0, 4 * rezolution * rezolution);
}

void PatchSurface::reCreate() {}

void PatchSurface::setBufferData(const void* data, unsigned int size) {
	vertexBuffer.setData(data, size);
	if (!getCeated()) {
		vertexBufferLayout.push(GL_FLOAT, 3);
		vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);
		setCreated(true);
	}
}
