
#include "mesh.h"

Mesh::Mesh(){
}

Mesh::~Mesh(){
	delete textureloader;
}

void Mesh::draw(){
}


void Mesh::setupMesh(){
}


void Mesh::addTexture(const char * location){
	texture = textureloader->loadNormalTexture(location);
}

void Mesh::addNormalMap(const char * location) {
	normalMap = textureloader->loadNormalTexture(location);
}

void Mesh::addSkybox(const char* right, const char* left, const char* top, const char* bottom, const char* back, const char* front) {
	skybox = textureloader->loadCubeMapTexture(right, left, top, bottom, back, front);
}