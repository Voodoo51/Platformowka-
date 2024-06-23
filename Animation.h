#pragma once
#include "raylib.h"
#include "Renderer.h"
#include <stdarg.h>

#define MAX_FRAMES 10

enum AnimationMode
{
	Default,
	Repeating
};

enum DrawMode
{
	AutoDraw,
	CustomDraw
};

class Animation
{
public:
	Animation(){};
	Animation(DrawMode drawMode, AnimationMode mode, float x, float y, bool screenSpace, float timeBetween, int count...);
	int GetFrameWidth(int index);
	int GetFrameHeight(int index);
	void Draw();
	void DrawColored(Color color);
	float x;
	float y;
	bool flipped = false;
	bool screenSpace;
private:
  	float timeBetween;
	float t;
	int count;
	int currentFrame;
	int dir;
	Texture2D textures[MAX_FRAMES];
	AnimationMode mode;
};

