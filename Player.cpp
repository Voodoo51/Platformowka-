#include "Player.h"
#include "iostream"

Player::Player(float x, float y, float walkSpeed, Animation idleAnimation, Animation walkAnimation, Sprite fallingFrame, Sprite jumpingFrame, Sprite heart)
{
	pos.x = x;
	pos.y = y;

	this->health = 5;
	this->score = 0;

	this->walkSpeed = walkSpeed;

	collisionSizerX = 30;
	collisionSizerY = 20;

	collider.width = walkAnimation.GetFrameWidth(0) - collisionSizerX;
	collider.height = walkAnimation.GetFrameHeight(0) - collisionSizerY;

	collider.x = x;
	collider.y = y;

	groundCheck.width = collider.width - 10;
	groundCheck.height = 0.1f;

	this->walkAnimation = walkAnimation;
	this->idleAnimation = idleAnimation;
	this->fallingFrame = fallingFrame;
	this->jumpingFrame = jumpingFrame;
	this->heart = heart;
	color = WHITE;

	spawnPoint.x = pos.x;
	spawnPoint.y = pos.y;

	hasImmunity = false;
	immunityCooldown = 5;
	t = 0;

	particleSystem.texture = LoadTexture("kloc64.png");
	particleSystem.instances = 0;
	particleSystem.scale = 0.1f;
	particleSystem.minLifeTime = 0.15f;
	particleSystem.maxLifeTime = 0.25f;
	particleSystem.minSpeed = 5;
	particleSystem.maxSpeed = 10;
	particleSystem.minRotationSpeed = 30;
	particleSystem.maxRotationSpeed = 60;
	particleSystem.speedDeceleration = 1;
	particleSystem.rotationSpeedDeceleration = 0.5;
	particleSystem.gravity = true;
	particleSystem.gravityStrength = 5;

	particleSystem.AllocateMemory();

}

void Player::Update()
{
	if (IsKeyDown(KEY_RIGHT))
	{
		pos.x += walkSpeed;
		walkAnimation.flipped = false;
		idleAnimation.flipped = false;
		fallingFrame.flipped = false;
		jumpingFrame.flipped = false;

		if(state != Jumping)
			state = Walking;

	}
	else if (IsKeyDown(KEY_LEFT))
	{
		pos.x -= walkSpeed;
		walkAnimation.flipped = true;
		idleAnimation.flipped = true;
		fallingFrame.flipped = true;
		jumpingFrame.flipped = true;

		if(state != Jumping)
			state = Walking;
	}
	else if(state != Jumping)
		state = Standing;

	if(IsKeyDown(KEY_SPACE) && isGrounded) 
	{
		velocity = -velocityJumpForce;
		isGrounded = false;
		state = Jumping;
	}
	//if (IsKeyDown(KEY_UP)) kurwa.y -= 5;
	//else if (IsKeyDown(KEY_DOWN)) kurwa.y += 5;


	Vector2 displacement = {0,0};
	Vector2 offset{0,0};
	if(!isGrounded)
	{
		floorHitOnce = false;
		pos.y += velocity;
		velocity += velocityDecelerationSpeed;
		state = Jumping;
	}
	else
	{
		velocity = 0;
	}
	int collisionCountX = 0;
	int collisionCountY = 0;
	bool yDownCollided = false;
		
	collider.x = pos.x + collisionSizerX/2 - 5;
	collider.y = pos.y + collisionSizerY/2;

	groundCheck.x = pos.x + 10/2 + collisionSizerX/2 - 5;
	groundCheck.y = pos.y + collider.height + collisionSizerY/2;

	for(int i = 0; i < colliders.size(); i++)
	{

		if(collider.IntersectsWith(colliders[i]))
		{
			displacement = collider.GetDisplacement2(colliders[i]);
			if(displacement.y != 0)
			{
				if(velocity >= 0 && displacement.y > 0)
					velocity = 0;
				if(velocity <= 0 && displacement.y < 0)
					velocity = 0;
				collisionCountY++;
			}
			else
				collisionCountX++;
			offset.x += displacement.x;
			offset.y += displacement.y;
		}

	}

	for(int i = 0; i < colliders.size(); i++)
	{
		if(groundCheck.IntersectsWith(colliders[i]))
		{
			isGrounded = true;

			if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
				state = Walking;
			else
				state = Standing;
			break;
		}
		else
			isGrounded = false;
	}

	for(int i = 0; i < coins.size(); i++)
	{
		if(coins[i].CanPickUp(collider))
		{
			coins[i].PickUp(&score);
			break;
		}
	}

	if(collisionCountX != 0)
	{
		offset.x /= collisionCountX;
	}
	if(collisionCountY != 0)
		offset.y /= collisionCountY;

	pos.x -= offset.x;
	pos.y -= offset.y;

	bool hitEnemy = false;
	for(int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->CanBeHit(groundCheck))
		{
			velocity = -velocityJumpForce;
			isGrounded = false;
			state = Jumping;
			hitEnemy = true;
			enemies[i]->OnDeath();
			break;
		}
	}
	
	if(hasImmunity)
	{
		if(t > immunityCooldown)
		{
			hasImmunity = false;
			color = WHITE;
		}
		else
		{
			color = RED;
		}
		t += 0.166;
	}

	if(!hitEnemy)
	{
		if(!hasImmunity)
		{
			for(int i = 0; i < enemies.size(); i++)
			{
				if(enemies[i]->CanHit(collider))
				{
					health--;
					hasImmunity = true;
					t = 0;

					if(health <= 0)
					{
						health = 5;
						pos.x = spawnPoint.x;
						pos.y = spawnPoint.y;
					}

					break;
				}
			}
		}
	}

	if(state == Standing)
	{
		idleAnimation.x = pos.x;
		idleAnimation.y = pos.y;
		idleAnimation.DrawColored(color);	
	}
	else if(state == Walking)
	{
		walkAnimation.x = pos.x;
		walkAnimation.y = pos.y;
		walkAnimation.DrawColored(color);
	}
	else if(state == Jumping)
	{
		if(velocity < 0)
		{
			jumpingFrame.x = pos.x;
			jumpingFrame.y = pos.y;
			jumpingFrame.DrawColored(color);
		}
		else
		{
			fallingFrame.x = pos.x;
			fallingFrame.y = pos.y;
			fallingFrame.DrawColored(color);
		}
	}


	if(pos.y > 1000)
	{
		pos.x = spawnPoint.x;
		pos.y = spawnPoint.y;
		health = 5;
	}

	
}

void Player::UpdateScreenSpace()
{
	for(int o = 0; o < health; o++)
	{
		heart.x = o * 80 - 20;
		heart.DrawColored(color);
	}

	DrawText(TextFormat("Punkty: %i", score), 1000, 25, 40, WHITE); 	
}

