#include <iostream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "Input.hpp"
#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"

GSInGame::GSInGame() : GameState("Game")
{
  CommandDispatcher::get().registerHandler(*this);
}

GSInGame::~GSInGame()
{}

void		GSInGame::onStart()
{
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputUp, static_cast<int>(Keyboard::Up));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputDown, static_cast<int>(Keyboard::Down));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputLeft, static_cast<int>(Keyboard::Left));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputRight, static_cast<int>(Keyboard::Right));
}

void		GSInGame::update(double elapsedTime)
{}

void		GSInGame::onEnd()
{}

bool		GSInGame::handleCommand(Command &command)
{
  static Method const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"down", &GSInGame::inputMove},
	{"left", &GSInGame::inputMove},
	{"life", &GSInGame::life},
	{"move", &GSInGame::move},
	{"retrieve", &GSInGame::retrieve},
	{"right", &GSInGame::inputMove},
	{"score", &GSInGame::score},
	{"spawn", &GSInGame::spawn},
	{"up", &GSInGame::inputMove}
  };

  for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); i++)
	{
		if (command.name == methods[i].name)
		{
			(this->*methods[i].method)(static_cast<GameCommand const &>(command));
			return true;
		}
	}
  return (false);
}

void		GSInGame::inputUp(InputCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));
	GameCommand cmd("up");

	if (obj)
	{
		cmd.x = static_cast<int16_t>(obj->getX());
		cmd.y = static_cast<int16_t>(obj->getY());
		cmd.vx = static_cast<int16_t>(obj->getVx());
		cmd.vy = static_cast<int16_t>(obj->getVy() - 1);
	}
	this->pushCommand(cmd);
}

void		GSInGame::inputDown(InputCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));
	GameCommand cmd("down");

	if (obj)
	{
		cmd.x = static_cast<int16_t>(obj->getX());
		cmd.y = static_cast<int16_t>(obj->getY());
		cmd.vx = static_cast<int16_t>(obj->getVx());
		cmd.vy = static_cast<int16_t>(obj->getVy() + 1);
	}
	this->pushCommand(cmd);
}

void		GSInGame::inputLeft(InputCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));
	GameCommand cmd("left");

	if (obj)
	{
		cmd.x = static_cast<int16_t>(obj->getX());
		cmd.y = static_cast<int16_t>(obj->getY());
		cmd.vx = static_cast<int16_t>(obj->getVx() - 1);
		cmd.vy = static_cast<int16_t>(obj->getVy());
	}
	this->pushCommand(cmd);
}

void		GSInGame::inputRight(InputCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));
	GameCommand cmd("right");

	if (obj)
	{
		cmd.x = static_cast<int16_t>(obj->getX());
		cmd.y = static_cast<int16_t>(obj->getY());
		cmd.vx = static_cast<int16_t>(obj->getVx() + 1);
		cmd.vy = static_cast<int16_t>(obj->getVy());
	}
	this->pushCommand(cmd);
}

void		GSInGame::inputMove(GameCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(event.idObject));

	if (obj)
		this->updatePositions(event, *obj);
	this->pushCommand(event);
}

void		GSInGame::spawn(GameCommand const &event)
{
	HitBox *tmp = new RectHitBox(event.x, event.y, 2, 2); //tmp

	//GameObject *obj = new PhysicObject(*tmp, event.vx, event.vy);


}

void		GSInGame::destroy(GameCommand const &event)
{
	delete (this->getGameObject(event.idObject));
}

void		GSInGame::score(GameCommand const &event)
{

}

void		GSInGame::life(GameCommand const &event)
{
}

void		GSInGame::retrieve(GameCommand const &event)
{

}

void		GSInGame::move(GameCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(event.idObject));

	if (obj)
		this->updatePositions(event, *obj);
}

void		GSInGame::updatePositions(GameCommand const &event, PhysicObject &obj) const
{
	obj.setX(event.x);
	obj.setY(event.y);
	obj.setVx(event.vx);
	obj.setVy(event.vy);
}
