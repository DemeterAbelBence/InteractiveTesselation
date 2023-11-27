#pragma once
//
#include "input.hpp"

namespace input {
    void InputHandler::initializeKeys() {
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_DOWN), &Transformable::translateY, 0.01f, -1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_UP), &Transformable::translateY, 0.01f, 1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_LEFT), &Transformable::translateX, 0.01f, -1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_RIGHT), &Transformable::translateX, 0.01f, 1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_Q), &Transformable::translateZ, 0.01f, 1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_W), &Transformable::translateZ, 0.01f, -1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_R), &Transformable::rotate, 0.1f * 3.14f, -1 });
		transformEvents.push_back({ new glfw::Key(GLFW_KEY_E), &Transformable::rotate, 0.1f * 3.14f, 1 });
	}
    void InputHandler::handleTransformationEvents(GLFWwindow* window, Object* object) {
		for (const auto& t : transformEvents) {
			if (t.key->isPressed(window)) {
				(object->*t.transformation)(t.sign * t.speed);
			}
		}
	}
	InputHandler::~InputHandler() {
		for (const auto& e : transformEvents)
			delete e.key;
	}
}