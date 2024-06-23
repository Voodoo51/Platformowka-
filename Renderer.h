#pragma once
#include <vector>
#include "Sprite.h"
#include "Animation.h"

class Sprite;
class Animation;

extern std::vector<Sprite*> worldSpaceSprites;
extern std::vector<Sprite*> screenSpaceSprites;
extern std::vector<Animation*> worldSpaceAnimations;
extern std::vector<Animation*> screenSpaceAnimations;

void DrawWorldSpace();
void DrawScreenSpace();

void AttachSprite(Sprite* sprite, bool screenSpace);

void DeAttachAnimation(Animation* animation);
