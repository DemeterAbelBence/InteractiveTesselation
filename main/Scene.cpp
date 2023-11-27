#include "Scene.hpp"

void Scene::createShaders() {
	gridShader = new GpuProgram("Grid Shader");
	gridShader->readFragmentSource("main/src/util/shaders/gridFragment.shader");
	gridShader->readVertexSource("main/src/util/shaders/gridVertex.shader");

	functionShader = new GpuProgram("Function Shader");
	functionShader->readFragmentSource("main/src/util/shaders/functionFragment.shader");
	functionShader->readVertexSource("main/src/util/shaders/functionVertex.shader");

	sunShader = new GpuProgram("Sun Shader");
	sunShader->readFragmentSource("main/src/util/shaders/sunFragment.shader");
	sunShader->readVertexSource("main/src/util/shaders/sunVertex.shader");

	patchShader = new TesselationProgram("Patch Shader");
	patchShader->readFragmentSource("main/src/util/shaders/patchFragment.shader");
	patchShader->readVertexSource("main/src/util/shaders/patchVertex.shader");
	patchShader->readTesselationControlSource("main/src/util/shaders/patchTesselationControl.shader");
	patchShader->readTesselationEvaluationSource("main/src/util/shaders/patchTesselationEvaluation.shader");

	gridShader->createProgram();
	camera->setUniforms(*gridShader);

	functionShader->createProgram();
	camera->setUniforms(*functionShader);

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
	float scale = 3.0f;

	Material material1 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		5.0f
	};

	Material material2 = {
		glm::vec3(0.5f, 0.5f, 0.5f),
		glm::vec3(0.7f, 0.0f, 0.0f),
		glm::vec3(0.2f, 0.2f, 0.2f),
		1.0f
	};

	Grid* grid = new Grid(6);
	grid->setShader(gridShader);
	grid->setScale(scale);
	grid->setCenter(center);
	grid->create();

	Function* function = new Function(30, 30);
	function->setMaterial(material2);
	function->setShader(functionShader);
	function->setScale(2.0f);
	float offset = scale / 2.0f;
	function->setCenter(center + glm::vec3(offset, 0.0f, offset));
	function->create();

	Sun* sun = new Sun(20, 20, center + glm::vec3(1.5f, 1.0f, 0.0f));
	sun->setUniformLight(*functionShader);
	sun->setMaterial(material1);
	sun->setShader(sunShader);
	sun->setScale(1.0f);
	sun->setRadius(0.1f);
	sun->create();

	PatchSurface* patchSurface = new PatchSurface(3);
	patchSurface->setScale(5.0f);
	patchSurface->setShader(patchShader);
	patchSurface->setCenter(center + glm::vec3(-1.0f, -1.0f, 0.0f));
	patchSurface->create();

	objects.push_back(patchSurface);
	/*objects.push_back(sun);
	objects.push_back(function);
	objects.push_back(grid);*/
}
void Scene::draw() const {
	camera->setUniforms(*functionShader);
	camera->setUniforms(*gridShader);
	camera->setUniforms(*sunShader);
	camera->setUniforms(*patchShader);

	for (const auto& object : objects)
		object->draw();
}
void Scene::update(GLFWwindow* window) {
	static input::InputHandler inputHandler;
	for (const auto& object : objects)
		inputHandler.handleTransformationEvents(window, object);

	patchShader->bind();
	patchShader->setFloat("MIN_DIST", minimal_distance);
	patchShader->setFloat("MAX_DIST", maximal_distance);
	patchShader->setInt("MIN_TESS", minimal_tesselation);
	patchShader->setInt("MAX_TESS", maximal_tesselation);
}

Scene::~Scene() {
	delete gridShader;
	delete functionShader;
	delete sunShader;
	delete patchShader;

	delete camera;
}
