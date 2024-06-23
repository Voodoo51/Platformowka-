#pragma once
#include "Sprite.h"
#include "Collision.h"

class Block
{
	public:
		Block(float x, float y, MapTexture mapTexture);
		void Remove();
		Sprite sprite;
		int spriteIndex;
		int collisionIndex;
};

void AddBlock(float x, float y, MapTexture mapTexture);
void RemoveBlock(int spriteIndex, int collisionIndex);

