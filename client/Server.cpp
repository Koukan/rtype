#include <iostream>
#include "Server.hpp"
#include "Game.hpp"
#include "NetworkModule.hpp"

Server::Server() : Net::PacketHandler<>(4096, "\n"),
		_name(""), _game(0)
{
	NetworkModule::get().setServer(this);
}

Server::~Server()
{
}

int			Server::handleInputPacket(Net::Packet &packet)
{
	static int			(Server::* const methods[])(Net::Packet&) = {
			&Server::connection,
			NULL,
			&Server::listGame,
			NULL,
			NULL,
			&Server::connectGame,
			&Server::player,
			&Server::createGame
	};
	uint8_t			type;

	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		return (this->*methods[type])(packet);
	}
	return 0;
}

void		Server::setGame(Game &game)
{
	this->_game = &game;
}

int			Server::connection(Net::Packet &packet)
{
	std::string		name;
	Net::Packet		answer(2);

	packet >> name;
	this->_name = name;
	answer << static_cast<uint8_t>(1);
	answer << '\n';
	this->handleOutputPacket(answer);
	std::cout << "Player " << name << " connected" << std::endl;
	return 1;
}

int		Server::listGame(Net::Packet&)
{
	return 1;
}

int		Server::connectGame(Net::Packet &packet)
{
	// uint16_t	id;
	// packet << id;
	// Game			*game = Server::get().getGame(id);
	// if (game)
	// {
	// 	if (game->addPlayer(*this))
	// 	{
	// 		return 1;
	// 	}
	// 	Net::Packet		answer(4);
	// 	packet << static_cast<uint8_t>(14);
	// 	packet << static_cast<uint16_t>(1);
	// 	packet << '\n';
	// 	this->handleOutputPacket(answer);
	// 	return 1;
	// }
	// Net::Packet		answer(4);
	// packet << static_cast<uint8_t>(14);
	// packet << static_cast<uint16_t>(2);
	// packet << '\n';
	// this->handleOutputPacket(answer);
	 return 1;
}

int		Server::player(Net::Packet &)
{
	return 1;
}

int		Server::createGame(Net::Packet &packet)
{
	// uint8_t		maxPlayer;
	// packet >> maxPlayer;
	// Game		*game = Server::get().createGame(maxPlayer);
	// if (game)
	// {
	// 	game->addPlayer(*this);
	// 	return 1;
	// }
	// Net::Packet		answer(4);
	// answer << static_cast<uint8_t>(14);
	// answer << static_cast<uint16_t>(3);
	// answer << '\n';
	// this->handleOutputPacket(answer);
	 return 1;
}
