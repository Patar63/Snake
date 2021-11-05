#include "food.h"


//generate random position
Food::Food()
{
}


Food::~Food()
{
}

//generate random position
void Food::GenFood()
{
	x_pos = Math::RandomNumber(-10, -10);
	y_pos = Math::RandomNumber(-10, -10);
}