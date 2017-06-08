
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
	~Scene();
	void update(float deltaTime);

	Mesh* wall;
	Mesh* floor;
	Mesh* light;

	// skybox TEMP
	Mesh* skybox_;

	// get camera
	Camera* getCamera() { return camera; };
	Input* getInput() { return input; };
	void setInput(Input* input_) { input = input_; };

	// child functions \\
	// add child
	void addChild(Mesh* child) { _childeren.push_back(child); };
	// remove child
	void removeChild(Mesh* child) { for (int i; i < _childeren.size(); i++) { if (_childeren[i] == child) { _childeren.erase(_childeren.begin() + i); }; }; };
	// get child count
	int getChildCount() { return _childeren.size(); };
	// get all childeren
	std::vector<Mesh*> getAllChilderen() { return _childeren; };

	// lamp functions \\
	// add lamp
	void addLamp(Mesh* lamp) { _lamp = lamp; };
	// remove lamp
	void removeLamp() { _lamp = NULL; };
	// get lamp
	Mesh* getLamp() { return _lamp; };
private:
	std::vector<Mesh*> _childeren;
	Mesh* _lamp = NULL;

	Camera* camera;
	Input* input;
};

#endif