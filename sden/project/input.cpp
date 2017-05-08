
#include "input.h"

// event handelers
void handleKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void handleMouse(GLFWwindow* window, double xpos, double ypos);
void handleScroll(GLFWwindow* window, double xoffset, double yoffset);

// key
bool _keys[GLFW_KEY_LAST];

// mouse
int _mouseX;
int _mouseY;

Input::Input(GLFWwindow* glfwWindow) {
	// set window
	window = glfwWindow;

	// Set the required callback functions
	glfwSetKeyCallback(window, handleKey);
	glfwSetCursorPosCallback(window, handleMouse);
	glfwSetScrollCallback(window, handleScroll);

	// set all key bools to false
	for (int i = 0; i < GLFW_KEY_LAST; i++){
		_keys[i] = false;
	}

	std::cout << "Input created!" << std::endl;
}


float Input::getMouseX(){
	return _mouseX;
}

float Input::getMouseY(){
	return _mouseY;
}

bool Input::getKey(int keycode){
	return _keys[keycode];
}

// key, mouse and scroll handelers
void handleKey(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key >= 0 && key <= GLFW_KEY_LAST){
		if (action == GLFW_PRESS){
			_keys[key] = true;
		}else if (action == GLFW_RELEASE){
			_keys[key] = false;
		}
	}

	// exit on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void handleMouse(GLFWwindow* window, double xpos, double ypos){
	_mouseX = xpos;
	_mouseY = ypos;
}

void handleScroll(GLFWwindow* window, double xoffset, double yoffset) {

}


