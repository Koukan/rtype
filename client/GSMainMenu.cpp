#include "GSMainMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"

GSMainMenu::GSMainMenu()
  : GameState("mainMenu")
{
};

GSMainMenu::~GSMainMenu()
{
}

void	GSMainMenu::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout((1024 - 100) / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setX((1024 - layout->getWidth()) / 2);
  layout->setY((768 - layout->getHeight()) / 2);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::createGame, "Create Game", "buttonFont", sprite, 300, 70, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::joinGame, "Join Game", "buttonFont", sprite, 300, 70, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::quitGame, "Quit", "buttonFont", sprite, 300, 70, layout);

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);
}

void	GSMainMenu::createGame()
{
  
}

void	GSMainMenu::joinGame()
{
}

void	GSMainMenu::quitGame()
{
  	GameStateManager::get().popState();
  	Game::get().quit();
}
