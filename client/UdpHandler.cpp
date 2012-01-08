#include "UdpHandler.hpp"
#include "Player.hpp"

UdpHandler::UdpHandler()
{
	this->enableWhitelist(true);
}

UdpHandler::~UdpHandler()
{
}

void		UdpHandler::init()
{
}

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	return 0;
}
