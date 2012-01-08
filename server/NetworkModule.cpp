#include "NetworkModule.hpp"
#include "CommandDispatcher.hpp"
#include "PacketCommand.hpp"
#include "PacketType.hpp"
#include "GameCommand.hpp"

NetworkModule::NetworkModule() : Module("NetworkModule", 20), _reactor(0)
{
	CommandDispatcher::get().registerHandler(*this);
}

NetworkModule::~NetworkModule()
{
}

void		NetworkModule::init()
{
	Net::InetAddr		addr(this->_port);

	this->_reactor = new DefaultSyncPolicy;
	this->_acceptor.setup(addr, *this->_reactor);
	this->_udp.setReactor(*this->_reactor);
	if (_udp.setup(addr) != -1)
		this->_udp.init();
}

void		NetworkModule::update(double)
{
	if (this->_reactor)
		this->_reactor->waitForEvent(0);
}

void		NetworkModule::destroy()
{
}

bool		NetworkModule::handleCommand(Command &command)
{
	//if (command.name == "TCPPacket")
	//{
		//PacketCommand &cmd = static_cast<PacketCommand&>(command);
		//cmd.player.handleOutputPacket(cmd.packet);
		//return true;
	//}
	//else if (command.name == "UDPPacket")
	//{
		//PacketCommand &cmd = static_cast<PacketCommand&>(command);
		//Net::InetAddr	addr;
		//cmd.player.getRemoteAddr(addr);
		//cmd.packet.setDestination(addr);
		//this->_udp.handleOutputPacket(cmd.packet);
		//return true;
	//}
	//return false;
	if (command.name == "Spawn")
	{
		GameCommand	&cmd = static_cast<GameCommand&>(command);
		if (cmd.player)
		{
			Net::Packet		packet(29);
			packet << 29 - sizeof(uint32_t);
			packet << static_cast<uint8_t>(UDP::SPAWN);
			packet << cmd.player->getPacketId();
			packet << cmd.idResource;
			packet << cmd.idObject;
			packet << cmd.x;
			packet << cmd.y;
			packet << cmd.vx;
			packet << cmd.vy;
		}
		return true;
	}
	return false;
}

void		NetworkModule::setPort(std::string const &port)
{
	this->_port = port;
}

void		NetworkModule::addUDPPlayer(Player &player)
{
	Net::InetAddr		addr;

	if (player.getRemoteAddr(addr) != -1) 
		this->_udp.addAddr(addr);
}

void		NetworkModule::removeUDPPlayer(Player &player)
{
	Net::InetAddr		addr;

	if (player.getRemoteAddr(addr) != -1)
		this->_udp.removeAddr(addr);
}
