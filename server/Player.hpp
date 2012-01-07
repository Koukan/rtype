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
	uint32_t		getPacketId();
	void			resetPacketId();
	void			addPacket(uint32_t id, Net::Packet &packet);
	Net::Packet const	&getPacket(uint32_t id) const;

  private:
	typedef std::list<std::pair<uint32_t, Net::Packet> >	packetsList;

	int			connection(Net::Packet &packet);
	int			listGame(Net::Packet &packet);
	int			connectGame(Net::Packet &packet);
	int			player(Net::Packet &packet);
	int			createGame(Net::Packet &packet);

	std::string		_name;
	Game			*_game;
	uint32_t		_idPacket;
	packetsList		_packets;
};
