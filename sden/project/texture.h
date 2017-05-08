
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <SOIL.h>

class Texture
{
public:
	Texture();
	GLuint loadTexture(const char* location);
private:
};

#endif