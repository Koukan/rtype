#include "UdpHandler.hpp"
#include "Server.hpp"
#include "Player.hpp"
#include "NetworkModule.hpp"
#include "GameCommand.hpp"
#include "Ship.hpp"

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
	static int			(UdpHandler::* const methods[])(Net::Packet&, Player&) = {
			&UdpHandler::spawn,
			&UdpHandler::destroy,
			&UdpHandler::move,
			&UdpHandler::score,
			&UdpHandler::statement,
			&UdpHandler::retrieve,
	};
	uint64_t			time;
	uint8_t				type;

	packet >> time;
	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		Player *player = NetworkModule::get().getPlayerByAddr(packet.getAddr());
		if (player)
			return (this->*methods[type])(packet, *player);
		else
			return 1;
	}
	return 0;
}

int			UdpHandler::spawn(Net::Packet &packet, Player &player)
{
	uint32_t	id_packet;

	//if (packet.size() < 24)
	//return 0;
	if (player.getShip())
		return 1;
	GameCommand *gc = new GameCommand("spawn");
	packet >> id_packet;
	packet >> gc->idObject;
	packet >> gc->idResource;
	gc->idObject = player.getShip()->getId();
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->player = &player;
	player.getGameLogic().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &packet, Player&)
{
	return 0;
}

int			UdpHandler::move(Net::Packet &packet, Player &player)
{
	//if (packet.size() < 24)
	//return 0;
	if (player.getShip())
		return 1;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	gc->idObject = player.getShip()->getId();
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->player = &player;
	player.getGameLogic().pushCommand(*gc);
	return 1;
}

int			UdpHandler::score(Net::Packet &packet, Player&)
{
	return 0;
}

int			UdpHandler::statement(Net::Packet &packet, Player&)
{
	return 0;
}

int         UdpHandler::retrieve(Net::Packet &packet, Player &player)
{
	uint32_t	packet_id;

	packet >> packet_id;
	Net::Packet const *tmp = player.getPacket(packet_id);
	if (tmp)
		this->handleOutputPacket(*tmp);
	return 1;
}
