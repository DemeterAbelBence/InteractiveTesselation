#pragma once

#include "Transformable.hpp"
#include "Object.hpp"
#include "glfw/glfw.hpp"

#include <vector>

namespace input {
	struct TransformationEvent {
		glfw::Key* key;
		void(Transformable::*transformation)(float) = nullptr;
		float speed;
		int sign;
	};

	class InputHandler {
	private:
		std::vector<TransformationEvent> transformEvents;
		void initializeKeys();

	public:
		InputHandler() { initializeKeys(); }
		void handleTransformationEvents(GLFWwindow* window, Object* object);
		~InputHandler();
	};
};