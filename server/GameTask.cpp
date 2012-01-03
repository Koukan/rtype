#include "GameTask.hpp"

GameTask::GameTask(Game &game, double elapsedTime)
	: _game(game), _elapsedTime(elapsedTime)
{
}

GameTask::~GameTask()
{
}

void		GameTask::operator()()
{
	_game.updateGameState(this->_elapsedTime);
}
