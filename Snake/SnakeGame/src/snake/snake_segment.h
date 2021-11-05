#pragma once
//class to handle other parts of snake
class SnakeSegment
{
public:
	SnakeSegment();			//constructor


	SnakeSegment(float x, float y);		//copy constructor


	~SnakeSegment();		//destructor

	//tracks segment positioning
	float x_pos, y_pos;
};

