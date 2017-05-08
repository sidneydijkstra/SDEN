
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include soil
#include <SOIL.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <string>

// include renderer
#include "renderer.h"
// include shader
#include "shader.h"
// include mesh
#include "mesh.h"
// include camera
#include "camera.h"
// include input
#include "input.h"

// devine functions
#define SWIDTH 800;
#define SHEIGHT 600;

// ******************** Camera ********************

// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 600;

//bool keys[1024];

// Deltatime
//GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
//GLfloat lastFrame = 0.0f;  	// Time of last frame
// ******************** Camera ********************
//void cameraMouseMovement();
//void cameraPositionMovement();


//Camera* camera = new Camera();
//Mesh* mesh;
//Input* input;
//GLFWwindow* window;
// main function
int main(){
	int screenWidth = SWIDTH;
	int screenHeight = SWIDTH;
	Renderer* renderer = new Renderer();
	renderer->createWindow(screenWidth, screenHeight);

	renderer->run();

	glfwTerminate();
	return 0;

	//window = renderer->window;

	//input = new Input(window);
	/*
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// tell openGl the size of the render window
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
	*/
	// add shader
	//Shader* shader = new Shader("shaders/vertex.shad", "shaders/fragment.shad");

	// add texture
	//Texture* texture = new Texture();

	// set openGL options
	//glEnable(GL_DEPTH_TEST);

	// set camera vars

	/*
	mesh = new Mesh();
	mesh->addTexture("assets/snoop.jpg");
	
	

	// game loop
	while (!glfwWindowShouldClose(window)) {
		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// clear color buffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// activate shader
		shader->Use();

		// update start

		cameraPositionMovement();
		cameraMouseMovement();

		mesh->position.x += 0.1f * deltaTime;
		renderer->render3DMesh(mesh, camera, shader);

		// update end

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	*/
	// Properly de-allocate all resources once they've outlived their purpose
    // Terminate GLFW, clearing any resources allocated by GLFW.
	// return 0 and exit program
}
/*
void cameraPositionMovement(){
	// Camera controls
	GLfloat cameraSpeed = 5.0f * deltaTime;
	if (input->getKey(GLFW_KEY_W))
		camera->position += cameraSpeed * camera->front;
	if (input->getKey(GLFW_KEY_S))
		camera->position -= cameraSpeed * camera->front;
	if (input->getKey(GLFW_KEY_A))
		camera->position -= glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
	if (input->getKey(GLFW_KEY_D))
		camera->position += glm::normalize(glm::cross(camera->front, camera->up)) * cameraSpeed;
	if (input->getKey(GLFW_KEY_SPACE))
		camera->position += cameraSpeed * camera->up;
	if (input->getKey(GLFW_KEY_LEFT_SHIFT))
		camera->position -= cameraSpeed * camera->up;


	if (input->getKey(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool firstMouse = true;
void cameraMouseMovement(){
	float xpos = input->getMouseX();
	float ypos = input->getMouseY();
	if (firstMouse){
		camera->lastX = xpos;
		camera->lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - camera->lastX;
	GLfloat yoffset = camera->lastY - ypos; // Reversed since y-coordinates go from bottom to left
	camera->lastX = xpos;
	camera->lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera->yaw += xoffset;
	camera->pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	front.y = sin(glm::radians(camera->pitch));
	front.z = sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch));
	camera->front = glm::normalize(front);
}
*/