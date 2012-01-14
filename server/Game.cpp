#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"
#include "Converter.hpp"

Game::Game(uint16_t id, uint8_t maxPlayers)
	: Module("Game" + id, 20), _logic(*this),
	  _id(id), _maxPlayers(maxPlayers)
{
	Server::get().loadModule(*this);
}

Game::~Game()
{
	Server::get().removeGame(this->_id);
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
		player.setId(this->_list.size());
		this->_list.push_back(&player);
		uint32_t	begin = this->_list.size() * 10000000 + 1000000001;
		uint32_t	end = begin + 9999999;
		std::string	id = "shootPlayer" + Net::Converter::toString(this->_list.size());
		_logic.addGroup(id, 10, begin, end);
		GameCommand	*cmd = new GameCommand("RangeId");
		cmd->idObject = begin;
		cmd->idResource = end;
		cmd->x = this->_list.size() - 1;
		cmd->player = &player;
		CommandDispatcher::get().pushCommand(*cmd);
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
	if (this->_list.empty())
		Server::get().unloadModule("Game" + this->_id);
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

uint8_t          Game::getMaxPlayers() const
{
	return _maxPlayers;
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
