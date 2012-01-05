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
};

