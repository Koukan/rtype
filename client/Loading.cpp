#include "Loading.hpp"
#include "Game.hpp"
#include "Bullet.hpp"
#include "Wall.hpp"
#include "SFMLSpriteProvider.hpp"
#include "GUIButton.hpp"
#include "GUIVLayout.hpp"
#include "GUIHLayout.hpp"

Loading::Loading() : GameState("Loading")
{
  //AudioManager::get().load("intro", "resource/sound/06-multiplayer-mouse-mania.ogg");
  //AudioManager::get().play("intro", "test", "intro");
  //AudioManager::get().setVolume("intro", "test", 1.0f);
}

Loading::~Loading()
{}

void	Loading::escape(const InputCommand &)
{
  	GameStateManager::get().popState();
  	Game::get().quit();
}

//void	Loading::click(const CL_InputEvent &event)
//{
//}

void	Loading::update(double time)
{
}

void	Loading::slowTest(const InputCommand &event)
{
	if (event.MouseWheel.Delta < 0)
  {
		  double timeEffect = this->getTimeEffect() - 0.1;
		  this->setTimeEffect("default", (timeEffect < 0) ? 0 : timeEffect);
  }
	else
		this->setTimeEffect("default", this->getTimeEffect() + 0.1);
}

void	Loading::buttonClick()
{
  std::cout << "youpi" << std::endl;
		//this->setComponentVisibility(false);
}

void	Loading::onStart()
{
  this->loadSpriteProvider(*(new SFMLSpriteProvider));
  this->load("resources/intro.xml");
  this->addGroup("ship", 10);
  this->addGroup("shot", 5);
  this->addGroup("walls");
  this->addGroup("poly1", 12);
  this->addGroup("poly2", 11);
  this->addGroup("particle", 20);

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
  this->addGameObject(_bullet, "ship");
  // end bulletml test

  // GUI

  GUILayout *layout = new GUIVLayout(50, 50, 100, 100);
  for (int i = 0; i < 6; ++i)
    {
      GUILayout *layout2 = new GUIHLayout(0, 0, 100, 50, layout);
      new GUIButton<Loading>(*this, &Loading::buttonClick, "test", *(new ButtonSprite("default button", "selected button", "pressed button")), 50, 50, layout2);
      new GUIButton<Loading>(*this, &Loading::buttonClick, "test", *(new ButtonSprite("default button", "selected button", "pressed button")), 50, 50, layout2);
      new GUIButton<Loading>(*this, &Loading::buttonClick, "test", *(new ButtonSprite("default button", "selected button", "pressed button")), 50, 50, layout2);
      new GUIButton<Loading>(*this, &Loading::buttonClick, "test", *(new ButtonSprite("default button", "selected button", "pressed button")), 50, 50, layout2);
    }
  //CL_PushButton *button1 = this->create<CL_PushButton>("button1");
  //button1->set_geometry(CL_Rect(100, 200, 200, 320));
  //this->getGUIComponent<CL_PushButton>("button1")->set_text("Okay!");
  //button1->func_clicked() = CL_Callback_v0(this, &Loading::buttonClick);
  //CL_LineEdit *lineedit =  this->create<CL_LineEdit>("lineedit");
  //lineedit->set_geometry(CL_Rect(100, 100, 200, 120));
  // end GUI

  // Input
  this->getInput().registerInputCallback(InputCommand::KeyReleased, *this, &Loading::escape, (int)Keyboard::Key::Escape);
  this->getInput().registerInputCallback(InputCommand::MouseWheelMoved, *this, &Loading::slowTest);
  //this->registerInputCallback(CL_InputEvent::pressed, *this, &Loading::slowTest, CL_MOUSE_WHEEL_DOWN);
  //this->registerInputCallback(CL_InputEvent::released, *this, &Loading::click, CL_InputDevice::pointer, CL_MOUSE_LEFT);
  // End Input
}
