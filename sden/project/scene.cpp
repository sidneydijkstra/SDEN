
#include "scene.h"

Scene::Scene() {
	camera = new Camera();
	player = new Mesh();
	player->addTexture("assets/dogh.jpg");
	enemy = new Mesh();
	enemy->addTexture("assets/snoop.jpg");
	this->addChild(player);
	this->addChild(enemy);

	enemy->position.y += 1.1f;
	enemy->scale.x += 10;
}

Scene::~Scene(){
	delete camera;
	for (int i = 0; i < childeren.size(); i++){
		delete childeren[i];
	}
}

void Scene::update(float deltaTime){
	this->getCamera()->move(deltaTime, this->getInput());

	player->position.x += 0.1f * deltaTime;
	enemy->position.x += 0.1f * deltaTime;
	//scamera->position = glm::vec3(player->position.x, player->position.y, player->position.z + 4);
}

