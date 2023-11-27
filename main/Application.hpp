#pragma once

#include "src/util/gl/Util.hpp"
#include <iostream>
#include <Windows.h>
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "dep/imGui/imGui.h"
#include "dep/imGui/imGui_impl_glfw.h"
#include "dep/imGui/imGui_impl_opengl3.h"

#include "Scene.hpp"
#include "Gui.hpp"


namespace Application {
	const unsigned int windowWidth = 1200;
	const unsigned int windowHeight = 800;

	const unsigned int sceneWidth = 800;
	const unsigned int sceneHeight = 800;

	GLFWwindow* initGlfwWindow(const char* windowName);
	void initOpenGl();
	void initImGui(GLFWwindow* window);
	void renderLoop(GLFWwindow* window);
}