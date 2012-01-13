#include <sstream>
#include "GSCreateMenu.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUITextBox.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "Game.hpp"

GSCreateMenu::GSCreateMenu()
  : GameState("mainMenu")
{
};

GSCreateMenu::~GSCreateMenu()
{
}

void	GSCreateMenu::returnMainMenu()
{
  GameStateManager::get().popState();
}

void	GSCreateMenu::createParty()
{
  std::stringstream ss;

  ss.clear();
  ss << this->_nbPlayers;
  std::cout << this->_nbPlayers << std::endl;
}

void	GSCreateMenu::nbPlayerList(std::string const &nb)
{
  _nbPlayers = nb;
}

void	GSCreateMenu::onStart()
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
  new GUIButton<GSCreateMenu>(*this, &GSCreateMenu::returnMainMenu, "Return to Menu", "buttonFont", *sprite, layout);
  new GUITextBox<GSCreateMenu>(*this, &GSCreateMenu::nbPlayerList, "buttonFont", *sprite, layout);
  GUIList<GSCreateMenu> *guilist = new GUIList<GSCreateMenu>(*this, &GSCreateMenu::nbPlayerList, "buttonFont", *sprite, *sprite, *sprite, layout);
  GUIList<GSCreateMenu> *guilist2 = new GUIList<GSCreateMenu>(*this, &GSCreateMenu::nbPlayerList, "buttonFont", *sprite, *sprite, *sprite, layout);
  guilist->addLabel("1 Player");
  guilist->addLabel("2 Players");
  guilist->addLabel("3 Players");
  guilist->addLabel("4 Players");
  guilist2->addLabel("1");
  guilist2->addLabel("2");
  new GUIButton<GSCreateMenu>(*this, &GSCreateMenu::createParty, "Go", "buttonFont", *sprite, layout);

  // add Scrolling background
  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);
}
