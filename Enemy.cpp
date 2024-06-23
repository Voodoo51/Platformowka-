#include "Enemy.h"
#include <iostream>

std::vector<Enemy*> enemies;

Enemy::Enemy(Vector2 startPos, Vector2 endPos, float speed, Animation * frames)
{
	this->startPos = startPos;
	this->endPos = endPos;
	this->speed = speed;
	this->frames = frames;

	collisionSizerX = 60;
	collisionSizerY = 40;

	hitBox.width = frames->GetFrameWidth(0) - collisionSizerX;
	hitBox.height = frames->GetFrameHeight(0) - collisionSizerY;

	killHitBox.width = hitBox.width - 40;
	killHitBox.height = 40;

	hitBox.x = startPos.x;
	hitBox.y = startPos.y;

	killHitBox.x = startPos.x;
	killHitBox.y = startPos.y;

	distance = endPos.x - startPos.x;

	currentPos = startPos;

	frames->flipped = true;

	t = 0;
	dir = 1;

	dead = false;
	velocity = 20;
	velocityDrop = 1;
	timeToDie = 15;

	enemies.push_back(this);
}

void Enemy::Update()
{
	if(dead)
	{
		if(t > timeToDie)
		{
			Die();
		}
		else
		{
			currentPos.x += 4;
			currentPos.y -= velocity;

			velocity -= velocityDrop;

			frames->x = currentPos.x;
			frames->y = currentPos.y;

			t += 0.1666;
		}

		return;
	}

	if(dir == 1)
	{
		currentPos.x = lerp(startPos.x, endPos.x, t);	
		currentPos.y = lerp(startPos.y, endPos.y, t);	
	}
	else
	{	
		currentPos.x = lerp(endPos.x, startPos.x, t);	
		currentPos.y = lerp(endPos.y, startPos.y, t);	
	}
	
	frames->x = currentPos.x;
	frames->y = currentPos.y;

	hitBox.x = currentPos.x + collisionSizerX/2;
	hitBox.y = currentPos.y + collisionSizerY/2;

	killHitBox.x = currentPos.x + 20 + collisionSizerX/2;
	killHitBox.y = currentPos.y - 5 + collisionSizerY/2;

	if(t >= 1)
	{
		frames->flipped = !frames->flipped;
		dir = dir == 1 ? -1 : 1;
		distanceTraveled = 0;
	}
	
	distanceTraveled += speed;

	t = distanceTraveled/distance;
}

bool Enemy::CanBeHit(Collision collider)
{
	return killHitBox.IntersectsWith(collider);
}

bool Enemy::CanHit(Collision collider)
{
	return hitBox.IntersectsWith(collider);
}

void Enemy::OnDeath()
{
	t = 0;
	dead = true;
	int indexToRemove = 0;
	for(int i = 0; i < enemies.size(); i++)
	{
		if(this == enemies[i])
		{
			indexToRemove = i;
			break;
		}
	}

	enemies.erase(enemies.begin() + indexToRemove);

}

void Enemy::Die()
{
	DeAttachAnimation(frames);

	DeleteLogic();

}
