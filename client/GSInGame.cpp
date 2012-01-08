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
{

}

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
{

}

bool		GSInGame::handleCommand(Command &command)
{
  static Method const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"down", &GSInGame::moveDown},
	{"left", &GSInGame::moveLeft},
	{"life", &GSInGame::life},
    {"move", &GSInGame::move},
	{"retrieve", &GSInGame::retrieve},
	{"right", &GSInGame::moveRight},
	{"score", &GSInGame::score},
	{"spawn", &GSInGame::spawn},
	{"up", &GSInGame::moveUp}
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

}

void		GSInGame::inputDown(InputCommand const &event)
{
}

void		GSInGame::inputLeft(InputCommand const &event)
{
}

void		GSInGame::inputRight(InputCommand const &event)
{
}

void		GSInGame::moveUp(GameCommand const &event)
{
	std::cout << "Up is pressed !" << std::endl;
}

void		GSInGame::moveDown(GameCommand const &event)
{
	std::cout << "Down is pressed !" << std::endl;
}

void		GSInGame::moveLeft(GameCommand const &event)
{
	std::cout << "Left is pressed !" << std::endl;
}

void		GSInGame::moveRight(GameCommand const &event)
{
	std::cout << "Right is pressed !" << std::endl;
}

void		GSInGame::spawn(GameCommand const &event)
{
	HitBox *tmp = new RectHitBox(event.x, event.y, 2, 2); //tmp

	//GameObject *obj = new PhysicObject(*tmp, event.vx, event.vy);


}

void		GSInGame::destroy(GameCommand const &event)
{
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
	try
	{
		PhysicObject *obj = _gameObjects.at(event.idObject);

		obj->setX(event.x);
		obj->setY(event.y);
		obj->setVx(event.vx);
		obj->setVy(event.vy);
	}
	catch(std::out_of_range &)
	{}
}