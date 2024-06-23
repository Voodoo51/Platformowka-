#pragma once
#include "Collision.h"
#include "Animation.h"
#include "Renderer.h"
#include "Player.h"
#include "raylib.h"
#include <vector>

class Coin;

extern std::vector<Coin> coins;

class Coin
{
	public:
		Coin(Animation* animation, int value);
		bool CanPickUp(Collision collider);
		void PickUp(int* score);
	private:
		Animation* animation;
		Collision collision;
		int value;
		int index;
};

void AddCoin(Animation* animation, int value);

