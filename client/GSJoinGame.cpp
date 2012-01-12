#include "GSJoinGame.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

GSJoinGame::GSJoinGame()
  : GameState("mainMenu")
{
};

GSJoinGame::~GSJoinGame()
{
}

void	GSJoinGame::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  this->_layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  this->_layout->setY((768 - this->_layout->getHeight()) / 2);

  this->_sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, this->_layout);

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);

  CommandDispatcher::get().pushCommand(*(new GameCommand("ListGames")));
}

void	GSJoinGame::returnMainMenu()
{
  	GameStateManager::get().popState();
}

bool	GSJoinGame::handleCommand(Command const &)
{
  if (command.name == "listGame")
    {
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie", "buttonFont", *this->_sprite, this->_layout);
    }
  return (false);
}
