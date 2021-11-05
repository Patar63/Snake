#pragma once
class Math
{
public:
	//generates random number for use of the food object
	static float RandomNumber(int min, int max);

	//used to compare positioning of snake and food
	static bool compare(float a, float b);
};

