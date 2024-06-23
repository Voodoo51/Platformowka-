#include <iostream>
#include <raylib.h>
#include "Sprite.h"
#include "Renderer.h"
#include "Collision.h"
#include "Animation.h"
#include "Block.h"
#include "Player.h"
#include "LevelEditor.h"
#include "CameraFollow.h"
#include "Enemy.h"
#include <cmath>

#define EDITOR 0

const int WIDTH = 1280;
const int HEIGHT = 960;

float t = 0;
bool anyButton = false;

int main()
{
	InitWindow(WIDTH, HEIGHT, "Platformowka");
	Camera2D camera = { 0 };
	Vector2 target = { 0, 0};

	CameraFollow cameraFollow(&camera, Interpolate, 0.05);
	Sprite background(4600, -300, "Textures//tlo.png");
	SetTargetFPS(60);
	const char* mapPath = "map.txt";
	
	int titleX = -285;
	int titleY = -350;
	int titleYDest = -950;
	Sprite title(titleX, titleY, "Textures//tytul.png");	

	int startX = 256 + 128 - 10;
	int startY = -16 - 8;
	int offsetX = 128;
	int count = 4;
	for (int i = 0; i < count; i++)
	{
		AddCoin(new Animation(AutoDraw, Repeating, startX + offsetX * i, startY, false, 3, 3, "Textures//light_0.png", "Textures//light_1.png", "Textures//light_2.png"), 2);

	}

	startX = 6528 - 5;
	startY = -384 - 16;
	count = 3;
	for (int i = 0; i < count; i++)
	{
		AddCoin(new Animation(AutoDraw, Repeating, startX + offsetX * i, startY, false, 3, 3, "Textures//light_0.png", "Textures//light_1.png", "Textures//light_2.png"), 2);

	}

	AddCoin(new Animation(AutoDraw, Repeating, 4352 - 5, 384 - 16, false, 3, 3, "Textures//light_0.png", "Textures//light_1.png", "Textures//light_2.png"), 2);
	AddCoin(new Animation(AutoDraw, Repeating, 4608 - 5, 256 - 16, false, 3, 3, "Textures//light_0.png", "Textures//light_1.png", "Textures//light_2.png"), 2);

#ifndef EDITOR 	
    	LevelEditor levelEditor(mapPath, &camera, 10);
	levelEditor.LoadMap();
	Animation playerAnim(AutoDraw, Default, 55, 128 + 16 false, 0.5, 8,
			"Textures//Eyevelyn_walk_1.png",
			"Textures//Eyevelyn_walk_2.png",
			"Textures//Eyevelyn_walk_3.png",
			"Textures//Eyevelyn_walk_4.png",
			"Textures//Eyevelyn_walk_5.png",
			"Textures//Eyevelyn_walk_6.png",
			"Textures//Eyevelyn_walk_7.png",
			"Textures//Eyevelyn_walk_8.png");
	
#elif EDITOR == 1
	LevelEditor levelEditor(mapPath, &camera, 10);
	levelEditor.LoadMap();
	Animation playerAnim(AutoDraw, Default, 55, 128 + 16, false, 0.5, 8,
			"Textures//Eyevelyn_walk_1.png",
			"Textures//Eyevelyn_walk_2.png",
			"Textures//Eyevelyn_walk_3.png",
			"Textures//Eyevelyn_walk_4.png",
			"Textures//Eyevelyn_walk_5.png",
			"Textures//Eyevelyn_walk_6.png",
			"Textures//Eyevelyn_walk_7.png",
			"Textures//Eyevelyn_walk_8.png");
	
#else
	Player player(55, 128 + 16,5,
			Animation(CustomDraw, Default, 100, 200, false, 1, 9,
			"Textures//Eyevelyn_sassy_1.png",
			"Textures//Eyevelyn_sassy_2.png",
			"Textures//Eyevelyn_sassy_3.png",
			"Textures//Eyevelyn_sassy_wink_1.png",
			"Textures//Eyevelyn_sassy_wink_2.png",
			"Textures//Eyevelyn_stomp_1.png",
			"Textures//Eyevelyn_stomp_2.png",
			"Textures//Eyevelyn_wink_1.png",
			"Textures//Eyevelyn_wink_2.png"
			),
			Animation(CustomDraw, Default, 100, 200, false, 0.5, 8,
			"Textures//Eyevelyn_walk_1.png",
			"Textures//Eyevelyn_walk_2.png",
			"Textures//Eyevelyn_walk_3.png",
			"Textures//Eyevelyn_walk_4.png",
			"Textures//Eyevelyn_walk_5.png",
			"Textures//Eyevelyn_walk_6.png",
			"Textures//Eyevelyn_walk_7.png",
			"Textures//Eyevelyn_walk_8.png"
			),
			Sprite(100, 200, "Textures//Eyevelyn_falling.png"),
			Sprite(100, 200, "Textures//Eyevelyn_jump_2.png"),
			Sprite(100, -30, "Textures//heart.png")
			);
	LoadMap(mapPath);
#endif

	Enemy enemy({3456 - 30, 384-10}, {3712-30, 384 -10}, 4, new Animation(AutoDraw, Default, 100, 100, false, 0.25, 8 , "Textures//spyder_crawl_1.png", "Textures//spyder_crawl_2.png", "Textures//spyder_crawl_3.png", "Textures//spyder_crawl_4.png","Textures//spyder_crawl_5.png","Textures//spyder_crawl_6.png","Textures//spyder_crawl_7.png","Textures//spyder_crawl_8.png"));
	Enemy enemy2({4864 - 20, 128 - 10}, {4992 - 40, 128 - 10}, 4, new Animation(AutoDraw, Default, 100, 100, false, 0.25, 8 , "Textures//spyder_crawl_1.png", "Textures//spyder_crawl_2.png", "Textures//spyder_crawl_3.png", "Textures//spyder_crawl_4.png","Textures//spyder_crawl_5.png","Textures//spyder_crawl_6.png","Textures//spyder_crawl_7.png","Textures//spyder_crawl_8.png"));
	Enemy enemy3({6016-20, -712 - 66}, {6272-40, -712 - 66}, 4, new Animation(AutoDraw, Default, 100, 100, false, 0.25, 8, "Textures//spyder_crawl_1.png", "Textures//spyder_crawl_2.png", "Textures//spyder_crawl_3.png", "Textures//spyder_crawl_4.png", "Textures//spyder_crawl_5.png", "Textures//spyder_crawl_6.png", "Textures//spyder_crawl_7.png", "Textures//spyder_crawl_8.png"));


	Vector2 offset{0,0};
	offset.x = WIDTH / 2.0f;
	offset.y = HEIGHT / 2.0f;
	camera.target = target;
	camera.offset = offset;
	camera.rotation = 0.0f;
	camera.zoom = 0.75f;
	Vector2 displacement = {0,0};
	
	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		BeginMode2D(camera);
#ifndef EDITOR
		cameraFollow.Follow({levelEditor.pos.x, levelEditor.pos.y});
		for(int i = 0; i < colliders.size(); i++)
		{
			colliders[i].Visualize();
		}
#elif EDITOR == 1
		cameraFollow.Follow({levelEditor.pos.x, levelEditor.pos.y});
		for(int i = 0; i < colliders.size(); i++)
		{
			colliders[i].Visualize();
		}
#else
		cameraFollow.Follow({player.pos.x + 140 / 2, player.pos.y + 140 / 2});
#endif

		background.DrawScaled(2);
		//background.Draw();
		DrawWorldSpace();
		Update();
		EndMode2D();
		
		if (IsKeyDown(KEY_ESCAPE))
		{
			CloseWindow();
		}

		UpdateScreenSpace();
		DrawScreenSpace();
		if(t <= 1)
		{
			if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_SPACE))		
			{
				anyButton = true;
			}

			if(anyButton)
			{
				t += 0.02f;

				title.y = lerp(titleY, titleYDest, powf(t,2)/(powf(t,2) + (powf(1.1 - 1.1*t,2)))); 
			}

			title.Draw();
		}
		EndDrawing();
	}
}
