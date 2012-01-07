#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "PacketType.hpp"

Player::Player() : Net::PacketHandler<>(4096, "", true),
		_name(""), _game(0), _idPacket(0)
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
			&Player::createGame
	};
	uint8_t			type;

	packet >> type;
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

uint32_t	Player::getPacketId()
{
	return this->_idPacket++;
}

void		Player::resetPacketId()
{
	this->_idPacket = 0;
}

void		Player::addPacket(uint32_t id, Net::Packet &packet)
{
	this->_packets.push_back(std::make_pair(id, packet));
	while (this->_packets.size() > 50)
		this->_packets.pop_front();
}

Net::Packet const	&Player::getPacket(uint32_t id) const
{
	for (packetsList::const_iterator it = this->_packets.end();
		 it != this->_packets.begin() && it->first > id; it--)
	{
		if (it->first == id)
			return it->second;
	}
}

int		Player::connection(Net::Packet &packet)
{
	std::string		name;
	Net::Packet		answer(5);

	packet >> name;
	this->_name = name;
	answer << 1;
	answer << static_cast<uint8_t>(TCP::ETABLISHED);
	this->handleOutputPacket(answer);
	std::cout << "Player " << name << " connected" << std::endl;
	return 1;
}

int		Player::listGame(Net::Packet&)
{
	return 1;
}

int		Player::connectGame(Net::Packet &packet)
{
	uint16_t	id;
	packet << id;
	Game			*game = Server::get().getGame(id);
	if (game)
	{
		if (game->addPlayer(*this))
		{
			return 1;
		}
		Net::Packet		answer(7);
		answer << 3;
		answer << static_cast<uint8_t>(TCP::ERROR);
		answer << static_cast<uint16_t>(Error::GAME_FULL);
		this->handleOutputPacket(answer);
		return 1;
	}
	Net::Packet		answer(7);
	answer << 3;
	answer << static_cast<uint8_t>(TCP::ERROR);
	answer << static_cast<uint16_t>(Error::GAME_NOT_EXIST);
	this->handleOutputPacket(answer);
	return 1;
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
	Net::Packet		answer(7);
	answer << 3;
	answer << static_cast<uint8_t>(TCP::ERROR);
	answer << static_cast<uint16_t>(Error::SERVER_FULL);
	this->handleOutputPacket(answer);
	return 1;
}
