#include "UdpHandler.hpp"
#include "Server.hpp"
#include "Player.hpp"
#include "NetworkModule.hpp"
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

int			UdpHandler::spawn(Net::Packet &packet, Player&)
{
return 0;
}

int			UdpHandler::destroy(Net::Packet &packet, Player&)
{
return 0;
}

int			UdpHandler::move(Net::Packet &packet, Player &player)
{
	uint32_t	id_object;
	int16_t		x;
	int16_t		y;
	int16_t		Vx;
	int16_t		Vy;

	//if (packet.size() < 24)
	//return 0;
	packet >> id_object;
	packet >> x;
	packet >> y;
	packet >> Vx;
	packet >> Vy;
	GameCommand *gc = new GameCommand("move");
	gc->idObject = player.getId();
	gc->x = x;
	gc->y = y;
	gc->vx = Vx;
	gc->vy = Vy;
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

int         UdpHandler::retrieve(Net::Packet &packet, Player&)
{
	return 0;
}
