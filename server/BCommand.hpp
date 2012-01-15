#pragma once

#include "BulletCommand.hpp"

class BCommand : public BulletCommand
{
  public:
    BCommand(std::string const &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life);
    BCommand(BulletMLParser &parser, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life);
    BCommand(BulletMLState &state, GameState &gstate,
		  double x = 0, double y = 0, double vx = 0, double vy = 0, int life);
    BCommand(BulletMLState &state, GameState &gstate, HitBox &box,
		  double vx = 0, double vy = 0, int life);
    virtual ~BCommand();

	virtual void	createSimpleBullet(double direction, double speed);
	virtual void	createBullet(BulletMLState *state, double direction,
								 double speed);
	virtual void	move(double time);

  private:
	double		_elapsedTime;
	uint32_t	_id;
	int			_life;
};
