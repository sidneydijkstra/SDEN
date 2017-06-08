
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
// include scene
#include "scene.h"
// include skybox
#include "skybox.h"

class Renderer
{
public:
	Renderer();
	~Renderer();
	void run();
	// create window
	void createWindow(int screenWidth_, int screenHeight_);

	// load object #### does not work yet ####
	void loadObject(const char * path);


	GLuint normalVAO, normalVBO;
	GLuint skyboxVAO, skyboxVBO;

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

	// calculate fps
	void calculateFPS();
	GLfloat currentTime;
	GLfloat lastTime;
	GLfloat fps;

	// input
	Input* input;
	// normal shader
	Shader* normalShader;
	// skybox shader
	Shader* skyboxShader;
	// scene
	Scene* scene;

	// render a 3D object
	void render3DMesh(Mesh* mesh, Camera* camera, Shader* shader, Scene* scene);
	void render3DSkybox(Skybox* mesh, Camera* camera, Shader* shader);

	// bind buffer functions
	void initCubeBuffer();

};

#endif