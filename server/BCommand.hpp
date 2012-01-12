#pragma once

#include "BulletCommand.hpp"

class BCommand : BulletCommand
{
  public:
    BCommand(std::string const &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BCommand(BulletMLParser &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BCommand(BulletMLState &state, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0);
    BCommand(BulletMLState &state, GameState &gstate, HitBox &box,
		  double vx = 0, double vy = 0);
    virtual ~BCommand();

	virtual void	createSimpleBullet(double direction, double speed);
	virtual void	createBullet(BulletMLState *state, double direction,
								 double speed);
	virtual void	move(double time);
};
