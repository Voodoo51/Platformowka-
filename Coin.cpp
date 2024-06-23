#include "Coin.h"

std::vector<Coin> coins;

Coin::Coin(Animation* animation, int value)
{
	this->animation = animation;
	this->value = value;
	
	index = coins.size();

}

bool Coin::CanPickUp(Collision collider)
{
	collision.x = animation->x;
	collision.y = animation->y;

	collision.width = animation->GetFrameWidth(0);
	collision.height = animation->GetFrameHeight(0);
	
	return collision.IntersectsWith(collider);
}

void Coin::PickUp(int* score)
{
	*score += value;

	DeAttachAnimation(animation);

	coins.erase(coins.begin() + index);

	for(int i = 0; i < coins.size(); i++)
	{
		if(coins[i].index >= index)
		{
			coins[i].index--;
		}
	}
}

void AddCoin(Animation* animation, int value)
{
	coins.push_back(Coin(animation, value));
}
