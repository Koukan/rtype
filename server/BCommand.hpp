#pragma once

#include "BulletCommand.hpp"

class BCommand : BulletCommand
{
  public:
    BCommand(std::string const &parser, GameState &gstate, double x = 0,
			 double y = 0, double direction = 0, double speed = 0);
	BCommand(BulletMLParser *parser, GameState &gstate, double x = 0,
			 double y = 0, double direction = 0, double speed = 0);
	BCommand(BulletMLState *state, GameState &gstate, double x = 0,
			 double y = 0, double direction = 0, double speed = 0);
	BCommand();
    virtual ~BCommand();

	virtual void	createSimpleBullet(double direction, double speed);
	virtual void	createBullet(BulletMLState *state, double direction,
								 double speed);
	virtual void	move(double time);
};
