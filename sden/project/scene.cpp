
#include "scene.h"


Scene::Scene() {
	camera = new Camera();
	player = new Mesh();
	player->addTexture("assets/dogh.jpg");
	enemy = new Mesh();
	enemy->addTexture("assets/snoop.jpg");
	this->addChild(player);
	this->addChild(enemy);

	// add  normal maps
	player->addNormalMap("assets/brick.jpg");
	enemy->addNormalMap("assets/brick.jpg");

	enemy->position.y += 1.1f;
	enemy->scale.x += 10;

	// add lamp
	Mesh* lamp = new Mesh();
	addLamp(lamp);
	lamp->position = glm::vec3(5,5,5);

	player->scale = glm::vec3(10,1,10);
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
	this->getCamera()->move(deltaTime, this->getInput());

	//getLamp()->position = camera->position;

	//player->position.x += 0.1f * deltaTime;
	enemy->position.x += 0.1f * deltaTime;
	//scamera->position = glm::vec3(player->position.x, player->position.y, player->position.z + 4);
}

