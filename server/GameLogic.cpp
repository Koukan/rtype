#include <iostream>
#include "Game.hpp"
#include "GameLogic.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "CircleHitBox.hpp"
#include "CommandDispatcher.hpp"
#include "ServerResourceManager.hpp"
#include "BCommand.hpp"

GameLogic::GameLogic(Game &game)
	: GameState("GameLogic"), _game(game), _nbEnemies(0), _elapseTime(0), _gameStarted(false)
{
}

GameLogic::~GameLogic()
{
}

#include <iostream>
void		GameLogic::onStart()
{
	addBulletParser("resources/BulletSimple.xml", "single");
	addBulletParser("resources/BulletSinusoidal.xml", "star");
	std::cout << "j ai load, youpi" << std::endl;
	this->addGroup("Wall", 0);
	this->addGroup("playerfires", 0);

  this->addGameObject(new PhysicObject(*new RectHitBox(2000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new PhysicObject(*new RectHitBox(-1000, -2000, 1000, 8000)), "Wall");
  this->addGameObject(new PhysicObject(*new RectHitBox(-1000, -2000, 8000, 1000)), "Wall");
  this->addGameObject(new PhysicObject(*new RectHitBox(-1000, 1000, 8000, 1000)), "Wall");
}

void		GameLogic::update(double elapseTime)
{
	this->handle(elapseTime);
	if (_gameStarted)
	{
		std::cout << "je vais creer des ennemis =D" << std::endl;
	//	this->createEnnemies(elapseTime);
	}
}
// loadBullet -> serverresourcemanager::get().addBulletParser(nom de fichier, id_ref) creer un BCommand(id_ref, *this, ...)
// modifier BCommand pour id_resource en fonction du sprite

bool		GameLogic::handleCommand(Command const &command)
{
	GameCommand	const &gc = static_cast<GameCommand const &>(command);
	if (gc.name == "move")
	{
		Ship	*ship = gc.player->getShip();
		ship->setX(gc.x);
		ship->setY(gc.y);
		ship->setVx(gc.vx);
		ship->setVy(gc.vy);
		GameCommand *answer = new GameCommand("Move");
		answer->idObject = gc.player->getShip()->getId();
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->player = gc.player;
		CommandDispatcher::get().pushCommand(*answer);
		return true;
	}
	else if (gc.name == "spawn")
	{
		std::cout << "spawn plop" << std::endl;
		CircleHitBox	*hitbox = new CircleHitBox(gc.x, gc.y, 5);
		Bullet			*bullet = new Bullet(*hitbox, gc.vx, gc.vy);
		bullet->setId(gc.idObject);
		this->addGameObject(bullet, "playerfires", 9);
		GameCommand *answer = new GameCommand("Spawn");
		answer->idResource = gc.idResource;
		answer->idObject = gc.idObject;
		answer->x = gc.x;
		answer->y = gc.y;
		answer->vx = gc.vx;
		answer->vy = gc.vy;
		answer->game = &_game;
		answer->player = gc.player;
		CommandDispatcher::get().pushCommand(*answer);
		return true;
	}
	return false;
}

Game		&GameLogic::getGame() const
{
	return this->_game;
}

void		GameLogic::startGame()
{
	double	y = 0;
	double	step = 720 / this->_game._list.size();

	for (std::list<Player*>::iterator it = this->_game._list.begin(); it != this->_game._list.end(); ++it)
	{
		Ship *tmp = new Ship(10, y, *it);
	    (*it)->setShip(tmp);
		this->addGameObject(tmp, "players", 10);
		GameCommand	*cmd = new GameCommand("Spawn");
		cmd->idResource = (*it)->getId();
		cmd->idObject = tmp->getId();
		cmd->x = tmp->getX();
		cmd->y = tmp->getY();
		cmd->vx = tmp->getVx();
		cmd->vy = tmp->getVy();
		cmd->game = &_game;
		std::cout << "Id " << (*it)->getId() << " Id Object " << cmd->idObject << std::endl;
		CommandDispatcher::get().pushCommand(*cmd);
		y += step;
	}
	this->_gameStarted = true;
}

void GameLogic::createEnnemies(double elapseTime)
{
	static Salvo const salvos[] = {
		{SINGLE, 1, "single", 50}
	};

	int const salvoFrequency = 1000;
	static int i = 0;
	static int y = 0;

	if (this->_elapseTime == 0)
	{
		if (this->_nbEnemies == 0)
		{
			i = rand() % (sizeof(salvos) / sizeof(*salvos));
			y = rand() % 768;
			this->_nbEnemies = salvos[i].nbEnemies;
			this->_elapseTime = salvoFrequency;
		}
		else
		{
			this->addGameObject(new BCommand(salvos[i].bulletName, *this, 1050, y, 0, 0));
			this->_elapseTime += salvos[i].occurenceFrequency;
			--this->_nbEnemies;
		}
	}
	else
	{
		if (this->_elapseTime - elapseTime < 0)
			this->_elapseTime = 0;
		else
			this->_elapseTime -= elapseTime;
	}
}
