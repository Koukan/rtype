#pragma once

#include "Net.hpp"

class Game;

class Server : public Net::PacketHandler<>
{
  public:
    Server();
    virtual ~Server();
	virtual int		handleInputPacket(Net::Packet &packet);
	void			setGame(Game &game);

  private:
	bool			treatEtablishedPacket(Net::Packet const &packet);
	bool			treatGamePacket(Net::Packet const &packet);
	bool			treatEndListGamePacket(Net::Packet const &packet);
	bool			treatPlayerPacket(Net::Packet const &packet);


	std::string		_name;
	Game			*_game;
};
