#include "Ray.h"

Ray::Ray(int* x, int* y, int xOffset, int yOffset, Direction direction)
{
	this->x = x;
	this->y = y;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->direction = direction;
}