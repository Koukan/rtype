#pragma once

#include "Net.hpp"

class UdpHandler : public Net::UdpPacketHandler
{
public:
	UdpHandler();
	virtual ~UdpHandler();

	virtual void	init();
	virtual int 	handleInputPacket(Net::Packet &packet);

private:	
	int			spawn(Net::Packet &packet);
	int			destroy(Net::Packet &packet);
	int			move(Net::Packet &packet);
	int			score(Net::Packet &packet);
	int			statement(Net::Packet &packet);
	int         retrieve(Net::Packet &packet);

	bool		testPacketId(uint32_t id);

	uint32_t	_lastPacketId;
};

