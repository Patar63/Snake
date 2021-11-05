//Computer Graphic Midterm - Patrick Thompson && Mel Fortin

#include "console\console.h"
#include "game\definitions.h"
#include "game\game.h"
#include "openGL\renderer\renderer.h"  //file pathing wasn't behaving, had to be specific


//create class objects
Console* Screen = Console::GetConsole();
Game* GameStartUp = Game::GetGame();
Snake* SnakePlayer = Game::GetGame()->snake;
Renderer* PrepRender = Renderer::GetRenderer();



int main() 
{
	double t = 0.0f;

	GameStartUp->Run();


	while (!glfwWindowShouldClose(PrepRender->Window))
	{
		double Time = glfwGetTime();

		if (Time - t >= 1.0 / 10)
		{
			t = Time;
			//called every frame
			PrepRender->render(10);
		}
	}

	glfwTerminate();
	
	return 0;
}