#include <iostream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "Input.hpp"
#include "Monster.hpp"
#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"

GSInGame::GSInGame() : GameState("Game"), _idPlayer(0), _lastIdPacket(0)
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
{
	std::cout << "lol" << std::endl;
}

void		GSInGame::onEnd()
{}

bool		GSInGame::handleCommand(Command const &command)
{
  static Method const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"life", &GSInGame::life},
	{"spawn", &GSInGame::spawn},
  };

  for (size_t i = 0;
		 i < sizeof(methods) / sizeof(*methods); ++i)
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
	std::cout << "up" << std::endl;
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));
	
	if (obj)
	{
		GameCommand *cmd = new GameCommand("up");

		cmd->x = static_cast<int16_t>(obj->getX());
		cmd->y = static_cast<int16_t>(obj->getY());
		cmd->vx = static_cast<int16_t>(obj->getVx());
		cmd->vy = static_cast<int16_t>(obj->getVy() - 1);
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::inputDown(InputCommand const &event)
{
	std::cout << "down" << std::endl;
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));

	if (obj)
	{
		GameCommand *cmd = new GameCommand("down");

		cmd->x = static_cast<int16_t>(obj->getX());
		cmd->y = static_cast<int16_t>(obj->getY());
		cmd->vx = static_cast<int16_t>(obj->getVx());
		cmd->vy = static_cast<int16_t>(obj->getVy() + 1);
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::inputLeft(InputCommand const &event)
{
	std::cout << "left" << std::endl;
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));

	if (obj)
	{
		GameCommand *cmd = new GameCommand("left");

		cmd->x = static_cast<int16_t>(obj->getX());
		cmd->y = static_cast<int16_t>(obj->getY());
		cmd->vx = static_cast<int16_t>(obj->getVx() - 1);
		cmd->vy = static_cast<int16_t>(obj->getVy());
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::inputRight(InputCommand const &event)
{
	std::cout << "right" << std::endl;
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));

	if (obj)
	{
		GameCommand *cmd = new GameCommand("right");

		cmd->x = static_cast<int16_t>(obj->getX());
		cmd->y = static_cast<int16_t>(obj->getY());
		cmd->vx = static_cast<int16_t>(obj->getVx() + 1);
		cmd->vy = static_cast<int16_t>(obj->getVy());
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::spawn(GameCommand const &event)
{
	if (event.idObject - 1 > _lastIdPacket)
		this->retrieve(event.idObject - 1);
	else
		_lastIdPacket = event.idObject;

	HitBox *hitbox = new RectHitBox(event.x, event.y, 2, 2);
	Monster *monster1 = new Monster(this->getSprite("monster"), *hitbox, event.vx, event.vy);
	this->addGameObject(static_cast<GameObject *>(monster1), "monsterGroup");
}

void		GSInGame::destroy(GameCommand const &event)
{
	if (event.idObject - 1 > _lastIdPacket)
		this->retrieve(event.idObject - 1);
	else
		_lastIdPacket = event.idObject;
	delete (this->getGameObject(event.idObject));
}

void		GSInGame::life(GameCommand const &event)
{
	if (event.idObject - 1 > _lastIdPacket)
		this->retrieve(event.idObject - 1);
	else
		_lastIdPacket = event.idObject;
	//actions
}

void		GSInGame::score(GameCommand const &event)
{

}

void		GSInGame::retrieve(uint32_t idPacket)
{
	for (uint32_t id = _lastIdPacket; id <= idPacket; ++id)
	{
		GameCommand *cmd = new GameCommand("retrieve");
		cmd->idObject = id;
		CommandDispatcher::get().pushCommand(*cmd);
	}
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
