#pragma once

#include "src/util/gl/Util.hpp"
#include "src/Rect.hpp"

#include "dep/imGui/imGui.h"
#include "dep/imGui/imGui_impl_glfw.h"
#include "dep/imGui/imGui_impl_opengl3.h"

#include "Scene.hpp"

#include <iostream>
#include <Windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace Gui {
	void drawRectangle(glm::vec3 color);

	void drawMaterialPicker(Scene& scene, unsigned int x, unsigned int y);
	void drawTesselationPicker(Scene& scene, unsigned int x, unsigned int y);
	void drawObjectPicker(Scene& scene, unsigned int x, unsigned int y);
	void drawFunctionPicker(Scene& scene, unsigned int x, unsigned int y);
	void drawPrimitivePicker(Scene& scene, unsigned int x, unsigned int y);

	void drawUserInteface(Scene& scene, int sceneWidth, int windowWidth, int windowHeight);
}