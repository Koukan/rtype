#include "Game.hpp"
#include "Server.hpp"
#include "GameTask.hpp"
#include "Server.hpp"
#include "PhysicManager.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"

Game::Game(uint16_t id, uint8_t maxPlayers)
	: Module("Game" + id, 20), _id(id), _maxPlayers(maxPlayers)
{
	Server::get().loadModule(*this);
}

Game::~Game()
{
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
		return true;
	}
	return false;
}

void		Game::removePlayer(Player &player)
{
	for (std::list<Player*>::iterator it = this->_list.begin();
		 it != this->_list.end(); it++)
	{
		if (*it == &player)
		{
			this->_list.erase(it);
			return ;
		}
	}
}

std::list<Player*> const &Game::getPlayers() const
{
	return this->_list;
}

void		Game::sendPacket(std::string const &type,
							 Net::Packet &packet,
							 Player *player)
{
	for (std::list<Player*>::iterator it = this->_list.begin();
		 it != this->_list.end(); it++)
	{
		if (player != *it)
		{
			CommandDispatcher::get().pushCommand(*(
				new PacketCommand(type, **it, packet)));
		}
	}
}
