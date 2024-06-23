#pragma once
#include "Logic.h"
#include "raylib.h"
#include "Block.h"
#include "iostream"
#include <fstream>
#include "Collision.h"

struct BlockPlaced 
{
	int spriteIndex;
	int collisionIndex; 
	MapTexture mapTexture;
};

class LevelEditor : public Logic
{
	public:
		LevelEditor(const char * mapPath, Camera2D* camera, float speed);
		void Update();
		void UpdateScreenSpace();
		void LoadMap();
		void SaveBlock(float x, float y, int mapTexture);
		void SaveMap();
		Vector2 pos;
		
	private:
		Camera2D* camera;
		float speed;

		int currentIndex = 0;
		std::vector<Texture2D> textures;
		std::vector<BlockPlaced> blocksPlaced;
		const char * mapPath;
		int snapSize = 128;

		float t = 0;
};

void LoadMap(const char* mapPath);

