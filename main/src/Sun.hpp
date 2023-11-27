#pragma once

#include "Sphere.hpp";

class Sun : public Sphere {

private:
	glm::vec3 lightPosition;

public:
	Sun(glm::vec3 _center);
	Sun(unsigned int N, unsigned int M, glm::vec3 _center);

	inline void translateX(float speed) override;
	inline void translateY(float speed) override;
	inline void translateZ(float speed) override;

	void rotate(float degrees) override;
	void setUniformLight(const GpuProgram& progarm) const;

private:
	void rotateLight();
};