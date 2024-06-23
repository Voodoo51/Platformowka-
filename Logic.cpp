#include "Logic.h"
#include "iostream"

std::vector<Logic*> logics;

Logic::Logic()
{
	logics.push_back(this);
}

void Logic::DeleteLogic()
{
	int index = 0;
	for(int i = 0; i < logics.size(); i++)
	{
		if(this == logics[i])
		{
			//delete logics[i];
			index = i;
			logics.erase(logics.begin() + i);
		}
	}

	DeleteLogicCallback(index);
}

void Update()
{
	for(int i = 0; i < logics.size(); i++)
	{
		logics[i]->Update();
	}
}

void UpdateScreenSpace()
{
	for(int i = 0; i < logics.size(); i++)
	{
		logics[i]->UpdateScreenSpace();
	}
}

void DeleteLogicCallback(int index)
{
	for(int i = index; i < logics.size(); i++)
	{
		logics[i]->index--;
	}
}

