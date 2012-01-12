#include "GSOptions.hpp"
#include "GSCreateMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"
#include "GSJoinGame.hpp"

GSOptions::GSOptions()
  : GameState("mainMenu")
{
};

GSOptions::~GSOptions()
{
}

void	GSOptions::onStart()
{
  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  GUILayout *layout = new GUIVLayout(1024 / 2, (768 - 100) / 2, 300, 300, 20);
  layout->setY((768 - layout->getHeight()) / 2);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  new GUIButton<GSOptions>(*this, &GSOptions::returnMenu, "Return", "buttonFont", *sprite, layout);

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);
}

void	GSOptions::returnMenu()
{
  GameStateManager::get().popState();
}
