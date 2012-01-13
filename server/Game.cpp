#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

Game::Game(uint16_t id, uint8_t maxPlayers)
	: Module("Game" + id, 20), _logic(*this),
	  _id(id), _maxPlayers(maxPlayers)
{
	Server::get().loadModule(*this);
}

Game::~Game()
{
	delete &this->_logic;
}

void		Game::init()
{
}

void		Game::update(double elapsedTime)
{
	Server::get().pushTask(*(new GameTask(*this, elapsedTime)));
}

void		Game::destroy()
{
}

void		Game::updateGameState(double elapsedTime)
{
	PhysicManager::apply(this->_logic, elapsedTime);
	this->_logic.update(elapsedTime);
}

bool		Game::addPlayer(Player &player)
{
	if (this->_list.size() < this->_maxPlayers)
	{
		this->_list.push_back(&player);
		player.setGame(*this);
		player.setId(_logic.getLastAttributedId());
		this->broadcastStatus(player, 1);
		if (this->_list.size() == this->_maxPlayers)
			this->startGame();
		return true;
	}
	return false;
}

void		Game::removePlayer(Player &player)
{
	std::list<Player*>::iterator it = std::find(this->_list.begin(), this->_list.end(), &player);

	if (it != this->_list.end())
		this->_list.erase(it);
}

size_t		Game::nbPlayers() const
{
	return _list.size();
}

bool		Game::isFull() const
{
	return this->nbPlayers() == _maxPlayers;
}

uint16_t	Game::getId() const
{
	return _id;
}

std::list<Player*> const &Game::getPlayers() const
{
	return this->_list;
}

GameLogic	&Game::getGameLogic()
{
  	return _logic;
}

void		Game::broadcastStatus(Player &player, int status)
{
		GameCommand *tmp = new GameCommand("Status");
		tmp->game = this;
		tmp->player = &player;
		tmp->idObject = status;
		CommandDispatcher::get().pushCommand(*tmp);
}

void		Game::startGame()
{
		GameCommand *tmp = new GameCommand("Startgame");
		tmp->game = this;
		CommandDispatcher::get().pushCommand(*tmp);
		_logic.startGame();	
}
