#include "Collision.h"
#include <iostream>

std::vector<Collision> colliders;

Collision::Collision(float x, float y, float width, float height, CollisionType collisionType)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	if(collisionType == map)
	{
		colliders.push_back(*this);
	}
}

void Collision::SetValues(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

bool Collision::IntersectsWith(Collision collider)
{

	if( collider.x <  x + width &&  collider.x + collider.width >  x &&
	    collider.y <  y + height &&  collider.y + collider.height >  y)
	{
		return true;
	}

	return false;
}

bool Collision::IntersectsWith(Collision collider, Vector2 * displacement)
{
	if( collider.x <  x + width &&  collider.x + collider.width >  x &&
	    collider.y <  y + height &&  collider.y + collider.height >  y)
	{
		displacement->x =  collider.x + collider.width/2  - ( x + width/2);
		displacement->y =0;//  collider.y + collider.height -  y;
		return true;
	}

	return false;
}

bool Collision::IntersectsWith(Vector2 mousePos)
{
	if(mousePos.x < x) return false;
	if(mousePos.x > x + width) return false;
	if(mousePos.y < y) return false;
	if(mousePos.y > y + height) return false;


	return true;
}

//Konwertuje z pozycji srodka do pozycji lewego gornego wierzcholka
bool Collision::IntersectsWithCircle(Vector2 center, float radius, Vector2* displacement)
{
	float halfWidth = width/2;
	float halfHeight = height/2;

	float ourCenterX = x + halfWidth;
	float ourCenterY = y + halfHeight;

	float clampedDistX = center.x - ourCenterX;
	float clampedDistY = center.y - ourCenterY;

	if(clampedDistX < 0)
	{
		if(-clampedDistX > halfWidth)
			clampedDistX = -halfWidth;
	}
	else
	{
		if(clampedDistX > halfWidth)
			clampedDistX = halfWidth;
	}

	if(clampedDistY < 0)
	{
		if(-clampedDistY > halfHeight)
			clampedDistY = -halfHeight;
	}
	else
	{
		if(clampedDistY > halfHeight)
			clampedDistY = halfHeight;
	}

	float distance = Vector2Distance(center, {ourCenterX + clampedDistX, ourCenterY + clampedDistY}) ;
	if(distance < radius)
	{
		distance -= radius;

		if(abs(clampedDistX) == abs(clampedDistY))
		{

			if(clampedDistY < 0) 
				displacement->x = -distance;
			else
				displacement->x = distance;
			if(clampedDistX < 0)
				displacement->y = -distance;
			else
				displacement->y = distance;
		}
		else if(abs(clampedDistX) > abs(clampedDistY))
		{
			if(clampedDistX < 0) 
			{
				halfWidth = -halfWidth;
				distance = -distance;
			}

			displacement->x = distance;
			displacement->y = 0;	
		}
		else
		{
			if(clampedDistY < 0) 
			{
				halfHeight = -halfHeight;
				distance = -distance;
			}

			displacement->x = 0;
			displacement->y = distance;

		}
		return true;
	}

	return false;
}

Vector2 Collision::GetDisplacement(Collision collider)
{
	Vector2 displacement = {0, 0};
	
	float ourHalfWidth = width/2;
	float ourHalfHeight = height/2;
	
	float colliderHalfWidth = collider.width/2;
	float colliderHalfHeight = collider.height/2;

	float xCenter =  x + ourHalfWidth;
	float yCenter =  y + ourHalfHeight;

	float xDist =  collider.x + colliderHalfWidth - xCenter;
	float yDist =  collider.y + colliderHalfHeight - yCenter;
	
	float posXDist = (xDist < 0 ? -xDist : xDist);
	float posYDist = (yDist < 0 ? -yDist : yDist);

	float overlapX = posXDist - (colliderHalfWidth + ourHalfWidth);
	float overlapY = posYDist - (colliderHalfHeight + ourHalfHeight);
	
	if(overlapX > overlapY)
	{
		if(xDist > 0)
		{
			//Horizontal Repositioning Left
			displacement.x =  -overlapX;//x + width -  collider.x; 
		}
		else
		{
			//Horizontal Repositioning Right
			displacement.x =  overlapX;//x - ( collider.x + collider.width); 
		}
	}
	else
	{
		if(yDist > 0)
		{	
			//Vertical Repositioning Up
			displacement.y =  -overlapY;//y + height -  collider.y; 
		}
		else
		{
			//Vertical Repositioning Down 
			displacement.y =  overlapY;//y - ( collider.y + collider.height); 
		}

	}

	return displacement;
}

Vector2 Collision::GetDisplacement2(Collision collider)
{
	Vector2 displacement{0,0};
	float xOrigin = x + width/2;
	float yOrigin = y + height/2;

	float colliderXOrigin = collider.x + collider.width/2;
	float colliderYOrigin = collider.y + collider.height/2;

	float xDist = colliderXOrigin - xOrigin;
	float yDist = colliderYOrigin - yOrigin;

	float posXDist = xDist > 0 ? xDist : -xDist;
	float posYDist = yDist > 0 ? yDist : -yDist;

	float xOverlap = posXDist - ((posXDist - width/2) + (posXDist - collider.width/2));
	float yOverlap = posYDist - ((posYDist - height/2) + (posYDist - collider.height/2));

	posXDist /= (width/2 + collider.width/2);
	posYDist /= (height/2 + collider.height/2);
	
	if(posXDist > posYDist)
	{
		if(xDist > 0)
		{
			//Horizontal Repositioning Left
			displacement.x =  xOverlap;//x + width -  collider.x; 
		}
		else
		{
			//Horizontal Repositioning Right
			displacement.x =  -xOverlap;//x - ( collider.x + collider.width); 
		}
	}
	else
	{
		if(yDist > 0)
		{	
			//Vertical Repositioning Up
			displacement.y =  yOverlap;//y + height -  collider.y; 
		}
		else
		{
			//Vertical Repositioning Down 
			displacement.y =  -yOverlap;//y - ( collider.y + collider.height); 
		}

	}


	return displacement;
}

void Collision::Visualize()
{
	DrawLine( x,  y,  x + width,  y, GREEN);
	DrawLine( x,  y,  x,  y + height, GREEN);
	DrawLine( x + width,  y,  x,  y + height, GREEN);
	DrawLine( x + width,  y,  x + width,  y + height, GREEN);
	DrawLine( x,  y + height,  x + width,  y + height, GREEN);
}

void AttachCollision(Collision collision)
{
	colliders.push_back(collision);
}
