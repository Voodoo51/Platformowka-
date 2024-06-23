#include "Block.h"


Block::Block(float x, float y, MapTexture mapTexture)
{
	sprite.x = x;
	sprite.y = y;

	LoadTextureByName(sprite.texture, mapTexture);

	spriteIndex = worldSpaceSprites.size();
	collisionIndex = colliders.size();

	AttachSprite(&sprite, false);
	AttachCollision(Collision(x, y, sprite.texture.width, sprite.texture.height, map));
}

void Block::Remove()
{
	worldSpaceSprites.erase(worldSpaceSprites.begin() + spriteIndex);
	colliders.erase(colliders.begin() + collisionIndex);
}

void AddBlock(float x, float y, MapTexture mapTexture)
{
	Sprite* sprite = new Sprite();
	sprite->x = x;
	sprite->y = y;
	LoadTextureByName(sprite->texture, mapTexture);

	AttachSprite(sprite, false);
	Collision(x, y, sprite->texture.width, sprite->texture.height, map);

}

void RemoveBlock(int spriteIndex, int collisionIndex)
{
	worldSpaceSprites.erase(worldSpaceSprites.begin() + spriteIndex);
	colliders.erase(colliders.begin() + collisionIndex);
}
