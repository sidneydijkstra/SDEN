
#include "scene.h"


Scene::Scene() {
	// add camera
	camera = new Camera();

	wall = new Mesh();
	light = new Mesh();
	floor = new Mesh();

	// set skybox options TEMP
	skybox_ = new Mesh();
	skybox_->addSkybox("assets/skybox/s_right.jpg", "assets/skybox/s_left.jpg", "assets/skybox/s_top.jpg", "assets/skybox/s_bottom.jpg", "assets/skybox/s_back.jpg", "assets/skybox/s_front.jpg");

	wall->addTexture("assets/dogh.jpg");
	//floor->addSkybox("assets/skybox/s_right.tga", "assets/skybox/s_left.tga", "assets/skybox/s_top.tga", "assets/skybox/s_bottom.tga", "assets/skybox/s_back.tga", "assets/skybox/s_front.tga");

	// addchild wall floor and light
	this->addChild(wall);
	this->addChild(light);
	this->addChild(floor);

	// add normal maps
	wall->addNormalMap("assets/brick.jpg");
	//floor->addNormalMap("assets/wood.jpg");

	// add lamp
	Mesh* lamp = new Mesh();
	addLamp(lamp);

	// set lamp variabels
	lamp->position = glm::vec3(1.5f,-1,0);

	// set light variabels
	light->position = lamp->position;
	light->color = glm::vec3(2.6f, 0.3f, 1.2f);

	// set wall variabels
	wall->scale = glm::vec3(10,10,1);
	wall->position = glm::vec3(0,0,-5);

	// set floor variabels
	floor->position = glm::vec3(0,-5.5f,0);
	floor->scale = glm::vec3(10,1,10);
}
Scene::~Scene(){
	delete this->camera;
	delete this->skybox_;
	for (int i = 0; i < this->_childeren.size(); i++){
		delete this->_childeren[i];
	}
	if (this->getLamp() != NULL) {
		delete this->getLamp();
	}
}

void Scene::update(float deltaTime){
	// move camera with mouse and keyboard
	this->getCamera()->move(deltaTime, this->getInput());

	//wall->rotation.y += 9 * deltaTime;

	// set skybox pos TEMP
	skybox_->position = camera->position;

	//wall->position.x += 0.1f * deltaTime;
	//camera->position = glm::vec3(light->position.x, light->position.y, light->position.z + 4);
}

