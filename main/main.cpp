#include <iostream>

#include "Application.hpp"

int main(void) {
    try {
        GLFWwindow*  window = Application::initGlfwWindow("FunctionDrawer");
        Application::initOpenGl();
        Application::initImGui(window);
        Application::renderLoop(window);
    }
    catch (const char* exception) {
        std::cout << exception << std::endl;
        return 0;
    }

    

    return 0;
}