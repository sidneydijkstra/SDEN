
#include "scene.h"

Scene::Scene() {
	camera = new Camera();
	player = new Mesh();
	player->addTexture("assets/snoop.jpg");
	this->addChild(player);
}

void Scene::update(float deltaTime){
	this->getCamera()->move(deltaTime, this->getInput());

	player->position.x += 0.1f * deltaTime;
	//scamera->position = glm::vec3(player->position.x, player->position.y, player->position.z + 4);
}

