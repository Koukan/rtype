#include "UdpHandler.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

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
	static int			(UdpHandler::* const methods[])(Net::Packet&) = {
			&UdpHandler::spawn,
			&UdpHandler::destroy,
			&UdpHandler::move,
			NULL,
			NULL,
			&UdpHandler::retrieve,
	};
	uint64_t			time;
	uint8_t				type;

	packet >> time;
	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
		return (this->*methods[type])(packet);
	return 0;
}

int			UdpHandler::spawn(Net::Packet &packet)
{
	uint32_t	id_packet;

	//if (packet.size() < 24)
	//return 0;
	GameCommand *gc = new GameCommand("spawn");
	packet >> id_packet;
	packet >> gc->idObject;
	packet >> gc->idResource;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &packet)
{
	return 0;
}

int			UdpHandler::move(Net::Packet &packet)
{
	//if (packet.size() < 24)
	//return 0;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::score(Net::Packet &packet)
{
	return 0;
}

int			UdpHandler::statement(Net::Packet &packet)
{
	return 0;
}

int         UdpHandler::retrieve(Net::Packet &packet)
{
/*	uint32_t	packet_id;

	packet >> packet_id;
	Net::Packet const *tmp = player.getPacket(packet_id);
	if (tmp)
		this->handleOutputPacket(*tmp);*/
	return 1;
}
