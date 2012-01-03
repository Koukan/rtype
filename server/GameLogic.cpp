#include <iostream>
#include "GameLogic.hpp"

GameLogic::GameLogic() : GameState("GameLogic")
{
}

GameLogic::~GameLogic()
{
}

void		GameLogic::update(double)
{
	std::cout << "ca marche" << std::endl;
}
