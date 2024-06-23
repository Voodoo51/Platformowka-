#pragma once
#include <raylib.h>
#include <vector>
#include "Logic.h"
#include <iostream>
#include "Collision.h"

enum SpawnMode
{
	AxisVertical,
	AxisHorizontal,
	Sphere
};

struct Particle
{
	Vector2 pos{0,0};
	Vector2 dir{0,0};
	int rotDir = 0;
	float rotation = 0;
	float speed = 0;
	float acceleration = 0;
	float rotationSpeed = 0;
	float lifeTime = 0;
	bool alive = true;
};

class ParticleSystem : public Logic
{
	public:
		ParticleSystem(){};
		ParticleSystem(const char* path, int instances, float minSpeed, float maxSpeed, float minLifeTime, float maxLifeTime, float minRotationSpeed, float maxRotationSpeed, float speedDeceleration, float rotationSpeedDeceleration);
		void Update();
		void AllocateMemory();
		void Play(Vector2 start, SpawnMode mode);

		Texture2D texture;	
		int instances;
		float scale;

		float minLifeTime;
		float maxLifeTime;

		float minSpeed;
		float maxSpeed;

		float minRotationSpeed;
		float maxRotationSpeed;

		float speedDeceleration;
		float rotationSpeedDeceleration;

		bool gravity = false;
		float gravityStrength;
		int aliveCount = 0;

	private:
		Particle* particles;
};

