#pragma once

enum Direction
{
	UP,
	DOWN,
	RIGHT,
	LEFT
};

struct RayInfo 
{
	
};

class Ray
{
public:
	Ray(int* x, int* y, int xOffset, int yOffset, Direction direction);
	int* x;
	int* y;
	int xOffset;
	int yOffset;
	Direction direction;
};