#include "GSJoinGame.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "GUILabel.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "GameListCommand.hpp"
#include "NetworkModule.hpp"
#include "Converter.hpp"

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

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);

  this->_sprite = new ButtonSprite("default button", "selected button", "pressed button");
  if (NetworkModule::get().connect())
    {
      CommandDispatcher::get().pushCommand(*(new GameListCommand("Connection", "TEST")));
      CommandDispatcher::get().pushCommand(*(new GameCommand("ListGames")));
      
      GUILayout *layout = new GUIHLayout(300, 768 / 2, 0, 0, 0);
      this->_layout = new GUIVLayout(0, 0, 300, 700, 20, layout, 8, "up arrow", "down arrow");
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, layout);
      
      // tests
      
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 1", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 2", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 3", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 4", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 5", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 6", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 7", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 8", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 9", "buttonFont", *this->_sprite, this->_layout);
      // new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Partie 10", "buttonFont", *this->_sprite, this->_layout);
    }
  else
    {
      this->_layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 700, 50);
      new GUILabel("Connection failed", "buttonFont", "", this->_layout);
      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, "Return", "buttonFont", *this->_sprite, this->_layout);
    }
}

void	GSJoinGame::returnMainMenu()
{
  	GameStateManager::get().popState();
}

bool	GSJoinGame::handleCommand(Command const &command)
{
  if (command.name == "listGame")
    {
      GameListCommand const &cmd = static_cast<GameListCommand const &>(command);
      std::string id = Net::Converter::toString(cmd.idGame);
      std::string nbPlayers = Net::Converter::toString(cmd.nbPlayers);
      std::string state = Net::Converter::toString(cmd.state);

      new GUIButton<GSJoinGame>(*this, &GSJoinGame::returnMainMenu, id + " | Players " + state + "/" + nbPlayers, "buttonFont", *this->_sprite, this->_layout);
      return (true);
    }
  return (false);
}
