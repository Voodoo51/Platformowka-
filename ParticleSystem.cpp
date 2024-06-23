#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const char* path, int instances, float minSpeed, float maxSpeed, float minLifeTime, float maxLifeTime, float minRotationSpeed, float maxRotationSpeed, float speedDeceleration, float rotationSpeedDeceleration)
{
	texture = LoadTexture(path);

	this->instances = instances;
	this->minSpeed = minSpeed;
	this->maxSpeed = maxSpeed;
	this->minLifeTime = minLifeTime;
	this->maxLifeTime = maxLifeTime;
	this->minRotationSpeed = minRotationSpeed;
	this->maxRotationSpeed = maxRotationSpeed;  
	this->speedDeceleration = speedDeceleration;
	this->rotationSpeedDeceleration = rotationSpeedDeceleration;
		
	aliveCount = instances;
	particles = (Particle*)malloc(instances * sizeof(Particle));
}

void ParticleSystem::AllocateMemory()
{
	particles = (Particle*)malloc(instances * sizeof(Particle));
}

void ParticleSystem::Update() 
{

	for(int i = 0; i < instances; i++)
	{
		if(!particles[i].alive) 
		{
			aliveCount++;
			continue;
		}
	
		if(gravity)
		{
			particles[i].pos.y += gravityStrength + particles[i].acceleration;
			Vector2 displacement;

			particles[i].acceleration += speedDeceleration;
			for(int j = 0; j < colliders.size(); j++)
			{
				Vector2 circleCenter;
				circleCenter.x = particles[i].pos.x + (texture.width/2) * scale;
				circleCenter.y = particles[i].pos.y + (texture.height/2) * scale;

				if(colliders[j].IntersectsWithCircle(circleCenter, (texture.width/2) * scale, &displacement))
				{
					particles[i].pos.x -= displacement.x;
					particles[i].pos.y -= displacement.y;
					particles[i].acceleration = 0;
					//break;
				}
			}
		}

		particles[i].pos.x += particles[i].dir.x * particles[i].speed;
		particles[i].pos.y += particles[i].dir.y * particles[i].speed;
	
		particles[i].rotation += particles[i].rotDir *  particles[i].rotationSpeed;

		particles[i].speed -= speedDeceleration;

		if(particles[i].speed <= 0) particles[i].speed = 0;

		particles[i].rotationSpeed -= rotationSpeedDeceleration;

		if(particles[i].rotationSpeed <= 0) particles[i].rotationSpeed = 0;

		particles[i].lifeTime -= 0.0166f;
		
		if(particles[i].lifeTime <= 0)  particles[i].alive = false;
		
		//DrawTexture(texture, particles[i].pos.x, particles[i].pos.y, WHITE);
		DrawTexturePro(texture, {0,0, (float)texture.width, (float)texture.height},
				{particles[i].pos.x,particles[i].pos.y,	
				(float)texture.width * scale,
				(float)texture.height * scale}, 
				{((float)texture.width * scale)/2, ((float)texture.height * scale)/2},
				DEG2RAD * particles[i].rotation, WHITE);
	}
}


void ParticleSystem::Play(Vector2 start, SpawnMode mode)
{
	srand(time(NULL));
	if(mode == AxisVertical)
	{
		for(int i = 0; i < instances; i++)
		{
			particles[i].pos = start;
			if(rand() % 2 == 1)
 				particles[i].dir.y = 1;
			else
				particles[i].dir.y = -1;

			particles[i].dir.x = 0;
		}
	}
	else if(mode == AxisHorizontal)
	{
		for(int i = 0; i < instances; i++)
		{
			particles[i].pos = start;
			if(rand() % 2 == 1)
 				particles[i].dir.x = 1;
			else
				particles[i].dir.x = -1;

			particles[i].dir.y = 0;
		}
	}
	else if(mode == Sphere)
	{

	}
	
	for(int i = 0; i < instances; i++)
	{
		particles[i].alive = true;
		particles[i].rotation = 0;
		if(rand()%2 == 0)
		{
			particles[i].rotDir = 1;
		}
		else
		{
			particles[i].rotDir = -1;
		}

		int minOnes = (int)minLifeTime;
		int minTens = (minLifeTime - minOnes) * 10;

		int maxOnes = (int)maxLifeTime;
		int maxTens = (maxLifeTime - maxOnes) * 10;
		
		if(minOnes == 0) minOnes = 1;
		if(maxOnes == 0) maxOnes = 1;
		if(minTens == 0) minTens = 1;
		if(maxTens == 0) maxTens = 1;

		particles[i].lifeTime = rand() % (maxOnes + 1) + minOnes + ((float)(rand() %  (maxTens) + minTens))/10;
	
		minOnes = (int)minSpeed;
		minTens = (minLifeTime - minOnes) * 10;

		maxOnes = (int)maxSpeed;
		maxTens = (maxSpeed - maxOnes) * 10;

		if(minOnes == 0) minOnes = 1;
		if(maxOnes == 0) maxOnes = 1;
		if(minTens == 0) minTens = 1;
		if(maxTens == 0) maxTens = 1;


		particles[i].speed = rand() % (maxOnes + 1) + minOnes + ((float)(rand() %  (maxTens) + minTens))/10;

		minOnes = (int)minRotationSpeed;
		minTens = (minRotationSpeed - minOnes) * 10;

		maxOnes = (int)maxRotationSpeed;
		maxTens = (maxRotationSpeed - maxOnes) * 10;

		if(minOnes == 0) minOnes = 1;
		if(maxOnes == 0) maxOnes = 1;
		if(minTens == 0) minTens = 1;
		if(maxTens == 0) maxTens = 1;


		particles[i].rotationSpeed = rand() % (maxOnes + 1) + minOnes + ((float)(rand() %  (maxTens) + minTens))/10;
	}

}






























