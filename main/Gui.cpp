#include "Gui.hpp"

void Gui::drawRectangle(glm::vec3 color) {
    static Rect rectangle(glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f), color);
    rectangle.draw();
}

void Gui::drawMaterialPicker(Scene& scene, unsigned int x, unsigned int y) {
    static float ambient[3] = {0.0f, 0.2f, 0.0f};
    static float diffuse[3] = {1.0f, 1.0f, 0.0f};
    static float specular[3] = {1.0f, 0.0f, 0.0f};
    static float shininess = 1.0f;

    ImGui::SetNextWindowSize(ImVec2(300, 130));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::Begin("Material properties");
    ImGui::SliderFloat3("ambient", &ambient[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat3("diffuse", &diffuse[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat3("specular", &specular[0], 0.0f, 1.0f, "%.2f", 0);
    ImGui::SliderFloat("shininess", &shininess, 0.1f, 1.0f, "%.2f", 0);
    ImGui::End();

    Material material = {
        glm::vec3(ambient[0], ambient[1], ambient[2]),
        glm::vec3(diffuse[0], diffuse[1], diffuse[2]),
        glm::vec3(specular[0], specular[1], specular[2]),
        shininess
    };

    scene.setObjectMaterial(0, material);
}

void Gui::drawTesselationPicker(Scene& scene, unsigned int x, unsigned int y) {
    static float min_tess = 1.0f;
    static float max_tess = 32.0f;
    static float min_dist = 0.0f;
    static float max_dist = 3.5f;

    ImGui::SetNextWindowSize(ImVec2(300, 130));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::Begin("Tesselation parameters");
    ImGui::SliderFloat("min tess", &min_tess, 1.0f, 64.0f, "%.0f", 0);
    ImGui::SliderFloat("max tess", &max_tess, 1.0f, 64.0f, "%.0f", 0);
    ImGui::SliderFloat("min dist", &min_dist, 0.0f, 10.0f, "%.1f", 0);
    ImGui::SliderFloat("max dist", &max_dist, 0.0f, 10.0f, "%.1f", 0);
    ImGui::End();

    scene.setTesselationParameters((unsigned int)min_tess, (unsigned int)max_tess, min_dist, max_dist);
}

void Gui::drawObjectPicker(Scene& scene, unsigned int x, unsigned int y) {
    const char* items[] = {"surface",  "lightsource" };
    static int currentItem;

    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::Begin("Select object");
    ImGui::ListBox("objects", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::End();
    scene.setObjectIndex(currentItem);
}

void Gui::drawFunctionPicker(Scene& scene, unsigned int x, unsigned int y) {
    static char positionBuffer[50];
    static char normalBuffer[50];

    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::Begin("Function formula");
    ImGui::InputText("formula", positionBuffer, sizeof(positionBuffer));

    if (ImGui::Button("Calculate    ")) {
        scene.reevaluateFunction(positionBuffer, normalBuffer);
    }

    if (ImGui::Button("Invert Normal")) {
        scene.invertFunctionNormal();
    }

    ImGui::End();
}

void Gui::drawPrimitivePicker(Scene& scene, unsigned int x, unsigned int y) {
    const char* items[] = { "line", "triangle" };
    static int currentItem;

    ImGui::SetNextWindowSize(ImVec2(300, 120));
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always);
    ImGui::Begin("Select primitive");
    ImGui::ListBox("primitives", &currentItem, items, IM_ARRAYSIZE(items));
    ImGui::End();

    currentItem == 0 ? scene.setPrimitiveType(GL_LINE) :
        scene.setPrimitiveType(GL_TRIANGLES);
}

void Gui::drawUserInteface(Scene& scene, int sceneWidth, int windowWidth, int windowHeight) {
    glViewport(sceneWidth, 0, windowWidth - sceneWidth, windowHeight);
    drawRectangle(glm::vec3(0.2f, 0.2f, 0.3f));

    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();  

    unsigned int pos_x = 850;
    unsigned int pos_y = 50;
    drawObjectPicker(scene, pos_x, pos_y);
    drawPrimitivePicker(scene, pos_x, pos_y += 150);
    //drawFunctionPicker(scene, pos_x, pos_y += 150);
    drawMaterialPicker(scene, pos_x, pos_y += 150);
    drawTesselationPicker(scene, pos_x, pos_y += 150);
   
}