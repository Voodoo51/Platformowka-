#include "Sprite.h"

Sprite::Sprite(float x, float y, bool screenSpace, MapTexture mapTexture)
{
	this->x = x;
	this->y = y;
	LoadTextureByName(this->texture, mapTexture);

	if (screenSpace)	
	{
		screenSpaceSprites.push_back(this);	
	}
	else
	{
		worldSpaceSprites.push_back(this);
	}
}

Sprite::Sprite(float x, float y, bool screenSpace, const char* path)
{
	this->x = x;
	this->y = y;
	this->texture = LoadTexture(path);

	if (screenSpace)	
	{
		screenSpaceSprites.push_back(this);	
	}
	else
	{
		worldSpaceSprites.push_back(this);
	}

}

Sprite::Sprite(float x, float y, const char* path)
{
	this->x = x;
	this->y = y;
	this->texture = LoadTexture(path);
}


void Sprite::Draw()
{
	if(flipped)
	{
		DrawTextureRec(texture, {0, 0, -((float)texture.width), (float)texture.height}, {x, y}, WHITE);
	}
	else
		DrawTexture(texture, x, y, WHITE);
}

void Sprite::DrawColored(Color color)
{
	if(flipped)
	{
		DrawTextureRec(texture, {0, 0, -((float)texture.width), (float)texture.height}, {x, y}, color);
	}
	else
		DrawTexture(texture, x, y, color);
}

void Sprite::DrawScaled(float scale)
{

	DrawTexturePro(texture, {0,0, (float)texture.width, (float)texture.height},
			{x, y, (float)texture.width * scale, (float)texture.height * scale},
			{((float)texture.width * scale)/2, ((float)texture.height * scale)/2}, 0, WHITE);

}
