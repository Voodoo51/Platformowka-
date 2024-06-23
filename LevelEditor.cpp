#include "LevelEditor.h"

LevelEditor::LevelEditor(const char * mapPath, Camera2D* camera, float speed)
{
	this->mapPath = mapPath;
	this->camera = camera;
	this->speed = speed;
	textures.push_back(LoadTexture("Textures//blok1.png"));
	textures.push_back(LoadTexture("Textures//blok2.png"));
}

void LevelEditor::LoadMap()
{
	FILE* f;
	if(fopen_s(&f, mapPath, "r") == 0)
	{
		std::ifstream line(mapPath);
		float x;
		float y;
		int mapTexture;
		while(line >> x >> y >> mapTexture)
		{
			AddBlock(x, y, (MapTexture)mapTexture);
			blocksPlaced.push_back({(int)(worldSpaceSprites.size() - 1), (int)(colliders.size() - 1), (MapTexture)mapTexture});
		}
	}
	else if(fopen_s(&f, mapPath, "a") == 0)
	{
		//Zrob plik
	}
	else
	{
		printf("Błąd wczytania pliku.");
		return;
	}
	fclose(f);
}

void LoadMap(const char* mapPath)
{
	FILE* f;
	if(fopen_s(&f, mapPath, "r") == 0)
	{
		std::ifstream line(mapPath);
		float x;
		float y;
		int mapTexture;
		while(line >> x >> y >> mapTexture)
		{
			AddBlock(x, y, (MapTexture)mapTexture);
		}
	}
	else if(fopen_s(&f, mapPath, "a") == 0)
	{
		//Zrob plik
	}
	else
	{
		printf("Błąd wczytania pliku.");
		return;
	}
	fclose(f);
}

void LevelEditor::SaveBlock(float x, float y, int mapTexture)
{
	FILE* f;
	if(fopen_s(&f, mapPath, "a") == 0)
	{
		fprintf_s(f, "%f %f %d \n ", x, y, mapTexture);
	}
	else
	{
		printf("Błąd zapisu pliku");
	}
	fclose(f);
}

void LevelEditor::SaveMap()
{
	FILE* f;
	if(fopen_s(&f, mapPath, "w") == 0)
	{
		for(int i = 0; i < blocksPlaced.size(); i++)
		{
			fprintf_s(f, "%f %f %d \n ", worldSpaceSprites[blocksPlaced[i].spriteIndex]->x, worldSpaceSprites[blocksPlaced[i].spriteIndex]->y, blocksPlaced[i].mapTexture);
		}
	}
	else
	{
		printf("Błąd zapisu pliku");
	}
	fclose(f);

}

void LevelEditor::Update()
{
	if(IsKeyDown(KEY_RIGHT)) pos.x += speed;
	else if(IsKeyDown(KEY_LEFT)) pos.x -= speed;
	if(IsKeyDown(KEY_UP)) pos.y -= speed;
	else if(IsKeyDown(KEY_DOWN)) pos.y += speed;

	int scrollDir = GetMouseWheelMove();

	if(scrollDir > 0 && currentIndex < textures.size()-1) currentIndex++;
	else if(scrollDir < 0 && currentIndex > 0) currentIndex--;

	Vector2 mousePos = GetMousePosition();

	mousePos = GetScreenToWorld2D(mousePos, *camera);
	
	Vector2 noSnapMousePos = mousePos;
	int offsetX = mousePos.x > 0 ? 0 : -snapSize;
	int offsetY = mousePos.y > 0 ? 0 : -snapSize;
	mousePos.x = ((int)mousePos.x + offsetX) / snapSize * snapSize;
	mousePos.y = ((int)mousePos.y + offsetY) / snapSize * snapSize;
	DrawTexture(textures[currentIndex], mousePos.x, mousePos.y, WHITE);

	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		bool canPlaceNew = true;
		for(int i = 0 ; i < blocksPlaced.size(); i++)
		{
			if(colliders[blocksPlaced[i].collisionIndex].IntersectsWith(noSnapMousePos))
			{
				canPlaceNew = false;
				break;
			}
		}

		if(canPlaceNew)
		{
			AddBlock(mousePos.x, mousePos.y, (MapTexture)currentIndex);
			blocksPlaced.push_back({(int)(worldSpaceSprites.size() - 1), (int)(colliders.size() - 1), (MapTexture)currentIndex});
			SaveMap();
		}

	}
	else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		for(int i = 0 ; i < blocksPlaced.size(); i++)
		{
			if(colliders[blocksPlaced[i].collisionIndex].IntersectsWith(noSnapMousePos))
			{
				int sIndex = blocksPlaced[i].spriteIndex;
				int cIndex = blocksPlaced[i].collisionIndex;

				RemoveBlock(blocksPlaced[i].spriteIndex, blocksPlaced[i].collisionIndex);
				blocksPlaced.erase(blocksPlaced.begin() + i);
				
				for(int i = 0; i < blocksPlaced.size(); i++)
				{
					if(blocksPlaced[i].spriteIndex > sIndex)
					{
						blocksPlaced[i].spriteIndex--;
					}
					if(blocksPlaced[i].collisionIndex > cIndex)
					{
						blocksPlaced[i].collisionIndex--;
					}
				}
				SaveMap();
				break;
			}
		}
	}

}

void LevelEditor::UpdateScreenSpace()
{
	DrawText("EDITOR ON", 10, 10, 30, WHITE);
	DrawText("Aktualna tekstura ", 10, 40, 25, WHITE);
	DrawTexture(textures[currentIndex], 10, 70, WHITE);
}










