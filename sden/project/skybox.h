
#ifndef SKYBOX_H
#define SKYBOX_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include "texture.h"

class Skybox
{
public:
	Skybox(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front);
	~Skybox();

	// skybox update function
	void update(glm::vec3 position);

	// skybox position
	glm::vec3 position = glm::vec3(0, 0, 0);
	// skybox perspective variables
	glm::mat4 view;
	glm::mat4 projection;

	// skybox vao and vbo
	GLuint skyboxVAO, skyboxVBO;

	// add a new texture
	void addSkyboxTexture(const char * right, const char * left, const char * top, const char * bottom, const char * back, const char * front);
	// skybox texture
	unsigned int texture = NULL;
private:
	// create the skybox buffers
	void initSkybox();

	// texture loader
	Texture* textureloader = new Texture();
};

#endif