#include "Sun.hpp"



Sun::Sun(glm::vec3 _center) : Sphere (20, 20) {
	lightPosition = _center;
	setCenter(_center);
}

Sun::Sun(unsigned int N, unsigned int M, glm::vec3 _center) : Sphere(N, M) {
	lightPosition = _center;
	setCenter(_center);
}

inline void Sun::translateX(float speed) {
	translation.x += speed;
	center.x += speed;
	lightPosition.x += speed;
}

inline void Sun::translateY(float speed) {
	translation.y += speed;
	center.y += speed;
	lightPosition.y += speed;
}

inline void Sun::translateZ(float speed) {
	translation.z += speed;
	center.z += speed;
	lightPosition.z += speed;
}

void Sun::rotate(float speed) {
	Transformable::rotate(speed);
	rotateLight(); 
}

void Sun::setUniformLight(const GpuProgram& progarm) const { 
	progarm.bind();
	progarm.setVec3("light.position", lightPosition);
}

void Sun::rotateLight() {
	glm::vec4 newLightPosition = makeRotationMatrix() * glm::vec4(lightPosition, 1.0f);
	lightPosition = glm::vec3(newLightPosition);
}
