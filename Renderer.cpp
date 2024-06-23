#include "Renderer.h"
#include <iostream>

std::vector<Sprite*> worldSpaceSprites;
std::vector<Sprite*> screenSpaceSprites;
std::vector<Animation*> worldSpaceAnimations;
std::vector<Animation*> screenSpaceAnimations;


void DrawWorldSpace()
{
	for (int i = 0; i < worldSpaceSprites.size(); i++)
	{
		worldSpaceSprites[i]->Draw();
	}
	for(int i = 0; i < worldSpaceAnimations.size(); i++)
	{
		worldSpaceAnimations[i]->Draw();
	}
}

void DrawScreenSpace()
{
	for (int i = 0; i < screenSpaceSprites.size(); i++)
	{
		screenSpaceSprites[i]->Draw();
	}
	for(int i = 0; i < screenSpaceAnimations.size(); i++)
	{
		screenSpaceAnimations[i]->Draw();
	}
}

void AttachSprite(Sprite* sprite, bool screenSpace)
{
	if(screenSpace)
	{
		screenSpaceSprites.push_back(sprite);
	}
	else
	{
		worldSpaceSprites.push_back(sprite);
	}
}

void DeAttachAnimation(Animation* animation)
{
	int indexToRemove = 0;
	if(animation->screenSpace)
	{
		for(int i = 0; i < screenSpaceAnimations.size(); i++)
		{
			if(screenSpaceAnimations[i] == animation)
			{
				indexToRemove = i;
				break;
			}
		}
		
		screenSpaceAnimations.erase(screenSpaceAnimations.begin() + indexToRemove);
	}
	else
	{
		for(int i = 0; i < worldSpaceAnimations.size(); i++)
		{
			if(worldSpaceAnimations[i] == animation)
			{
				indexToRemove = i;
				break;
			}
		}

		worldSpaceAnimations.erase(worldSpaceAnimations.begin() + indexToRemove);
	}
}
