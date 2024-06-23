#include "TextureUtils.h"

void LoadTextureByName(Texture2D& texture, MapTexture mapTexture)
{ 
	switch(mapTexture)
	{
		case blok1:
			texture = LoadTexture("Textures//blok1.png");
		break;
		case blok2:
			texture = LoadTexture("Textures//blok2.png");
		break;
	
	}
}

