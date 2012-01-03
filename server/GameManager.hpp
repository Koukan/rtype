#pragma once

#include "Game.hpp"

class GameManager
{
  public:
    GameManager();
    virtual ~GameManager();
	Game		*getGame(uint16_t id);
	Game		*createGame(uint8_t maxPlayers = 4);

  private:
	typedef	std::map<uint16_t, Game*>	gamesMap;

	uint16_t		_id;
	gamesMap		_games;
};
