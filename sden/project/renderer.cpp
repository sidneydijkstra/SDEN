
#include "renderer.h"

Renderer::Renderer() {
	// instantiate the GLFW windo
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

}

Renderer::~Renderer(){
	// delete shader
	delete shader;
	// delete scene
	delete scene;
	// delete input
	delete input;
}

// create a window
void Renderer::createWindow(int screenWidth_, int screenHeight_) {
	// create a window object
	window = glfwCreateWindow(screenWidth_, screenHeight_, "SDEN", nullptr, nullptr);
	if (window == nullptr){
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);

	// set width and height
	screenHeight = screenHeight_;
	screenWidth = screenWidth_;
	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	// tell openGl the size of the render window
	glfwGetFramebufferSize(window, &screenWidth, &screenWidth);

	glViewport(0, 0, screenWidth, screenWidth);

	// set openGL options
	glEnable(GL_DEPTH_TEST);

	// create input
	input = new Input(window);
}

// main game loop
void Renderer::run() {
	shader = new Shader("shaders/normal.vert", "shaders/normal.frag");
	scene = new Scene();
	scene->setInput(input);

	renderVAO();
	// game loop
	while (!glfwWindowShouldClose(window)) {
		// calulate deltatime
		calculateDeltatime();

		// calculate fps
		calculateFPS();


		// poll events
		glfwPollEvents();

		// use shaders
		shader->Use();

		// clear color buffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update start

		// update scene
		scene->update(deltaTime);

		// render scene childeren
		for (int i = 0; i < scene->getChildCount(); i++){
			render3DMesh(scene->getAllChilderen()[i], scene->getCamera(), shader);
		}

		// update end

		// Swap the screen buffers
		glfwSwapBuffers(window);
	} 

}

// render a 3D cube
void Renderer::render3DMesh(Mesh * mesh, Camera * camera, Shader * shader){
	glBindVertexArray(VAO);
	// bind texture
	if (mesh->texture != NULL) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->texture);
		glUniform1i(glGetUniformLocation(shader->Program, "ourTexture"), 0);
	}
	glm::mat4 model;
	model = glm::scale(model, mesh->scale);
	model = glm::translate(model, mesh->position);
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	mesh->view = glm::lookAt(camera->position, camera->position + camera->front, camera->up);
	mesh->projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.001f, 100.0f);

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	GLint viewLoc = glGetUniformLocation(shader->Program, "view");
	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mesh->view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(mesh->projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Renderer::renderVAO() {
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	// Vertices attribute
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

// Calculate deltatime of current frame
void Renderer::calculateDeltatime(){
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void Renderer::calculateFPS() {
	currentTime = glfwGetTime();
	fps++;
	if (currentTime - lastTime >= 1) {
		// print fps
		std::cout << "fps: " << fps << std::endl;

		lastTime = glfwGetTime();
		fps = 0;
	}
}
