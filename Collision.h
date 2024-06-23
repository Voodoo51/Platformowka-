#pragma once
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cmath>

enum CollisionType
{
	map,
	projectile,
	other
};

class Collision
{
public:
	Collision(){};
	Collision(float x, float y, float width, float height, CollisionType collisionType);
	void SetValues(float x, float y, float width, float height);
	bool IntersectsWith(Collision collider);
	bool IntersectsWith(Collision collider, Vector2 * displacement);
	bool IntersectsWith(Vector2 mousePos);
	bool IntersectsWithCircle(Vector2 center, float radius, Vector2* displacement);
	Vector2 GetDisplacement2(Collision collider);
	Vector2 GetDisplacement(Collision collider);
	void Visualize();
	float x;
	float y;
	float width;
	float height;
};

extern std::vector<Collision> colliders;

void AttachCollision(Collision collision);
