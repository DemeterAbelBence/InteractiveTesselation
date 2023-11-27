#pragma once

#include "gl/VertexArray.hpp"
#include "gl/GpuProgram.hpp"
#include "datatypes/Material.hpp"
#include "Transformable.hpp"

#include <glm.hpp>

class Object : public Transformable {

private:
	bool created = false;

protected:
	VertexArray vertexArray;
	VertexBuffer vertexBuffer;
	VertexBufferLayout vertexBufferLayout;

	GpuProgram* shader;
	Material material;

public:
	Object();
	inline void setCreated(bool value) { created = value; }
	inline bool getCeated() const { return created; }
	inline void setShader(GpuProgram* _shader) { shader = _shader; }
	inline void setMaterial(const Material& _material) { material = _material; }
	inline void setPrimitive(unsigned int type) { glPolygonMode(GL_FRONT_AND_BACK, type); }

	void setUniformMaterial() const;
	void setAllUniforms() const;
	
	virtual void create() = 0;
	virtual void draw() const = 0;
	virtual void reCreate() = 0;
};