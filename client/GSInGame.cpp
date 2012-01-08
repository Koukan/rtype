#include <iostream>
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
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::moveUp, static_cast<int>(Keyboard::Up));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::moveDown, static_cast<int>(Keyboard::Down));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::moveLeft, static_cast<int>(Keyboard::Left));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::moveRight, static_cast<int>(Keyboard::Right));
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
	{"moveUp", &GSInGame::moveUp},
        {"moveDown", &GSInGame::moveDown},
        {"moveLeft", &GSInGame::moveLeft},
        {"moveRight", &GSInGame::moveRight}
  };

  return (true);
}

void		GSInGame::moveUp(InputCommand const &event)
{
	std::cout << "Up is pressed !" << std::endl;
}

void		GSInGame::moveDown(InputCommand const &event)
{
	std::cout << "Down is pressed !" << std::endl;
}

void		GSInGame::moveLeft(InputCommand const &event)
{
	std::cout << "Left is pressed !" << std::endl;
}

void		GSInGame::moveRight(InputCommand const &event)
{
	std::cout << "Right is pressed !" << std::endl;
}

void		GSInGame::spawn()
{

}
