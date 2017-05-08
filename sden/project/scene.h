
#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "mesh.h"
#include "camera.h"
#include "input.h"
// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene
{
public:
	Scene();
	void update(float deltaTime);
	Mesh* player;

	// get camera
	Camera* getCamera() { return camera; };
	Input* getInput() { return input; };
	void setInput(Input* input_) { input = input_; };

	// child functions
	// add child
	void addChild(Mesh* child) { childeren.push_back(child); };
	// remove child
	void removeChild(Mesh* child) { for (int i; i < childeren.size(); i++) { if (childeren[i] == child) { childeren.erase(childeren.begin() + i); }; }; };
	// get child count
	int getChildCount() { return childeren.size(); };
	// get all childeren
	std::vector<Mesh*> getAllChilderen() { return childeren; };
private:
	std::vector<Mesh*> childeren;

	Camera* camera;
	Input* input;
};

#endif