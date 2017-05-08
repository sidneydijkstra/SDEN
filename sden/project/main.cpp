
#include "renderer.h"

// devine functions
#define SWIDTH 800;
#define SHEIGHT 600;

// main function
int main() {
	int screenWidth = SWIDTH;
	int screenHeight = SWIDTH;
	Renderer* renderer = new Renderer();
	renderer->createWindow(screenWidth, screenHeight);

	renderer->run();

	glfwTerminate();
	return 0;
}