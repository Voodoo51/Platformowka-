#pragma once
#include "raylib.h"
#include "Logic.h"
#include "Animation.h"
#include "CameraFollow.h"
#include "Collision.h"
#include <memory>

class Enemy : public Logic
{
	public:
		Enemy(Vector2 startPos, Vector2 endPos, float speed, Animation * frames);
		void Update();
		bool CanBeHit(Collision collider);
		bool CanHit(Collision collider);
		void OnDeath();
	private:
		void Die();
		Vector2 startPos;
		Vector2 endPos;
		Vector2 currentPos;
		
		Collision hitBox;
		Collision killHitBox;
		int collisionSizerX;
		int collisionSizerY;

		Animation* frames;
		float speed;
		float distanceTraveled;
		float distance;
		float t;
		int dir;

		bool dead;
		float velocity;
		float velocityDrop;
		float timeToDie;

};

extern std::vector<Enemy*> enemies;
