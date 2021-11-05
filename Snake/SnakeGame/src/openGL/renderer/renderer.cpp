#include "renderer.h"

void glfw_error_callback(int error, const char* description)
{
}

void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (key == GLFW_KEY_W)
		SnakePlayer->SnakeDirect = UP;
	if (key == GLFW_KEY_A)
		SnakePlayer->SnakeDirect = LEFT;
	if (key == GLFW_KEY_S)
		SnakePlayer->SnakeDirect = DOWN;
	if (key == GLFW_KEY_D)
		SnakePlayer->SnakeDirect = RIGHT;
}

Renderer* Renderer::This = NULL;

Renderer::Renderer()
{
	//initalize openGL and GLFW
	initGLFW();
	initGLEW();

	//initalize shaders
	GLSL_vertexShader = new Shader(R"glsl(
    #version 450 core
    in vec2 position;
    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
    }
	)glsl");

	GLSL_fragmentShader = new Shader(R"glsl(
    #version 450 core
    out vec4 outColor;
    uniform vec3 triangleColor;
    void main()
    {
        outColor = vec4(triangleColor, 1.0);
    }
	)glsl");
}
Renderer::~Renderer()
{
	delete GLSL_vertexShader;
	delete GLSL_fragmentShader;
}

Renderer* Renderer::GetRenderer()
{
	if (This == NULL)
	{
		This = new Renderer();
	}
	return This;

}

void Renderer::initGLEW()
{
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	Screen->LogAndFile("GLEW Initalized");
}

void Renderer::initGLFW()
{
	//Initalize GLFW
	if (!glfwInit())
	{
		Screen->LogAndFile("Failed to initiate GLFW");
		exit(EXIT_FAILURE);
	}
	glfwSetErrorCallback(glfw_error_callback);
	Window = initWindow();
	glfwSetKeyCallback(Window, glfw_key_callback);

	Screen->LogAndFile("GLFW Initalized");
}

GLFWwindow* Renderer::initWindow()
{
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	GLFWwindow* gameWindow = glfwCreateWindow(640, 640, "Main", NULL, NULL);

	if (!gameWindow)
	{
		Screen->LogAndFile("Failed to initiate GLFW window \"Main\"");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(gameWindow);
	glfwSwapInterval(1);

	return gameWindow;
}

void Renderer::Square(GLfloat x, GLfloat y)
{
	//ensure x and y can't clip outside the window
	if (x > 0.9)
		x = 0.9f;
	if (y > 0.9)
		y = 0.9f;

	GLfloat vertices[] = {
		x, y, 
		(x + 0.1f), y, 
		(x + 0.1f), (y + 0.1f), 
		x, (y + 0.1f) 
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &GLSL_vertexShader->shaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &GLSL_fragmentShader->shaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

	//simple set colour
	glUniform3f(uniColor, 1.0f, 1.0f, 1.0f);

	// Draw a square
	glDrawArrays(GL_QUADS, 0, 4);
}
void Renderer::Square(GLfloat x, GLfloat y, int R, int G, int B)
{

	//ensure x and y can't clip outside the window
	if (x > 0.9)
		x = 0.9f;
	if (y > 0.9)
		y = 0.9f;

	GLfloat vertices[] = {
		x, y, 
		(x + 0.1f), y, 
		(x + 0.1f), (y + 0.1f), 
		x, (y + 0.1f) 
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &GLSL_vertexShader->shaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &GLSL_fragmentShader->shaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

	//simple set colour
	glUniform3f(uniColor, openGL_utils::RGBtoOpenGL(R), openGL_utils::RGBtoOpenGL(G), openGL_utils::RGBtoOpenGL(B));

	// Draw a square
	glDrawArrays(GL_QUADS, 0, 4);
}

void Renderer::SnakePlayerRend()
{
	if (!GameStartUp->isRunning)
		return;

	float clampedSnakeSpeed = (SnakePlayer->SnakeSpeed / 10);

	for (int i = SnakePlayer->SnakeParts.size() - 1; i >= 0; i--)
	{

		//out of bounds check
		if ((SnakePlayer->SnakeParts[0]->x_pos > 1.0f) || (SnakePlayer->SnakeParts[0]->x_pos < -1.0f) || (SnakePlayer->SnakeParts[0]->y_pos > 1.0f) || (SnakePlayer->SnakeParts[0]->y_pos < -1.0f))
			GameStartUp->End();


		if (i == 0)
		{
			//if its the head (1st) change colour to red
			else if (SnakePlayer->SnakeDirect == UP)
			{
				SnakePlayer->SnakeParts[i]->y_pos = SnakePlayer->SnakeParts[i]->y_pos + clampedSnakeSpeed;
				Square(SnakePlayer->SnakeParts[i]->x_pos, SnakePlayer->SnakeParts[i]->y_pos, 255, 0, 0);
			}
			else if (SnakePlayer->SnakeDirect == DOWN)
			{
				SnakePlayer->SnakeParts[i]->y_pos = SnakePlayer->SnakeParts[i]->y_pos - clampedSnakeSpeed;
				Square(SnakePlayer->SnakeParts[i]->x_pos, SnakePlayer->SnakeParts[i]->y_pos, 255, 0, 0);
			}
			else if (SnakePlayer->SnakeDirect == LEFT)
			{
				SnakePlayer->SnakeParts[i]->x_pos = SnakePlayer->SnakeParts[i]->x_pos - clampedSnakeSpeed;
				Square(SnakePlayer->SnakeParts[i]->x_pos, SnakePlayer->SnakeParts[i]->y_pos, 255, 0, 0);
			}
			else if (SnakePlayer->SnakeDirect == RIGHT)
			{
				SnakePlayer->SnakeParts[i]->x_pos = SnakePlayer->SnakeParts[i]->x_pos + clampedSnakeSpeed;
				Square(SnakePlayer->SnakeParts[i]->x_pos, SnakePlayer->SnakeParts[i]->y_pos, 255, 0, 0);
			}

			//if the snake collides with itself
			for (uint32_t j = 1; j < SnakePlayer->SnakeParts.size(); j++)
			{
				if ((SnakePlayer->SnakeParts[i]->x_pos == SnakePlayer->SnakeParts[j]->x_pos) && (SnakePlayer->SnakeParts[i]->y_pos == SnakePlayer->SnakeParts[j]->y_pos))
				{
					//causing game end exits the main loop
					GameStartUp->End();
				}
			}
			//if the snakes head collides with a piece of food
			if (Math::compare(SnakePlayer->SnakeParts[0]->x_pos, GameStartUp->foodPiece->x_pos) && Math::compare(SnakePlayer->SnakeParts[0]->y_pos, GameStartUp->foodPiece->y_pos))
			{
				//spawn food at a new location
				GameStartUp->foodPiece->GenFood();
				//add to the snake
				SnakePlayer->SnakeParts.push_back(new SnakeSegment());

			}


		}
		else
		{
			//all other parts follow this pattern a,b,c,d -> b =a c=b d=c etc
			SnakePlayer->SnakeParts[i]->x_pos = SnakePlayer->SnakeParts[i - 1]->x_pos;
			SnakePlayer->SnakeParts[i]->y_pos = SnakePlayer->SnakeParts[i - 1]->y_pos;

			Square(SnakePlayer->SnakeParts[i]->x_pos, SnakePlayer->SnakeParts[i]->y_pos);

		}
	}


}

void Renderer::FoodDraw()
{
	Square(GameStartUp->foodPiece->x_pos, GameStartUp->foodPiece->y_pos, 0, 0, 255);
}

void Renderer::render(int frameRate)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SnakePlayerRend();
	FoodDraw();

	glfwSwapBuffers(Window);
	glfwPollEvents();
}
