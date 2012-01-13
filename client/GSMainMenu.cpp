#include "GSMainMenu.hpp"
#include "GSCreateMenu.hpp"
#include "GSJoinGame.hpp"
#include "GSOptions.hpp"
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
  this->addGroup("background", 1, 50000001, 59999999);
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20, 100, "up arrow", "down arrow");
  layout->setY((768 - layout->getHeight()) / 2);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::createGame, "Create Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::joinGame, "Join Game", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::options, "Options", "buttonFont", *sprite, layout);
  new GUIButton<GSMainMenu>(*this, &GSMainMenu::quitGame, "Quit", "buttonFont", *sprite, layout);

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);
}

void	GSMainMenu::createGame()
{
  GameStateManager::get().loadState<GSCreateMenu>("createGame");
  GameStateManager::get().pushState("createGame");
}

void	GSMainMenu::joinGame()
{
  GameStateManager::get().loadState<GSJoinGame>("joinGame");
  GameStateManager::get().pushState("joinGame");
}

void	GSMainMenu::options()
{
  GameStateManager::get().loadState<GSOptions>("options");
  GameStateManager::get().pushState("options");
}
void	GSMainMenu::quitGame()
{
  	GameStateManager::get().popState();
  	Game::get().quit();
}
