#pragma once
#include <vector>

class Logic
{
	public:
		Logic();
		void DeleteLogic();
		virtual void Update() {};
		virtual void UpdateScreenSpace() {};
		int index;

};

extern std::vector<Logic*> logics;
void Update();
void UpdateScreenSpace();
void DeleteLogicCallback(int index);

