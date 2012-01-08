#include <iostream>
#include "Game.hpp"
#include "GameLogic.hpp"

GameLogic::GameLogic(Game &game)
	: GameState("GameLogic"), _game(game)
{
}

GameLogic::~GameLogic()
{
}

void		GameLogic::update(double)
{
}

bool		GameLogic::handleCommand(Command &command)
{
	return true;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}
