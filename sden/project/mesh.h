
#ifndef MESH_H
#define MESH_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// include shader
#include "shader.h"
// include texture
#include "texture.h"

class Mesh{
public:
	Mesh();
	~Mesh();

	void draw();
	void addTexture(const char* location);

	// mesh variables
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 rotation = glm::vec3(0, 0, 0);

	glm::mat4 view;
	glm::mat4 projection;

	// texture
	GLuint texture = NULL;
private:
	void setupMesh();


	// pointers
	Texture* textureloader = new Texture();


};

#endif