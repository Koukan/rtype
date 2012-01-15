#include "UdpHandler.hpp"
#include "Server.hpp"
#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "GameCommand.hpp"

UdpHandler::UdpHandler() : _lastPacketId(static_cast<uint32_t>(-1))
{
	this->enableWhitelist(true);
}

UdpHandler::~UdpHandler()
{
}

void		UdpHandler::init()
{
	this->setNonBlocking(true);
	this->_reactor->registerHandler(*this, *this, Net::Reactor::READ);
}

int			UdpHandler::handleInputPacket(Net::Packet &packet)
{
	static int			(UdpHandler::* const methods[])(Net::Packet&, uint64_t) = {
			&UdpHandler::spawn,
			&UdpHandler::destroy,
			&UdpHandler::move,
			NULL,
			NULL,
			&UdpHandler::retrieve,
	};
	uint64_t			time, timediff;
	uint8_t				type;

	//std::cout << "input udp packet" << std::endl;
	if (packet.size() < 13)
		return 0;
	packet >> time;
	packet >> type;

	timediff = Net::Clock::getMsSinceEpoch() - time;
	std::cout << "packet udp time :"  << timediff << " type " << (int)type << std::endl;
	if (type < sizeof(methods) / sizeof(*methods) && methods[type] != NULL)
		return (this->*methods[type])(packet, 0);
	return 0;
}

int			UdpHandler::spawn(Net::Packet &packet, uint64_t timediff)
{
	uint32_t	id_packet;

	if (packet.size() != 29)
		return 0;
	packet >> id_packet;
	if (!this->testPacketId(id_packet))
		return 1;
	GameCommand *gc = new GameCommand("spawn");
	packet >> gc->idResource;
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->x += timediff * gc->vx;
	gc->y += timediff * gc->vy;

	//std::cout << "spawn de type " << gc->idResource << " x:" << gc->x << " y:" << gc->y << " vx:" << gc->vx << " vy:" << gc->vy << std::endl;
	std::cout << "Resource = " << gc->idResource << " Id = " << gc->idObject << std::endl;
	CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::destroy(Net::Packet &packet, uint64_t)
{
	uint32_t	id_packet;

	packet >> id_packet;
	if (!this->testPacketId(id_packet))
		return 1;
	GameCommand *gc = new GameCommand("destroy");
	packet >> gc->idObject;
	CommandDispatcher::get().pushCommand(*gc);	
	return 1;
}

int			UdpHandler::move(Net::Packet &packet, uint64_t timediff)
{
	//if (packet.size() < 24)
	//return 0;
	if (timediff > 100)
		return 1;
	GameCommand *gc = new GameCommand("move");
	packet >> gc->idObject;
	packet >> gc->x;
	packet >> gc->y;
	packet >> gc->vx;
	packet >> gc->vy;
	gc->x += timediff * gc->vx;
	gc->y += timediff * gc->vy;
	CommandDispatcher::get().pushCommand(*gc);
	return 1;
}

int			UdpHandler::score(Net::Packet &packet, uint64_t)
{
	return 1;
}

int			UdpHandler::statement(Net::Packet &packet, uint64_t)
{
	return 1;
}

int         UdpHandler::retrieve(Net::Packet &packet, uint64_t)
{
/*	uint32_t	packet_id;

	packet >> packet_id;
	Net::Packet const *tmp = player.getPacket(packet_id);
	if (tmp)
		this->handleOutputPacket(*tmp);*/
	return 1;
}


bool		UdpHandler::testPacketId(uint32_t id)
{
	if (_lastPacketId == static_cast<uint32_t>(-1) || id > _lastPacketId)
	{
		uint32_t	val = id - _lastPacketId;
		if (val == 1)
		{
		  _lastPacketId = id;
		  return true;
		}
		GameCommand *gc;
		for (; val > 1; --val)
		{
			gc = new GameCommand("retrieve");
			gc->idObject = val + _lastPacketId;
			CommandDispatcher::get().pushCommand(*gc);
		}
		CommandDispatcher::get().handle(0);

	}
	return false;
}
