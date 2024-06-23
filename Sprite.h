#pragma once
#include "raylib.h"
#include "TextureUtils.h"
#include "Renderer.h"

class Sprite 
{
public:
	Sprite(){};
	Sprite(float x, float y, bool screenSpace, MapTexture mapTexture);
	Sprite(float x, float y, bool screenSpace, const char* path);
	Sprite(float x, float y, const char* path);
	void Draw();
	void DrawColored(Color color);
	void DrawScaled(float scale);
	Texture2D texture;
	float x;
	float y;
	bool flipped = false;
};
