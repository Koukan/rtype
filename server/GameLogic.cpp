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

bool		GameLogic::handleCommand(Command const &command)
{
	return false;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}

void		GameLogic::startGame()
{
	for (std::list<Player*>::iterator it = this->_game._list.begin(); it != this->_game._list.end(); ++it)
	{
		
	}
}
