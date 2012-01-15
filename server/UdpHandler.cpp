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
	this->setNonBlocking(true);
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
			&UdpHandler::ping
	};
	uint64_t			time;
	uint8_t				type;

	packet >> time;
	packet >> type;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
	{
		Player *player = NetworkModule::get().getPlayerByAddr(packet.getAddr());
		std::cout << packet.getAddr().getHost() << " " << packet.getAddr().getPort() << std::endl;
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
	if (!player.getShip())
		return 1;
	GameCommand *gc = new GameCommand("spawn");
	packet >> id_packet;
	packet >> gc->idResource;
	packet >> gc->idObject;
	packet >> gc->x;
	std::cout << "IdResource " << gc->idResource  <<  " idobjetc " << gc->idObject << std::endl;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->x += player.getLatency() * gc->vx;
	gc->y += player.getLatency() * gc->vy;
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
	if (!player.getShip())
		return 1;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	gc->idObject = player.getShip()->getId();
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->x += player.getLatency() * gc->vx;
	gc->y += player.getLatency() * gc->vy;
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


int         UdpHandler::ping(Net::Packet &packet, Player &player)
{
	uint8_t			id;
	uint64_t		time_recv;

	packet >> id;
	packet >> time_recv;
	if (id == 1)
		player.setLatency((Net::Clock::getMsSinceEpoch() - time_recv) / 2 + 10);
	else if (id == 2)
	{		
		Net::Packet     pong(10);
		pong << static_cast<uint8_t>(UDP::PING);
		pong << static_cast<uint8_t>(3);
		pong << time_recv;
		pong.setDestination(packet.getAddr());
		this->handleOutputPacket(pong);
	}
	return 1;
}
