
#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(GLFWwindow* window);

	// input functions
	float getMouseX();
	float getMouseY();

	// mouse functions
	bool getKey(int keycode);

private:

	// window
	GLFWwindow* window;

	// mouse pos
	float mouseX;
	float mouseY;
};

#endif