#include <iostream>
#include "GSInGame.hpp"
#include "Input.hpp"
#include "SFMLSpriteProvider.hpp"

GSInGame::GSInGame() : GameState("Game")
{

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
