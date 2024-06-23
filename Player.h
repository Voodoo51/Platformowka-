#pragma once
#include "Logic.h"
#include "Collision.h"
#include "Animation.h"
#include "ParticleSystem.h"
#include "Coin.h"
#include "Player.h"
#include "Enemy.h"
#include <cmath>

extern float velocity;
extern float velocityJumpForce;
extern float velocityDecelerationSpeed;


class Player : public Logic
{
	enum PlayerState
	{
		Standing,
		Walking,
		Jumping
	};

	public:
		Player(float x, float y, float walkSpeed, Animation idleAnimation, Animation walkAnimation, Sprite fallingAnim, Sprite jumpingAnim, Sprite heart);
		void Start(){};
		void Update();
		void UpdateScreenSpace();
		Vector2 pos;
	private:
		Vector2 spawnPoint;
		Collision collider;
		Collision groundCheck;
		int collisionSizerX;
		int collisionSizerY;

		Vector2 groundCheckPos;
		
		bool isGrounded = false;

		float walkSpeed;
		float velocity = 5;
		float velocityJumpForce = 20;
		float velocityDecelerationSpeed = 0.8;

		int health;
		
		int score;

		Color color;
		Animation idleAnimation;
		Animation walkAnimation;
		Sprite jumpingFrame;
		Sprite fallingFrame;
		Sprite heart;
		PlayerState state;

		ParticleSystem particleSystem;
	
		float t;
		float immunityCooldown;

		bool hasImmunity = false;
		bool floorHitOnce = true;
};

