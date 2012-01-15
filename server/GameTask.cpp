#include "GameTask.hpp"
#include "Server.hpp"

GameTask::GameTask(Game &game, double elapsedTime)
	: _game(game), _elapsedTime(elapsedTime)
{
}

GameTask::~GameTask()
{
}

void		GameTask::operator()()
{
	GameManager::gamesMap const &map = Server::get().getGameList();

	for (GameManager::gamesMap::const_iterator it = map.begin(); it !=map.end(); it++)
	{
		if (&_game == it->second)
			_game.updateGameState(this->_elapsedTime);
	}
}
