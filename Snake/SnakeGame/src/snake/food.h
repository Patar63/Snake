#pragma once
#include "..\math\math_util.h"
class Food
{
public:
	//construct and destruct food object
	Food();
	~Food();

	//positioning for the food
	float x_pos, y_pos;

	//make food function
	void GenFood();

};

