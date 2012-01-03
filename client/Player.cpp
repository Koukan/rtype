#include <iostream>
#include "Player.hpp"
#include "Game.hpp"

Player::Player() : Net::PacketHandler<>(4096, "\n"),
		_name(""), _game(0)
{
	std::cout << "Client connected" << std::endl;
}

Player::~Player()
{
	std::cout << "Client disconnected" << std::endl;
}

int			Player::handleInputPacket(Net::Packet &packet)
{
	static int			(Player::* const methods[])(Net::Packet&) = {
			NULL,
			&Player::etablished,
			NULL,
			&Player::game,
			&Player::endGame,
			NULL,
			&Player::player,
			NULL
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

int		Player::etablished(Net::Packet&)
{
	return 1;
}

int		Player::game(Net::Packet&)
{
	return 1;
}

int		Player::endGame(Net::Packet&)
{
	return 1;
}

int		Player::player(Net::Packet &)
{
	return 1;
}
