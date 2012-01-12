#include <iostream>
#include "Server.hpp"
#include "Game.hpp"
#include "PacketType.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameListCommand.hpp"

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
	static bool			(Server::* const methods[])(Net::Packet &) = {
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

// Generer command comme gamecommand et la push dans commandDispatcher

bool		Server::treatEtablishedPacket(Net::Packet &packet)
{
	return true;
}

#include <iostream>
bool		Server::treatGamePacket(Net::Packet &packet)
{
	uint16_t	idGame;
	uint8_t		nbPlayers;
	uint8_t		state;

	packet >> idGame;
	packet >> nbPlayers;
	packet >> state;

	std::cout << "receive game" << std::endl;
	CommandDispatcher::get().pushCommand(*(new GameListCommand("listGame", idGame, nbPlayers, state)));
	return true;
}

bool		Server::treatEndListGamePacket(Net::Packet &packet)
{
	return true;
}

bool		Server::treatPlayerPacket(Net::Packet &packet)
{
	uint16_t	status;
	std::string name;
	uint8_t		idPlayer;

	packet >> status;
	packet >> idPlayer;

	return true;
}
