#include "snake.h"

//define snake move speed
float Snake::SnakeSpeed = 1.0f;

Snake::Snake()
{
	//call head of snake
	this->SnakeParts.push_back(new SnakeSegment(0, 0));
}


Snake::~Snake()
{
}
