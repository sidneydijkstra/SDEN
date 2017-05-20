
#include "scene.h"


Scene::Scene() {
	// add camera
	camera = new Camera();

	// add player and set texture
	player = new Mesh();
	player->addTexture("assets/dogh.jpg");

	// add enemy and set texture
	enemy = new Mesh();

	// addchild player and enemy
	this->addChild(player);
	this->addChild(enemy);

	// add normal maps
	player->addNormalMap("assets/brick.jpg");

	// add lamp
	Mesh* lamp = new Mesh();
	addLamp(lamp);

	// set lamp variabels
	lamp->position = glm::vec3(1.5f,-1,0);

	// set enemy variabels
	enemy->position = lamp->position;
	enemy->color = glm::vec3(2.6f, 0.3f, 1.2f);

	// set player variabels
	player->scale = glm::vec3(10,10,1);
	player->position = glm::vec3(0,0,-5);
}
Scene::~Scene(){
	delete this->camera;
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

	//player->rotation.y += 9 * deltaTime;

	//player->position.x += 0.1f * deltaTime;
	//scamera->position = glm::vec3(player->position.x, player->position.y, player->position.z + 4);
}

