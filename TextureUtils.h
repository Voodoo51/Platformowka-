#pragma once
#include "raylib.h"

enum MapTexture
{
	blok1,
	blok2
};

void LoadTextureByName(Texture2D& texture, MapTexture mapTexture);

