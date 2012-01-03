#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
#include "Server.hpp"

Player::Player() : Net::PacketHandler<>(4096, "\n"),
		_name(""), _game(0)
{
	std::cout << "Client connected" << std::endl;
}

Player::~Player()
{
	std::cout << "Client disconnected" << std::endl;
	if (this->_game)
		this->_game->removePlayer(*this);
}

int			Player::handleInputPacket(Net::Packet &packet)
{
	static void			(Player::* const methods[])(Net::Packet&) = {
			&Player::connection,
			&Player::etablished,
			&Player::listGame,
			&Player::game,
			&Player::endGame,
			&Player::connectGame,
			&Player::player,
			&Player::createGame
	};
	uint8_t			type;

	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods))
	{
		(this->*methods[type])(packet);
		return 1;
	}
	return 0;
}

void		Player::setGame(Game &game)
{
	this->_game = &game;
}

void		Player::connection(Net::Packet &packet)
{
	std::string		name;
	Net::Packet		answer(2);

	packet >> name;
	this->_name = name;
	answer << static_cast<uint8_t>(1);
	answer << '\n';
	this->handleOutputPacket(answer);
	std::cout << "Player " << name << " connected" << std::endl;
}

void		Player::etablished(Net::Packet&)
{
}

void		Player::listGame(Net::Packet&)
{
}

void		Player::game(Net::Packet&)
{
}

void		Player::endGame(Net::Packet&)
{
}

void		Player::connectGame(Net::Packet &packet)
{
	uint16_t	id;
	packet << id;
	Game			*game = Server::get().getGame(id);
	if (game)
	{
		if (game->addPlayer(*this))
		{
			return;
		}
		Net::Packet		answer(4);
		packet << static_cast<uint8_t>(14);
		packet << static_cast<uint16_t>(1);
		packet << '\n';
		this->handleOutputPacket(answer);
		return;
	}
	Net::Packet		answer(4);
	packet << static_cast<uint8_t>(14);
	packet << static_cast<uint16_t>(2);
	packet << '\n';
	this->handleOutputPacket(answer);
}

void		Player::player(Net::Packet &)
{
}

void		Player::createGame(Net::Packet &packet)
{
	uint8_t		maxPlayer;
	packet >> maxPlayer;
	Game		*game = Server::get().createGame(maxPlayer);
	if (game)
	{
		game->addPlayer(*this);
		return ;
	}
	Net::Packet		answer(4);
	answer << static_cast<uint8_t>(14);
	answer << static_cast<uint16_t>(3);
	answer << '\n';
	this->handleOutputPacket(answer);
}
