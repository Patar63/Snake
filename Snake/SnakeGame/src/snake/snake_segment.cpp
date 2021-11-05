#include "snake_segment.h"

//create a segement of the snake
SnakeSegment::SnakeSegment()
{
	x_pos, y_pos = 0;
}

//pass coordinates to be accurate in placement of the segment
SnakeSegment::SnakeSegment(float x, float y)
{
	x_pos = x;
	y_pos = y;
}

SnakeSegment::~SnakeSegment()
{
}
