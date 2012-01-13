#include <iostream>
#include "RectHitBox.hpp"
#include "GSInGame.hpp"
#include "GSPauseMenu.hpp"
#include "Input.hpp"
#include "Monster.hpp"
#include "CommandDispatcher.hpp"
#include "SFMLSpriteProvider.hpp"
#include "SFMLFontProvider.hpp"
#include "ScrollingSprite.hpp"


GSInGame::GSInGame() : GameState("Game"), _idPlayer(0), _scores(4, 0)
{
  //CommandDispatcher::get().registerHandler(*this);
	
}

GSInGame::~GSInGame()
{}

void		GSInGame::onStart()
{
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputEscape, static_cast<int>(Keyboard::Escape));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputUp, static_cast<int>(Keyboard::Up));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputDown, static_cast<int>(Keyboard::Down));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputLeft, static_cast<int>(Keyboard::Left));
  this->getInput().registerInputCallback(InputCommand::KeyPressed, *this, &GSInGame::inputRight, static_cast<int>(Keyboard::Right));

  // add providers
  this->addProvider(*(new SFMLSpriteProvider));
  this->addProvider(*(new SFMLFontProvider));

  // load xml
  this->load("resources/intro.xml");

  // add gui

  Font *fontp1 = this->getFont("buttonFont");
  fontp1->setText("Player 1");
  fontp1->setPosition(20, 0);
  this->addGameObject(fontp1, "score", 20);
  Font *fontp2 = this->getFont("buttonFont");
  fontp2->setText("Player 2");
  fontp2->setPosition(700, 0);
  this->addGameObject(fontp2, "score", 20);
  Font *fontp3 = this->getFont("buttonFont");
  fontp3->setText("Player 3");
  fontp3->setPosition(20, 700);
  this->addGameObject(fontp3, "score", 20);
  Font *fontp4 = this->getFont("buttonFont");
  fontp4->setText("Player 4");
  fontp4->setPosition(700, 700);
  this->addGameObject(fontp4, "score", 20);

  ScrollingSprite *obj = new ScrollingSprite(0, 0, 1024, 768, ScrollingSprite::HORIZONTAL, -0.05);
  obj->pushSprite("space background");
  this->addGameObject(obj, "background", 1);

}

void		GSInGame::update(double elapsedTime)
{
}

void		GSInGame::onEnd()
{}

bool		GSInGame::handleCommand(Command const &command)
{
  static Method const	methods[] = {
	{"destroy", &GSInGame::destroy},
	{"life", &GSInGame::life},
	{"score", &GSInGame::score},
	{"spawn", &GSInGame::spawn},
	{"move", &GSInGame::move}
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

void		GSInGame::inputUp(InputCommand const &event)
{
	this->moveObject(event, 0, 0, -1, 0);
}

void		GSInGame::inputDown(InputCommand const &event)
{
	this->moveObject(event, 0, 0, 1, 0);
}

void		GSInGame::inputLeft(InputCommand const &event)
{
	this->moveObject(event, 0, 0, -1, 0);
}

void		GSInGame::inputRight(InputCommand const &event)
{
	this->moveObject(event, 0, 0, 1, 0);
}

void		GSInGame::inputEscape(InputCommand const &event)
{
  GameStateManager::get().pushState(*(new GSPauseMenu()), GameState::ALL);
}

void		GSInGame::moveObject(InputCommand const &event, int16_t x, int16_t y, int16_t vx, int16_t vy)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(_idPlayer));

	if (obj)
	{
		GameCommand *cmd = new GameCommand("Move");
		cmd->x = static_cast<int16_t>(obj->getX() + x);
		cmd->y = static_cast<int16_t>(obj->getY() + y);
		cmd->vx = static_cast<int16_t>(obj->getVx() + vx);
		cmd->vy = static_cast<int16_t>(obj->getVy() + vy);
		this->updatePositions(*cmd, *obj);
		CommandDispatcher::get().pushCommand(*cmd); //send to network
	}
}

void		GSInGame::spawn(GameCommand const &event)
{
	HitBox *hitbox = new RectHitBox(event.x, event.y, 2, 2);
	Monster *monster1 = new Monster(this->getSprite("monster"), *hitbox, event.vx, event.vy);
	this->addGameObject(static_cast<GameObject *>(monster1), "monsterGroup");
}

void		GSInGame::destroy(GameCommand const &event)
{
	delete (this->getGameObject(event.idObject));
}

void		GSInGame::life(GameCommand const &event)
{
	//actions
}

void		GSInGame::score(GameCommand const &event)
{
	if (event.idObject < 4)
	{
		_scores[event.idObject] = event.score;

	}
}

void		GSInGame::move(GameCommand const &event)
{
	PhysicObject *obj = static_cast<PhysicObject *>(this->getGameObject(event.idObject));

	if (obj)
		this->updatePositions(event, *obj);
}

void		GSInGame::updatePositions(GameCommand const &event, PhysicObject &obj) const
{
	obj.setX(event.x);
	obj.setY(event.y);
	obj.setVx(event.vx);
	obj.setVy(event.vy);
}
