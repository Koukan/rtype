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
	void			connection(Net::Packet &packet);
	void			etablished(Net::Packet &packet);
	void			listGame(Net::Packet &packet);
	void			game(Net::Packet &packet);
	void			endGame(Net::Packet &packet);
	void			connectGame(Net::Packet &packet);
	void			player(Net::Packet &packet);
	void			createGame(Net::Packet &packet);

	std::string		_name;
	Game			*_game;
};
