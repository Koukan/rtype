#include <iostream>
#include "Server.hpp"
#include "Game.hpp"
#include "NetworkModule.hpp"

Server::Server() : Net::PacketHandler<>(4096, "", true),
		_name(""), _game(0)
{
	NetworkModule::get().setServer(this);
}

Server::~Server()
{
}

int			Server::handleInputPacket(Net::Packet &packet)
{
	static bool			(Server::* const methods[])(Net::Packet const&) = {
			NULL,
			&Server::treatEtablishedPacket,
			NULL,
			&Server::treatGamePacket,
			&Server::treatEndListGamePacket,
			NULL,
			&Server::treatPlayerPacket,
			NULL
			/* must be completed */
	};
	uint8_t			type;

	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		return (this->*methods[type])(packet);
	}
	return false;
}

void		Server::setGame(Game &game)
{
	this->_game = &game;
}

bool		Server::treatEtablishedPacket(Net::Packet const &packet)
{
	return true;
}

bool		Server::treatGamePacket(Net::Packet const &packet)
{
	return true;
}

bool		Server::treatEndListGamePacket(Net::Packet const &packet)
{
	return true;
}

bool		Server::treatPlayerPacket(Net::Packet const &packet)
{
	return true;
}