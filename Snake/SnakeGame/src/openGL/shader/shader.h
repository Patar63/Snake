#pragma once
#ifndef GLEW_H
#define GLEW_H
#include <glew.h>
#endif
class Shader
{
public:
	//constructor and destructor 
	Shader(GLchar* shaderGLSL);
	~Shader();

	const GLchar* shaderSource;
};

