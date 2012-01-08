#include <math.h>
#include "BCommand.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "ServerResourceManager.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

inline static double dtor(double x) { return x * M_PI / 180; }
inline static double rtod(double x) { return x * 180 / M_PI; }

BCommand::BCommand(std::string const &parser, GameState &gstate,
		double x, double y, double direction, double speed)
	: BulletCommand(parser, gstate, x, y, direction, speed)
{
}

BCommand::BCommand(BulletMLParser *parser, GameState &gstate,
		double x, double y, double direction, double speed)
	: BulletCommand(parser, gstate, x, y, direction, speed)
{
}

BCommand::BCommand(BulletMLState *state, GameState &gstate,
		double x, double y, double direction, double speed)
	: BulletCommand(state, gstate, x, y, direction, speed)
{
}

BCommand::~BCommand()
{
}

void	BCommand::createSimpleBullet(double direction, double speed)
{
	Bullet	*bullet = new Bullet(_state, this->_simpleSprite,
							_x, _y, dtor(direction), speed);

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

void	BCommand::createBullet(BulletMLState *state,
				double direction, double speed)
{
	BCommand	*bullet = new BCommand(state, this->_state,
					this->_x, this->_y, dtor(direction), speed);

	this->_state.addGameObject(bullet, state->getGroup());
	delete state;
	GameCommand		*cmd = new GameCommand("Spawn");
	cmd->idObject = bullet->getId();
	cmd->idResource = ServerResourceManager::get().
			getId(state->getSprite());
	cmd->x = this->_x;
	cmd->y = this->_y;
	cmd->vx = this->_vx;
	cmd->vy = this->_vy;
	cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
	CommandDispatcher::get().pushCommand(*cmd);
}

void	BCommand::move(double time)
{
	
	this->_turn += time * 50;
	this->run();
	if (!this->_end)
	{
		this->PhysicObject::move(time);
		GameCommand	*cmd = new GameCommand("Move");
		cmd->idObject = this->_id;
		cmd->x = this->_x;
		cmd->y = this->_y;
		cmd->vx = this->_vx;
		cmd->vy = this->_vy;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		CommandDispatcher::get().pushCommand(*cmd);
	}
	else
	{
		GameCommand	*cmd = new GameCommand("Destroy");
		cmd->idObject = this->_id;
		cmd->game = &static_cast<GameLogic&>(this->_state).getGame();
		CommandDispatcher::get().pushCommand(*cmd);
	}
}
