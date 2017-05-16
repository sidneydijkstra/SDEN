
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
	texture = textureloader->loadTexture(location);
}