#include "GSLoading.hpp"
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

void	GSLoading::update(double time)
{
}

void	GSLoading::slowTest(const InputCommand &event)
{
	if (event.MouseWheel.Delta < 0)
  {
		  double timeEffect = this->getTimeEffect() - 0.1;
		  this->setTimeEffect("default", (timeEffect < 0) ? 0 : timeEffect);
  }
	else
		this->setTimeEffect("default", this->getTimeEffect() + 0.1);
}

void	GSLoading::buttonClick()
{
  std::cout << "youpi" << std::endl;
		//this->setComponentVisibility(false);

}

void	GSLoading::listChoice(std::string const &name)
{
		//this->setComponentVisibility(false);
}

void	GSLoading::onStart()
{
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));
  this->load("resources/intro.xml");
  this->load("resources/player.xml");
  this->addGroup("ship", 10);
  this->addGroup("shot", 5);
  this->addGroup("walls");
  this->addGroup("poly1", 12);
  this->addGroup("poly2", 11);
  this->addGroup("particle", 20);

  Sprite *test = this->getSprite("player1");
  test->setX(250);
  test->setY(600);
  this->addGameObject(test, "player", 20);

  double x = -50, y = -50, width = 1100, height = 820, wallWidth = 500;
  new Wall(-wallWidth + x, -wallWidth + y, width + 2 * wallWidth, wallWidth, "walls");
  new Wall(-wallWidth + x, y + height, width + 2 * wallWidth, wallWidth, "walls");
  new Wall(-wallWidth + x, y, wallWidth, height, "walls");
  new Wall(x + width, y, wallWidth, height, "walls");

  this->setCollisionGroups("walls", "shot", &Wall::collideBullet);
  this->setCollisionGroups("walls", "ship", &Wall::collideBullet);

  /////////////////////////////

  // bulletml test
  this->addBulletParser("resources/test.xml", "Test");
  _bullet = new BulletCommand("Test", *this, 512, 360);
  this->addGameObject(_bullet, "ship", 1);
  // end bulletml test

  // GUI

  GUILayout *layout = new GUIVLayout(50, 50, 100, 100, 0);
  ButtonSprite *sprite = new ButtonSprite("default button", "selected button", "pressed button");
  GUIList<GSLoading> *guilist = new GUIList<GSLoading>(*this, &GSLoading::listChoice, "buttonFont", *sprite, *sprite, *sprite, layout);
  guilist->addLabel("un");
  guilist->addLabel("deux");
  guilist->addLabel("trois");
  new GUIButton<GSLoading>(*this, &GSLoading::buttonClick, "test 1", "font test", *sprite, layout);
  new GUIButton<GSLoading>(*this, &GSLoading::buttonClick, "test 2", "font test", *sprite, layout);
  new GUIButton<GSLoading>(*this, &GSLoading::buttonClick, "test 3", "font test", *sprite, layout);
  new GUIButton<GSLoading>(*this, &GSLoading::buttonClick, "test 4", "font test", *sprite, layout);
  new GUIButton<GSLoading>(*this, &GSLoading::buttonClick, "test 5", "font test", *sprite, layout);

  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");

  this->addGameObject(obj, "background", 1);

  // end GUI

  // Input
  this->getInput().registerInputCallback(InputCommand::KeyReleased, *this, &GSLoading::escape, (int)Keyboard::Escape);
  this->getInput().registerInputCallback(InputCommand::MouseWheelMoved, *this, &GSLoading::slowTest);
//  this->registerInputCallback(CL_InputEvent::pressed, *this, &GSLoading::slowTest, CL_MOUSE_WHEEL_DOWN);
 // this->registerInputCallback(CL_InputEvent::released, *this, &GSLoading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);
  // End Input
}
