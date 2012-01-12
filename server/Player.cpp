#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"

Player::Player() : Net::PacketHandler<>(4096, "", true),
		_name(""), _game(0), _idPacket(0), _idShip(0)
{
	NetworkModule::get().addUDPPlayer(*this);
	std::cout << "Client connected" << std::endl;
}

Player::~Player()
{
	NetworkModule::get().addUDPPlayer(*this);
	std::cout << "Client disconnected" << std::endl;
	if (this->_game)
		this->_game->removePlayer(*this);
}

int			Player::handleInputPacket(Net::Packet &packet)
{
	static int			(Player::* const methods[])(Net::Packet&) = {
			&Player::connection,
			NULL,
			&Player::listGame,
			NULL,
			NULL,
			&Player::connectGame,
			&Player::player,
			&Player::createGame,
			NULL,
			&Player::requireResource
	};
	uint8_t			type;

	packet >> type;
	std::cout << "Incoming packet " << int(type) << std::endl;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		return (this->*methods[type])(packet);
	}
	return 0;
}

void		Player::setGame(Game &game)
{
	this->_game = &game;
}

void		Player::setId(uint32_t id)
{
	this->_idShip = id;
}

uint32_t	Player::getId() const
{
	return this->_idShip;
}

std::string const   &Player::getName() const
{
	return _name;
}

uint32_t	Player::getPacketId()
{
	return this->_idPacket++;
}

void		Player::resetPacketId()
{
	this->_idPacket = 0;
}

Ship		*Player::getShip() const
{
	return _ship;
}

void		Player::setShip(Ship *ship)
{
	_ship = ship;
}

void		Player::addPacket(uint32_t id, Net::Packet &packet)
{
	this->_packets.push_back(std::make_pair(id, packet));
	while (this->_packets.size() > 50)
		this->_packets.pop_front();
}

Net::Packet const	*Player::getPacket(uint32_t id) const
{
	for (packetsList::const_iterator it = this->_packets.end();
		 it != this->_packets.begin() && it->first > id; it--)
	{
		if (it->first == id)
			return &(it->second);
	}
	return 0;
}

int		Player::connection(Net::Packet &packet)
{
	Net::Packet		answer(5);

	std::cout << "connection packet" << std::endl;
	packet >> _name;
	answer << static_cast<uint16_t>(sizeof(uint8_t));
	answer << static_cast<uint8_t>(TCP::ETABLISHED);
	this->handleOutputPacket(answer);
	std::cout << "Player " << _name << " connected" << std::endl;
	return 1;
}

int		Player::listGame(Net::Packet&)
{	
	GameManager::gamesMap const &map = Server::get().getGameList();

	for (GameManager::gamesMap::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		Net::Packet		tmp(12);

		tmp << static_cast<uint16_t>(sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t));
		tmp << static_cast<uint8_t>(TCP::LIST_GAMES);
		tmp << static_cast<uint16_t>(it->second->getId());
		tmp << static_cast<uint8_t>(it->second->nbPlayers());
		tmp << static_cast<uint8_t>(it->second->isFull());
		this->handleOutputPacket(tmp);
	}
	Net::Packet		end(3);
	end << static_cast<uint16_t>(sizeof(uint8_t));
	end << static_cast<uint8_t>(TCP::END_LIST_GAME);
	this->handleOutputPacket(end);
	return 1;
}

int		Player::connectGame(Net::Packet &packet)
{
	uint16_t	id;
	packet >> id;
	Game			*game = Server::get().getGame(id);

	if (game)
	{
		if (game->addPlayer(*this))
		{
			return 1;
		}
		return this->sendError(Error::GAME_FULL);
	}
	return this->sendError(Error::GAME_NOT_EXIST);
}

int		Player::player(Net::Packet &)
{
	return 1;
}

int		Player::createGame(Net::Packet &packet)
{
	uint8_t		maxPlayer;
	packet >> maxPlayer;
	Game		*game = Server::get().createGame(maxPlayer);
	if (game)
	{
		game->addPlayer(*this);
		return 1;
	}
	return this->sendError(Error::SERVER_FULL);
}

int		Player::requireResource(Net::Packet &packet)
{
	return 1;
}

GameLogic           &Player::getGameLogic()
{
	return _game->getGameLogic();
}

int         		Player::sendError(Error::Type error)
{	
	Net::Packet		answer(7);

	answer << static_cast<uint16_t>((sizeof(uint8_t) + sizeof(uint16_t)));
	answer << static_cast<uint8_t>(TCP::TCP_ERROR);
	answer << static_cast<uint16_t>(error);
	this->handleOutputPacket(answer);
	return 1;
}
