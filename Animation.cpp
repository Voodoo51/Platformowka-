#include "Animation.h"

Animation::Animation(DrawMode drawMode, AnimationMode mode, float x, float y, bool screenSpace, float timeBetween, int count...)
{
	this->mode = mode;
	this->timeBetween = timeBetween;
	this->count = count;
	this->currentFrame = 0;
	this->t = 0;
	this->x = x;
	this->y = y;
	this->screenSpace = screenSpace;
	this->flipped = false;
	dir = 1;
	va_list args;
	va_start(args, count);
		
	for(int i = 0; i < count; i++)
	{
		textures[i] = LoadTexture(va_arg(args, char *));	
	}

	va_end(args);
	
	if(drawMode == AutoDraw)
	{
		if(screenSpace)
		{
			screenSpaceAnimations.push_back(this);
		}
		else
		{
			worldSpaceAnimations.push_back(this);
		}
	}

}

void Animation::Draw()
{
	if(mode == Default)
	{
		t+= 0.1;

		if(t >= timeBetween)
		{
			currentFrame++;
			t = 0;
		}

		if(currentFrame >= count)
			currentFrame = 0;

		if(!flipped)
			DrawTexture(textures[currentFrame], x, y, WHITE);	
		else
			DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, WHITE);
	}
	else if(mode == Repeating)
	{
		if(dir == 1)
		{
			t+= 0.1;

			if(t >= timeBetween)
			{
				currentFrame++;
				t = 0;
			}

			if(currentFrame >= count)
			{	
				dir = -1;
				currentFrame--;
				t += timeBetween;
			}
	
			if(!flipped)
				DrawTexture(textures[currentFrame], x, y, WHITE);	
	  		else
				DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, WHITE);
		}
		else if(dir == -1)
		{
			t+= 0.1;

			if(t >= timeBetween)
			{
				currentFrame--;
				t = 0;
			}

			if(currentFrame < 0)
			{	
				dir = 1;
				currentFrame++;
				t += timeBetween;
			}
	
				if(!flipped)
				DrawTexture(textures[currentFrame], x, y, WHITE);	
	  		else
				DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, WHITE);
		}

	}
}

void Animation::DrawColored(Color color)
{
	if(mode == Default)
	{
		t+= 0.1;

		if(t >= timeBetween)
		{
			currentFrame++;
			t = 0;
		}

		if(currentFrame >= count)
			currentFrame = 0;

		if(!flipped)
			DrawTexture(textures[currentFrame], x, y, color);	
		else
			DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, color);
	}
	else if(mode == Repeating)
	{
		if(dir == 1)
		{
			t+= 0.1;

			if(t >= timeBetween)
			{
				currentFrame++;
				t = 0;
			}

			if(currentFrame >= count)
			{	
				dir = -1;
				currentFrame--;
				t += timeBetween;
			}
	
			if(!flipped)
				DrawTexture(textures[currentFrame], x, y, color);	
	  		else
				DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, color);
		}
		else if(dir == -1)
		{
			t+= 0.1;

			if(t >= timeBetween)
			{
				currentFrame--;
				t = 0;
			}

			if(currentFrame < 0)
			{	
				dir = 1;
				currentFrame++;
				t += timeBetween;
			}
	
				if(!flipped)
				DrawTexture(textures[currentFrame], x, y, color);	
	  		else
				DrawTextureRec(textures[currentFrame], {0, 0, -((float)textures[currentFrame].width), (float)textures[currentFrame].height}, {x, y}, color);
		}

	}
}


int Animation::GetFrameWidth(int index)
{
	return textures[index].width;
}

int Animation::GetFrameHeight(int index)
{
	return textures[index].height;
}

