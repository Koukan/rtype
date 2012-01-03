#pragma once

#include "Net.hpp"

class Game;

class Player : public Net::PacketHandler<>
{
  public:
    Player();
    virtual ~Player();
	virtual int		handleInputPacket(Net::Packet &packet);
	void			setGame(Game &game);

  private:
	int			connection(Net::Packet &packet);
	int			listGame(Net::Packet &packet);
	int			connectGame(Net::Packet &packet);
	int			player(Net::Packet &packet);
	int			createGame(Net::Packet &packet);

	std::string		_name;
	Game			*_game;
};
