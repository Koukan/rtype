#include <iostream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "Input.hpp"
#include "Monster.hpp"
#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"

GSInGame::GSInGame() : GameState("Game"), _idPlayer(0), _scores(4, 0)
{
  //CommandDispatcher::get().registerHandler(*this);
	
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
}

void		GSInGame::onEnd()
{}

bool		GSInGame::handleCommand(Command const &command)
{
  static Method const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"life", &GSInGame::life},
<<<<<<< HEAD:client/GSInGame.cpp
	{"score", &GSInGame::score},
	{"spawn", &GSInGame::spawn}
=======
	{"spawn", &GSInGame::spawn},
	{"move", &GSInGame::move}
>>>>>>> ac6236ff8d88533ae198a7c92d5c0890b9590b32:client/GSInGame.cpp
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
	this->moveObject(event, 0, 0, -1, 0);
}

void		GSInGame::inputDown(InputCommand const &event)
{
	this->moveObject(event, 0, 0, 1, 0);
}

void		GSInGame::inputLeft(InputCommand const &event)
{
	this->moveObject(event, 0, 0, -1, 0);
}

void		GSInGame::inputRight(InputCommand const &event)
{
	this->moveObject(event, 0, 0, 1, 0);
}

void		GSInGame::moveObject(InputCommand const &event, int16_t x, int16_t y, int16_t vx, int16_t vy)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));

	if (obj)
	{
		GameCommand *cmd = new GameCommand("Move");
		cmd->x = static_cast<int16_t>(obj->getX() + x);
		cmd->y = static_cast<int16_t>(obj->getY() + y);
		cmd->vx = static_cast<int16_t>(obj->getVx() + vx);
		cmd->vy = static_cast<int16_t>(obj->getVy() + vy);
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::spawn(GameCommand const &event)
{
	HitBox *hitbox = new RectHitBox(event.x, event.y, 2, 2);
	Monster *monster1 = new Monster(this->getSprite("monster"), *hitbox, event.vx, event.vy);
	this->addGameObject(static_cast<GameObject *>(monster1), "monsterGroup");
}

void		GSInGame::destroy(GameCommand const &event)
{
	delete (this->getGameObject(event.idObject));
}

void		GSInGame::life(GameCommand const &event)
{
	//actions
}

void		GSInGame::score(GameCommand const &event)
{
	if (event.idObject < 4)
	{
		_scores[event.idObject] = event.score;
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
