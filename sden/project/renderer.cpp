
#include "renderer.h"

Renderer::Renderer() {
	// instantiate the GLFW windo
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
	// skybox shader TEMP
	skyboxShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
	scene = new Scene();
	scene->setInput(input);

	initCubeBuffer();
	initSkyboxBuffer();
	// game loop
	while (!glfwWindowShouldClose(window)) {
		// calulate deltatime
		calculateDeltatime();

		// calculate fps
		calculateFPS();


		// poll events
		glfwPollEvents();

		// clear color buffer
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update start

		// render skybox TEMP
		skyboxShader->Use();
		render3DSkybox(scene->skybox_, scene->getCamera(), skyboxShader, scene);
		glDepthMask(GL_TRUE);

		// use shaders
		shader->Use();

		// update scene
		scene->update(deltaTime);

		// render scene childeren
		for (int i = 0; i < scene->getChildCount(); i++){
			render3DMesh(scene->getAllChilderen()[i], scene->getCamera(), shader, scene);
		}


		// update end

		// if G == keydown recompile shaders
		if (input->getKey(GLFW_KEY_G)) {
			shader = new Shader("shaders/normal.vert", "shaders/normal.frag");
		}

		// Swap the screen buffers
		glfwSwapBuffers(window);
	} 

}

// render a 3D cube
void Renderer::render3DMesh(Mesh * mesh, Camera * camera, Shader * shader, Scene * scene){
	// bind normal VAO
	glBindVertexArray(normalVAO);

	// bind texture if there is a texture in the mesh
	if (mesh->texture != NULL) {
		// add texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->texture);
		glUniform1i(glGetUniformLocation(shader->Program, "fragTexture"), 0);

		// set doTexture to true
		GLint uniformDoTexture = glGetUniformLocation(shader->Program, "doTexture");
		glUniform1d(uniformDoTexture, true);

		// bind a normal map if there is a normal map in the mesh
		if (mesh->normalMap != NULL) {
			// add normal map
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, mesh->normalMap);
			glUniform1i(glGetUniformLocation(shader->Program, "fragNormalMap"), 1);

			// set doTexture to true
			GLint uniformDoNormalMap = glGetUniformLocation(shader->Program, "doNormalMap");
			glUniform1d(uniformDoNormalMap, true);
		}else {
			// set doTexture to false
			GLint uniformDoNormalMap = glGetUniformLocation(shader->Program, "doNormalMap");
			glUniform1d(uniformDoNormalMap, false);
		}
	}else {
		// set doTexture to false
		GLint uniformDoTexture = glGetUniformLocation(shader->Program, "doTexture");
		glUniform1d(uniformDoTexture, false);

		// set doTexture to false
		GLint uniformDoNormalMap = glGetUniformLocation(shader->Program, "doNormalMap");
		glUniform1d(uniformDoNormalMap, false);
	}

	// set positions, rotation and sacle
	glm::mat4 model;
	model = glm::scale(model, mesh->scale);
	model = glm::translate(model, mesh->position);
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// set perspective
	mesh->view = glm::lookAt(camera->position, camera->position + camera->front, camera->up);
	mesh->projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.001f, 100.0f);

	// set uniform model, view and perspective
	GLint uniformModel = glGetUniformLocation(shader->Program, "model");
	GLint uniformView = glGetUniformLocation(shader->Program, "view");
	GLint uniformProjection = glGetUniformLocation(shader->Program, "projection");
	// pass the matrices to the shader
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mesh->view));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(mesh->projection));

	// set uniform color, light color and view position
	GLint uniformColor = glGetUniformLocation(shader->Program, "fragObjectColor");
	GLint uniformLightColor = glGetUniformLocation(shader->Program, "fragLightColor");
	GLint uniformViewPosition = glGetUniformLocation(shader->Program, "fragViewPosition");
	// pass the matrices to the shader
	glUniform3f(uniformColor, mesh->color.x, mesh->color.y, mesh->color.z);
	glUniform3f(uniformLightColor, mesh->lightColor.x, mesh->lightColor.y, mesh->lightColor.z);
	glUniform3f(uniformViewPosition, camera->position.x, camera->position.y, camera->position.z);

	// if there is a lamp in current scene set all the right uniforms
	if (scene->getLamp() != NULL) {
		// set uniform light position and do lighting
		GLint uniformLightPosition = glGetUniformLocation(shader->Program, "fragLightPosition");
		GLint uniformDoLighting = glGetUniformLocation(shader->Program, "doLighting");
		// pass the matrices to the shader
		glUniform3f(uniformLightPosition, scene->getLamp()->position.x, scene->getLamp()->position.y, scene->getLamp()->position.z);
		glUniform1d(uniformDoLighting, true);
	}
	else {
		// set uniform do lighting
		GLint uniformDoLighting = glGetUniformLocation(shader->Program, "doLighting");
		// pass the matrices to the shader
		glUniform1d(uniformDoLighting, false);
	}

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);

}

// render a skybox TEMP
void Renderer::render3DSkybox(Mesh * mesh, Camera * camera, Shader * shader, Scene * scene){
	// set depth mash to false
	glDepthMask(GL_FALSE);
	// bind skybox VAO
	glBindVertexArray(skyboxVAO);

	// check if mesh has a skybox texture
	if (mesh->skybox == NULL) {
		std::cout << "skybox doesent have a skybox texture" << std::endl;
		return;
	}else {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mesh->skybox);
	}

	// set positions, rotation and sacle
	glm::mat4 model;
	model = glm::translate(model, mesh->position);

	// set perspective
	mesh->view = glm::lookAt(camera->position, camera->position + camera->front, camera->up);
	mesh->projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.001f, 100.0f);

	// set uniform model, view and perspective
	GLint uniformModel = glGetUniformLocation(shader->Program, "model");
	GLint uniformView = glGetUniformLocation(shader->Program, "view");
	GLint uniformProjection = glGetUniformLocation(shader->Program, "projection");
	// pass the matrices to the shader
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mesh->view));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(mesh->projection));

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	// set depth mash to true
	glDepthMask(GL_TRUE);
}

void Renderer::initCubeBuffer() {
	GLfloat vertices[] = {
		// Positions           // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glGenVertexArrays(1, &normalVAO);
	glGenBuffers(1, &normalVBO);

	glBindVertexArray(normalVAO);

	// Vertices attribute
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Renderer::initSkyboxBuffer(){
	float vertices[] = {      
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	// Vertices attribute
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
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

// ################## does not work ################## \\
// load object
void Renderer::loadObject(const char* path) {

	FILE * file = fopen(path, "r");

	// check if you can open file
	if (file == NULL) {
		std::cout << "unable to open .obj file! [CANT LOAD OBJECT]" << std::endl;
		return;
	}

	std::vector< unsigned int > vertexIndices, textureIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_texture;
	std::vector<glm::vec3> temp_normals;

	while (1) {

		char lineHeader[128];

		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);

		// check if at end of lines
		if (res == EOF) { // EOF = end of line
			break;
		}

		// read line and proces information
		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_texture.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				std::cout << "File can't be read by our simple parser [Try exporting with other options]" << std::endl;
				return;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

}
