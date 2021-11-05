#pragma once
// Link statically with GLEW
#define GLEW_STATIC

#ifndef GLEW_H
#define GLEW_H
#include <glew.h>
#endif

#ifndef GLFW_H
#define GLFW_H
#include <glfw3.h>
#endif

#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include "..\..\game\definitions.h"
#endif

#ifndef Screen_H
#define Screen_H 
#include "..\..\console\console.h"
extern Console* Screen;
#endif

#ifndef GameStartUp_H
#define GameStartUp_H 
#include "..\..\game\game.h"
#include "..\..\openGL\utils\utils.h"

extern Game* GameStartUp;
#endif

#ifndef SnakePlayer_H
#define SnakePlayer_H 
extern Snake* SnakePlayer;
#endif

#include "..\shader\shader.h"

void glfw_error_callback(int error, const char* description);

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


class Renderer
{
private:
	static Renderer* Renderer::This;
	Shader* GLSL_vertexShader;
	Shader* GLSL_fragmentShader;
public:
	Renderer();
	~Renderer();

	static Renderer* GetRenderer();

	GLFWwindow* Window;

	void initGLEW();
	void initGLFW();
	GLFWwindow* initWindow();
	void Square(GLfloat x, GLfloat y);
	void Square(GLfloat x, GLfloat y, int R, int G, int B);

	void FoodDraw(); 
	void SnakePlayerRend();
	void render(int frameRate);
};

