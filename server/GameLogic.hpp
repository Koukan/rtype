#pragma once

#include <list>
#include "GameState.hpp"
#include "Ship.hpp" 

class Game;

class GameLogic : public GameState
{
  public:
    GameLogic(Game &game);
    virtual ~GameLogic();
	virtual void		update(double elapsedTime);
	virtual bool		handleCommand(Command const &command);
	Game				&getGame() const;
	void				startGame();

  private:
	Game				&_game;
	std::list<Ship>		_ships;
};
