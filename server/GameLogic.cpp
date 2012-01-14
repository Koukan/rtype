#include <iostream>
#include "Game.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "CircleHitBox.hpp"
#include "CommandDispatcher.hpp"

GameLogic::GameLogic(Game &game)
	: GameState("GameLogic"), _game(game)
{
}

GameLogic::~GameLogic()
{
}

void		GameLogic::update(double elapseTime)
{
	this->handle(elapseTime);
}

bool		GameLogic::handleCommand(Command const &command)
{
	GameCommand	const &gc = static_cast<GameCommand const &>(command);
	if (gc.name == "move")
	{
		Ship	*ship = gc.player->getShip();
		ship->setX(gc.x);
		ship->setY(gc.y);
		ship->setVx(gc.vx);
		ship->setVy(gc.vy);
		GameCommand *answer = new GameCommand("Move");
		answer->idObject = gc.player->getShip()->getId();
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->player = gc.player;
		CommandDispatcher::get().pushCommand(*answer);
		return true;
	}
	else if (gc.name == "spawn")
	{
		std::cout << "spawn plop" << std::endl;
		CircleHitBox	*hitbox = new CircleHitBox(gc.x, gc.y, 5);
		Bullet			*bullet = new Bullet(*hitbox, gc.vx, gc.vy);
		bullet->setId(gc.idObject);
		this->addGameObject(bullet, "playerfires", 9);
		GameCommand *answer = new GameCommand("Spawn");
		answer->idResource = gc.idResource;
		answer->idObject = gc.idObject;
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->player = gc.player;
		CommandDispatcher::get().pushCommand(*answer);
		return true;
	}
	return false;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}

void		GameLogic::startGame()
{
	double	y = 0;
	double	step = 720 / this->_game._list.size();

	for (std::list<Player*>::iterator it = this->_game._list.begin(); it != this->_game._list.end(); ++it)
	{
		Ship *tmp = new Ship(10, y, *it);
	    (*it)->setShip(tmp);
		this->addGameObject(tmp, "players", 10);
		GameCommand	*cmd = new GameCommand("Spawn");
		cmd->idResource = (*it)->getId();
		cmd->idObject = tmp->getId();
		cmd->x = tmp->getX();
		cmd->y = tmp->getY();
		cmd->vx = tmp->getVx();
		cmd->vy = tmp->getVy();
		cmd->game = &_game;
		std::cout << "Id " << (*it)->getId() << " Id Object " << cmd->idObject << std::endl;
		CommandDispatcher::get().pushCommand(*cmd);
		y += step;
	}
}
