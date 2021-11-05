#pragma once
#include <vector>
#include "..\snake\snake_segment.h"
class Snake
{
public:
	Snake();
	~Snake();

	//snake speed
	static float SnakeSpeed;

	//decides the direction the snake is moving
	int SnakeDirect;

	//vector hold segmented list of snake parts
	std::vector<SnakeSegment*> SnakeParts;
	

};

