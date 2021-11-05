#pragma once
#include "..\snake\snake.h"
#include "..\snake\food.h"

class Game
{
public:
	
	static Game* GetGame();

	//something to act as the main snake reference
	Snake* snake;

	//something to act as the main food reference 
	Food* foodPiece;

	void Run(); //begin game
	bool isRunning; // make sure game is going
	void End(); //End game

private:
	Game();								//constructor
	Game(const Game&) {};             // copy constructor

	static Game* This;

};

