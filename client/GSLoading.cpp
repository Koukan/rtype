#include "GSLoading.hpp"
#include "GSInGame.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "Wall.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "GUIButton.hpp"
#include "GUIList.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"
#include "ScrollingSprite.hpp"
#include "GameStateManager.hpp"

GSLoading::GSLoading() : GameState("Loading")
{
  //AudioManager::get().load("intro", "resource/sound/06-multiplayer-mouse-mania.ogg");
  //AudioManager::get().play("intro", "test", "intro");
  //AudioManager::get().setVolume("intro", "test", 1.0f);
}

GSLoading::~GSLoading()
{}

void	GSLoading::escape(const InputCommand &)
{
  	GameStateManager::get().popState();
  	Game::get().quit();
}

//void	GSLoading::click(const CL_InputEvent &event)
//{
//}

void	GSLoading::update(double )
{
}

void	GSLoading::buttonClick()
{
  std::cout << "youpi" << std::endl;
		//this->setComponentVisibility(false);

}

void	GSLoading::listChoice(std::string const &)
{
		//this->setComponentVisibility(false);
}

bool		GSLoading::handleCommand(Command const &command)
{
  static Method const	methods[] = {
	{"GameBegin", &GSLoading::gameBeginCommand},
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

void	GSLoading::onStart()
{
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));
  this->load("resources/intro.xml");
  this->load("resources/player.xml");

  Sprite *test = this->getSprite("player1");
  test->setX(550);
  test->setY(360);
  this->addGameObject(test, "gui", 20);

  Font *font = this->getFont("buttonFont");
  font->setX(400);
  font->setY(350);
  font->setText("Loading");
  this->addGameObject(font, "gui", 20);
}

void	GSLoading::gameBeginCommand(Command const &)
{
	GameStateManager::get().loadState<GSInGame>("GSInGame");
	GameStateManager::get().changeState("GSInGame");
}