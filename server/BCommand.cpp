#include <math.h>
#include "BCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ServerResourceManager.hpp"
#include "CircleHitBox.hpp"
#include "RectHitBox.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BCommand::BCommand(std::string const &parser, GameState &gstate,
		  double x, double y, double vx, double vy)
	: BulletCommand(parser, gstate, x, y, vx, vy), _elapsedTime(0)
{
}

BCommand::BCommand(BulletMLParser &parser, GameState &gstate,
		  double x, double y, double vx, double vy)
	: BulletCommand(parser, gstate, x, y, vx, vy), _elapsedTime(0)
{
}

BCommand::BCommand(BulletMLState &state, GameState &gstate,
		  double x, double y, double vx, double vy)
	: BulletCommand(state, gstate, x, y, vx, vy), _elapsedTime(0)
{
}

BCommand::BCommand(BulletMLState &state, GameState &gstate, HitBox &box,
		  double vx, double vy)
	: BulletCommand(state, gstate, box, vx, vy), _elapsedTime(0)
{
}

BCommand::~BCommand()
{
}

void	BCommand::createSimpleBullet(double direction, double speed)
{
	Bullet		*bullet = 0;
	HitBox		*box = 0;
	double		vx, vy;
	double		dir = dtor(direction);

	if (_shape == BulletCommand::Circle)
		box = new CircleHitBox(_x, _y,
			static_cast<double>(_width));
	else if (_shape == BulletCommand::Rectangle)
		box = new RectHitBox(_x, _y,
			static_cast<double>(_width),
			static_cast<double>(_height));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	if (box)
	{
		bullet = new Bullet(*box, vx, vy);
		this->_state.addGameObject(bullet, this->_simpleGroup);
		GameCommand		*cmd = new GameCommand("Spawn");
		cmd->idObject = bullet->getId();
		cmd->idResource = ServerResourceManager::get().getId(this->_simpleSprite);
		cmd->x = this->_x;
		cmd->y = this->_y;
		cmd->vx = this->_vx;
		cmd->vy = this->_vy;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		CommandDispatcher::get().pushCommand(*cmd);
	}
}

void	BCommand::createBullet(BulletMLState *state,
				double direction, double speed)
{
	BCommand	*bullet = 0;
	HitBox		*box = 0;
	double		vx, vy;
	double		dir = dtor(direction);

	if (state->getShape() == "circle")
		box = new CircleHitBox(_x, _y,
			static_cast<double>(state->getRadius()));
	else if (state->getShape() == "rectangle")
		box = new RectHitBox(_x, _y,
			static_cast<double>(state->getWidth()),
			static_cast<double>(state->getHeight()));
	vx = speed * cos(dir);
	vy = speed * sin(dir);
	state->setSprite("");
	if (box)
	{
		bullet = new BCommand(*state, _state, *box, vx, vy);
		this->_state.addGameObject(bullet, state->getGroup());
	}
	else
	{
		bullet = new BCommand(*state, _state, _x, _y, vx, vy);
		this->_state.addGameObject(bullet, state->getGroup());
	}
	delete state;
	if (bullet)
	{
		GameCommand		*cmd = new GameCommand("Spawn");
		cmd->idObject = bullet->getId();
		cmd->idResource = ServerResourceManager::get().getId(state->getSprite());
		cmd->x = this->_x;
		cmd->y = this->_y;
		cmd->vx = this->_vx;
		cmd->vy = this->_vy;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		CommandDispatcher::get().pushCommand(*cmd);
	}
}

void	BCommand::move(double time)
{
	this->_turn += time * 50;
	this->_elapsedTime += time;
	this->run();
	if (!this->_end)
	{
		this->PhysicObject::move(time);
		if (this->_elapsedTime > 500)
		{
			this->_elapsedTime -= 500;
			GameCommand	*cmd = new GameCommand("Move");
			cmd->idObject = this->_id;
			cmd->x = this->_x;
			cmd->y = this->_y;
			cmd->vx = this->_vx;
			cmd->vy = this->_vy;
			cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
			CommandDispatcher::get().pushCommand(*cmd);
		}
	}
	else
	{
		GameCommand	*cmd = new GameCommand("Destroy");
		cmd->idObject = this->_id;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		CommandDispatcher::get().pushCommand(*cmd);
		this->erase();
	}
}
