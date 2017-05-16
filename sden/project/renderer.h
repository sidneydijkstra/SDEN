
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// include mesh
#include "mesh.h"
// include shader
#include "shader.h"
// include camera
#include "camera.h"
// include camera
#include "scene.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void run();
	// create window
	void createWindow(int screenWidth_, int screenHeight_);
	// render a 3D object
	void render3DMesh(Mesh* mesh, Camera* camera, Shader* shader);

	void renderVAO();
	GLuint VAO, VBO;

	// screen width
	int screenWidth;
	int screenHeight;
	// window
	GLFWwindow* window;

private:
	// Calculate deltatime of current frame
	void calculateDeltatime();
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	// input
	Input* input;
	// shader
	Shader* shader;
	// scene
	Scene* scene;
};

#endif