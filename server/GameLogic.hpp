#pragma once

#include "GameState.hpp"

class GameLogic : public GameState
{
  public:
    GameLogic();
    virtual ~GameLogic();
	virtual void		update(double elapsedTime);

  private:
};
