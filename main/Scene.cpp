#include "Scene.hpp"

void Scene::createShaders() {
	sunShader = new GpuProgram("Sun Shader");
	sunShader->readFragmentSource("main/src/util/shaders/sunFragment.shader");
	sunShader->readVertexSource("main/src/util/shaders/sunVertex.shader");

	patchShader = new TesselationProgram("Patch Shader");
	patchShader->readFragmentSource("main/src/util/shaders/patchFragment.shader");
	patchShader->readVertexSource("main/src/util/shaders/patchVertex.shader");
	patchShader->readTesselationControlSource("main/src/util/shaders/patchTesselationControl.shader");
	patchShader->readTesselationEvaluationSource("main/src/util/shaders/patchTesselationEvaluation.shader");

	sunShader->createProgram();
	camera->setUniforms(*sunShader);

	patchShader->createProgram();
	camera->setUniforms(*patchShader);
}
Scene::Scene() {
	center = glm::vec3(0.0f, 0.0f, 1.0f);
	camera = new Camera();
	camera->createViewMatrix();
	createShaders();
}

void Scene::setPrimitiveType(unsigned int type) {
	for (const auto& object : objects)
		object->setPrimitive(type);
}
void Scene::setObjectMaterial(unsigned int index, const Material material) {
	objects[index]->setMaterial(material);
}
void Scene::setTesselationParameters(unsigned int min_tess, unsigned int max_tess, float min_dist, float max_dist) {
	minimal_tesselation = min_tess;
	maximal_tesselation = max_tess;
	minimal_distance = min_dist;
	maximal_distance = max_dist;
}
void Scene::reevaluateFunction(const char* positionString, const char* normalString) {
	/*function->setNormalFormula(normalString);
	function->setPositionFormula(positionString);
	function->deleteVertexData();
	function->create();*/
}
void Scene::invertFunctionNormal() {
	/*function->invertNormalSign();
	function->deleteVertexData();
	function->create();*/
}

void Scene::create() {
	sun = new Sun(10, 10, center);
	sun->setUniformLight(*patchShader);
	sun->setShader(sunShader);
	sun->setScale(1.0f);
	sun->setRadius(0.1f);
	sun->create();

	PatchSurface* patchSurface = new PatchSurface(20);
	patchSurface->setScale(10.0f);
	patchSurface->setShader(patchShader);
	patchSurface->setCenter(center + glm::vec3(-2.3f, 0.0f, -1.0f));
	patchSurface->translateY(-1.0f);
	patchSurface->create();

	objects.push_back(patchSurface);
	objects.push_back(sun);
}
void Scene::draw() const {
	camera->setUniforms(*sunShader);
	camera->setUniforms(*patchShader);

	sun->setUniformLight(*patchShader);

	for (const auto& object : objects)
		object->draw();
}
void Scene::update(GLFWwindow* window) {
	static input::InputHandler inputHandler;
	inputHandler.handleTransformationEvents(window, objects[object_index]);

	patchShader->bind();
	patchShader->setFloat("MIN_DIST", minimal_distance);
	patchShader->setFloat("MAX_DIST", maximal_distance);
	patchShader->setInt("MIN_TESS", minimal_tesselation);
	patchShader->setInt("MAX_TESS", maximal_tesselation);
}

Scene::~Scene() {
	delete sunShader;
	delete patchShader;

	delete camera;
}
